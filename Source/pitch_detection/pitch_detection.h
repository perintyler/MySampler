/*** pitch_detection/pitch_detection.h ***/

#pragma once

#include <string>
#include <juce_audio_formats/juce_audio_formats.h>

#include "frequency.h"
#include "exceptions.h"

void loadPitchDetectionModel();

void printPitchDetectionInfo();

float detectFrequency(juce::AudioBuffer<float>&, int sampleRate);

Note detectNote(juce::AudioBuffer<float>&, int sampleRate, std::string sampleName = "");
