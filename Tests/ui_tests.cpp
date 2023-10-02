/*** Piano960 Tests | ui_tests.cpp ***/

#include <string>
#include <catch2/catch_test_macros.hpp>
#include <juce_graphics/juce_graphics.h>

#include "audio_processor.h"
#include "app.h"

#include "gui/lockable_keys.h"
#include "gui/main_view.h"
#include "gui/presets_dropdown_menu.h"

TEST_CASE("UI Test #1: app", "[ui][app]") 
{
    juce::ScopedJuceInitialiser_GUI libraryInitialiser;
    const juce::MessageManagerLock mml;

    AudioProcessor processor {};
    processor.suspendProcessing(true);
    auto app = App { processor };

    REQUIRE(app.isResizable() == false);
    REQUIRE(app.getBounds().getWidth() * app.getBounds().getHeight() > 0);
}

TEST_CASE("UI Test #2: main view", "[ui][main_view]") 
{
    juce::ScopedJuceInitialiser_GUI libraryInitialiser;
    const juce::MessageManagerLock mml;

    AudioProcessor processor {};
    processor.suspendProcessing(true);
    MainView view(processor);

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
    AudioProcessor processor {};
    processor.suspendProcessing(true);
    LockableKeys keyboard(processor);
    int numKeys = LAST_MIDI_NOTE - FIRST_MIDI_NOTE;
    REQUIRE(keyboard.getNumChildComponents() > numKeys);
    // TODO: require that each lock button is on the key with the same index 
}

TEST_CASE("UI Test #4: click randomize button", "[ui][main_view][randomize_button][user_input]")
{}

TEST_CASE("UI Test #5: new preset dialog", "[ui][dialog][new_preset_dialog][user_input]")
{}

TEST_CASE("UI Test #6: presets dropdown menu", "[ui][presets_dropdown_menu][user_input]")
{
    juce::ScopedJuceInitialiser_GUI libraryInitialiser;
    const juce::MessageManagerLock mml;
    AudioProcessor processor {};
    processor.suspendProcessing(true);

    PresetsDropdownMenu dropdown(processor);
    REQUIRE(dropdown.getNumItems() == 3);
}

TEST_CASE("UI Test #7: sound source grid", "[ui][main_view][category_grid]")
{}




