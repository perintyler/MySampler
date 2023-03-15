/*** Piano960 | confih.h ***/

#pragma once

#include "pitch/notes.h"

const Note FIRST_MIDI_NOTE = C2;

const Note LAST_MIDI_NOTE = C8;

const int NUM_KEYS = LAST_MIDI_NOTE - FIRST_MIDI_NOTE + 1;

const double ATTACK = 0.1; // seconds

const double RELEASE = 0.1; // seconds

const double SUSTAIN = 10.0; // seconds
