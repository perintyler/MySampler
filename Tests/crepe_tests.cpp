/*** Piano960 | crepe_tests.cpp ***/

#ifdef CREPE_MODEL

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

#include <catch2/catch_test_macros.hpp>
#include <juce_audio_formats/juce_audio_formats.h>
#include "JsonCpp/json/json.h"

#include "pitch/crepe.h"
#include "config.h"
#include "paths.h"

int SAMPLE_RATE_BEFORE_DOWNSAMPLING = 44100;

int SAMPLE_RATE_AFTER_DOWNSAMPLING = 16000;

using BufferAndSampleRate = std::pair<juce::AudioBuffer<double>, float>;

const Json::Value TEST_DATA = []{
    std::string pathToCrepeTestData = (
        std::filesystem::path { TEST_DATA_DIRECTORY } 
      / std::filesystem::path { "crepe-inputs.json" }
    ).string();
    std::ifstream file(pathToCrepeTestData);
    Json::Reader reader;
    Json::Value jsonData;
    reader.parse(file, jsonData);
    return jsonData;
}();

juce::AudioBuffer<double> getAudioBuffer(const std::string& testFile)
{
    int numSamples = TEST_DATA[testFile]["audio"].size();
    juce::AudioBuffer<double> buffer(2, numSamples);

    for (int i = 0; i < numSamples; i++) {
        buffer.setSample(0, i, TEST_DATA[testFile]["audio"][i][0].asDouble());
        buffer.setSample(1, i, TEST_DATA[testFile]["audio"][i][1].asDouble());
    }

    return buffer;
}

// BufferAndSampleRate get_audio_buffer(const std::string& testFileName)
// {
//     std::filesystem::path filePath = std::filesystem::path { TEST_DATA_DIRECTORY } 
//                                    / std::filesystem::path { testFileName };
//     juce::File wavFile { filePath.string() };

//     assert(wavFile.existsAsFile());
//     juce::WavAudioFormat wavFormat;
//     std::unique_ptr<juce::AudioFormatReader> audioReader = std::unique_ptr<juce::AudioFormatReader>(
//         wavFormat.createReaderFor(wavFile.createInputStream().release(), true)
//     );

//     juce::AudioSampleBuffer audioBuffer;
//     int bufferSize = audioReader->lengthInSamples;
//     audioBuffer.setSize(audioReader->numChannels, bufferSize);
//     audioReader->read(&audioBuffer, 0, bufferSize, 0, true, true);

//     return std::make_pair(audioBuffer, audioReader->sampleRate);
// }

std::vector<double> audioBufferToVector(juce::AudioBuffer<double>& buffer)
{
    std::vector<double> audio;
    audio.reserve(buffer.getNumSamples());
    for (int index = 0; index < buffer.getNumSamples(); index++) {
        audio.push_back(buffer.getSample(0, index));
    }
    return audio;
}

std::vector<double> jsonAudioToVector(const Json::Value& node)
{
    std::vector<double> audio;
    audio.reserve(node.size());
    std::transform(node.begin(), node.end(), std::back_inserter(audio), [](const auto& sample) { 
        return sample.asDouble();
    });
    return audio;
}

void printExpectedAndActual(const Json::Value& expected, juce::AudioBuffer<double>& actual)
{
    std::vector<double> expectedVector = jsonAudioToVector(expected);
    std::vector<double> actualVector = audioBufferToVector(actual);

    for (int index = 0; index < 100; index++) {
        std::cout << "(" 
                  << expectedVector.at(index) 
                  << ", " 
                  << actualVector.at(index)
                  << ")" 
                  << std::endl;
    }
}

TEST_CASE("prepare audio for crepe model", "[pitch_detection]")
{
    for (auto const& audioFile : TEST_DATA.getMemberNames()) {
        std::cout << "AUDIO FILE: " << audioFile << std::endl;

        juce::AudioBuffer<double> buffer = getAudioBuffer(audioFile);

        pitch_detection::makeAudioMono(buffer);

        auto actualMonoAudio = audioBufferToVector(buffer);
        auto expectedMonoAudio = jsonAudioToVector(TEST_DATA[audioFile]["mono"]);

        REQUIRE(actualMonoAudio.size() == expectedMonoAudio.size());
        REQUIRE(actualMonoAudio == expectedMonoAudio);

        pitch_detection::downSampleAudio(buffer, SAMPLE_RATE_BEFORE_DOWNSAMPLING);
        auto actualAudioAfterDownSampling = audioBufferToVector(buffer);
        auto expectedAudioAfterDownSampling = jsonAudioToVector(TEST_DATA[audioFile]["downsampled"]);

        printExpectedAndActual(TEST_DATA[audioFile]["downsampled"], buffer);
        break;
        REQUIRE(actualAudioAfterDownSampling.size() == expectedAudioAfterDownSampling.size());
        REQUIRE(actualAudioAfterDownSampling == expectedAudioAfterDownSampling);

        break;

        pitch_detection::create1024SampleFrames(buffer, SAMPLE_RATE_AFTER_DOWNSAMPLING);
        auto actualAudioFrames = audioBufferToVector(buffer);
        auto expectedAudioFrames = jsonAudioToVector(TEST_DATA[audioFile]["framedAudio"]);

        REQUIRE(actualAudioFrames.size() == expectedAudioFrames.size());
        REQUIRE(actualAudioFrames == expectedAudioFrames);

        pitch_detection::normalizeAudio(buffer, SAMPLE_RATE_AFTER_DOWNSAMPLING);
        auto actualNormalizedAudio = audioBufferToVector(buffer);
        auto expectedNormalizedAudio = jsonAudioToVector(TEST_DATA[audioFile]["normalize"]);

        REQUIRE(actualNormalizedAudio.size() == expectedNormalizedAudio.size());
        REQUIRE(actualNormalizedAudio == expectedNormalizedAudio);
    }
}

#endif