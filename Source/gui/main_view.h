/*** Piano960 | gui/main_view.h ***/

#pragma once

#include <memory>

#include <juce_graphics/juce_graphics.h>

#include "../audio_processor.h"
#include "lockable_keys.h"
#include "new_preset_dialog.h"
#include "presets_dropdown_menu.h"
#include "sound_source_grid.h"

class MainView : public juce::Component, private juce::Timer {
public:
    
    MainView(AudioProcessor& processor);
    
    ~MainView() override = default;

    static float getHeight();

    void resized() override;

    float getMinimumWidth() const;

private:

    void timerCallback() override;

    std::unique_ptr<juce::TextButton> randomizeButton;
    
    std::unique_ptr<juce::TextButton> saveButton; // rename to savePresetButton

    std::unique_ptr<LockableKeys> keyboard;

    std::unique_ptr<PresetsDropdownMenu> presetsMenu;

    std::unique_ptr<SoundSourceGrid> soundSourceGrid;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainView)
};
