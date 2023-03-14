// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - Piano960 | VST3, AU - - - - - - - - - - - - - - - - - - - -
// - - Created by Tyler Perin  - - - - - - - - - - - - - - - - - -
// - - Copyright © 2022 Sound Voyager. All rights reserved.- - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//   samples.cpp
//   ~~~~~~~~~~~
//
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#include <cmath>
#include <string>
#include <filesystem>
#include <random>

#include "samples.h"
#include "logs.h"
#include "random.h"
#include "pitch/pitch.h"

#ifdef SAMPLES_DIRECTORY
  const std::string PATH_TO_SAMPLES_DIRECTORY { SAMPLES_DIRECTORY };
#else
  const std::string PATH_TO_SAMPLES_DIRECTORY { "/usr/local/include/Piano960/Resources" };
#endif

static std::random_device randomDevice;
static std::mt19937 numberGenerator(randomDevice()); // Mersenne Twister
static std::uniform_real_distribution<double> uniformDistribution(0.0, 1.0); // unit interval uniform distribution

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

    return juce::String { juce::String };
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

/** Generates a random sample from the installed wav files. The sample will be transposed
 ** to match the pitch of the desired MIDI key.
 **/
juce::SamplerSound* getRandomSamplerSound(NoteID note)
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

        juce::AudioSampleBuffer buffer;
        int bufferSize = static_cast<int>(audioReader->lengthInSamples);
        buffer.setSize(audioReader->numChannels, bufferSize);

        audioReader = std::unique_ptr<juce::AudioFormatReader>(
            wavFormat.createReaderFor(randomSample.createInputStream().release(), true)
        );
        audioReader->read(&buffer, 0, bufferSize, 0, true, true);

        try {
            rootNoteOfSample = detectNote(buffer, audioReader->sampleRate);
            foundValidSample = true;
        } catch (FrequencyNotDetectedException) {
            logs::newBadSample(pathToFile);
        }
    }

    juce::BigInteger keyRange;
    keyRange.setRange(note, note+1, true);
    
    return new juce::SamplerSound(
        pathToFile, *audioReader, keyRange, rootNoteOfSample,
        ATTACK, RELEASE, MAX_SAMPLE_LENGTH
    );
}
