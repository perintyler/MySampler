/* editor_tests.cpp */

#include <catch2/catch_test_macros.hpp>
#include <juce_graphics/juce_graphics.h>

#include "audio_processor.h"
#include "app.h"

TEST_CASE("app tests") 
{
    // block messages from other threads for the duration of the test 
    // we're not testing processing here 
    juce::MessageManager::getInstance()->runDispatchLoop();

    AudioProcessor processor {};
    App app { processor };

    REQUIRE(app.isResizable() == false);

    REQUIRE(app.getBounds().getWidth() * app.getBounds().getHeight() > 0);

    REQUIRE(app.findChildWithID("randomize-button")->isVisible());

    REQUIRE(app.findChildWithID("keyboard")->isVisible());

    REQUIRE(app.findChildWithID("randomize-button")->isVisible());

    auto keyboardBounds = app.findChildWithID("keyboard")->getBounds();
    REQUIRE(keyboardBounds.getWidth() * keyboardBounds.getHeight() > 0);

    auto randomizeButtonBounds = app.findChildWithID("randomize-button")->getBounds();
    REQUIRE(randomizeButtonBounds.getWidth() * randomizeButtonBounds.getHeight() > 0);

    juce::MessageManager::getInstance()->stopDispatchLoop();
    juce::MessageManager::deleteInstance();
}
