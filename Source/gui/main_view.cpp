/*** Piano960 | gui/main_view.cpp ***/

#include <juce_gui_basics/juce_gui_basics.h>

#include "main_view.h"
#include "new_preset_dialog.h"
#include "presets_dropdown_menu.h"

const bool AUTO_FOCUS = false;

// TODO: put margin constants in App and put the margins around MainView

const int HORIZONTAL_MARGIN_SIZE = 10; // pixels

const int VERTICAL_MARGIN_SIZE = 5; // pixels

const juce::String RANDOMIZE_BUTTON_LABEL { "randomize" };

const juce::String SAVE_BUTTON_LABEL { "save" };

MainView::MainView(juce::MidiKeyboardState&  keyboardState,
                   std::function<void()>     randomizeSamples, 
                   SavePresetCallback        createNewPreset,
                   PresetSelectedCallback    selectPreset,
                   OnKeyLockStateChange      onLockButtonClicked) 
  : randomizeButton    (std::make_unique<juce::TextButton>(RANDOMIZE_BUTTON_LABEL))
  , saveButton         (std::make_unique<juce::TextButton>(SAVE_BUTTON_LABEL))
  , keyboard           (std::make_unique<LockableKeys>(keyboardState, onLockButtonClicked))
  , presetDropdownMenu (std::make_unique<PresetsDropdownMenu>(selectPreset))
{
    randomizeButton->onClick = randomizeSamples;

    saveButton->onClick = [createNewPreset, &presetDropdownMenu=presetDropdownMenu](){ 
        NewPresetDialog::show(createNewPreset);
    };

    addAndMakeVisible(saveButton.get());
    addAndMakeVisible(randomizeButton.get());
    addAndMakeVisible(keyboard.get());
    addAndMakeVisible(presetDropdownMenu.get());

    // component IDs are only used for testing
    setComponentID("app");
    keyboard->setComponentID("keyboard");
    randomizeButton->setComponentID("randomize-button");
    saveButton->setComponentID("save-button");
    
    // wait for timer, then put the MIDI keyboard into the computer keyboard's focus
    if (AUTO_FOCUS) { startTimer(400); }
}

/** Since the keyboard component's keys have fixed widths/lengths, a MainView component
 ** must be at least as big as the child keyboard component
 */
float MainView::getMinimumWidth() const
{
    return keyboard->getTotalKeyboardWidth();
}

void MainView::refresh()
{
    presetDropdownMenu->refresh();
}

/** Set bounds of randomize button, save button, and keyboard 
 */
void MainView::resized()
{
    //
    // TODO:
    //  get rid of all these margin constants and apply the margins when adding MainView to App
    //

    int presetsMenuXCoord = HORIZONTAL_MARGIN_SIZE;
    int presetsMenuYCoord = VERTICAL_MARGIN_SIZE;
    int presetsMenuWidth = 100;
    int presetsMenuHeight = 30;

    int keyboardXCoord = HORIZONTAL_MARGIN_SIZE;
    int keyboardYCoord = VERTICAL_MARGIN_SIZE + presetsMenuHeight + 5;
    int keyboardWidth = getMinimumWidth();
    int keyboardHeight = 200;

    int randomizeButtonHeight = 40;
    int randomizeButtonWidth = 0.5*keyboardWidth;
    int randomizeButtonXCoord = HORIZONTAL_MARGIN_SIZE;
    int randomizeButtonYCoord = keyboardYCoord + keyboardHeight + 5;

    int saveButtonXCoord = randomizeButtonXCoord + randomizeButtonWidth + 5;
    int saveButtonYCoord = randomizeButtonYCoord;
    int saveButtonHeight = randomizeButtonHeight;
    int saveButtonWidth = 0.5*keyboardWidth - 5;

    keyboard->setBounds(keyboardXCoord, keyboardYCoord, keyboardWidth, keyboardHeight);
    presetDropdownMenu->setBounds(presetsMenuXCoord, presetsMenuYCoord, presetsMenuWidth, presetsMenuHeight);
    randomizeButton->setBounds(randomizeButtonXCoord, randomizeButtonYCoord, randomizeButtonWidth, randomizeButtonHeight);
    saveButton->setBounds(saveButtonXCoord, saveButtonYCoord, saveButtonWidth, saveButtonHeight);
}

void MainView::timerCallback()
{
    keyboard->grabKeyboardFocus();
}
