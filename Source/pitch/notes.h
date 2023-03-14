/*** pitch/notes.h ***/

#pragma once

#include <string>

using NoteID = int; // MIDI Number

const int OCTAVE_SIZE = 12;

const NoteID B0 = 11;

const NoteID C0 = 12;

const NoteID G0 = 19;

const NoteID C1 = C0 + 1*OCTAVE_SIZE;

const NoteID C2 = C0 + 2*OCTAVE_SIZE;

const NoteID C3 = C0 + 3*OCTAVE_SIZE;

const NoteID C4 = C0 + 4*OCTAVE_SIZE;

const NoteID C5 = C0 + 5*OCTAVE_SIZE;

const NoteID C7 = C0 + 6*OCTAVE_SIZE;

const NoteID B8 = B0 + 7*OCTAVE_SIZE;

const NoteID C8 = C0 + 7*OCTAVE_SIZE;

const NoteID G8 = G0 + 7*OCTAVE_SIZE;

NoteID matchNoteToFrequency(float frequency);

bool isValidNote(float frequency);

bool isBlackNote(NoteID);
