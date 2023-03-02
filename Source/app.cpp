/* plugin_editor.cpp */

#include <juce_graphics/juce_graphics.h>

#include "app.h"
#include "lock_buttons.h"

const int HORIZONTAL_MARGIN_SIZE = 10; // pixels

const int VERTICAL_MARGIN_SIZE = 5; // pixels

const float WHITE_KEY_WIDTH = 40.0;

const float BLACK_KEY_WIDTH_RATIO = 1.0;

const juce::String RANDOMIZE_BUTTON_LABEL { "randomize" };

const juce::String SAVE_BUTTON_LABEL { "save" };

App::App(AudioProcessor& audioProcessor)
    : AudioProcessorEditor (&audioProcessor)
    , processor            (audioProcessor)
    , keyboard             (audioProcessor.getKeyboardState(), juce::MidiKeyboardComponent::horizontalKeyboard)
    , randomizeButton      (RANDOMIZE_BUTTON_LABEL)
    , saveButton           (SAVE_BUTTON_LABEL)
{
    saveButton.onClick = [&]() { processor.logSamples(); };
    randomizeButton.onClick = [&]() { processor.randomize_samples(); };

    // configure MIDI keyboard
    keyboard.setScrollButtonsVisible(false);
    keyboard.setKeyWidth(WHITE_KEY_WIDTH);
    keyboard.setBlackNoteWidthProportion(BLACK_KEY_WIDTH_RATIO);
    keyboard.setAvailableRange(FIRST_MIDI_NOTE, LAST_MIDI_NOTE);
    keyboard.setBufferedToImage(true);

    // the editor's sub-components use plugin dimensions to set their
    // own bounds, so the plugin size must be set before adding sub-components
    setSize(
        keyboard.getTotalKeyboardWidth() + 2*HORIZONTAL_MARGIN_SIZE,
        250.0
    );

    #ifdef TESTMODE
    setComponentID("app");
    keyboard.setComponentID("keyboard");
    randomizeButton.setComponentID("randomize-button");
    saveButton.setComponentID("save-button");
    #else
    processor.randomize_samples();
    #endif

    addAndMakeVisible(saveButton);
    addAndMakeVisible(randomizeButton);
    addAndMakeVisible(keyboard, 0);
    addAndMakeLockButtonsVisible(keyboard, processor);
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
