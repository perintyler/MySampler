/*** pitch_detection/pitch_detection.cpp ***/

#include <iostream>
#include <filesystem>
#include <iostream>
#include <fstream>

#include "../JsonCpp/json/json.h"

#include "pitch_detection.h"
#include "exceptions.h"
#include "../notes.h"

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

#ifndef PITCH_DETECTION_CACHE_FILE
    #define NO_PITCH_DETECTION_CACHE
#endif

// the pitch detection cache is stored as a JSON file in the installation directory
static std::unordered_map<std::string, Note> __pitch_detection_cache__ = []
{
    std::unordered_map<std::string, Note> pitchDetectionCache;

    // ---------------------------------------------
    #ifndef NO_PITCH_DETECTION_CACHE

    if (!std::filesystem::exists(PITCH_DETECTION_CACHE_FILE)) {
        std::cerr << "pitch detection cache file does not exist: " << PITCH_DETECTION_CACHE_FILE << std::endl;
        return pitchDetectionCache;
    }

    std::ifstream file(PITCH_DETECTION_CACHE_FILE);
    Json::Reader reader;
    Json::Value cachefileContents;
    reader.parse(file, cachefileContents);

    try {
        for (auto const& sampleName : cachefileContents.getMemberNames()) 
        {
            Note note = cachefileContents[sampleName].asInt();
            pitchDetectionCache.insert({ sampleName, note });
        }
    } catch(Json::LogicError) {
        std::cerr << "pitch detection cache file is invalid and can't be parsed: " << PITCH_DETECTION_CACHE_FILE << std::endl;
    }

    #endif 
    // ---------------------------------------------

    return pitchDetectionCache;
}();

static void cache_pitch_detection(std::string sampleName, Note note)
{
    #ifndef NO_PITCH_DETECTION_CACHE
    __pitch_detection_cache__.insert({ sampleName, note });

    if (std::filesystem::exists(PITCH_DETECTION_CACHE_FILE)) 
    {
        Json::Value jsonCache;

        for (const auto& pitch_detection_pair : __pitch_detection_cache__) 
            jsonCache[pitch_detection_pair.first] = static_cast<int>(pitch_detection_pair.second);

        std::ofstream cachefile(PITCH_DETECTION_CACHE_FILE);

        if (!cachefile.is_open()) {
            std::cerr << "pitch detection cache file could not be overwritten: " << PITCH_DETECTION_CACHE_FILE << std::endl;
        } else {
            Json::StreamWriterBuilder cachefileWriter; // writer["indentation"] = "\t";
            cachefile << Json::writeString(cachefileWriter, jsonCache) << std::endl;
            cachefile.close();
        }
    }
    #endif
}

void loadPitchDetectionModel()
{
    #if defined(CREPE_MODEL) || defined(SPICE_MODEL)
    if (!pitch_detection::model_is_loaded()) {
        pitch_detection::load_model();
    }
    #endif
}

float detectFrequency(juce::AudioBuffer<float>& buffer, int sampleRate)
{
    return pitch_detection::getFundementalFrequency(buffer, sampleRate);
}

Note detectNote(juce::AudioBuffer<float>& buffer, int sampleRate, std::string sampleName /* = "" */)
{    
    if (!sampleName.empty() && __pitch_detection_cache__.count(sampleName) != 0)
        return __pitch_detection_cache__.at(sampleName);

    Note detectedNote = getNoteForFrequency(detectFrequency(buffer, sampleRate));

    #ifndef NO_PITCH_DETECTION_CACHE
      if (!sampleName.empty()) { cache_pitch_detection(sampleName, detectedNote); }
    #endif

    return detectedNote;
}

void printPitchDetectionInfo()
{
    std::cout << "Using " << PITCH_DETECTION_ALGO << " pitch detection algorithm." << std::endl;
}
