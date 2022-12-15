// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - Piano960 | VST3, AU - - - - - - - - - - - - - - - - - - - -
// - - Created by Tyler Perin  - - - - - - - - - - - - - - - - - -
// - - Copyright © 2022 Sound Voyager. All rights reserved.- - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//   samples.h
//   ~~~~~~~~~
//
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#pragma once

#include <juce_audio_formats/juce_audio_formats.h>

#include "pitch_detection.h"
#include "piano.h"

// TODO: move these constants to a config file

const double ATTACK = 0.1; // seconds

const double RELEASE = 0.1; // seconds

const double MAX_SAMPLE_LENGTH = 10.0; // seconds

const int MAX_TRANSPOSITION_SIZE = 3*piano::OCTAVE_SIZE;

const bool DEBUG_MODE = true; // TODO: make this a Precompiled Variable

juce::SamplerSound* getRandomSamplerSound(int keyNumber);
