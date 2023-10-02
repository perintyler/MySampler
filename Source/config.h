/*** MySampler | confih.h ***/

#pragma once

#include <string>
#include "notes.h"

// #define NO_LOG // uncomment this line out to turn off logging

const std::string PLUGIN_NAME { "MySampler" };

const Note FIRST_MIDI_NOTE = C2;

const Note LAST_MIDI_NOTE = C8;

const int NUM_KEYS = LAST_MIDI_NOTE - FIRST_MIDI_NOTE + 1;

const double ATTACK = 0.1; // seconds

const double RELEASE = 0.1; // seconds

const double SUSTAIN = 10.0; // seconds

const int NUM_SYNTH_VOICES = 8;
