/*** MySampler | Source/sampler.cpp ***/

#include <cmath>
#include <string>
#include <random>
#include <algorithm>
#include <assert.h>

#include <juce_audio_formats/juce_audio_formats.h>

#include "logs.h"
#include "paths.h"
#include "config.h"
#include "presets.h"
#include "sound_source.h"
#include "pitch_detection/pitch_detection.h"
#include "sampler.h"

#ifdef SAMPLES_DIRECTORY
  const std::string PATH_TO_SAMPLES_DIRECTORY { SAMPLES_DIRECTORY };
#else
  const std::string PATH_TO_SAMPLES_DIRECTORY { "/usr/local/include/MySampler/samples" };
#endif

// ------------------------------------------------------------------------------------------
namespace { // ------------------ START OF ANONYMOUS NAMESPACE ------------------------------
// ------------------------------------------------------------------------------------------

using SampleReader = std::unique_ptr<juce::AudioFormatReader>;

static std::random_device randomDevice;
static std::mt19937 numberGenerator(randomDevice()); // Mersenne Twister
static std::uniform_real_distribution<double> uniformDistribution(0.0, 1.0); // unit interval uniform distribution

//
// Randomly selects a file from a nested directory of sample-packs
//  - https://stackoverflow.com/questions/58400066/how-to-quickly-pick-a-random-file-from-a-folder-tree
//
juce::String getPathToRandomSample(std::set<SoundSource> categories)
{
    std::string path;
    int numFilesTraversed = 1;
    std::filesystem::recursive_directory_iterator fileIterator(PATH_TO_SAMPLES_DIRECTORY);
    
    for (const std::filesystem::directory_entry &entry: fileIterator) 
    {
        if (!std::filesystem::is_directory(entry)) 
        {
            std::string nameOfParentDirectory = entry.path().parent_path().filename().string();
            SoundSource category = getSoundSource(nameOfParentDirectory);

            if ((categories.find(category) != categories.end())
              && (uniformDistribution(numberGenerator) < (1.0 / numFilesTraversed))
            ) {
                path = entry.path().string();
            }

            numFilesTraversed++;
        }
    }

    return juce::String { path };
}

bool validateSample(juce::File& sample, juce::String pathToFile)
{
    if (!sample.existsAsFile()) {
        std::cerr << "wav file does not exist: " << pathToFile.toStdString() << std::endl;
        return false;
    } else if (sample.getFileExtension() != ".wav") {
        std::cerr << "sample is not a wav file: " << pathToFile.toStdString() << std::endl;
        return false;
    }

    return true;
}

// --------------------------------------------------------------------------------------
} // ---------------------------- END OF ANONYMOUS NAMESPACE ----------------------------
// --------------------------------------------------------------------------------------

RandomSampler::RandomSampler(Note firstNote, Note lastNote)
    : synthesiser()
    , firstNote(firstNote)
    , lastNote(lastNote)
{
    for (int midiNumber = FIRST_MIDI_NOTE; midiNumber <= LAST_MIDI_NOTE; midiNumber++)
        lockedKeys[midiNumber] = false;

    for (auto i = 0; i < NUM_SYNTH_VOICES; ++i)
        synthesiser.addVoice(new juce::SamplerVoice());
}

RandomSampler::RandomSampler() 
    : RandomSampler(FIRST_MIDI_NOTE, LAST_MIDI_NOTE)
{}

const Sample& RandomSampler::getSample(Note note) const
{
    return samples.get(note);
}

bool RandomSampler::isKeyLocked(Note note) const
{
    jassert(lockedKeys.count(note));
    return lockedKeys.at(note) == true;
}

void RandomSampler::lockKey(Note note)
{
    jassert(lockedKeys.count(note));
    lockedKeys[note] = true;
}

void RandomSampler::unlockKey(Note note)
{
    jassert(lockedKeys.count(note));
    lockedKeys[note] = false;
}

bool RandomSampler::isReady() const
{
    return samples.length() == (lastNote - firstNote);
}

const SampleSet& RandomSampler::getAllSamples() const
{ 
    return samples; 
}

const SampleSet RandomSampler::getLockedSamples() const
{
    return samples.filter([this](Note note, const Sample&) {
        return isKeyLocked(note);
    });
}

void RandomSampler::setSamples(const SampleSet& newSamples)
{
    samples.clear();

    for (const auto& [note, sample] : newSamples) {
        samples.set(note, sample.filepath, sample.rootNote);
    }
}

void RandomSampler::randomize(bool pitch_shift /* = true */) 
{
    synthesiser.clearSounds();

    for (Note note = firstNote; note <= lastNote; note++) 
    {
        if (!isKeyLocked(note)) 
        {
            juce::File randomSample;
            int rootNoteOfSample;
            juce::String pathToFile;
            std::string sampleName;
            juce::WavAudioFormat wavFormat;
            std::unique_ptr<juce::AudioFormatReader> audioReader;
            bool foundValidSample = false;

            while (!foundValidSample) {
                pathToFile = getPathToRandomSample(getAllCategories());
                sampleName = pathToFile.toStdString();
                juce::File randomSample(pathToFile);
                
                if (!validateSample(randomSample, pathToFile)) {
                    logs::newBadSample(pathToFile);
                    continue;
                }

                audioReader = std::unique_ptr<juce::AudioFormatReader>(
                    wavFormat.createReaderFor(randomSample.createInputStream().release(), true)
                );
                
                juce::AudioSampleBuffer buffer;
                int bufferSize = static_cast<int>(audioReader->lengthInSamples);
                buffer.setSize(audioReader->numChannels, bufferSize);
                audioReader->read(&buffer, 0, bufferSize, 0, true, true);
                
                if (pitch_shift) {
                    try {
                        rootNoteOfSample = detectNote(buffer, audioReader->sampleRate, sampleName);
                        foundValidSample = true;
                    } catch (PitchDetectionException) {
                        logs::newBadSample(pathToFile);
                    }
                } else {
                    foundValidSample = true;
                }
            }

            samples.set(note, sampleName, rootNoteOfSample);

            juce::BigInteger keyRange;
            keyRange.setRange(note, note+1, true);

            synthesiser.addSound(std::move(
                juce::SynthesiserSound::Ptr(new juce::SamplerSound(
                    pathToFile, *audioReader, keyRange, rootNoteOfSample, ATTACK, RELEASE, SUSTAIN
                ))
            ));
        }
    }
}
