/*** pitch_detection/notes.h ***/

#pragma once

#include <assert.h>
#include <string>

const int OCTAVE_SIZE = 12;

enum Semitone { C=0, Db, D, Eb, E, F, Gb, G, Ab, A, Bb, B };

constexpr Semitone Csharp = Db;
constexpr Semitone Dsharp = Eb;
constexpr Semitone Fsharp = Gb;
constexpr Semitone Gsharp = Ab;
constexpr Semitone Asharp = Bb;

using Note = int; // MIDI Number

const Note B0 = 11;
const Note C0 = 12;
const Note G0 = 19;
const Note C1 = C0 + 1*OCTAVE_SIZE;
const Note C2 = C0 + 2*OCTAVE_SIZE;
const Note C3 = C0 + 3*OCTAVE_SIZE;
const Note C4 = C0 + 4*OCTAVE_SIZE;
const Note C5 = C0 + 5*OCTAVE_SIZE;
const Note C6 = C0 + 6*OCTAVE_SIZE;
const Note C7 = C0 + 7*OCTAVE_SIZE;
const Note B8 = B0 + 7*OCTAVE_SIZE;
const Note C8 = C0 + 7*OCTAVE_SIZE;
const Note G8 = G0 + 7*OCTAVE_SIZE;

Semitone getSemitone(float frequency);

Semitone getSemitone(Note);

bool isBlackKey(Semitone);

bool isBlackKey(Note);

std::string getSemitoneString(Semitone);
