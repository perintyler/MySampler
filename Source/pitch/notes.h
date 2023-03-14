/*** pitch/notes.h ***/

#pragma once

#include <string>

using Note = int; // MIDI Number

const int OCTAVE_SIZE = 12;

const Note B0 = 11;

const Note C0 = 12;

const Note G0 = 19;

const Note C1 = C0 + 1*OCTAVE_SIZE;

const Note C2 = C0 + 2*OCTAVE_SIZE;

const Note C3 = C0 + 3*OCTAVE_SIZE;

const Note C4 = C0 + 4*OCTAVE_SIZE;

const Note C5 = C0 + 5*OCTAVE_SIZE;

const Note C7 = C0 + 6*OCTAVE_SIZE;

const Note B8 = B0 + 7*OCTAVE_SIZE;

const Note C8 = C0 + 7*OCTAVE_SIZE;

const Note G8 = G0 + 7*OCTAVE_SIZE;

Note matchNoteToFrequency(float frequency);

bool isValidNote(float frequency);

bool isBlackNote(Note);
