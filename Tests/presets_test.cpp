/*** Piano960 Tests | presets_test.cpp ***/

#include <algorithm>

#include <catch2/catch_test_macros.hpp>

#include "presets.h"
#include "pitch/notes.h"

TEST_CASE("presets: get all preset names")
{
  std::vector<std::string> expected { "default-1", "default-2", "default-3" };
  std::vector<std::string> acutal= getPresetNames();

  for (const std::string& presetName : expected)
    REQUIRE(std::find(acutal.begin(), acutal.end(), presetName) != acutal.end());
}

TEST_CASE("presets: get preset")
{}

TEST_CASE("presets: add/delete preset")
{}