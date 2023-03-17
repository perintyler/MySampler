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

using BufferAndSampleRate = std::pair<juce::AudioBuffer<float>, float>;

Json::Value TEST_DATA = []{
    std::string pathToCrepeTestData = (
        std::filesystem::path { TEST_DATA_DIRECTORY } 
      / std::filesystem::path { "crepe-preparation.json" }
    ).string();
    std::ifstream file(pathToCrepeTestData);
    Json::Reader reader;
    Json::Value jsonData;
    reader.parse(file, jsonData);
    return jsonData;
}();

BufferAndSampleRate get_audio_buffer(const std::string& testFileName)
{
    std::filesystem::path filePath = std::filesystem::path { TEST_DATA_DIRECTORY } 
                                   / std::filesystem::path { testFileName };
    juce::File wavFile { filePath.string() };

    assert(wavFile.existsAsFile());
    juce::WavAudioFormat wavFormat;
    std::unique_ptr<juce::AudioFormatReader> audioReader = std::unique_ptr<juce::AudioFormatReader>(
        wavFormat.createReaderFor(wavFile.createInputStream().release(), true)
    );

    juce::AudioSampleBuffer audioBuffer;
    int bufferSize = audioReader->lengthInSamples;
    audioBuffer.setSize(audioReader->numChannels, bufferSize);
    audioReader->read(&audioBuffer, 0, bufferSize, 0, true, true);

    return std::make_pair(audioBuffer, audioReader->sampleRate);
}

std::vector<float> audioBufferToVector(juce::AudioBuffer<float>& buffer)
{
    std::vector<float> audio;
    const float* samples = buffer.getReadPointer(0);
    for (int index = 0; index < buffer.getNumSamples(); index++) {
        audio.push_back(samples[index]);
    }
    return audio;
}

std::vector<float> jsonAudioToVector(Json::Value& node)
{
    std::vector<float> audio;
    audio.reserve(node.size());
    std::transform(node.begin(), node.end(), std::back_inserter(audio), [](const auto& sample) { 
        return sample.asFloat();
    });
    return audio;
}

void print_expected_and_actual(Json::Value& expected, juce::AudioBuffer& actual)
{
    std::vector<float> expectedVector = jsonAudioToVector(actual);
    std::vector<float> actualVector = audioBufferToVector(expected);

    for (int index = 0; index < buffer.getNumSamples(); index++) {
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
        auto bufferAndSampleRate = get_audio_buffer(audioFile);
        juce::AudioBuffer buffer = bufferAndSampleRate.first;
        int sampleRate = bufferAndSampleRate.second;

        pitch_detection::makeAudioMono(buffer);
        auto actualMonoAudio = audioBufferToVector(buffer);
        auto expectedMonoAudio = jsonAudioToVector(TEST_DATA[audioFile]["mono"]);

        REQUIRE(actualMonoAudio.size() == expectedMonoAudio.size());
        REQUIRE(actualMonoAudio == expectedMonoAudio);

        pitch_detection::downSampleAudio(buffer, sampleRate);
        auto actualAudioAfterDownSampling = audioBufferToVector(buffer);
        auto expectedAudioAfterDownSampling = jsonAudioToVector(TEST_DATA[audioFile]["downsampled"]);

        REQUIRE(actualAudioAfterDownSampling.size() == expectedAudioAfterDownSampling.size());
        REQUIRE(actualAudioAfterDownSampling == expectedAudioAfterDownSampling);

        int sampleRateAfterDownSampling = 16000;
        pitch_detection::create1024SampleFrames(buffer, sampleRateAfterDownSampling);
        auto actualAudioFrames = audioBufferToVector(buffer);
        auto expectedAudioFrames = jsonAudioToVector(TEST_DATA[audioFile]["framedAudio"]);

        REQUIRE(actualAudioFrames.size() == expectedAudioFrames.size());
        REQUIRE(actualAudioFrames == expectedAudioFrames);

        pitch_detection::normalizeAudio(buffer, sampleRateAfterDownSampling);
        auto actualNormalizedAudio = audioBufferToVector(buffer);
        auto expectedNormalizedAudio = jsonAudioToVector(TEST_DATA[audioFile]["normalize"]);

        REQUIRE(actualNormalizedAudio.size() == expectedNormalizedAudio.size());
        REQUIRE(actualNormalizedAudio == expectedNormalizedAudio);
    }
}

#endif