/*** Piano960 Tests | presets_test.cpp ***/

#include <algorithm>
#include <filesystem>

#include <catch2/catch_test_macros.hpp>

#include "pitch_detection/notes.h"
#include "presets.h"

const std::vector<std::string> DEFAULT_PRESET_NAMES = { "default-preset-1", "default-preset-2", "default-preset-3" };

TEST_CASE("Preset Test #1: get all preset names", "[presets]")
{
    std::vector<std::string> actualNames = getPresetNames();

    for (const std::string& expectedName : DEFAULT_PRESET_NAMES) {
        REQUIRE(std::find(actualNames.begin(), actualNames.end(), expectedName) != actualNames.end());
    }
}

TEST_CASE("Preset Test #2: get preset", "[presets]")
{
    for (const std::string& presetName : DEFAULT_PRESET_NAMES) {
        SampleSet samples = getSamplesForPreset(presetName);
        REQUIRE(!samples.empty());

        for (const auto& [note, sample] : samples) {
            REQUIRE(isValidNote(note));
            REQUIRE(isValidNote(sample.rootNote));
            REQUIRE(std::filesystem::exists(sample.filepath));
        }
    }
}

TEST_CASE("Preset Test #3: add/delete preset", "[presets]")
{}
