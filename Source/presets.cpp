/*** Piano960 | presets.cpp ***/

#include <assert.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

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

/**
 * load the installed presets file into the `__presets__` map right away
 **/
static std::map<std::string, SampleSet> __presets__ = ([]{
    std::map<std::string, SampleSet> presets;

    // if the presets file doesn't exist (which means the plugin wasn't 
    // installed correctly), just return the empty presets map
    if (!std::filesystem::exists(std::string{PATH_TO_PRESETS_FILE})) {
        std::cerr << "presets file does not exist: " << PATH_TO_PRESETS_FILE << std::endl;
        return presets;
    }

    std::ifstream file(PATH_TO_PRESETS_FILE);
    Json::Reader reader;
    Json::Value presetsFileContents;
    reader.parse(file, presetsFileContents);

    try {
        for (const std::string& presetName : presetsFileContents.getMemberNames()) {
            
            SampleSet samples;
            Json::Value presetJson = presetsFileContents[presetName];

            for (Json::Value::ArrayIndex index = 0; index < presetJson.size(); index++) {
                Json::Value sampleJson = presetsFileContents[presetName][index];
                samples.set(
                    sampleJson["assignedKey"].asInt(), 
                    sampleJson["pathToSample"].asString(),
                    sampleJson["detectedNote"].asInt()
                );
            }

            presets.insert({ presetName, samples });
        }
    } catch(Json::LogicError error) {
        std::cerr << "presets file is invalid and can't be parsed: " << PATH_TO_PRESETS_FILE 
                  << " (" << error.what() << ")." << std::endl;
    }

    return presets;
})();

static bool presetExists(std::string presetName)
{
  return __presets__.count(presetName) != 0;
}

static void overwritePresetsFile()
{
    Json::Value presetsFileContents;

    for (const std::string& presetName : getPresetNames()) {

        Json::Value jsonSampleArray;

        for (const auto& [note, sample] : getSamplesForPreset(presetName))
        {
            Json::Value jsonSample;
            jsonSample["pathToSample"] = sample.filepath.string();
            jsonSample["assignedKey"] = static_cast<int>(note);
            jsonSample["detectedNote"] = static_cast<int>(sample.rootNote);
            jsonSampleArray.append(jsonSample);
        }

        presetsFileContents[presetName] = jsonSampleArray;
    }

    std::ofstream presetsFile(std::string { PATH_TO_PRESETS_FILE });

    if (!presetsFile.is_open()) {
        std::cerr << "Presets file could not be open: " << PATH_TO_PRESETS_FILE << std::endl;
    } else {
        Json::StreamWriterBuilder presetFileWriter; // writer["indentation"] = "\t";
        presetsFile << Json::writeString(presetFileWriter, presetsFileContents) << std::endl;
        presetsFile.close();
    }
}

std::vector<std::string> getPresetNames()
{
    std::vector<std::string> presetNames;

    for (const auto& [name, preset]: __presets__) {
        presetNames.push_back(name);
    }

    return presetNames;
}

SampleSet getSamplesForPreset(std::string presetName)
{
    // this preset exists check shouldn't be neccessary. get rid of it?
    if (!presetExists(presetName)) { 
        std::cerr << "preset does not exist: " << presetName;
        if (presetExists("default-preset-1")) {
            std::cerr << " (using 'default-preset-1' set instead)." << std::endl;
            return getSamplesForPreset("default-preset-1");
        } else {
            std::cerr << " (using empty sample set instead).";
            return SampleSet {};
        }
    }

    return __presets__[presetName];
}

void savePreset(std::string presetName, const SampleSet& samples) 
{
    logs::debug("saving new preset: " + presetName);
    std::string uniqueName { presetName };
    
    for (int numDuplicates = 0; presetExists(uniqueName); numDuplicates++)
      uniqueName = presetName + std::to_string(numDuplicates);

    __presets__.insert({uniqueName, samples});

    overwritePresetsFile();
}

void deletePreset(std::string presetName)
{
    if (!presetExists(presetName))
        std::cerr << "tried to delete a preset that doesn't exist: " << presetName << std::endl;
    else {
        __presets__.erase(presetName);
        overwritePresetsFile();
    }
}

void pretty_print_presets()
{
    // for (const std::string& presetName : getPresetNames()) {
    //     std::cout << presetName << std::endl;
    // }
}
