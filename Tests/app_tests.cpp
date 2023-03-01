/* editor_tests.cpp */

#include <catch2/catch_test_macros.hpp>

#include "audio_processor.h"
#include "app.h"

class AppTestFixture {
public:
     AppFixture()
        : processor ()
        , app (processor) 
     {}

private:
    AudioProcessor processor;

protected:
   App app;

 };

TEST_CASE_METHOD(AppTestFixture, "app: is visibile")
{
    REQUIRE(app.isVisible() == false);
}

TEST_CASE_METHOD(AppTestFixture, "app: is not resizable")
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

