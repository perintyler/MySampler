/*** Piano960 | crepe_tests.cpp ***/

#ifdef CREPE_MODEL

#include <filesystem>
#include <string>

#include <catch2/catch_test_macros.hpp>
#include <juce_audio_formats/juce_audio_formats.h>

#include "pitch/crepe.h"
#include "config.h"
#include "paths.h"

using BufferAndSampleRate = std::pair<juce::AudioBuffer<float>, float>;

BufferAndSampleRate get_audio_buffer(const char* testFileName)
{
    std::filesystem::path filePath = std::filesystem::path { TEST_DATA_DIRECTORY } 
                                   / std::filesystem::path { testFileName };
    juce::File wavFile { filePath.string() };
    std::cout << filePath.string() << std::endl;
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

TEST_CASE("prepare audio for CREPE model: normalize audio", "[pitch_detection]") 
{
    auto bufferAndSampleRate = get_audio_buffer("G#3-female-vocal-chop.wav");
    pitch_detection::normalizeAudio(bufferAndSampleRate.first, bufferAndSampleRate.second);
    // TODO
}

TEST_CASE("prepare audio for CREPE model: create 1024 sample frames", "[pitch_detection]") 
{
    auto bufferAndSampleRate = get_audio_buffer("C3-acoustic-bass-oneshot.wav");
    pitch_detection::create1024SampleFrames(bufferAndSampleRate.first, bufferAndSampleRate.second);
    // TODO
}

TEST_CASE("prepare audio for CREPE model: make audio mono", "[pitch_detection]") 
{
    auto bufferAndSampleRate = get_audio_buffer("C3-acoustic-bass-oneshot.wav");
    pitch_detection::makeAudioMono(bufferAndSampleRate.first);
    // TODO
}

TEST_CASE("prepare audio for CREPE model: down-sample audio", "[pitch_detection]") 
{
    auto bufferAndSampleRate = get_audio_buffer("C6-keyboard-oneshot.wav");
    pitch_detection::downSampleAudio(bufferAndSampleRate.first, bufferAndSampleRate.second);
    // TODO
}

#endif