/*** Piano960: samples.cpp ***/

#include <cmath>
#include <string>
#include <random>
#include <assert.h>

#include "samples.h"
#include "logs.h"
#include "paths.h"
#include "config.h"
#include "pitch/pitch.h"

#include <juce_audio_formats/juce_audio_formats.h>

#ifdef SAMPLES_DIRECTORY
  const std::string PATH_TO_SAMPLES_DIRECTORY { SAMPLES_DIRECTORY };
#else
  const std::string PATH_TO_SAMPLES_DIRECTORY { "/usr/local/include/Piano960/samples" };
#endif

static std::random_device randomDevice;
static std::mt19937 numberGenerator(randomDevice()); // Mersenne Twister
static std::uniform_real_distribution<double> uniformDistribution(0.0, 1.0); // unit interval uniform distribution

using SampleReader = std::unique_ptr<juce::AudioFormatReader>;

/** Randomly selects a file from a nested directory of sample-packs
 **  - https://stackoverflow.com/questions/58400066/how-to-quickly-pick-a-random-file-from-a-folder-tree
 */
juce::String getPathToRandomSample()
{
    std::string path;
    int numFilesTraversed = 1;
    std::filesystem::recursive_directory_iterator fileIterator(PATH_TO_SAMPLES_DIRECTORY);
    
    for (const std::filesystem::directory_entry &entry: fileIterator) {
        if (!std::filesystem::is_directory(entry)) {
            if (uniformDistribution(numberGenerator) < (1.0 / numFilesTraversed)) {
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

// --------------------------------

const Sample& SampleSet::get(Note note) const 
{
    assert(count(note) != 0);
    return at(note);
}

int SampleSet::length() const
{
    return static_cast<int>(size());
}

void SampleSet::set(Note key, std::filesystem::path filepath, Note rootNote)
{
    std::string sampleName = filepath.stem().string();
    insert_or_assign(key, Sample{sampleName, filepath, rootNote});
}

std::vector<std::pair<Note, const Sample&>> SampleSet::asVector() const
{
    return std::vector<std::pair<Note, const Sample&>>(begin(), end());
}

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
    SampleSet lockedSamples;

    for (const auto& [note, sample] : samples.asVector()) {
        if (isKeyLocked(note))
            lockedSamples.set(note, sample.filepath, sample.rootNote);
    }

    return lockedSamples;
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
                pathToFile = getPathToRandomSample();
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
