/* pitch_detection/crepe.h */

#pragma once

#include <juce_audio_formats/juce_audio_formats.h>

namespace pitch_detection
{
    bool model_is_loaded();

    void load_model();
    
    float getFundementalFrequency(juce::AudioBuffer<float>&, int sampleRate);
}
