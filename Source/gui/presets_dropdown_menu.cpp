/*** Piano960 | gui/presets_dropdown_menu.cpp ***/

#include <assert.h>

#include "presets_dropdown_menu.h"
#include "../presets.h"

namespace
{
    int getDropdownItemId (int presetIndex)    { return presetIndex    + 1; }
    int getPresetIndex    (int dropdownItemId) { return dropdownItemId - 1; }
}

PresetsDropdownMenu::Listener::Listener(PresetSelectedCallback callback)
  : juce::ComboBox::Listener()
  , onPresetSelected(callback)
{}

void PresetsDropdownMenu::Listener::comboBoxChanged(juce::ComboBox* comboBox) 
{
    int dropdownOptionID = comboBox->getSelectedId(); // Get the selected item ID

    comboBox->setText("presets");

    if (dropdownOptionID != 0) {
        std::string presetName = getPresetNames().at(getPresetIndex(dropdownOptionID));
        onPresetSelected(presetName);
        juce::AlertWindow::showMessageBoxAsync(
            juce::AlertWindow::WarningIcon, "Loaded Preset",  "Successfully loaded preset '" + presetName + "'."
        );
    }
}

PresetsDropdownMenu::PresetsDropdownMenu(AudioProcessor& processor)
  : listener([&processor=processor](std::string presetName) { 
        processor.sampler.setSamples(getSamplesForPreset(presetName));
    })
{
    setText("presets");
    setJustificationType(juce::Justification::centred);
    refresh();
    addListener(&listener);
}

PresetsDropdownMenu::~PresetsDropdownMenu()
{
    removeListener(&listener);
}

void PresetsDropdownMenu::refresh()
{
    if (getNumItems() > 0) {
        clear();
    }

    std::vector<std::string> presetNames = getPresetNames();

    for (int presetIndex = 0; presetIndex < presetNames.size(); presetIndex++) {
        addItem(presetNames.at(presetIndex), getDropdownItemId(presetIndex));
    }
}
