/* pitch_detection_v2.h */

#pragma once

namespace pitch_detection_v2 
{
    bool model_is_loaded();
    void load_model();
    float getFundementalFrequency(juce::AudioBuffer<float>&, int sampleRate);
}
