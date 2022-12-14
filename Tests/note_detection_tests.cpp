// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - Piano960 | VST3, AU - - - - - - - - - - - - - - - - - - - -
// - - Created by Tyler Perin  - - - - - - - - - - - - - - - - - -
// - - Copyright © 2022 Sound Voyager. All rights reserved.- - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//   note_detection_tests.cpp
//   ~~~~~~~~~~~~~~~~~~~~~~~~
//
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#include <catch2/catch_test_macros.hpp>
#include <juce_audio_formats/juce_audio_formats.h>

#include "piano.h"

TEST_CASE("inbetween B3 and C4", "[note_numbers]") 
{
    float frequency = 250.0;
    int noteNumberForB3 = 59;
    REQUIRE(piano::getKeyNumber(frequency) == noteNumberForB3);
}

TEST_CASE("G4", "[note_numbers]") 
{}

TEST_CASE("Csharp6", "[note_numbers]") 
{}