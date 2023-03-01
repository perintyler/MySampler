/* editor_tests.cpp */

#include <catch2/catch_test_macros.hpp>

#include "audio_processor.h"
#include "app.h"

AudioProcessor processor {};
App app(processor);

TEST_CASE("app: is visibile")
{
    REQUIRE(app.isVisible() == false);
}

TEST_CASE("app: is not resizable")
{
    REQUIRE(app.isResizable() == false);
}

TEST_CASE("app: keyboard is sub-component") 
{}

TEST_CASE("app: randomize button is sub-component") 
{}

TEST_CASE("app: paints keyboard") 
{}

TEST_CASE("app: paints randomize button") 
{}

TEST_CASE("app: lays out keyboard") 
{}

TEST_CASE("app: lays out randomize button") 
{}

TEST_CASE("app: cleans up sub-components upon destuction") 
{}

