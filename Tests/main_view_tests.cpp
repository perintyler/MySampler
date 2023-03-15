/*** Piano960 | main_view_tests.cpp ***/

#include <catch2/catch_test_macros.hpp>

#include "main_view.h"

TEST_CASE("main view sub-components", "[main_view]") 
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

