/*** Piano960 | sample_categories.h ***/

#pragma once

#include <set>
#include <string>

// rename to SoundSource

enum class SoundSource: int
{
    NONE=0,
    PIANO,
    CELLO,
    STRINGS,
    TROMBONE,
    BASSOON,
    CLARINET,
    ORGAN,
    OBOE,
    WOODWIND,
    TRUMPET,
    GLOCKENSPIEL,
    SFX,
    MALLET,
    OTHER,
    GUITAR,
    PLUCK,
    WORLD,
    NATURE,
    BRASS,
    BASS,
    VOCAL,
    PAD,
    SAXOPHONE,
    SYNTH,
    TUBA,
    BELL,
    TEXTURE,
    VOILIN,
    HORN,
    ARP,
    FLUTE,
    KEYBOARD,
};

const SoundSource FIRST_SOUND_SOURCE = SoundSource::PIANO;
const SoundSource LAST_SOUND_SOURCE = SoundSource::KEYBOARD;

std::set<SoundSource> getAllSoundSources();

SoundSource getNextSoundSource(SoundSource);

std::string soundSourceToString(SoundSource);

SoundSource getSoundSource(std::string);
