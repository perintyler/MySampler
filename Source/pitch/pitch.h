/* pitch/pitch_detection.h */

#pragma once

#include <string>
#include <juce_audio_formats/juce_audio_formats.h>

#include "exceptions.h"
#include "notes.h"

float detectFrequency(juce::AudioBuffer<float>&, int sampleRate);

NoteID detectNote(juce::AudioBuffer<float>&, int sampleRate);

std::string getPitchDetectionAlgorithmName();
