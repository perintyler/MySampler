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
