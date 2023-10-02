/*** Piano960 | gui/main_view.h ***/

#pragma once

#include <memory>

#include <juce_graphics/juce_graphics.h>

#include "lockable_keys.h"
#include "new_preset_dialog.h"
#include "presets_dropdown_menu.h"
#include "sound_source_grid.h"

class MainView : public juce::Component, private juce::Timer {
public:
    
    MainView(
        juce::MidiKeyboardState&  keyboardState,
        std::function<void()>     randomizeSamples, 
        SavePresetCallback        createNewPreset,
        PresetSelectedCallback    selectPreset,
        OnKeyLockStateChange      onLockButtonClicked);
    
    ~MainView() override = default;

    void resized() override;

    float getMinimumWidth() const;

    void refresh();

private:

    void timerCallback() override;

    std::unique_ptr<juce::TextButton> randomizeButton;
    
    std::unique_ptr<juce::TextButton> saveButton; // rename to savePresetButton

    std::unique_ptr<LockableKeys> keyboard;

    std::unique_ptr<PresetsDropdownMenu> presetDropdownMenu;

    std::unique_ptr<SoundSourceGrid> categoryGrid;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainView)
};
