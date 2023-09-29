/*** Piano960 | sample_categories.cpp ***/

#include <vector>
#include <assert.h>
#include <algorithm>

#include "sample_categories.h"

const std::vector<std::string> CATEGORY_STRINGS {
    "None",
    "Piano",
    "Cello",
    "Trombone",
    "Organ",
    "Woodwind",
    "Trumpet",
    "Glockenspiel",
    "SFX",
    "Guitar",
    "Pluck",
    "World",
    "Brass",
    "Bass",
    "Vocal",
    "Pad",
    "Synth",
    "Bell",
    "Voilin",
    "Arp",
    "Flute",
    "Keyboard"
};

std::string sampleCategoryToString(SampleCategory category)
{
    assert(category >= SampleCategory::NONE && category <= SampleCategory::KEYBOARD);
    return CATEGORY_STRINGS.at(static_cast<int>(category));
}

SampleCategory getSampleCategory(std::string categoryAsString)
{
    auto iterator = std::find(CATEGORY_STRINGS.begin(), CATEGORY_STRINGS.end(), categoryAsString);
    if (iterator == CATEGORY_STRINGS.end()) {
        return SampleCategory::NONE;
    } else {
        int categoryIndex = iterator - CATEGORY_STRINGS.begin();
        return static_cast<SampleCategory>(categoryIndex);
    }
}
