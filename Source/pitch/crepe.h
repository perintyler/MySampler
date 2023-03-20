/*** Piano960 | pitch/crepe.h ***/

#pragma once

#ifdef CREPE_MODEL

#include <string>

#include <juce_audio_formats/juce_audio_formats.h>

namespace pitch_detection
{    
    bool model_is_loaded();

    void load_model();
    
    float getFundementalFrequency(juce::AudioBuffer<float>&, int sampleRate);

    #ifdef TESTMODE
    void create1024SampleFrames(juce::AudioBuffer<double>&, int sampleRate);
    void makeAudioMono(juce::AudioBuffer<double>& buffer);
    void normalizeAudio(juce::AudioBuffer<double>&, int sampleRate);
    void downSampleAudio(juce::AudioBuffer<double>&, int sampleRate);
    #endif
}

#endif
