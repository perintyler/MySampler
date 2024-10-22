/*** Piano960 | yin.h ***/

#pragma once

#include <string>
#include <juce_audio_formats/juce_audio_formats.h>

namespace pitch_detection 
{
    static const float TOLERANCE = 0.10f;

    float getFundementalFrequency(juce::AudioBuffer<float>&, int sampleRate, int startFrame=0);
}