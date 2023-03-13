/* pitch/pitch_detection.cpp */

#include "pitch.h"

#if defined(CREPE_MODEL)
  #include "crepe.h"
#elif defined(SPICE_MODEL)
  #include "spice.h"
#else
  #include "yin.h"
#endif

float detectFrequency(juce::AudioBuffer<float>& buffer, int sampleRate)
{
    return pitch_detection::getFundementalFrequency(buffer, sampleRate);
}

NoteID detectNote(juce::AudioBuffer<float>& buffer, int sampleRate)
{
    return matchNoteToFrequency(detectFrequency(buffer, sampleRate));
}

std::string getPitchDetectionAlgorithmName()
{
    return pitch_detection::ALGORITHM_NAME;
}
