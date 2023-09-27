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
