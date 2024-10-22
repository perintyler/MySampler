/*** Piano960 | pitch_detection/spice.h ***/

#pragma once

#ifdef SPICE_MODEL

#include <string>
#include <juce_audio_formats/juce_audio_formats.h>

namespace pitch_detection
{
    bool model_is_loaded();

    void load_model();

    float getFundementalFrequency(juce::AudioBuffer<float>&, int sampleRate, int startFrame=0);
}

#endif
