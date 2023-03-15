// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//   samples.h
//   ~~~~~~~~~
//
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#pragma once

#include <memory>
#include <juce_audio_formats/juce_audio_formats.h>

#include "pitch/notes.h"

std::unique_ptr<juce::SamplerSound> getRandomSamplerSound(Note);
