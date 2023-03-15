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
    void create1024SampleFrames(juce::AudioBuffer<float>&, int sampleRate);
    void makeAudioMono(juce::AudioBuffer<float>& buffer);
    void normalizeAudio(juce::AudioBuffer<float>&, int sampleRate);
    void downSampleAudio(juce::AudioBuffer<float>&, int sampleRate);
    #endif
}

#endif
