/*** pitch/semitones.h ***/

#pragma once

#include <string>

#include "notes.h"

enum Semitone { C=0, Db, D, Eb, E, F, Gb, G, Ab, A, Bb, B };

constexpr Semitone Csharp = Db;
constexpr Semitone Dsharp = Eb;
constexpr Semitone Fsharp = Gb;
constexpr Semitone Gsharp = Ab;
constexpr Semitone Asharp = Bb;

Semitone getSemitone(Note);

Semitone getSemitone(float frequency);

std::string getSemitoneString(Semitone);
