/*** Piano960 | new_preset_dialog.h ***/

#pragma once

#include <juce_graphics/juce_graphics.h>

#include "../audio_processor.h"
#include "presets_dropdown_menu.h"

using SavePresetCallback = std::function<bool(std::string)>;

class NewPresetDialog : public juce::Component
{
public:
    NewPresetDialog(const AudioProcessor&, const std::unique_ptr<PresetsDropdownMenu>& dropdown = nullptr);
    
    static void show(const AudioProcessor&, const std::unique_ptr<PresetsDropdownMenu>& dropdown = nullptr);

    static const juce::Colour COLOR;
    static const juce::String TITLE;

    void resized() override;

private:
    bool tryToCreatePreset(std::string presetName, const AudioProcessor&); // returns true if successful

    void showNewPresetAlert(bool success, std::string message) const;

    juce::TextButton savePresetButton { "save" };
    juce::TextEditor presetNameTextField;
};
