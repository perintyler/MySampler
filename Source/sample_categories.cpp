/*** Piano960 | sample_categories.cpp ***/

#include <assert.h>

#include "sample_categories.h"

const std::vector<std::string> CATEGORY_STRINGS
{
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
    return CATEGORY_STRINGS.at(category);
}

SampleCategory getSampleCategory(std::string name)
{
    auto iterator = CATEGORY_STRINGS.find(CATEGORY_STRINGS.start(), CATEGORY_STRINGS.end(), name);
    assert(iterator != CATEGORY_STRINGS.end());
    int categoryIndex = iterator - CATEGORY_STRINGS.begin();
    return static_cast<SampleCategory>(categoryIndex);
}
