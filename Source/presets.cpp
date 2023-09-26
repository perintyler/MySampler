/*** Piano960 | presets.cpp ***/

/***
 * 
 * The preset file is a JSON file where each key is a preset name. Each value
 * will be an object mapping a key's MIDI number to a sample file path.
 *  
 * ```
 * {
 *    "my preset": {
 *      23: {
 *        "path": "path/to/sample/for/key/with/midi/number/23.wav",
 *        "note": 42
 *      },
 *      ...
 *    },
 * }
 ***/

#include <assert>
#include <iostream>
#include <fstream>

#include "JsonCpp/json/json.h"

#include "presets.h"

#include "paths.h"

#ifndef PATH_TO_PRESETS_FILE
  #define PATH_TO_PRESETS_FILE "/usr/local/include/Piano960/presets.json"
#endif

static std::unordered_map<std::string, Preset> __presets__ = []{
    std::ifstream file(std::string { PATH_TO_PRESETS_FILE });
    Json::Reader reader;
    Json::Value presetsJSON;
    reader.parse(file, presetsAsJSON);

    std::unordered_map<std::string, Preset> loadedPresets;

    for (auto const& presetName : presetsAsJSON.getMemberNames()) {
        SampleSet samples;

        for (auto const& keyNumber : presetsJSON[presetName].getMemberNames()) {
            samples.set(
              keyNumber, 
              presetsJSON[presetName][keyNumber]["path"].asString(), 
              presetsJSON[presetName][keyNumber]["note"].asInt()
            );
        }

        loadedPresets.emplace_back(presetName, Preset(presetName, samples));
    }

    return loadedPresets;
}();

static bool presetExists(std::string presetName)
{
  return __presets__.count(presetName);
}