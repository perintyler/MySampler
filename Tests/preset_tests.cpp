/*** Piano960 Tests | presets_test.cpp ***/

#include <algorithm>

#include <catch2/catch_test_macros.hpp>

#include "presets.h"
#include "pitch_detection/notes.h"

TEST_CASE("Preset Test #1: get all preset names", "[presets]")
{
  std::vector<std::string> expected { "test-preset-1", "test-preset-2", "test-preset-3" };
  std::vector<std::string> acutal= getPresetNames();

  for (const std::string& presetName : expected)
    REQUIRE(std::find(acutal.begin(), acutal.end(), presetName) != acutal.end());
}

TEST_CASE("Preset Test #2: get preset", "[presets]")
{

}

TEST_CASE("Preset Test #3: add/delete preset", "[presets]")
{}
