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

const SoundSource FIRST_SOUND_SOURCE = SoundSource::PIANO;
const SoundSource LAST_SOUND_SOURCE = SoundSource::KEYBOARD;

std::set<SoundSource> getAllSoundSources();

SoundSource getNextSoundSource(SoundSource);

std::string soundSourceToString(SoundSource);

SoundSource getSoundSource(std::string);
