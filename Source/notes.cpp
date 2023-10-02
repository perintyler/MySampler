/*** Piano960 | pitch_detection/notes.cpp ***/

#include "notes.h"

const int NUM_SEMITONES = 12;

const std::string SEMITONE_STRINGS[] = { "C", "D#", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B" };

const Semitone BLACK_KEYS[5] { Db, Eb, Gb, Ab, Bb };

Semitone getSemitone(Note note)
{
    return Semitone((note - C0) % NUM_SEMITONES);
}

bool isBlackKey(Semitone semitone)
{
    return std::find(std::begin(BLACK_KEYS), std::end(BLACK_KEYS), semitone) != std::end(BLACK_KEYS);
}

bool isBlackKey(Note note)
{
    return isBlackKey(getSemitone(note));
}

std::string getSemitoneString(Semitone semitone)
{
    int semitoneIndex = static_cast<int>(semitone);
    assert(semitoneIndex > 0 && semitoneIndex < 12);
    return SEMITONE_STRINGS[semitoneIndex];
}

