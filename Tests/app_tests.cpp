/* editor_tests.cpp */

#include <catch2/catch_test_macros.hpp>

#include "audio_processor.h"
#include "app.h"

AudioProcessor processor {};
App app(processor);

TEST("app: is visibile")
{
    REQUIRE(app.isVisible() == false);
}

TEST("app: keyboard is sub-component") 
{}

TEST("app: randomize button is sub-component") 
{}

TEST("app: paints keyboard") 
{}

TEST("app: paints randomize button") 
{}

TEST("app: lays out keyboard") 
{}

TEST("app: lays out randomize button") 
{}

TEST("app: cleans up sub-components upon destuction") 
{}

