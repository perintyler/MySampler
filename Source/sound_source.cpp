/*** Piano960 | sample_categories.cpp ***/

#include <vector>
#include <assert.h>
#include <algorithm>

#include "sound_source.h"

const std::vector<std::string> SOUND_SOURCE_STRINGS {
    "None",
    "Piano",
    "Cello",
    "Strings",
    "Trombone",
    "Bassoon",
    "Clarinet",
    "Organ",
    "Oboe",
    "Woodwind",
    "Trumpet",
    "Glockenspiel",
    "SFX",
    "Mallet",
    "Other",
    "Guitar",
    "Pluck",
    "World",
    "Nature",
    "Brass",
    "Bass",
    "Vocal",
    "Pad",
    "Saxophone",
    "Synth",
    "Tuba",
    "Bell",
    "Texture",
    "Voilin",
    "Horn",
    "Arp",
    "Flute",
    "Keyboard",
};

SoundSource getNextSoundSource(SoundSource soundsource)
{
    int indexOfNextCategory = static_cast<int>(soundsource) + 1;
    return static_cast<SoundSource>(indexOfNextCategory);
}

std::string soundSourceToString(SoundSource soundsource)
{
    assert(soundsource >= SoundSource::NONE && soundsource <= SoundSource::KEYBOARD);
    return SOUND_SOURCE_STRINGS.at(static_cast<int>(soundsource));
}

std::set<SoundSource> getAllSoundSources()
{
    std::set<SoundSource> categories;

    for (SoundSource soundsource = FIRST_SOUND_SOURCE
       ; soundsource <= LAST_SOUND_SOURCE
       ; soundsource = getNextSoundSource(soundsource)
    ){
        categories.insert(soundsource);
    }

    return categories;
}

SoundSource getSoundSource(std::string soundsourceAsString)
{
    auto iterator = std::find(SOUND_SOURCE_STRINGS.begin(), SOUND_SOURCE_STRINGS.end(), soundsourceAsString);
    if (iterator == SOUND_SOURCE_STRINGS.end()) {
        return SoundSource::NONE;
    } else {
        int soundsourceIndex = static_cast<int>(iterator - SOUND_SOURCE_STRINGS.begin());
        return static_cast<SoundSource>(soundsourceIndex);
    }
}


