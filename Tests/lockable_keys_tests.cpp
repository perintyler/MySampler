/*** Piano960 | lockable_keys_tests.cpp ***/

#include <catch2/catch_test_macros.hpp>
#include <juce_graphics/juce_graphics.h>

#include "lockable_keys.h"

TEST_CASE("keys have lock buttons") 
{
    juce::ScopedJuceInitialiser_GUI libraryInitialiser;
    const juce::MessageManagerLock mml;
    juce::MidiKeyboardState state;
    LockableKeys keys { state, [](Note){} };
    REQUIRE(keys.getNumChildComponents() > (LAST_MIDI_NOTE - FIRST_MIDI_NOTE));
}
