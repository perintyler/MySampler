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
    REQUIRE(app.isVisible() == true);
}


TEST_CASE_METHOD(AppTestFixture, "app: is showing")
{
    REQUIRE(app.isShowing() == true);
}

TEST_CASE_METHOD(AppTestFixture, "app: is not resizable")
{
    REQUIRE(app.isResizable() == false);
}

TEST_CASE_METHOD(AppTestFixture, "app: keyboard is sub-component") 
{}

TEST_CASE_METHOD(AppTestFixture, "app: randomize button is sub-component") 
{}

TEST_CASE_METHOD(AppTestFixture, "app: paints keyboard") 
{}

TEST_CASE_METHOD(AppTestFixture, "app: paints randomize button") 
{}

TEST_CASE_METHOD(AppTestFixture, "app: lays out keyboard") 
{}

TEST_CASE_METHOD(AppTestFixture, "app: lays out randomize button") 
{}

TEST_CASE_METHOD(AppTestFixture, "app: cleans up sub-components upon destuction") 
{}