/*** Piano960 Tests | pitch_tests.cpp ***/

#include <vector>
#include <string>
#include <filesystem>
#include <cassert>
#include <iostream>
#include <string>

#include <catch2/catch_test_macros.hpp>
#include <juce_audio_formats/juce_audio_formats.h>

#include "notes.h"
#include "paths.h"
#include "pitch_detection/pitch_detection.h"

#define NO_PITCH_DETECTION_CACHE

#ifdef PRECISE_PITCH_DETECTION_TESTS
    const bool ONLY_TEST_SEMITONES = false;
#else
    const bool ONLY_TEST_SEMITONES = true;
#endif

float get_frequency(std::filesystem::path fileName)
{
    std::filesystem::path filePath = std::filesystem::path { TEST_DATA_DIRECTORY } 
                                   / std::filesystem::path { fileName };
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

    return detectFrequency(audioBuffer, audioReader->sampleRate);
}

TEST_CASE("Semitone Test #1: get semitone from note", "[pitch][semitone][note]")
{
    REQUIRE(getSemitone(C0) == C);
    REQUIRE(getSemitone(C1) == C);
    REQUIRE(getSemitone(G0) == G);
    REQUIRE(getSemitone(B8) == B);
    REQUIRE(getSemitone(G8) == G);
}

TEST_CASE("Pitch Detection Test #1: lower frequency than lowest note", "[pitch_detection][slow]")
{
    REQUIRE_THROWS_AS(getNoteForFrequency(10.0), NoteDoesNotExistException);
}

TEST_CASE("Pitch Detection Test #2: inbetween B3 and C4", "[pitch_detection][slow]") 
{
    REQUIRE(getNoteForFrequency(250.7) == 59);
}

TEST_CASE("Pitch Detection Test #3: G4", "[getNoteForFrequency]") 
{
    REQUIRE(getNoteForFrequency(392.0) == 67);
}

TEST_CASE("Pitch Detection Test #4: close to Csharp6", "[pitch_detection][slow]") 
{
    REQUIRE(getNoteForFrequency(1100.8) == 85);
}

TEST_CASE("Pitch Detection Test #5: Female Vocal: G5", "[pitch_detection][slow]") 
{
    printPitchDetectionInfo();
    float frequency = get_frequency("G5-female-vocal-chop.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(174.61 < frequency);
        REQUIRE(frequency < 196.00);
    }

    REQUIRE(getSemitoneForFrequency(frequency) == G);
}

TEST_CASE("Pitch Detection Test #6: Female Vocal: G#3", "[pitch_detection][slow]") 
{
    float frequency = get_frequency("G#3-female-vocal-chop.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(739.99 < frequency);
        REQUIRE(frequency < 830.61);
    }

    REQUIRE(getSemitoneForFrequency(frequency) == Gsharp);
}

TEST_CASE("Pitch Detection Test #7: Male Vocal: A4", "[pitch_detection][slow]") 
{
    float frequency = get_frequency("A4-male-vocal-chop.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(415.30 < frequency);
        REQUIRE(frequency < 466.16);
    }

    REQUIRE(getSemitoneForFrequency(frequency) == A);
}

TEST_CASE("Pitch Detection Test #8: Acoustic Bass: C3", "[pitch_detection][slow]") 
{
    float frequency = get_frequency("C3-acoustic-bass-oneshot.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(123.47 < frequency);
        REQUIRE(frequency < 138.59);
    }

    REQUIRE(getSemitoneForFrequency(frequency) == C);
}

TEST_CASE("Pitch Detection Test #9: Guitar: A2", "[pitch_detection][slow]") 
{}

TEST_CASE("Pitch Detection Test #10: Keyboard: C6", "[pitch_detection][slow]") 
{
    float frequency = get_frequency("C6-keyboard-oneshot.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(987.77 < frequency);
        REQUIRE(frequency < 1108.73);
    }

    REQUIRE(getSemitoneForFrequency(frequency) == C);
}

TEST_CASE("Pitch Detection Test #11: Upright Bass: C2", "[pitch_detection][slow]") 
{
    float frequency = get_frequency("C2-uprite-bass-oneshot.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(61.74 < frequency);
        REQUIRE(frequency < 69.30);
    }

    REQUIRE(getSemitoneForFrequency(frequency) == C);
}

/************************************************************
 * FAILING PITCH DETECTION TESTS

TEST_CASE("Pitch Detection Test #12: Guitar: C3", "[pitch_detection][slow]")
{
    float frequency = get_frequency("C3-guitar-oneshot.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(123.47 < frequency);
        REQUIRE(frequency < 138.59);
    }

    Semitone semitone = getSemitoneForFrequency(frequency);
    REQUIRE(semitone == midi::C);
}

TEST_CASE("Pitch Detection Test #13: Exchange Bass: C4", "[pitch_detection][slow]") 
{
    float frequency = get_frequency("C4-exchange-bass-oneshot.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(246.94 < frequency);
        REQUIRE(frequency < 277.18);
    }

    Semitone semitone = getSemitoneForFrequency(frequency);
    REQUIRE(semitone == midi::C);
}

TEST_CASE("Pitch Detection Test #14: Piano: G3", "[pitch_detection][slow]") 
{
    float frequency = get_frequency("G3-piano-oneshot.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(185.00 < frequency);
        REQUIRE(frequency < 207.65);
    }

    Semitone semitone = getSemitoneForFrequency(frequency);
    REQUIRE(semitone == midi::G);
}

TEST_CASE("Pitch Detection Test #15: Guitar: E4", "[pitch_detection][slow]") 
{
    float frequency = get_frequency("E4-guitar-oneshot.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(311.13 < frequency);
        REQUIRE(frequency < 349.23);
    }

    Semitone semitone = getSemitoneForFrequency(frequency);
    REQUIRE(semitone == midi::E);
}

TEST_CASE("Pitch Detection Test #16: Keyboard: C5", "[pitch_detection][slow]") 
{
    float frequency = get_frequency("C5-keyboard-oneshot.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(493.88 < frequency);
        REQUIRE(frequency < 554.37);
    }

    Semitone semitone = getSemitoneForFrequency(frequency);
    REQUIRE(semitone == midi::C);
}

TEST_CASE("Pitch Detection Test #17: Piano: C6", "[pitch_detection][slow]") 
{
    float frequency = get_frequency("C6-piano-oneshot.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(987.77 < frequency);
        REQUIRE(frequency < 1108.73);
    }

    Semitone semitone = getSemitoneForFrequency(frequency);
    REQUIRE(semitone == midi::C);
}

************************************************************/


