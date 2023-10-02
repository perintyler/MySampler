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
#include <string>

#include <juce_audio_devices/juce_audio_devices.h>

#include "notes.h"

/***
 ** A locally installed audio file
 ***/
struct Sample 
{
  std::string name;
  std::filesystem::path filepath;
  Note rootNote;

  void pretty_print() const;
};

using NoteAndSample = std::pair<Note, const Sample&>;

using SampleFilterFunction = std::function<bool(Note, const Sample&)>;

/***
 ** A collection of audio files used by a `RandomSampler`. Each sample corresponds 
 ** to a midi note.
 ***/
class SampleSet: protected std::map<Note, Sample>
{
public:

  SampleSet(): std::map<Note, Sample>() {}

  const Sample& get(Note) const;

  bool has(Note) const;

  void set(Note key, std::filesystem::path, Note rootNote);

  int length() const;

  SampleSet filter(SampleFilterFunction) const;

  void filterInPlace(SampleFilterFunction);

  std::vector<NoteAndSample> asVector() const;

  using std::map<Note, Sample>::begin;
  using std::map<Note, Sample>::end;
  using std::map<Note, Sample>::empty;
  using std::map<Note, Sample>::clear;
  using std::map<Note, Sample>::value_type;
  // using std::map<Note, Sample>::size;

  void pretty_print() const;
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

    void randomize(bool pitch_shift = true);

    bool isReady() const;

    const SampleSet& getAllSamples() const;

    const SampleSet getLockedSamples() const;

    void setSamples(const SampleSet&);

private:
    Note firstNote;
    Note lastNote;
    SampleSet samples {};
    std::map<Note, bool> lockedKeys {};
};