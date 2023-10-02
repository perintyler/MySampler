/*** Piano960 | sample_categories.cpp ***/

#include <vector>
#include <assert.h>
#include <algorithm>

#include "sound_source.h"

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

SoundSource getNextSoundSource(SoundSource category)
{
    int indexOfNextCategory = static_cast<int>(category) + 1;
    return static_cast<SoundSource>(indexOfNextCategory);
}

std::string sampleCategoryToString(SoundSource category)
{
    assert(category >= SoundSource::NONE && category <= SoundSource::KEYBOARD);
    return CATEGORY_STRINGS.at(static_cast<int>(category));
}

std::set<SoundSource> getAllCategories()
{
    std::set<SoundSource> categories;

    for (SoundSource category = FIRST_CATEGORY
       ; category <= LAST_CATEGORY
       ; category = getNextSoundSource(category)
    ){
        categories.insert(category);
    }

    return categories;
}

SoundSource getSoundSource(std::string categoryAsString)
{
    auto iterator = std::find(CATEGORY_STRINGS.begin(), CATEGORY_STRINGS.end(), categoryAsString);
    if (iterator == CATEGORY_STRINGS.end()) {
        return SoundSource::NONE;
    } else {
        int categoryIndex = iterator - CATEGORY_STRINGS.begin();
        return static_cast<SoundSource>(categoryIndex);
    }
}


