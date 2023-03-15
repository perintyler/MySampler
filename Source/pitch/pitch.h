/*** pitch/pitch.h ***/

#pragma once

#include <string>
#include <juce_audio_formats/juce_audio_formats.h>

#include "exceptions.h"
#include "notes.h"
#include "semitones.h"

void loadPitchDetectionModel();

void printPitchDetectionInfo();

float detectFrequency(juce::AudioBuffer<float>&, int sampleRate);

Note detectNote(juce::AudioBuffer<float>&, int sampleRate);
