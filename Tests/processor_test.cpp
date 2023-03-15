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

#include "audio_processor.h"
#include "config.h"
#include "samples.h"
#include "pitch/pitch.h"

TEST_CASE("processor: Name", "[processor]")
{
    auto processor = AudioProcessor {};
    REQUIRE(processor.getName() == juce::String {"Piano960"});
}

TEST_CASE("processor: HasEditor", "[processor]")
{
    auto processor = AudioProcessor {};
    REQUIRE(processor.hasEditor() == true);
}

TEST_CASE("processor: CurrentProgram", "[processor]")
{
    auto processor = AudioProcessor {};
    REQUIRE(processor.getCurrentProgram() == 0);
}

TEST_CASE("processor: NumPrograms", "[processor]")
{
    auto processor = AudioProcessor {};
    REQUIRE(processor.getNumPrograms() == 1);
}

TEST_CASE("processor: AcceptsMidi", "[processor]")
{
    auto processor = AudioProcessor {};
    REQUIRE(processor.acceptsMidi() == true);
}

TEST_CASE("processor: ProducesMidi", "[demo][processor]")
{
    auto processor = AudioProcessor {};
    REQUIRE(processor.producesMidi() == false);
}

TEST_CASE("processor: IsMidiEffect", "[processor]")
{
    auto processor = AudioProcessor {};
    REQUIRE(processor.isMidiEffect() == false);
}

TEST_CASE("processor: TailLength", "[processor]")
{
    auto processor = AudioProcessor {};
    REQUIRE(processor.getTailLengthSeconds() == 0.0);
}

TEST_CASE("processor: BusesLayoutSupportMono", "[processor]")
{
    auto processor     = AudioProcessor {};
    auto layout        = juce::AudioProcessor::BusesLayout {};
    layout.inputBuses  = juce::AudioChannelSet::mono();
    layout.outputBuses = juce::AudioChannelSet::mono();

    REQUIRE(processor.isBusesLayoutSupported(layout) == true);
}

TEST_CASE("processor: BusesLayoutSupportStereo", "[processor]")
{
    auto processor     = AudioProcessor {};
    auto layout        = juce::AudioProcessor::BusesLayout {};
    layout.inputBuses  = juce::AudioChannelSet::stereo();
    layout.outputBuses = juce::AudioChannelSet::stereo();

    REQUIRE(processor.isBusesLayoutSupported(layout) == true);
}

TEST_CASE("processor: BusesLayoutSupportInvalid", "[processor]")
{
    auto processor     = AudioProcessor {};
    auto layout        = juce::AudioProcessor::BusesLayout {};
    layout.inputBuses  = juce::AudioChannelSet::mono();
    layout.outputBuses = juce::AudioChannelSet::stereo();

    REQUIRE(processor.isBusesLayoutSupported(layout) == false);
}

TEST_CASE("get random sampler sound", "[processor]")
{
    int C3 = 48;
    REQUIRE(getRandomSamplerSound(C3));
}

TEST_CASE("processor: randomize samples", "[processor]")
{
    auto processor = AudioProcessor {};
    processor.randomizeSamples();
    REQUIRE(processor.getSampleNames().size() == NUM_KEYS);
}

