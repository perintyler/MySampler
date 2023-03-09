/* plugin_editor.cpp */

#include <juce_graphics/juce_graphics.h>
#include <functional>

#include "app.h"
// #include "lock_buttons.h"

const juce::Colour BACKGROUND_COLOR = juce::Colours::grey;

const int HORIZONTAL_MARGIN_SIZE = 10; // pixels

const int VERTICAL_MARGIN_SIZE = 5; // pixels

const juce::String RANDOMIZE_BUTTON_LABEL { "randomize" };

const juce::String SAVE_BUTTON_LABEL { "save" };

App::App(AudioProcessor& audioProcessor) : AudioProcessorEditor(&audioProcessor)
    , processor       (audioProcessor)
    , randomizeButton (RANDOMIZE_BUTTON_LABEL)
    , saveButton      (SAVE_BUTTON_LABEL)
    , keyboard        (processor.getKeyboardState(), [this](midi::MidiNumber midiNumber)
    {
        if (this->processor.isKeyLocked(midiNumber))
            this->processor.unlockKey(midiNumber);
        else
            this->processor.lockKey(midiNumber);
    })
{
    setResizable(false, false);

    saveButton.onClick      = [&]() { processor.logSamples(); };
    randomizeButton.onClick = [&]() { processor.randomize_samples(); };
    
    // the editor's sub-components use plugin dimensions to set their
    // own bounds, so the plugin size must be set before adding sub-components
    setSize(
        keyboard.getTotalKeyboardWidth() + 2*HORIZONTAL_MARGIN_SIZE,
        250.0
    );

    addAndMakeVisible(saveButton);
    addAndMakeVisible(randomizeButton);
    addAndMakeVisible(keyboard, 0);

    #ifdef TESTMODE
      setComponentID("app");
      keyboard.setComponentID("keyboard");
      randomizeButton.setComponentID("randomize-button");
      saveButton.setComponentID("save-button");
    #else
      processor.randomize_samples();
    #endif
}

/** Render the UI
 **/
void App::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    g.setColour(BACKGROUND_COLOR);
}

/** Lay out subcomponents
 **/
void App::resized()
{
    int keyboardWidth = getWidth() - HORIZONTAL_MARGIN_SIZE*2;
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

    keyboard.setBounds(keyboardXCoord, keyboardYCoord, keyboardWidth, keyboardHeight);
    randomizeButton.setBounds(randomizeButtonXCoord, randomizeButtonYCoord, randomizeButtonWidth, randomizeButtonHeight);
    saveButton.setBounds(saveButtonXCoord, saveButtonYCoord, saveButtonWidth, saveButtonHeight);
}
