/* editor_tests.cpp */

#include <catch2/catch_test_macros.hpp>
#include <juce_graphics/juce_graphics.h>

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
    REQUIRE(app.findChildWithID("keyboard")->isVisible());
}

TEST_CASE_METHOD(AppTestFixture, "app: paints randomize button") 
{
    REQUIRE(app.findChildWithID("randomize-button")->isVisible());
}

TEST_CASE_METHOD(AppTestFixture, "app: keyboard has size") 
{
    auto bounds = app.findChildWithID("keyboard")->getBounds();
    REQUIRE(bounds.getWidth() * bounds.getHeight() > 0);
}

TEST_CASE_METHOD(AppTestFixture, "app: randomize button has size") 
{
    auto bounds = app.findChildWithID("randomize-button")->getBounds();
    REQUIRE(bounds.getWidth() * bounds.getHeight() > 0);
}

TEST_CASE_METHOD(AppTestFixture, "app: cleans up sub-components upon destuction") 
{}