/*** Piano960 | sample_categories.h ***/

#pragma once

#include <string>

enum class SampleCategory
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

std::string sampleCategoryToString(SampleCategory);

SampleCategory getSampleCategory(std::string);
