// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - Piano960 | VST3, AU - - - - - - - - - - - - - - - - - - - -
// - - Created by Tyler Perin  - - - - - - - - - - - - - - - - - -
// - - Copyright © 2022 Sound Voyager. All rights reserved.- - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//   plugin_editor.cpp
//   ~~~~~~~~~~~~~~~~~
//
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#include "plugin_editor.h"

Piano960Editor::Piano960Editor(Piano960Processor& processor)
    : AudioProcessorEditor (&processor)
    , audioProcessor       (processor)
    , keyboardComponent    (audioProcessor.getKeyboardState(), juce::MidiKeyboardComponent::horizontalKeyboard)
    , randomizeButton      (RANDOMIZE_BUTTON_LABEL)
{
    randomizeButton.onClick = [&]() { processor.randomize_samples(); };

    addAndMakeVisible(randomizeButton);
    addAndMakeVisible(keyboardComponent);
        
    setSize(1220, 160);

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
    int keyboardWidth = getWidth() - 20;
    int keyboardHeight = getHeight() - 50;

    int buttonHeight = 30;
    int buttonWidth = keyboardWidth;
    
    int keyboardXCoord = LEFT_MARGIN_SIZE;
    int keyboardYCoord = TOP_MARGIN_SIZE + buttonHeight + 5;
    
    int buttonXCoord = LEFT_MARGIN_SIZE;
    int buttonYCoord = TOP_MARGIN_SIZE;

    randomizeButton.setBounds(buttonXCoord, buttonYCoord, buttonWidth, buttonHeight);
    keyboardComponent.setBounds(keyboardXCoord, keyboardYCoord, keyboardWidth, keyboardHeight);
}
