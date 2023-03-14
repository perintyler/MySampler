/*** pitch/pitch.cpp ***/

#include "pitch.h"

#if defined(CREPE_MODEL)
    #include "crepe.h"
    const std::string PITCH_DETECTION_ALGO = "CREPE";
#elif defined(SPICE_MODEL)
    #include "spice.h"
    const std::string PITCH_DETECTION_ALGO = "SPICE";
#else
    #include "yin.h"
    const std::string PITCH_DETECTION_ALGO = "YIN";
#endif

void loadPitchDetectionModel()
{
    #if defined(CREPE_MODEL) || defined(SPICE_MODEL)
    pitch_detection::load_model();
    #endif
}

float detectFrequency(juce::AudioBuffer<float>& buffer, int sampleRate)
{
    return pitch_detection::getFundementalFrequency(buffer, sampleRate);
}

Note detectNote(juce::AudioBuffer<float>& buffer, int sampleRate)
{
    return matchNoteToFrequency(detectFrequency(buffer, sampleRate));
}

void printPitchDetectionInfo()
{
    std::cout << "Using " << PITCH_DETECTION_ALGO << " pitch detection algorithm." << std::endl;
}
