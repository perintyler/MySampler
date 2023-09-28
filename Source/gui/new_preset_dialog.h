/*** Piano960 | new_preset_dialog.h ***/

#pragma once

#include <juce_graphics/juce_graphics.h>

using SavePresetCallback = std::function<bool(std::string)>;

class NewPresetDialog : public juce::Component
{
public:

    NewPresetDialog(SavePresetCallback);
    
    void resized() override;

    static const juce::Colour COLOR;
    static const juce::String TITLE;

    static void show(SavePresetCallback);

private:
    void showNewPresetAlert(bool success, std::string message) const;

    juce::TextButton savePresetButton { "save" };
    juce::TextEditor presetNameTextField;
};
