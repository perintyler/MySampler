/* main_test.cpp */

#define CATCH_CONFIG_RUNNER
#include "<catch2/catch.hpp>"
#include "<juce_events/juce_events.h>"

int main(int argc, char* argv[])
{
    juce::initialiseJuce_GUI();
    int result = Catch::Session().run(argc, argv);
    juce::shutdownJuce_GUI();
    return result;
}
