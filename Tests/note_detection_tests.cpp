// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//   note_detection_tests.cpp
//   ~~~~~~~~~~~~~~~~~~~~~~~~
//
// MIDI Note Numbers Reference: 
//   | https://www.inspiredacoustics.com/en/MIDI_note_numbers_and_center_frequencies
// Note Frequencies Reference
//   | https://pages.mtu.edu/~suits/notefreqs.html
//
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#include <catch2/catch_test_macros.hpp>
#include <juce_audio_formats/juce_audio_formats.h>

#include "midi.h"

TEST_CASE("lower frequency than lowest note")
{
    REQUIRE_THROWS_AS(midi::getMidiNumber(10.0), midi::InvalidMidiNoteException);
}

TEST_CASE("inbetween B3 and C4", "[note_numbers]") 
{
    REQUIRE(midi::getMidiNumber(250.7) == 59);
}

TEST_CASE("G4", "[note_numbers]") 
{
    REQUIRE(midi::getMidiNumber(392.0) == 67);
}

TEST_CASE("close to Csharp6", "[note_numbers]") 
{
    REQUIRE(midi::getMidiNumber(1100.8) == 85);
}
