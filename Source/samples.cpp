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
// #include "paths.h"

#define SAMPLES_DIRECTORY "/usr/local/include/Piano960/samples/"

namespace filesystem = std::__fs::filesystem; // TODO: investigate why I need to use std::__fs

const int NUM_SAMPLES = []{
    int numNonAudioFiles = 2; // every directory includes a '.' and '..' file link
    int numFilesInDirectory = (int) std::distance(
        filesystem::directory_iterator(SAMPLES_DIRECTORY),
        filesystem::directory_iterator {}
    );
    return numFilesInDirectory - numNonAudioFiles;
}();

juce::File getRandomSample()
{
    int sampleID = juce::Random::getSystemRandom().nextInt(NUM_SAMPLES);
    std::string fileName = std::to_string(sampleID) + ".wav";
    filesystem::path filePath = filesystem::path { SAMPLES_DIRECTORY } / filesystem::path { fileName };
    return juce::File { filePath.string() };
}

std::unique_ptr<juce::AudioFormatReader> createWAVReader(juce::File& wavFile)
{
    juce::WavAudioFormat wavFormat;

    if (!wavFile.existsAsFile()) {
        juce::String errorMessage = "wav file does not exist: " + wavFile.getFullPathName();
        throw filesystem::filesystem_error(errorMessage.toStdString(), std::error_code());
    } else if (wavFile.getFileExtension() != ".wav") {
        juce::String errorMessage = "sample is not a wav file: " + wavFile.getFullPathName();
        throw filesystem::filesystem_error(errorMessage.toStdString(), std::error_code());
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
    juce::String fileName;

    while ((audioReader == nullptr)) {
        juce::File randomSample = getRandomSample();
        fileName = randomSample.getFileName();
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
            juce::Logger::writeToLog(
                "Could not detect fundemental frequency of sample:" + fileName
            );
        }
    }

    juce::BigInteger keyRange;
    keyRange.setRange(midiNumber, midiNumber+1, true);
    
    return new juce::SamplerSound(
        fileName, *audioReader,
        keyRange, rootNoteOfSample,
        ATTACK, RELEASE, MAX_SAMPLE_LENGTH
    );
}
