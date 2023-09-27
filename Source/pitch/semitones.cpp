/*** pitch/semitones.cpp ***/

#include <assert.h>

#include "semitones.h"
#include "notes.h"

const int NUM_SEMITONES = 12;

const std::string SEMITONE_STRINGS[] = { "C", "D#", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B" };

Semitone getSemitone(float frequency)
{
    int semitoneNumber = matchNoteToFrequency(frequency) % OCTAVE_SIZE;
    assert(0 <= semitoneNumber);
    assert(semitoneNumber < OCTAVE_SIZE);
    return Semitone(semitoneNumber);
}

Semitone getSemitone(Note note)
{
    return Semitone((note - C0) % NUM_SEMITONES);
}

std::string getSemitoneString(Semitone semitone)
{
    int semitoneIndex = static_cast<int>(semitone);
    assert(semitoneIndex > 0 && semitoneIndex < 12);
    return SEMITONE_STRINGS[semitoneIndex];
}

