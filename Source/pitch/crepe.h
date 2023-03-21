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

    // ------ the functions below are only exposed for testing purposes ------
   
    #ifdef TESTMODE
     
      void makeAudioMono(juce::AudioBuffer<float>& buffer);

      juce::AudioBuffer<float> downSampleAudio(juce::AudioBuffer<float>&, int sampleRate);

      std::vector<std::vector<float>> create1024SampleFrames(juce::AudioBuffer<float>&, int sampleRate);
     
      std::vector<float> normalizeAudio(std::vector<std::vector<float>> sampleFrames);
   
    #endif
}

#endif
