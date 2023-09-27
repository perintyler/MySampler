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

void validateSample(juce::File& sample, juce::String pathToFile)
{
    if (!sample.existsAsFile()) {
        juce::String errorMessage = "wav file does not exist: " + pathToFile;
        throw std::filesystem::filesystem_error(errorMessage.toStdString(), std::error_code());
    } else if (sample.getFileExtension() != ".wav") {
        juce::String errorMessage = "sample is not a wav file: " + pathToFile;
        throw std::filesystem::filesystem_error(errorMessage.toStdString(), std::error_code());
    }
}

// --------------------------------

const Sample& SampleSet::get(Note note) const 
{
    assert(count(note) != 0);
    return at(note);
}

void SampleSet::set(Note key, std::filesystem::path filepath, Note rootNote)
{
    std::string sampleName = filepath.stem().string();
    insert({key, Sample{sampleName, filepath, rootNote}});
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

void RandomSampler::randomize() 
{
    synthesiser.clearSounds();

    for (Note note = firstNote; note <= lastNote; note++) 
    {
        if (!isKeyLocked(note)) 
        {
            juce::File randomSample;
            int rootNoteOfSample;
            juce::String pathToFile;
            juce::WavAudioFormat wavFormat;
            std::unique_ptr<juce::AudioFormatReader> audioReader;
            bool foundValidSample = false;

            while (!foundValidSample) {
                pathToFile = getPathToRandomSample();
                juce::File randomSample(pathToFile);
                validateSample(randomSample, pathToFile);

                audioReader = std::unique_ptr<juce::AudioFormatReader>(
                    wavFormat.createReaderFor(randomSample.createInputStream().release(), true)
                );
                
                juce::AudioSampleBuffer buffer;
                int bufferSize = static_cast<int>(audioReader->lengthInSamples);
                buffer.setSize(audioReader->numChannels, bufferSize);
                audioReader->read(&buffer, 0, bufferSize, 0, true, true);
                
                try {
                    rootNoteOfSample = detectNote(buffer, audioReader->sampleRate);
                    foundValidSample = true;
                } catch (PitchDetectionException) {
                    logs::newBadSample(pathToFile);
                }
            }

            samples.set(note, pathToFile.toStdString(), rootNoteOfSample);

            juce::BigInteger keyRange;
            keyRange.setRange(note, note+1, true);

            synthesiser.addSound(
                juce::SynthesiserSound::Ptr(new juce::SamplerSound(
                    pathToFile, *audioReader, keyRange, rootNoteOfSample, ATTACK, RELEASE, SUSTAIN
                ))
            );
        }
    }
}
