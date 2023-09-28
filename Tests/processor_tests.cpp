/*** Piano960 Tests | processor_tests.cpp ***/

#include <catch2/catch_test_macros.hpp>

#include "audio_processor.h"
#include "config.h"
#include "samples.h"
#include "pitch_detection/pitch.h"

TEST_CASE("Processor Test #1: Name", "[processor]")
{
    auto processor = AudioProcessor {};
    REQUIRE(processor.getName() == juce::String {"Piano960"});
}

TEST_CASE("Processor Test #2: HasEditor", "[processor]")
{
    auto processor = AudioProcessor {};
    REQUIRE(processor.hasEditor() == true);
}

TEST_CASE("Processor Test #3: CurrentProgram", "[processor]")
{
    auto processor = AudioProcessor {};
    REQUIRE(processor.getCurrentProgram() == 0);
}

TEST_CASE("Processor Test #4: NumPrograms", "[processor]")
{
    auto processor = AudioProcessor {};
    REQUIRE(processor.getNumPrograms() == 1);
}

TEST_CASE("Processor Test #5: AcceptsMidi", "[processor]")
{
    auto processor = AudioProcessor {};
    REQUIRE(processor.acceptsMidi() == true);
}

TEST_CASE("Processor Test #6: ProducesMidi", "[demo][processor]")
{
    auto processor = AudioProcessor {};
    REQUIRE(processor.producesMidi() == false);
}

TEST_CASE("Processor Test #7: IsMidiEffect", "[processor]")
{
    auto processor = AudioProcessor {};
    REQUIRE(processor.isMidiEffect() == false);
}

TEST_CASE("Processor Test #8: TailLength", "[processor]")
{
    auto processor = AudioProcessor {};
    REQUIRE(processor.getTailLengthSeconds() == 0.0);
}

TEST_CASE("Processor Test #9: BusesLayoutSupportMono", "[processor]")
{
    auto processor     = AudioProcessor {};
    auto layout        = juce::AudioProcessor::BusesLayout {};
    layout.inputBuses  = juce::AudioChannelSet::mono();
    layout.outputBuses = juce::AudioChannelSet::mono();

    REQUIRE(processor.isBusesLayoutSupported(layout) == true);
}

TEST_CASE("Processor Test #10: BusesLayoutSupportStereo", "[processor]")
{
    auto processor     = AudioProcessor {};
    auto layout        = juce::AudioProcessor::BusesLayout {};
    layout.inputBuses  = juce::AudioChannelSet::stereo();
    layout.outputBuses = juce::AudioChannelSet::stereo();

    REQUIRE(processor.isBusesLayoutSupported(layout) == true);
}

TEST_CASE("Processor Test #11: BusesLayoutSupportInvalid", "[processor]")
{
    auto processor     = AudioProcessor {};
    auto layout        = juce::AudioProcessor::BusesLayout {};
    layout.inputBuses  = juce::AudioChannelSet::mono();
    layout.outputBuses = juce::AudioChannelSet::stereo();

    REQUIRE(processor.isBusesLayoutSupported(layout) == false);
}

