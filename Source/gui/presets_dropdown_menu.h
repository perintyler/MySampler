/*** Piano960 | gui/presets_dropdown_menu.h ***/

// TODO: rename this file to presets_dropdown_menu.h 

#pragma once

#include <functional>
#include <string>
#include <juce_gui_basics/juce_gui_basics.h>

#include "../audio_processor.h"

using PresetSelectedCallback = std::function<void(std::string)>;

/** TODO
 **   Turns out, a combobox has a onChange property that can be set with a lambda
 **   and is called when a new dropdown option is selected. This is much simpler
 **   than this listener implementation. Replace it.
 **/
class PresetsDropdownMenu : public juce::ComboBox {
public:

    PresetsDropdownMenu(AudioProcessor&);

    ~PresetsDropdownMenu();

    void refresh(); // adds/removes any new/deleted presets

private:
    void onPresetSelected(std::string presetName);

    class Listener : public juce::ComboBox::Listener {
        public:
            Listener(PresetSelectedCallback);
            void comboBoxChanged(juce::ComboBox*) override;
        private:
            PresetSelectedCallback onPresetSelected;
            std::vector<std::string> presetNames {}; // index corresponds to combobox item ID
    };
private:
    PresetsDropdownMenu::Listener listener;
};
