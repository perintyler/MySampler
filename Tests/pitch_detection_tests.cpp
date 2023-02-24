// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//   pitch_detection_tests.cpp
//   ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// This file contains unit tests for the `PitchDetection`
// translation unit.
//
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#include <vector>
#include <string>
#include <filesystem>
#include <cassert>
#include <iostream>

#include <catch2/catch_test_macros.hpp>
#include <juce_audio_formats/juce_audio_formats.h>

#include "pitch_detection.h"
#include "midi.h"
#include "paths.h"

bool ONLY_TEST_SEMITONES = true;

float get_frequency(std::filesystem::path fileName)
{
    std::filesystem::path filePath = std::filesystem::path { TEST_DATA_DIRECTORY } / std::filesystem::path { fileName };
    juce::File wavFile { filePath.string() };

    assert(wavFile.existsAsFile());

    juce::WavAudioFormat wavFormat;
    std::unique_ptr<juce::AudioFormatReader> audioReader = std::unique_ptr<juce::AudioFormatReader>(
        wavFormat.createReaderFor(wavFile.createInputStream().release(), true)
    );

    juce::AudioSampleBuffer audioBuffer;
    int bufferSize = std::min((int) audioReader->lengthInSamples, (int) (0.10*audioReader->sampleRate)); // (audioReader->sampleRate));
    audioBuffer.clear(); // Why again?
    audioBuffer.setSize(audioReader->numChannels, bufferSize);
    audioReader->read(&audioBuffer, 0, bufferSize, 0, true, true);

    return getFundementalFrequency(audioBuffer.getReadPointer(0), bufferSize, audioReader->sampleRate);
}

TEST_CASE("Female Vocal: G5", "[pitch_detection]") 
{
    float frequency = get_frequency("G5-female-vocal-chop.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(174.61 < frequency);
        REQUIRE(frequency < 196.00);
    }

    midi::Semitone semitone = midi::getSemitone(frequency);
    REQUIRE(semitone == midi::G);
}

TEST_CASE("Female Vocal: G#3", "[pitch_detection]") 
{
    float frequency = get_frequency("G#3-female-vocal-chop.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(739.99 < frequency);
        REQUIRE(frequency < 830.61);
    }

    midi::Semitone semitone = midi::getSemitone(frequency);
    REQUIRE(semitone == midi::Gsharp);
}

TEST_CASE("Male Vocal: A4", "[pitch_detection]") 
{
    float frequency = get_frequency("A4-male-vocal-chop.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(415.30 < frequency);
        REQUIRE(frequency < 466.16);
    }

    midi::Semitone semitone = midi::getSemitone(frequency);
    REQUIRE(semitone == midi::A);
}

TEST_CASE("Guitar: C3", "[pitch_detection]")
{
    float frequency = get_frequency("C3-guitar-oneshot.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(123.47 < frequency);
        REQUIRE(frequency < 138.59);
    }

    midi::Semitone semitone = midi::getSemitone(frequency);
    REQUIRE(semitone == midi::C);
}

TEST_CASE("Upright Bass: C2", "[pitch_detection]") 
{
    float frequency = get_frequency("C2-uprite-bass-oneshot.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(61.74 < frequency);
        REQUIRE(frequency < 69.30);
    }

    midi::Semitone semitone = midi::getSemitone(frequency);
    REQUIRE(semitone == midi::C);
}

TEST_CASE("Acoustic Bass: C3", "[pitch_detection]") 
{
    float frequency = get_frequency("C3-acoustic-bass-oneshot.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(123.47 < frequency);
        REQUIRE(frequency < 138.59);
    }

    midi::Semitone semitone = midi::getSemitone(frequency);
    REQUIRE(semitone == midi::C);
}

TEST_CASE("Exchange Bass: C4", "[pitch_detection]") 
{
    float frequency = get_frequency("C4-exchange-bass-oneshot.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(246.94 < frequency);
        REQUIRE(frequency < 277.18);
    }

    midi::Semitone semitone = midi::getSemitone(frequency);
    REQUIRE(semitone == midi::C);
}

TEST_CASE("Piano: C6", "[pitch_detection]") 
{
    float frequency = get_frequency("C6-piano-oneshot.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(987.77 < frequency);
        REQUIRE(frequency < 1108.73);
    }

    midi::Semitone semitone = midi::getSemitone(frequency);
    REQUIRE(semitone == midi::C);
}

TEST_CASE("Piano: G3", "[pitch_detection]") 
{
    float frequency = get_frequency("G3-piano-oneshot.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(185.00 < frequency);
        REQUIRE(frequency < 207.65);
    }

    midi::Semitone semitone = midi::getSemitone(frequency);
    REQUIRE(semitone == midi::G);
}

TEST_CASE("Guitar: A2", "[pitch_detection]") 
{
    float frequency = get_frequency("A2-guitar-oneshot.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(103.83 < frequency);
        REQUIRE(frequency < 116.54);
    }

    midi::Semitone semitone = midi::getSemitone(frequency);
    REQUIRE(semitone == midi::A);
}

TEST_CASE("Guitar: E4", "[pitch_detection]") 
{
    float frequency = get_frequency("E4-guitar-oneshot.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(311.13 < frequency);
        REQUIRE(frequency < 349.23);
    }

    midi::Semitone semitone = midi::getSemitone(frequency);
    REQUIRE(semitone == midi::E);
}


TEST_CASE("Keyboard: C5", "[pitch_detection]") 
{
    float frequency = get_frequency("C5-keyboard-oneshot.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(493.88 < frequency);
        REQUIRE(frequency < 554.37);
    }

    midi::Semitone semitone = midi::getSemitone(frequency);
    REQUIRE(semitone == midi::C);
}

TEST_CASE("Keyboard: C6", "[pitch_detection]") 
{
    float frequency = get_frequency("C6-keyboard-oneshot.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(987.77 < frequency);
        REQUIRE(frequency < 1108.73);
    }

    midi::Semitone semitone = midi::getSemitone(frequency);
    REQUIRE(semitone == midi::C);
}
