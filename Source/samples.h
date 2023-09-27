// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//   samples.h
//   ~~~~~~~~~
//
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#pragma once

#include <memory>
#include <map>
#include <filesystem>
#include <juce_audio_devices/juce_audio_devices.h>

#include "pitch/notes.h"

/***
 ** A locally installed audio file
 ***/
struct Sample 
{
  std::string name;
  std::filesystem::path filepath;
  Note rootNote;
};

/***
 ** A collection of audio files used by a `RandomSampler`. Each sample corresponds 
 ** to a midi note.
 ***/
class SampleSet: private std::unordered_map<Note, Sample>
{
public:

  SampleSet(): std::unordered_map<Note, Sample>() {}

  const Sample& get(Note) const;

  void set(Note key, std::filesystem::path, Note rootNote);

  std::vector<std::pair<Note, const Sample&>> asVector() const;
};

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

    RandomSampler();

    bool isKeyLocked(Note) const;

    void lockKey(Note);

    void unlockKey(Note);

    const Sample& getSample(Note) const;

    void randomize();

    bool isReady();

private:
    Note firstNote;
    Note lastNote;
    SampleSet samples {};
    std::map<Note, bool> lockedKeys {};
};