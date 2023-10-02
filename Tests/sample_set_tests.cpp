/*** MySampler | Tests/sample_set_tests.cpp ***/

#include <vector>
#include <string>
#include <filesystem>

#include <catch2/catch_test_macros.hpp>

#include "pitch_detection/pitch_detection.h"
#include "presets.h"
#include "sample_set.h"

TEST_CASE("SampleSet Test #1: length", "[samples][sample_set]")
{
    SampleSet emptySet {};
    REQUIRE(emptySet.length() == 0);

    REQUIRE(getSamplesForPreset("default-preset-1").length() == 4);
    REQUIRE(getSamplesForPreset("default-preset-2").length() == 8);
    REQUIRE(getSamplesForPreset("default-preset-3").length() == 9);
}

TEST_CASE("SampleSet Test #2: has", "[samples][sample_set]")
{
    auto samples = getSamplesForPreset("default-preset-1");

    REQUIRE(!samples.has(0));
    REQUIRE(!samples.has(53));
    REQUIRE(!samples.has(55));
    REQUIRE(!samples.has(90));

    REQUIRE(samples.has(42));
    REQUIRE(samples.has(52));
    REQUIRE(samples.has(54));
    REQUIRE(samples.has(58));
}

TEST_CASE("SampleSet Test #3: get", "[samples][sample_set]")
{
    auto samples = getSamplesForPreset("default-preset-1");

    REQUIRE(samples.get(42).filepath.string() == "/usr/local/include/MySampler/samples/Pad/instrument-oneshots-by-fredricch.pads.pad ~ coast.wav");
    REQUIRE(samples.get(42).rootNote == 60);

    REQUIRE(samples.get(52).filepath.string() == "/usr/local/include/MySampler/samples/Trumpet/instrument-oneshots-by-fredricch.leads.trumpet ~ broken.wav");
    REQUIRE(samples.get(52).rootNote == 65);
}

TEST_CASE("SampleSet Test #4: set", "[samples][sample_set]")
{
    SampleSet samples { };

    Note key = C0;
    std::filesystem::path filepath { "/fake-path" };
    Note rootNote = C1;

    REQUIRE(samples.length() == 0);
    samples.set(key, filepath, rootNote);
    REQUIRE(samples.length() == 1);

    const Sample& sample = samples.get(key);
    REQUIRE(sample.filepath.string() == filepath.string());
    REQUIRE(sample.rootNote == rootNote);

    samples.set(key, filepath, rootNote+1);
    REQUIRE(samples.get(key).rootNote == rootNote+1);
}

TEST_CASE("SampleSet Test #5: as vector", "[samples][sample_set]")
{
    std::vector<std::string> defaultPresetNames = {"default-preset-1", "default-preset-2", "default-preset-3"};
    
    for (const std::string& presetName : defaultPresetNames) {
        auto samples = getSamplesForPreset(presetName);

        for (const auto& [note, sample] : samples.asVector()) {
            REQUIRE(samples.get(note).name     == sample.name);
            REQUIRE(samples.get(note).filepath == sample.filepath);
            REQUIRE(samples.get(note).rootNote == sample.rootNote);
        }
    }
}

TEST_CASE("SampleSet Test #6: filter", "[samples][sample_set]")
{
    REQUIRE(
        getSamplesForPreset("default-preset-1")
       .filter([](Note, Sample sample){ return sample.rootNote > 50; })
       .length() == 3
    );

    REQUIRE(
        getSamplesForPreset("default-preset-1")
       .filter([](Note note, Sample){ return note > 55; })
       .length() == 1
    );
}

TEST_CASE("SampleSet Test #6: filter in place", "[samples][sample_set]")
{
    SampleSet samples { };
    samples.set(1, std::filesystem::path{}, 10);
    samples.set(2, std::filesystem::path{}, 20);
    samples.set(3, std::filesystem::path{}, 30);

    REQUIRE(samples.length() == 3);

    samples.filterInPlace([](Note note, const Sample& sample){
        return note == 1 || sample.rootNote == 30;
    });

    REQUIRE(samples.length() == 2);
    REQUIRE(samples.has(1));
    REQUIRE(!samples.has(2));
    REQUIRE(samples.has(3));
}
