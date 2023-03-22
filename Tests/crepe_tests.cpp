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

juce::AudioBuffer<float> getAudioBuffer(
    const std::string& testFile, 
    const std::string& testType = "audio", 
    int numChannels=2
) {
    int numSamples = TEST_DATA[testFile][testType].size();
    juce::AudioBuffer<float> buffer(numChannels, numSamples);

    for (int i = 0; i < numSamples; i++) {
        for (int channel = 0; channel < numChannels; channel++) {
            buffer.setSample(channel, i, TEST_DATA[testFile][testType][i][channel].asFloat());
        }
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

        /* --- TEST STEREO TO MONO --- */

        pitch_detection::makeAudioMono(buffer);

        REQUIRE(buffer.getNumSamples() == TEST_DATA[audioFile]["mono"].size());

        for (int i = 0; i < buffer.getNumSamples(); i++)
            REQUIRE(buffer.getSample(0, i) == Catch::Approx(TEST_DATA[audioFile]["mono"][i].asFloat()));

        /* --- TEST DOWN SAMPLING --- */

        juce::AudioBuffer<float> downsampled = pitch_detection::downSampleAudio(
            buffer, SAMPLE_RATE_BEFORE_DOWNSAMPLING
        );

        REQUIRE(downsampled.getNumSamples() == TEST_DATA[audioFile]["downsampled"].size());

        /* --- TEST FRAMING --- */

        auto frames = pitch_detection::create1024SampleFrames(
            downsampled, 
            SAMPLE_RATE_AFTER_DOWNSAMPLING
        );

        REQUIRE(frames.size() == TEST_DATA[audioFile]["framedAudio"][0].size());

        for (const std::vector<float>& frame : frames)
            REQUIRE(frame.size() == 1024);

        /* --- TEST NORMALIZATION --- */

        pitch_detection::normalizeAudioFrames(frames);

        for (int frameIndex = 0; frameIndex < 1; frameIndex++) {
            for (int sampleIndex = 0; sampleIndex < frames[frameIndex].size(); sampleIndex++) {
                float actual = frames.at(frameIndex).at(sampleIndex);
                float expected = TEST_DATA[audioFile]["framedAudio"][0][frameIndex][sampleIndex].asFloat();
                REQUIRE(actual == Catch::Approx(expected));
            }
        }
    }
}

#endif