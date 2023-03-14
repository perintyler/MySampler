/* pitch/pitch.cpp */

#include "pitch.h"

#if defined(CREPE_MODEL)

    const std::string PITCH_DETECTION_ALGORITHM_NAME = "CREPE";
    #include "crepe.h"

#elif defined(SPICE_MODEL)

    const std::string PITCH_DETECTION_ALGORITHM_NAME = "SPICE";
    #include "spice.h"

#else

    const std::string PITCH_DETECTION_ALGORITHM_NAME = "YIN";
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
    return PITCH_DETECTION_ALGORITHM_NAME;
}
