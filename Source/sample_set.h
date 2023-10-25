/*** MySampler | Source/sample_set.h ***/

#pragma once

#include <map>
#include <filesystem>
#include <string>
#include <functional>
#include <vector>
#include <juce_audio_formats/juce_audio_formats.h>

#include "notes.h"
#include "sample.h"

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
