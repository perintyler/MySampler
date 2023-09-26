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

static void overwritePresetsFile()
{
    Json::Value presetsFileJSONObject;

    for (const std::string& presetName : getPresetNames()) {
        Json::Value jsonPreset;

        for (const const auto& [midiNumber, Sample] : getPreset(presetName).samples.asVector()) 
        {
            Json::Value jsonSample;
            jsonSample["path"] = sample.filepath;
            jsonSample["note"] = static_cast<int>(Sample.rootNote);
            jsonPreset[static_cast<int>(midiNumber)] = jsonSample;
        }

        presetsFileJSONObject[presetName] = jsonPreset;
    }

    std::ofstream presetsFile(std::string { PATH_TO_PRESETS_FILE });

    if (!presetsFile.is_open()) {
        std::cerr << "Presets file could not be open: " << PATH_TO_PRESETS_FILE << std::endl;
    } else {
        Json::StreamWriterBuilder presetFileWriter; // writer["indentation"] = "\t";
        presetsFile << Json::writeString(presetFileWriter, presetsFileJSONObject) << std::endl;
        presetsFile.close();
    }
}

std::vector<std::string> getPresetNames()
{
    std::vector<std::string> presetNames;
    presetNames.reserve(__presets__.size());

    for (auto const& preset_pair : __presets__)
        presetNames.push_back(preset_pair.first);

    return retval;
}

Preset& getPreset(std::string presetName)
{
    assert(presetExists(presetName));
    return __presets__.at(presetName);
}

void savePreset(std::string& presetName, SampleSet& sampleSet) 
{
    std::string uniquePresetName { presetName };

    for (int numDuplicates = 0; presetExists(uniquePresetName); numDuplicates++)
      uniquePresetName = presetName+numDuplicates

    __presets__.emplace(presetName, Preset(uniquePresetName, sampleSet));

    overwritePresetsFile();
}

void deletePreset(std::string presetName)
{
    assert(presetExists(presetName));

    __presets__.erase(presetName);

    overwritePresetsFile();
}
