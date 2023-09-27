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
  Note rootNote;
}

/***
 ** A collection of audio files used by a `RandomSampler`. Each sample corresponds 
 ** to a midi note.
 ***/
class SampleSet: private std::unordered_map<Note, Sample>
{
public:
  Sample get(Note note) const;

  void set(Note key, std::filesystem::path, Note rootNote);

  std::vector<std::pair<Note, Sample>> asVector();
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

    RandomSampler(Note firstNote, Note lastNote);

    bool isKeyLocked(Note);

    void lockKey(Note);

    void unlockKey(Note);

    Sample& getSample(Note) const;

    void randomize();

    bool isReady();

private:
    Note firstNote;
    Note lastNote;
    SampleSet samples {};
    std::map<Note, bool> lockedKeys {};
}