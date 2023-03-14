// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//   pitch_detection_tests.cpp
//   ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// This file contains unit tests for the `PitchDetection`
// translation unit.
//
// MIDI Note Numbers Reference: 
//   | https://www.inspiredacoustics.com/en/MIDI_note_numbers_and_center_frequencies
// Note Frequencies Reference
//   | https://pages.mtu.edu/~suits/notefreqs.html
//
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#include <vector>
#include <string>
#include <filesystem>
#include <cassert>
#include <iostream>
#include <string>

#include <catch2/catch_test_macros.hpp>
#include <juce_audio_formats/juce_audio_formats.h>

#include "pitch/pitch.h"
#include "paths.h"

bool ONLY_TEST_SEMITONES = true;

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

TEST_CASE("lower frequency than lowest note", "[matchNoteToFrequency]")
{
    REQUIRE_THROWS_AS(matchNoteToFrequency(10.0), NoteDoesNotExistException);
}

TEST_CASE("inbetween B3 and C4", "[matchNoteToFrequency]") 
{
    REQUIRE(matchNoteToFrequency(250.7) == 59);
}

TEST_CASE("G4", "[matchNoteToFrequency]") 
{
    REQUIRE(matchNoteToFrequency(392.0) == 67);
}

TEST_CASE("close to Csharp6", "[matchNoteToFrequency]") 
{
    REQUIRE(matchNoteToFrequency(1100.8) == 85);
}

TEST_CASE("Female Vocal: G5", "[pitch_detection]") 
{
    printPitchDetectionInfo();
    float frequency = get_frequency("G5-female-vocal-chop.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(174.61 < frequency);
        REQUIRE(frequency < 196.00);
    }

    REQUIRE(getSemitone(frequency) == G);
}

TEST_CASE("Female Vocal: G#3", "[pitch_detection]") 
{
    float frequency = get_frequency("G#3-female-vocal-chop.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(739.99 < frequency);
        REQUIRE(frequency < 830.61);
    }

    REQUIRE(getSemitone(frequency) == Gsharp);
}

TEST_CASE("Male Vocal: A4", "[pitch_detection]") 
{
    float frequency = get_frequency("A4-male-vocal-chop.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(415.30 < frequency);
        REQUIRE(frequency < 466.16);
    }

    REQUIRE(getSemitone(frequency) == A);
}

TEST_CASE("Acoustic Bass: C3", "[pitch_detection]") 
{
    float frequency = get_frequency("C3-acoustic-bass-oneshot.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(123.47 < frequency);
        REQUIRE(frequency < 138.59);
    }

    REQUIRE(getSemitone(frequency) == C);
}

TEST_CASE("Guitar: A2", "[pitch_detection]") 
{
    float frequency = get_frequency("A2-guitar-oneshot.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(103.83 < frequency);
        REQUIRE(frequency < 116.54);
    }

    REQUIRE(getSemitone(frequency) == A);
}

TEST_CASE("Keyboard: C6", "[pitch_detection]") 
{
    float frequency = get_frequency("C6-keyboard-oneshot.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(987.77 < frequency);
        REQUIRE(frequency < 1108.73);
    }

    REQUIRE(getSemitone(frequency) == C);
}

/************************************************************
 * FAILING PITCH DETECTION TESTS

TEST_CASE("Guitar: C3", "[pitch_detection]")
{
    float frequency = get_frequency("C3-guitar-oneshot.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(123.47 < frequency);
        REQUIRE(frequency < 138.59);
    }

    Semitone semitone = getSemitone(frequency);
    REQUIRE(semitone == midi::C);
}

TEST_CASE("Upright Bass: C2", "[pitch_detection]") 
{
    float frequency = get_frequency("C2-uprite-bass-oneshot.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(61.74 < frequency);
        REQUIRE(frequency < 69.30);
    }

    Semitone semitone = getSemitone(frequency);
    REQUIRE(semitone == midi::C);
}

TEST_CASE("Exchange Bass: C4", "[pitch_detection]") 
{
    float frequency = get_frequency("C4-exchange-bass-oneshot.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(246.94 < frequency);
        REQUIRE(frequency < 277.18);
    }

    Semitone semitone = getSemitone(frequency);
    REQUIRE(semitone == midi::C);
}

TEST_CASE("Piano: G3", "[pitch_detection]") 
{
    float frequency = get_frequency("G3-piano-oneshot.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(185.00 < frequency);
        REQUIRE(frequency < 207.65);
    }

    Semitone semitone = getSemitone(frequency);
    REQUIRE(semitone == midi::G);
}

TEST_CASE("Guitar: E4", "[pitch_detection]") 
{
    float frequency = get_frequency("E4-guitar-oneshot.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(311.13 < frequency);
        REQUIRE(frequency < 349.23);
    }

    Semitone semitone = getSemitone(frequency);
    REQUIRE(semitone == midi::E);
}

TEST_CASE("Keyboard: C5", "[pitch_detection]") 
{
    float frequency = get_frequency("C5-keyboard-oneshot.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(493.88 < frequency);
        REQUIRE(frequency < 554.37);
    }

    Semitone semitone = getSemitone(frequency);
    REQUIRE(semitone == midi::C);
}

TEST_CASE("Piano: C6", "[pitch_detection]") 
{
    float frequency = get_frequency("C6-piano-oneshot.wav");

    if (!ONLY_TEST_SEMITONES) {
        REQUIRE(987.77 < frequency);
        REQUIRE(frequency < 1108.73);
    }

    Semitone semitone = getSemitone(frequency);
    REQUIRE(semitone == midi::C);
}

************************************************************/


