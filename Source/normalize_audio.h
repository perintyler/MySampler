/*** Piano960 | normalize_audio.h ***/

#pragma once

#include <juce_audio_formats/juce_audio_formats.h>

const float TARGET_VOLUME = 10.0; // decibals

void normalize_audio(juce::AudioBuffer<float>&, int sampleRate);
