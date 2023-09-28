
#include <juce_gui_basics/juce_gui_basics.h>
#include "main_view.h"
#include "new_preset_dialog.h"

const bool AUTO_FOCUS = false;

// TODO: put margin constants in App and put the margins around MainView

const int HORIZONTAL_MARGIN_SIZE = 10; // pixels

const int VERTICAL_MARGIN_SIZE = 5; // pixels

const juce::String RANDOMIZE_BUTTON_LABEL { "randomize" };

const juce::String SAVE_BUTTON_LABEL { "save" };

MainView::MainView(juce::MidiKeyboardState&  keyboardState,
                   std::function<void()>     onRandomizeButtonClicked, 
                   std::function<void()>     onSaveButtonClicked,
                   SavePresetCallback        savePreset,
                   OnKeyLockStateChange      onLockButtonClicked) 
  : randomizeButton (std::make_unique<juce::TextButton>(RANDOMIZE_BUTTON_LABEL))
  , saveButton      (std::make_unique<juce::TextButton>(SAVE_BUTTON_LABEL))
  , keyboard        (std::make_unique<LockableKeys>(keyboardState, onLockButtonClicked))
{
    randomizeButton->onClick = onRandomizeButtonClicked;

    saveButton->onClick = [savePreset](){ NewPresetDialog::show(savePreset); };

    addAndMakeVisible(saveButton.get());
    addAndMakeVisible(randomizeButton.get());
    addAndMakeVisible(keyboard.get());

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

/** Set bounds of randomize button, save button, and keyboard 
 */
void MainView::resized()
{
    int keyboardWidth = getMinimumWidth();
    int keyboardHeight = 200;

    int randomizeButtonHeight = 30;
    int randomizeButtonWidth = 0.8*keyboardWidth;
    
    int saveButtonHeight = randomizeButtonHeight;
    int saveButtonWidth = 0.2*keyboardWidth - 5;
    
    int keyboardXCoord = HORIZONTAL_MARGIN_SIZE;
    int keyboardYCoord = VERTICAL_MARGIN_SIZE + randomizeButtonHeight + 5;
    
    int randomizeButtonXCoord = HORIZONTAL_MARGIN_SIZE;
    int randomizeButtonYCoord = VERTICAL_MARGIN_SIZE;

    int saveButtonXCoord = HORIZONTAL_MARGIN_SIZE + randomizeButtonWidth + 5;
    int saveButtonYCoord = VERTICAL_MARGIN_SIZE;

    keyboard->setBounds(keyboardXCoord, keyboardYCoord, keyboardWidth, keyboardHeight);
    randomizeButton->setBounds(randomizeButtonXCoord, randomizeButtonYCoord, randomizeButtonWidth, randomizeButtonHeight);
    saveButton->setBounds(saveButtonXCoord, saveButtonYCoord, saveButtonWidth, saveButtonHeight);
}

void MainView::timerCallback()
{
    keyboard->grabKeyboardFocus();
}
