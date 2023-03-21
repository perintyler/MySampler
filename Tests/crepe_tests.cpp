/*** Piano960 | crepe_tests.cpp ***/

#ifdef CREPE_MODEL

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include <juce_audio_formats/juce_audio_formats.h>
#include "JsonCpp/json/json.h"

#include "pitch/crepe.h"
#include "config.h"
#include "paths.h"

int SAMPLE_RATE_BEFORE_DOWNSAMPLING = 44100;

int SAMPLE_RATE_AFTER_DOWNSAMPLING = 16000;

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

juce::AudioBuffer<float> getAudioBuffer(const std::string& testFile)
{
    int numSamples = TEST_DATA[testFile]["audio"].size();
    juce::AudioBuffer<float> buffer(2, numSamples);

    for (int i = 0; i < numSamples; i++) {
        buffer.setSample(0, i, TEST_DATA[testFile]["audio"][i][0].asDouble());
        buffer.setSample(1, i, TEST_DATA[testFile]["audio"][i][1].asDouble());
    }

    return buffer;
}

std::vector<float> audioBufferToVector(juce::AudioBuffer<float>& buffer)
{
    std::vector<float> audio;
    audio.reserve(buffer.getNumSamples());
    for (int index = 0; index < buffer.getNumSamples(); index++) {
        audio.push_back(buffer.getSample(0, index));
    }
    return audio;
}

std::vector<float> jsonAudioToVector(const Json::Value& node)
{
    std::vector<float> audio;
    audio.reserve(node.size());
    std::transform(node.begin(), node.end(), std::back_inserter(audio), [](const auto& sample) { 
        return sample.asFloat();
    });
    return audio;
}

// debug function
void printExpectedAndActual(const Json::Value& expected, juce::AudioBuffer<float>& actual)
{
    std::vector<float> expectedVector = jsonAudioToVector(expected);
    std::vector<float> actualVector = audioBufferToVector(actual);

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

        juce::AudioBuffer<float> buffer = getAudioBuffer(audioFile);

        pitch_detection::makeAudioMono(buffer);

        auto actualMonoAudio = audioBufferToVector(buffer);
        auto expectedMonoAudio = jsonAudioToVector(TEST_DATA[audioFile]["mono"]);

        REQUIRE(actualMonoAudio.size() == expectedMonoAudio.size());
        REQUIRE(actualMonoAudio == expectedMonoAudio);

        juce::AudioBuffer<float> downsampled = pitch_detection::downSampleAudio(
            buffer, SAMPLE_RATE_BEFORE_DOWNSAMPLING
        );

        REQUIRE(downsampled.getNumSamples() == TEST_DATA[audioFile]["downsampled"].size());

        continue; 

        pitch_detection::create1024SampleFrames(downsampled, SAMPLE_RATE_AFTER_DOWNSAMPLING);
        pitch_detection::normalizeAudio(downsampled, SAMPLE_RATE_AFTER_DOWNSAMPLING);
        
        auto actualNormalizedAudio = audioBufferToVector(downsampled);
        auto expectedNormalizedAudio = jsonAudioToVector(TEST_DATA[audioFile]["normalize"]);

        REQUIRE(actualNormalizedAudio.size() == expectedNormalizedAudio.size());
        for (int i = 0; i < expectedNormalizedAudio.size(); i++) {
            REQUIRE(actualNormalizedAudio.at(i) == Catch::Approx(expectedNormalizedAudio.at(i)));
        }
    }
}

#endif