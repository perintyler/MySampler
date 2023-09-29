/*** Piano960 | gui/main_view.h ***/

#pragma once

#include <memory>

#include <juce_graphics/juce_graphics.h>

#include "lockable_keys.h"
#include "new_preset_dialog.h"
#include "presets_dropdown_menu.h"

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

    /** TODO
     **   I don't think these members need to be unique_ptr.
     **/
    std::unique_ptr<juce::TextButton> randomizeButton;
    
    std::unique_ptr<juce::TextButton> saveButton;

    std::unique_ptr<LockableKeys> keyboard;

    std::unique_ptr<PresetsDropdownMenu> presetDropdownMenu;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainView)
};
