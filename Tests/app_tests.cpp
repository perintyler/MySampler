/* editor_tests.cpp */

#include <catch2/catch_test_macros.hpp>

#include "audio_processor.h"
#include "app.h"

TEST_CASE("app tests") 
{
    juce::ScopedJuceInitialiser_GUI libraryInitialiser;
    const juce::MessageManagerLock mml;

    auto processor = AudioProcessor {};
    processor.suspendProcessing(true);
    auto app = App { processor };

    REQUIRE(app.isResizable() == false);

    REQUIRE(app.getBounds().getWidth() * app.getBounds().getHeight() > 0);
}
