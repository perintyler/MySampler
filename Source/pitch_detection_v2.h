/* pitch_detection_v2.h */

#pragma once

#include <juce_audio_formats/juce_audio_formats.h>

namespace pitch_detection_v2 
{
    struct SpiceModelError : public std::exception {
        const char * what () const throw ();
    };

    bool model_is_loaded();
    void load_model();
    float getFundementalFrequency(juce::AudioBuffer<float>&, int sampleRate);
}
