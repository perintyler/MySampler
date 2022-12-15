// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - Piano960 | VST3, AU - - - - - - - - - - - - - - - - - - - -
// - - Created by Tyler Perin  - - - - - - - - - - - - - - - - - -
// - - Copyright © 2022 Sound Voyager. All rights reserved.- - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//   processor_test.cpp
//   ~~~~~~~~~~~~~~~~~~
//
// This file contains unit tests for the `PitchDetection`
// translation unit.
//
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#include <catch2/catch_test_macros.hpp>

#include "plugin_processor.h"

TEST_CASE("processor: Name", "[demo][processor]")
{
    auto processor = Piano960Processor {};
    REQUIRE(processor.getName() == juce::String {"Piano960"});
}

TEST_CASE("processor: HasEditor", "[demo][processor]")
{
    auto processor = Piano960Processor {};
    REQUIRE(processor.hasEditor() == true);
}

TEST_CASE("processor: CurrentProgram", "[demo][processor]")
{
    auto processor = Piano960Processor {};
    REQUIRE(processor.getCurrentProgram() == 0);
    // REQUIRE(processor.getProgramName(1) == juce::String {});
}

TEST_CASE("processor: NumPrograms", "[demo][processor]")
{
    auto processor = Piano960Processor {};
    REQUIRE(processor.getNumPrograms() == 1);
}

TEST_CASE("processor: AcceptsMidi", "[demo][processor]")
{
    auto processor = Piano960Processor {};
    REQUIRE(processor.acceptsMidi() == true);
}

TEST_CASE("processor: ProducesMidi", "[demo][processor]")
{
    auto processor = Piano960Processor {};
    REQUIRE(processor.producesMidi() == false);
}

TEST_CASE("processor: IsMidiEffect", "[demo][processor]")
{
    auto processor = Piano960Processor {};
    REQUIRE(processor.isMidiEffect() == false);
}

TEST_CASE("processor: TailLength", "[demo][processor]")
{
    auto processor = Piano960Processor {};
    REQUIRE(processor.getTailLengthSeconds() == 0.0);
}

TEST_CASE("processor: BusesLayoutSupportMono", "[demo][processor]")
{
    auto processor     = Piano960Processor {};
    auto layout        = juce::AudioProcessor::BusesLayout {};
    layout.inputBuses  = juce::AudioChannelSet::mono();
    layout.outputBuses = juce::AudioChannelSet::mono();

    REQUIRE(processor.isBusesLayoutSupported(layout) == true);
}

TEST_CASE("processor: BusesLayoutSupportStereo", "[demo][processor]")
{
    auto processor     = Piano960Processor {};
    auto layout        = juce::AudioProcessor::BusesLayout {};
    layout.inputBuses  = juce::AudioChannelSet::stereo();
    layout.outputBuses = juce::AudioChannelSet::stereo();

    REQUIRE(processor.isBusesLayoutSupported(layout) == true);
}

TEST_CASE("processor: BusesLayoutSupportInvalid", "[demo][processor]")
{
    auto processor     = Piano960Processor {};
    auto layout        = juce::AudioProcessor::BusesLayout {};
    layout.inputBuses  = juce::AudioChannelSet::mono();
    layout.outputBuses = juce::AudioChannelSet::stereo();

    REQUIRE(processor.isBusesLayoutSupported(layout) == false);
}
