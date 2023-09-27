/*** Piano960 | presets.cpp ***/

#include <assert.h>
#include <iostream>
#include <fstream>

#include "JsonCpp/json/json.h"

#include "presets.h"

#include "paths.h"

#ifndef PATH_TO_PRESETS_FILE
  #define PATH_TO_PRESETS_FILE "/usr/local/include/Piano960/presets.json"
#endif

// load presets from the installed presets file
static std::unordered_map<std::string, Preset> __presets__ = []
{
    std::unordered_map<std::string, Preset> presets;

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
        for (auto const& presetName : presetsFileContents.getMemberNames()) {

            Json::Value presetJson = presetsFileContents[presetName];
            SampleSet samples;

            for (auto const& midiNumber : presetJson.getMemberNames()) {

                std::string rootNoteOfSample = presetJson[midiNumber]["note"].asString();
                std::string samplePath = presetJson[midiNumber]["path"].asString();

                samples.set(std::stoi(midiNumber), samplePath, std::stoi(rootNoteOfSample));
            }

            presets.insert({ presetName, Preset{presetName, samples} });
        }
    } catch(Json::LogicError) {
        std::cerr << "presets file is invalid and can't be parsed: " << PATH_TO_PRESETS_FILE << std::endl;
    }

    return presets;
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
