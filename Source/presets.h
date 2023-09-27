/*** Piano960 | presets.h ***/

/***
 * 
 * The preset file is a JSON file where each key is the name if a preset. 
 * Each value will be an object containing a MIDI number and a sample's file path.
 *  
 * ```json
 * {
 *    "my preset": {
 *      23: {
 *        "path": "path/to/sample/for/key/with/midi/number/23.wav",
 *        "note": 42
 *      },
 *      ...
 *    },
 * }
 * ```
 * 
 ***/

#pragma once

#include "samples.h"

struct Preset 
{
    std::string name;
    SampleSet samples;
};

std::vector<std::string> getPresetNames();

Preset& getPreset(std::string presetName);

void savePreset(std::string presetName, SampleSet&);

void deletePreset(std::string presetName);
