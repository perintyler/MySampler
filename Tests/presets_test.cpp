/*** Piano960 Tests | presets_test.cpp ***/

#include "presets.h"
#include "pitch/notes.h"

TEST_CASE("presets: get all preset names")
{
  std::vector<std::string> expectedPresetNames { "default #1", "default #2", "default #3" };
  std::vector<std::string> actualPresetNames = getPresetNames();

  for (const std::string& presetName : expectedPresetNames)
    REQUIRE(actualPresetNames.count(presetName) == 1);
}

TEST_CASE("presets: get preset")
{}

TEST_CASE("presets: add/delete preset")
{}