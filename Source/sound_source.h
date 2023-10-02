/*** Piano960 | sample_categories.h ***/

#pragma once

#include <set>
#include <string>

// rename to SoundSource

enum class SoundSource: int
{
    NONE = 0,
    PIANO,
    CELLO,
    TROMBONE,
    ORGAN,
    WOODWIND,
    TRUMPET,
    GLOCKENSPIEL,
    SFX,
    GUITAR,
    PLUCK,
    WORLD,
    BRASS,
    BASS,
    VOCAL,
    PAD,
    SYNTH,
    BELL,
    VOILIN,
    ARP,
    FLUTE,
    KEYBOARD
};

const SoundSource FIRST_CATEGORY = SoundSource::PIANO;
const SoundSource LAST_CATEGORY = SoundSource::KEYBOARD;

std::set<SoundSource> getAllCategories();

SoundSource getNextSoundSource(SoundSource);

std::string sampleCategoryToString(SoundSource);

SoundSource getSoundSource(std::string);
