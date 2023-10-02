/*** Piano960 | presets.h ***/

/***
 * 
 * The preset file is a JSON file where each key is the name if a preset. 
 * Each value will be an object containing a MIDI number and a sample's file path.
 *  
 * ```json
 * {
 *    "my first preset": [
 *      {
 *        "assignedKey": 23,
 *        "pathToSample": "path/to/sample/for/key/with/midi/number/23.wav",
 *        "detectedNote": 42
 *      },
 *      ...
 *    ],
 *    "my second preset": [ ... ]
 * }
 * ```
 * 
 ***/

#pragma once

#include <vector>
#include <string>

#include "sample_set.h"

std::vector<std::string> getPresetNames();

SampleSet getSamplesForPreset(std::string presetName); // this should return a 'const Prest&'

void savePreset(std::string presetName, const SampleSet&);

void deletePreset(std::string presetName);

void pretty_print_presets();