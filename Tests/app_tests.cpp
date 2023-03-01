/* editor_tests.cpp */

#include <catch2/catch_test_macros.hpp>

#include "audio_processor.h"
#include "app.h"

class AppTestFixture {
public:
     AppTestFixture()
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

TEST_CASE_METHOD(AppTestFixture, "app: is unclipped")
{
    REQUIRE(app.isPaintingUnclipped() == true);
}

TEST_CASE_METHOD(AppTestFixture, "app: is not resizable")
{
    REQUIRE(app.isResizable() == false);
}

TEST_CASE_METHOD(AppTestFixture, "app: has size")
{
    REQUIRE(app.getBounds().getWidth() * app.getBounds().getHeight() > 0);
}

TEST_CASE_METHOD(AppTestFixture, "app: keyboard is sub-component") 
{
    REQUIRE(app.findChildWithID("keyboard") != nullptr);
}

TEST_CASE_METHOD(AppTestFixture, "app: randomize button is sub-component") 
{
    REQUIRE(app.findChildWithID("randomize-button") != nullptr);
}

TEST_CASE_METHOD(AppTestFixture, "app: paints keyboard") 
{
    REQUIRE(app.findChildWithID("keyboard").isShowing());
}

TEST_CASE_METHOD(AppTestFixture, "app: paints randomize button") 
{
    REQUIRE(app.findChildWithID("randomize-button").isShowing());
}

TEST_CASE_METHOD(AppTestFixture, "app: lays out keyboard") 
{
    auto bounds = app.findChildWithID("keyboard").getBounds();
    REQUIRE(bounds.getWidth() * bounds.getHeight() > 600);
}

TEST_CASE_METHOD(AppTestFixture, "app: lays out randomize button") 
{}

TEST_CASE_METHOD(AppTestFixture, "app: cleans up sub-components upon destuction") 
{}