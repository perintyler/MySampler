/*** Piano960 | gui/presets_dropdown_menu.cpp ***/

#include <assert.h>

#include "presets_dropdown_menu.h"
#include "../presets.h"

namespace
{
    int getDropdownItemId (int presetIndex)    { return presetIndex    + 1; }
    int getPresetIndex    (int dropdownItemId) { return dropdownItemId - 1; }
}

PresetsDropdownMenu::Listener::Listener(PresetSelectedCallback presetSelectedCallback)
  : juce::ComboBox::Listener()
  , callback(presetSelectedCallback)
{}

void PresetsDropdownMenu::Listener::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) 
{
    int dropdownOptionID = comboBoxThatHasChanged->getSelectedId(); // Get the selected item ID

    comboBoxThatHasChanged->setText("presets");

    if (dropdownOptionID != 0) {
        std::string presetName = getPresetNames().at(getPresetIndex(dropdownOptionID));
        callback(presetName);
        juce::AlertWindow::showMessageBoxAsync(
            juce::AlertWindow::WarningIcon, "Loaded Preset",  "Successfully loaded preset '" + presetName + "'."
        );
    }
}

PresetsDropdownMenu::PresetsDropdownMenu(PresetSelectedCallback presetSelectedCallback)
  : listener(presetSelectedCallback)
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
