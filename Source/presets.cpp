/*** Piano960 | presets.cpp ***/

#include <assert.h>
#include <iostream>
#include <fstream>

#include "JsonCpp/json/json.h"

#include "presets.h"
#include "paths.h"
#include "logs.h"

//
// Note:
//  Default presets are currently stored in the same JSON file as custom presets.
//  The default presets should probably be in the source code, or maybe they should
//  be embedded into the binary) 
//

#ifndef PATH_TO_PRESETS_FILE
  #define PATH_TO_PRESETS_FILE "/usr/local/include/Piano960/presets.json"
#endif

const std::vector<std::string> DEFAULT_PRESET_NAMES {"test-preset-1", "test-preset-2", "test-preset-3"};

#ifdef TESTMODE
    const std::vector<std::string> PRESET_TYPES {"default-presets"}; // only load default presets when testing
#else
    const std::vector<std::string> PRESET_TYPES {"default-presets", "custom-presets"};
#endif

/**
 * load the installed presets file into the `__presets__` map right away
 **/
static std::map<std::string, Preset> __presets__ = []
{
    std::map<std::string, Preset> presets;

    // if the presets file doesn't exist (which means the plugin wasn't 
    // installed correctly), just return the empty presets map
    if (!std::filesystem::exists(PATH_TO_PRESETS_FILE)) {
        std::cerr << "presets file does not exist: " << PATH_TO_PRESETS_FILE << std::endl;
        return presets;
    }

    std::ifstream file(PATH_TO_PRESETS_FILE);
    Json::Reader reader;
    Json::Value presetsFileContents;
    reader.parse(file, presetsFileContents);

    try {
        for (const std::string& presetType : PRESET_TYPES) {
            for (auto const& presetName : presetsFileContents[presetType].getMemberNames()) {

                Json::Value presetJson = presetsFileContents[presetType][presetName];
                SampleSet samples;

                for (auto const& sampleJson : presetJson) {
                    samples.set(
                        (Note) sampleJson["assignedKey"].asInt(), 
                        sampleJson["pathToSample"].asString(),
                        (Note) sampleJson["detectedNote"].asInt()
                    );
                }

                presets.insert({ presetName, Preset{presetName, samples} });
            }
        }
    } catch(Json::LogicError) {
        std::cerr << "presets file is invalid and can't be parsed: " << PATH_TO_PRESETS_FILE << std::endl;
    }

    return presets;
}();

static bool isDefaultPreset(std::string presetName)
{
    return std::find(DEFAULT_PRESET_NAMES.begin(), DEFAULT_PRESET_NAMES.end(), presetName) 
        != DEFAULT_PRESET_NAMES.end();
}

static bool presetExists(std::string presetName)
{
  return __presets__.count(presetName);
}

static void overwritePresetsFile()
{
    Json::Value defaultPresetsJson;
    Json::Value customPresetsJson;

    for (const std::string& presetName : getPresetNames()) {

        Json::Value jsonSampleArray;

        for (const auto& [note, sample] : getPreset(presetName).samples.asVector())
        {
            Json::Value jsonSample;
            jsonSample["pathToSample"] = sample.filepath.string();
            jsonSample["assignedKey"] = static_cast<int>(note);
            jsonSample["detectedNote"] = static_cast<int>(sample.rootNote);
            jsonSampleArray.append(jsonSample);
        }

        if (isDefaultPreset(presetName))
            defaultPresetsJson[presetName] = jsonSampleArray;
        else
            customPresetsJson[presetName] = jsonSampleArray;
    }

    Json::Value presetFileContents;
    presetFileContents["default-presets"] = defaultPresetsJson;
    presetFileContents["custom-presets"] = customPresetsJson;

    std::ofstream presetsFile(std::string { PATH_TO_PRESETS_FILE });

    if (!presetsFile.is_open()) {
        std::cerr << "Presets file could not be open: " << PATH_TO_PRESETS_FILE << std::endl;
    } else {
        Json::StreamWriterBuilder presetFileWriter; // writer["indentation"] = "\t";
        presetsFile << Json::writeString(presetFileWriter, presetFileContents) << std::endl;
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

void savePreset(std::string presetName, const SampleSet& samples) 
{
    logs::debug("saving new preset: " + presetName);
    std::string uniqueName { presetName };

    for (int numDuplicates = 0; presetExists(uniqueName); numDuplicates++)
      uniqueName = presetName + std::to_string(numDuplicates);

    __presets__.insert({uniqueName, Preset{uniqueName, samples}});

    overwritePresetsFile();
}

void deletePreset(std::string presetName)
{
    if (isDefaultPreset(presetName))
        std::cerr << "tried to delete default preset: " << presetName << std::endl;
    else if (!presetExists(presetName))
        std::cerr << "tried to delete a preset that doesn't exist: " << presetName << std::endl;
    else {
        __presets__.erase(presetName);
        overwritePresetsFile();
    }
}
