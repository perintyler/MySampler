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

#include "samples.h"
#include "logs.h"
#include "random.h"
#include "pitch/pitch.h"

#ifdef SAMPLES_DIRECTORY
  const std::string PATH_TO_SAMPLES_DIRECTORY { SAMPLES_DIRECTORY };
#else
  const std::string PATH_TO_SAMPLES_DIRECTORY { "/usr/local/include/Piano960/Resources" };
#endif

std::unique_ptr<juce::AudioFormatReader> createWAVReader(juce::File& wavFile)
{
    juce::WavAudioFormat wavFormat;

    if (!wavFile.existsAsFile()) {
        juce::String errorMessage = "wav file does not exist: " + wavFile.getFullPathName();
        throw std::filesystem::filesystem_error(errorMessage.toStdString(), std::error_code());
    } else if (wavFile.getFileExtension() != ".wav") {
        juce::String errorMessage = "sample is not a wav file: " + wavFile.getFullPathName();
        throw std::filesystem::filesystem_error(errorMessage.toStdString(), std::error_code());
    }

    return std::unique_ptr<juce::AudioFormatReader>(
        wavFormat.createReaderFor(wavFile.createInputStream().release(), true)
    );
}

juce::AudioSampleBuffer createAudioBuffer(std::unique_ptr<juce::AudioFormatReader>& audioReader, int bufferSize)
{
    juce::AudioSampleBuffer buffer;
    bufferSize = std::min(bufferSize, (int) audioReader->lengthInSamples);
    buffer.setSize(audioReader->numChannels, bufferSize);
    audioReader->read(&buffer, 0, bufferSize, 0, true, true);
    return buffer;
}

/** Generates a random sample from the installed wav files. The sample will be transposed
 ** to match the pitch of the desired MIDI key.
 **/
juce::SamplerSound* getRandomSamplerSound(NoteID note)
{
    juce::File randomSample;
    int rootNoteOfSample;
    std::unique_ptr<juce::AudioFormatReader> audioReader;
    juce::String pathToFile;

    while (audioReader == nullptr) 
    {
        pathToFile = juce::String { getPathToRandomFile(PATH_TO_SAMPLES_DIRECTORY) };
        juce::File randomSample(pathToFile);
        audioReader = createWAVReader(randomSample);
        int bufferSize = static_cast<int>(audioReader->lengthInSamples);
        juce::AudioSampleBuffer buffer = createAudioBuffer(audioReader, bufferSize);
        
        try {
            rootNoteOfSample = detectNote(buffer, audioReader->sampleRate);
        } 
        catch (FrequencyNotDetectedException) {
            logs::newBadSample(pathToFile);
        }
    }

    juce::BigInteger keyRange;
    keyRange.setRange(note, note+1, true);
    
    return new juce::SamplerSound(
        pathToFile, *audioReader,
        keyRange, rootNoteOfSample,
        ATTACK, RELEASE, MAX_SAMPLE_LENGTH
    );
}
