// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//   samples.h
//   ~~~~~~~~~
//
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#pragma once

#include <memory>

#include "pitch/notes.h"

/***
 ** A locally installed audio file
 ***/
struct Sample 
{
  std::string name;
  std::filesystem::path filepath;
  MidiNumber rootNote;
}

/***
 ** A collection of audio files used by a `RandomSampler`. Each sample corresponds 
 ** to a midi note.
 ***/
class SampleSet: private std::unordered_map<MidiNote, Sample>
{
public:
  Sample get(MidiNote note) const;

  void set(MidiNote key, std::filesystem::path, MidiNumber rootNote);

  std::vector<std::pair<MidiNumber, Sample>> asVector();
}

/***
 ** A synthesizer that generates a sound source for each key using a different 
 ** random sample from Piano960's installed sample set. A key's sample can be
 ** locked/unlocked (using the `lockKey` and `unlockKey` functions), meaning the
 ** key's sound source won't be re-randomized every time `RandomSampler::randomize` 
 ** is called.
 ***/
class RandomSampler
{
public:
    juce::Synthesiser synthesiser; // make this private

    RandomSampler(MidiNumber firstNote, MidiNumber lastNote);

    bool isKeyLocked(MidiNumber);

    void lockKey(MidiNumber);

    void unlockKey(MidiNumber);

    Sample& getSample(MidiNumber) const;

    void randomize();

    bool isReady();

private:
    MidiNumber firstNote;
    MidiNumber lastNote;
    SampleSet samples {};
    std::map<Note, bool> lockedKeys {};
}