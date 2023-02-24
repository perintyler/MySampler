/* plugin_editor.cpp */

#include <juce_graphics/juce_graphics.h>

#include "plugin_editor.h"
#include "lock_buttons.h"

Piano960Editor::Piano960Editor(Piano960Processor& processor)
    : AudioProcessorEditor (&processor)
    , audioProcessor       (processor)
    , keyboardComponent    (audioProcessor.getKeyboardState(), juce::MidiKeyboardComponent::horizontalKeyboard)
    , randomizeButton      (RANDOMIZE_BUTTON_LABEL)
    , saveButton           (SAVE_BUTTON_LABEL)
{
    saveButton.onClick = [&]() { processor.logSamples(); };
    randomizeButton.onClick = [&]() { processor.randomize_samples(); };

    keyboardComponent.setScrollButtonsVisible(false);
    keyboardComponent.setKeyWidth(WHITE_KEY_WIDTH);
    keyboardComponent.setBlackNoteWidthProportion(BLACK_KEY_WIDTH_RATIO);
    keyboardComponent.setAvailableRange(FIRST_MIDI_NOTE, LAST_MIDI_NOTE);

    setSize(
        keyboardComponent.getTotalKeyboardWidth() + 2*HORIZONTAL_MARGIN_SIZE,
        250.0
    );

    addAndMakeVisible(saveButton);
    addAndMakeVisible(randomizeButton);
    addAndMakeVisible(keyboardComponent, 0);
    addAndMakeLockButtonsVisible(keyboardComponent, processor);

    processor.randomize_samples();
}

// render the UI
void Piano960Editor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    g.setColour(BACKGROUND_COLOR);
}

// lay out the subcomponents
void Piano960Editor::resized()
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

    keyboardComponent.setBounds(keyboardXCoord, keyboardYCoord, keyboardWidth, keyboardHeight);
    randomizeButton.setBounds(randomizeButtonXCoord, randomizeButtonYCoord, randomizeButtonWidth, randomizeButtonHeight);
    saveButton.setBounds(saveButtonXCoord, saveButtonYCoord, saveButtonWidth, saveButtonHeight);
}
