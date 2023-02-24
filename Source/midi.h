/* midi.h */

#pragma once

namespace midi {

    enum Semitone { C, Db, D, Eb, E, F, Gb, G, Ab, A, Bb, B };
        
    constexpr Semitone Csharp = Db;
    constexpr Semitone Dsharp = Eb;
    constexpr Semitone Fsharp = Gb;
    constexpr Semitone Gsharp = Ab;
    constexpr Semitone Asharp = Bb;

    using MidiNumber = int; // TODO: replace ints with these

    const int OCTAVE_SIZE = 12;
    
    const MidiNumber B0 = 23;
    
    const MidiNumber C0 = 24;
    
    const MidiNumber G0 = 31;
    
    const MidiNumber C1 = C0 + 1*OCTAVE_SIZE;

    const MidiNumber C2 = C0 + 2*OCTAVE_SIZE;

    const MidiNumber C3 = C0 + 3*OCTAVE_SIZE;

    const MidiNumber C4 = C0 + 4*OCTAVE_SIZE;
    
    const MidiNumber C5 = C0 + 5*OCTAVE_SIZE;
    
    const MidiNumber C7 = C0 + 6*OCTAVE_SIZE;

    const MidiNumber B8 = B0 + 7*OCTAVE_SIZE;

    const MidiNumber C8 = C0 + 7*OCTAVE_SIZE;

    const MidiNumber G8 = G0 + 7*OCTAVE_SIZE;

    bool isBlackNote(MidiNumber);
    
    Semitone getSemitone(float frequency);

    float getFrequency(MidiNumber);

    int getMidiNumber(float frequency);

} // piano namespace
