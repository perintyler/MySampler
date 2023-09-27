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

#include <assert.h>
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
    reader.parse(file, presetsJSON);

    std::unordered_map<std::string, Preset> loadedPresets;

    for (auto const& presetName : presetsJSON.getMemberNames()) {
        SampleSet samples;

        for (auto const& keyNumber : presetsJSON[presetName].getMemberNames()) {
            samples.set(
                std::stoi(keyNumber),
                presetsJSON[presetName][keyNumber]["path"].asString(), 
                presetsJSON[presetName][keyNumber]["note"].asInt()
            );
        }

        Preset preset;
        preset.name = presetName;
        preset.samples = samples;

        loadedPresets.insert({presetName, preset});
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

        for (const auto& [midiNumber, sample] : getPreset(presetName).samples.asVector()) 
        {
            Json::Value jsonSample;
            jsonSample["path"] = sample.filepath.string();
            jsonSample["note"] = static_cast<int>(sample.rootNote);
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

    return presetNames;
}

Preset& getPreset(std::string presetName)
{
    assert(presetExists(presetName));
    return __presets__.at(presetName);
}

void savePreset(std::string& presetName, SampleSet& samples) 
{
    std::string uniqueName { presetName };

    for (int numDuplicates = 0; presetExists(uniqueName); numDuplicates++)
      uniqueName = presetName + std::to_string(numDuplicates);

    Preset preset;
    preset.name = uniqueName;
    preset.samples = samples;

    __presets__.insert({uniqueName, preset});

    overwritePresetsFile();
}

void deletePreset(std::string presetName)
{
    assert(presetExists(presetName));

    __presets__.erase(presetName);

    overwritePresetsFile();
}
