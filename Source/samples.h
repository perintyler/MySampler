// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//   samples.h
//   ~~~~~~~~~
//
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#pragma once

#include <juce_audio_formats/juce_audio_formats.h>

#include "pitch_detection.h"
#include "midi.h"

const double ATTACK = 0.1; // seconds

const double RELEASE = 0.1; // seconds

const double MAX_SAMPLE_LENGTH = 10.0; // seconds

const int MAX_TRANSPOSITION_SIZE = 3*midi::OCTAVE_SIZE;

const bool DEBUG_MODE = true; // TODO: make this a Precompiled Variable

juce::SamplerSound* getRandomSamplerSound(int keyNumber);
