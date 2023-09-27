/*** Piano960 | presets.h */

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
