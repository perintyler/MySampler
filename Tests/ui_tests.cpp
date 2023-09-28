/*** Piano960 Tests | ui_tests.cpp ***/

#include <catch2/catch_test_macros.hpp>
#include <juce_graphics/juce_graphics.h>

#include "lockable_keys.h"
#include "main_view.h"
#include "audio_processor.h"
#include "app.h"

TEST_CASE("UI Test #1: app", "[ui][app]") 
{
    juce::ScopedJuceInitialiser_GUI libraryInitialiser;
    const juce::MessageManagerLock mml;

    auto processor = AudioProcessor {};
    processor.suspendProcessing(true);
    auto app = App { processor };

    REQUIRE(app.isResizable() == false);
    REQUIRE(app.getBounds().getWidth() * app.getBounds().getHeight() > 0);
}

TEST_CASE("UI Test #2: main view", "[ui][main_view]") 
{
    juce::ScopedJuceInitialiser_GUI libraryInitialiser;
    const juce::MessageManagerLock mml;

    juce::MidiKeyboardState keyboardState;
    MainView view(keyboardState, [](){}, [](){}, [](Note){});

    SECTION("sub-components are created and visible") 
    {
        REQUIRE(view.findChildWithID("randomize-button")->isVisible());
        REQUIRE(view.findChildWithID("keyboard")->isVisible());
        REQUIRE(view.findChildWithID("save-button")->isVisible());
    }

    SECTION("sub-components have size") 
    {
        view.setSize(1000, 1000);

        auto keyboardBounds = view.findChildWithID("keyboard")->getBounds();
        REQUIRE(keyboardBounds.getWidth() * keyboardBounds.getHeight() > 0);

        auto randomizeButtonBounds = view.findChildWithID("randomize-button")->getBounds();
        REQUIRE(randomizeButtonBounds.getWidth() * randomizeButtonBounds.getHeight() > 0);
    }

    SECTION("text buttons are clickable")
    {
        static_cast<juce::Button*>(view.findChildWithID("randomize-button"))->triggerClick();
        static_cast<juce::Button*>(view.findChildWithID("save-button"))->triggerClick();
    }
}

TEST_CASE("UI Test #3: lockable keys", "[ui][lockable_keys]") 
{
    juce::ScopedJuceInitialiser_GUI libraryInitialiser;
    const juce::MessageManagerLock mml;
    juce::MidiKeyboardState state;
    LockableKeys keyboard { state, [](Note){} };
    int numKeys = LAST_MIDI_NOTE - FIRST_MIDI_NOTE;
    REQUIRE(keyboard.getNumChildComponents() > numKeys);
    // TODO: require that each lock button is on the key with the same index 
}

TEST_CASE("UI Test #4: click randomize button", "[ui][main_view][randomize_button][user_input]")
{}

TEST_CASE("UI Test #5: new preset dialog", "[ui][dialog][new_preset_dialog][user_input]")
{}

TEST_CASE("UI Test #6: preset dropdown", "[ui][preset_dropdown][user_input]")
{}



