/*** MySampler | confih.h ***/

#pragma once

#include <set>
#include <string>

#include "notes.h"
#include "sound_source.h"

// #define NO_LOG // uncomment this line out to turn off logging

const std::string PLUGIN_NAME { "MySampler" };

const Note FIRST_MIDI_NOTE = C1;

const Note LAST_MIDI_NOTE = C6;

const int NUM_KEYS = LAST_MIDI_NOTE - FIRST_MIDI_NOTE + 1;

const double ATTACK = 0.1; // seconds

const double RELEASE = 0.1; // seconds

const double SUSTAIN = 10.0; // seconds

const int NUM_SYNTH_VOICES = 8;

const bool DOUBLE_CHECK_PITCH_DETECTION=false;

const std::set<SoundSource> DEFAULT_SOUND_SOURCES = { // these will all be ON at startup
    SoundSource::PIANO,
    SoundSource::VOCAL,
    SoundSource::GUITAR,
    SoundSource::WORLD,
    SoundSource::KEYBOARD,
    SoundSource::SYNTH
};

