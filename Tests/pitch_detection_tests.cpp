// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - Piano960 | VST3, AU - - - - - - - - - - - - - - - - - - - -
// - - Created by Tyler Perin  - - - - - - - - - - - - - - - - - -
// - - Copyright © 2022 Sound Voyager. All rights reserved.- - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//   pitch_detection_tests.cpp
//   ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#include <vector>
#include <string>
#include <filesystem>
#include <cassert>
#include <iostream>

#include <catch2/catch_test_macros.hpp>
#include <juce_audio_formats/juce_audio_formats.h>

#include "config.h"
#include "pitch_detection.h"

std::vector<float> get_test_audio(std::filesystem::path fileName, int bufferSize, int sampleRate)
{
    std::cout << TEST_DATA_DIRECTORY << std::endl;

    std::filesystem::path filePath = std::filesystem::path { TEST_DATA_DIRECTORY } / std::filesystem::path { fileName };
    juce::File wavFile { filePath.string() };


    assert(wavFile.existsAsFile());
    juce::WavAudioFormat wavFormat;
    std::unique_ptr<juce::AudioFormatReader> audioReader = std::unique_ptr<juce::AudioFormatReader>(
        wavFormat.createReaderFor(wavFile.createInputStream().release(), true)
    );

    juce::AudioSampleBuffer audioBuffer;
    audioBuffer.clear(); // Why again?
    audioBuffer.setSize(audioReader->numChannels, bufferSize);
    audioReader->read(&audioBuffer, 0, bufferSize, 0, true, true);

    const float* bufferReadPointer = audioBuffer.getReadPointer(0);

    std::vector<float> audio;
    for (int i = 0; i < bufferSize; ++i) {
        std::cout << i << std::endl;
        audio.push_back(bufferReadPointer[i]);
    }

    return audio;
  }

TEST_CASE("G5 female vocal chop", "[pitch_detection]") 
{
    int bufferSize = 1000;
    int sampleRate = 44100;
    int expectedNoteNumber = 79;
    std::vector<float> audio = get_test_audio("G5-female-vocal-chop.wav", bufferSize, sampleRate);
    float frequency = getFundementalFrequency(audio.data(), bufferSize, sampleRate);
    REQUIRE(739.99 < frequency);
    REQUIRE(frequency < 830.61);
}

TEST_CASE("Piano One-Shot", "[pitch_detection]") 
{}

TEST_CASE("Guitar One-Shot", "[pitch_detection]") 
{}