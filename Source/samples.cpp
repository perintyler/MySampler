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

#ifndef SAMPLES_DIRECTORY
    #define SAMPLES_DIRECTORY "/usr/local/include/Piano960/samples/"
#endif

juce::File getRandomSample()
{
    return juce::File { getPathToRandomFile(SAMPLES_DIRECTORY) };
}

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
    buffer.clear(); // Why again?
    bufferSize = std::min(bufferSize, (int) audioReader->lengthInSamples);
    buffer.setSize(audioReader->numChannels, bufferSize);
    audioReader->read(&buffer, 0, bufferSize, 0, true, true);
    return buffer;
}

/* TODO: this needs a docstring
 */
juce::SamplerSound* getRandomSamplerSound(midi::MidiNumber midiNumber)
{
    juce::File randomSample;
    int rootNoteOfSample;
    std::unique_ptr<juce::AudioFormatReader> audioReader;
    juce::String pathToFile;

    while ((audioReader == nullptr)) {
        juce::File randomSample = getRandomSample();
        pathToFile = randomSample.getFullPathName();
        audioReader = createWAVReader(randomSample);
        int bufferSize = (int) (0.10*audioReader->sampleRate);
        juce::AudioSampleBuffer buffer = createAudioBuffer(audioReader, bufferSize);
        try {
            int frequencyOfSample = getFundementalFrequency(
                buffer.getReadPointer(0),
                bufferSize,
                audioReader->sampleRate,
                true
            );
            rootNoteOfSample = midi::getMidiNumber(frequencyOfSample);
        } catch (FrequencyNotDetectedException) {
            logs::newBadSample(pathToFile);
        }
    }

    juce::BigInteger keyRange;
    keyRange.setRange(midiNumber, midiNumber+1, true);
    
    return new juce::SamplerSound(
        pathToFile, *audioReader,
        keyRange, rootNoteOfSample,
        ATTACK, RELEASE, MAX_SAMPLE_LENGTH
    );
}
