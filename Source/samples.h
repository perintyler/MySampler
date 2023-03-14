// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//   samples.h
//   ~~~~~~~~~
//
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#pragma once

#include <juce_audio_formats/juce_audio_formats.h>

#include "pitch/notes.h"

const double ATTACK = 0.1; // seconds

const double RELEASE = 0.1; // seconds

const double MAX_SAMPLE_LENGTH = 10.0; // seconds

const bool DEBUG_MODE = true; // TODO: make this a Precompiled Variable

juce::SamplerSound* getRandomSamplerSound(Note);
