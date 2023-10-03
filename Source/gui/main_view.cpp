/*** Piano960 | gui/main_view.cpp ***/

#include <juce_gui_basics/juce_gui_basics.h>

#include "main_view.h"
#include "new_preset_dialog.h"
#include "presets_dropdown_menu.h"

const bool AUTO_FOCUS = false;

// TODO: put margin constants in App and put the margins around MainView

const juce::String RANDOMIZE_BUTTON_LABEL { "randomize" };

const juce::String SAVE_BUTTON_LABEL { "save" };

MainView::MainView(AudioProcessor& processor)
  : randomizeButton (std::make_unique<juce::TextButton>(RANDOMIZE_BUTTON_LABEL))
  , saveButton      (std::make_unique<juce::TextButton>(SAVE_BUTTON_LABEL))
  , keyboard        (std::make_unique<LockableKeys>(processor))
  , presetsMenu     (std::make_unique<PresetsDropdownMenu>(processor))
  , categoryGrid    (std::make_unique<SoundSourceGrid>())
{
    randomizeButton->onClick = [&processor=processor]() {
        processor.sampler.randomize(); 
    };

    saveButton->onClick = [&processor=processor, &presetsMenu    =presetsMenu    ](){ 
        NewPresetDialog::show(processor, presetsMenu    );
    };

    addAndMakeVisible(saveButton.get());
    addAndMakeVisible(randomizeButton.get());
    addAndMakeVisible(keyboard.get());
    addAndMakeVisible(presetsMenu    .get());
    addAndMakeVisible(categoryGrid.get());

    // set IDs for testing purposes
    setComponentID("app");
    keyboard->setComponentID("keyboard");
    randomizeButton->setComponentID("randomize-button");
    saveButton->setComponentID("save-button");
    
    // wait for timer, then put the MIDI keyboard into the computer keyboard's focus
    if (AUTO_FOCUS) { 
        startTimer(400); 
    }
}

/** Since the keyboard component's keys have fixed widths/lengths, a MainView component
 ** must be at least as big as the child keyboard component
 */
float MainView::getMinimumWidth() const
{
    return keyboard->getTotalKeyboardWidth();
}

/** Set bounds of randomize button, save button, and keyboard 
 */
void MainView::resized()
{
    //
    // TODO:
    //  get rid of all these margin constants and apply the margins when adding MainView to App
    //

    int presetsMenuXCoord = 0;
    int presetsMenuYCoord = 0;
    int presetsMenuWidth = 100;
    int presetsMenuHeight = 30;

    int saveButtonXCoord = presetsMenuWidth + 10;
    int saveButtonYCoord = 0;
    int saveButtonHeight = presetsMenuHeight;
    int saveButtonWidth = 150;

    int keyboardXCoord = 0;
    int keyboardYCoord = presetsMenuHeight + 5;
    int keyboardWidth = getMinimumWidth();
    int keyboardHeight = 200;

    int categoryGridHeight = 35;
    int categoryGridWidth = getLocalBounds().getWidth();
    int categoryGridXCoord = 0;
    int categoryGridYCoord = keyboardYCoord + keyboardHeight + 5;

    int randomizeButtonHeight = 40;
    int randomizeButtonWidth = categoryGridWidth;
    int randomizeButtonXCoord = 0;
    int randomizeButtonYCoord = categoryGridYCoord + categoryGridHeight + 10;

    presetsMenu    ->setBounds(presetsMenuXCoord, presetsMenuYCoord, presetsMenuWidth, presetsMenuHeight);
    saveButton->setBounds(saveButtonXCoord, saveButtonYCoord, saveButtonWidth, saveButtonHeight);
    keyboard->setBounds(keyboardXCoord, keyboardYCoord, keyboardWidth, keyboardHeight);
    categoryGrid->setBounds(categoryGridXCoord, categoryGridYCoord, categoryGridWidth, categoryGridHeight);
    randomizeButton->setBounds(randomizeButtonXCoord, randomizeButtonYCoord, randomizeButtonWidth, randomizeButtonHeight);
}

void MainView::timerCallback()
{
    keyboard->grabKeyboardFocus();
}
