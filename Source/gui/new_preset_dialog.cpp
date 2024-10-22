/*** Piano960 | new_preset_dialog.cpp ***/

#include <juce_gui_basics/juce_gui_basics.h>

#include "new_preset_dialog.h"

const juce::Colour NewPresetDialog::COLOR = juce::Colours::burlywood;

const juce::String NewPresetDialog::TITLE = juce::String{"Create New Preset"};

NewPresetDialog::NewPresetDialog(const AudioProcessor& processor, 
                                 const std::unique_ptr<PresetsDropdownMenu>& dropdown) 
{
    setSize(300, 60);
    addAndMakeVisible(presetNameTextField);
    addAndMakeVisible(savePresetButton);

    savePresetButton.onClick = [this, &dropdown=dropdown, &processor]() {
        std::string newPresetName = presetNameTextField.getText().toStdString();

        if (newPresetName.empty()) {
            showNewPresetAlert(false, "Please enter a name for your new preset.");
        } else {
            bool success = tryToCreatePreset(newPresetName, processor);

            // close the modal before alerting user of results (which opens another modal)
            if (juce::DialogWindow* dialog = findParentComponentOfClass<juce::DialogWindow>()) {
                dialog->exitModalState(1234); // figure out what 1234 is here
            } else {
                // this should never happen. Should I force the plugin to crash if it gets here?
                std::cerr << "could not close new preset dialog" << std::endl;
            }

            if (success) {
                dropdown->refresh();
                showNewPresetAlert(true, "Successfully saved new preset '" + newPresetName + "'.");
            } else {
                showNewPresetAlert(false, "'" + newPresetName + "' is invalid and cannot be saved.\n"
                                        + "(Note: only locked keys are used for the preset)");
            }
        }
    };
}

void NewPresetDialog::showNewPresetAlert(bool success, std::string message) const
{
    juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::WarningIcon, success ? "Success" : "Error", message);
}

/*** returns whether the preset was successfully created or not ***/
bool NewPresetDialog::tryToCreatePreset(std::string presetName, const AudioProcessor& processor)
{
    const SampleSet lockedSamples = processor.sampler.getLockedSamples();

    if (lockedSamples.length() == 0) {
        return false;
    } else {
        savePreset(presetName, processor.sampler.getLockedSamples());
        return true;
    }
}

void NewPresetDialog::resized()
{
    presetNameTextField.setBounds(10, 10, 280, 30);
    savePresetButton.setBounds(10, 50, 280, 40);
}

void NewPresetDialog::show(const AudioProcessor& processor, 
                           const std::unique_ptr<PresetsDropdownMenu>& dropdown) 
{
    juce::Component::SafePointer<NewPresetDialog> dialog(new NewPresetDialog(processor, dropdown));

    juce::DialogWindow::showDialog(
        NewPresetDialog::TITLE,  // dialog title
        std::move(dialog),       // dialog content
        nullptr,                 // dialog parent window (nullptr for popup)
        NewPresetDialog::COLOR,  // background color
        true                     // close dialog if escape key pressed  
    );
}
  
