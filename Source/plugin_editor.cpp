// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//   plugin_editor.cpp
//   ~~~~~~~~~~~~~~~~~
//
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#include "plugin_editor.h"
#include <juce_graphics/juce_graphics.h>
#include "BinaryData.h"

void setLockButtonImage(juce::ImageButton* lockButton)
{
    juce::Image unlockedIcon = juce::ImageFileFormat::loadFrom(
        BinaryData::unlocked_png,
        BinaryData::unlocked_pngSize
    );
    
    juce::Colour black = juce::Colour::fromRGB(
        juce::uint8(256), juce::uint8(256), juce::uint8(256)
    );
    
    lockButton->setImages(
        true,                                // resizeButtonNowToFitThisImage
        true,                                // rescaleImagesWhenButtonSizeChanges
        true,                                // preserveImageProportions
        unlockedIcon,                        // normal image
        1.0,                                 // imageOpacityWhenNormal
        black,                               // overlayColourWhenNormal
        unlockedIcon,                        // overImage
        1.0,                                 // imageOpacityWhenOver
        black,                               // overlayColourWhenOver
        unlockedIcon,                        // downImage
        1.0,                                 // imageOpacityWhenDown
        black,                               // overlayColourWhenDown
        true                                 // hitTestAlphaThreshold
    );
}

Piano960Editor::Piano960Editor(Piano960Processor& processor)
    : AudioProcessorEditor (&processor)
    , audioProcessor       (processor)
    , keyboardComponent    (audioProcessor.getKeyboardState(), juce::MidiKeyboardComponent::horizontalKeyboard)
    , randomizeButton      (RANDOMIZE_BUTTON_LABEL)
{
    for (
         int keyNumber = keyboardComponent.getRangeStart();
         keyNumber < 75; // keyboardComponent.getRangeEnd()-1;
         keyNumber++
    ) {
        juce::String lockButtonName = juce::String("lock-button") + juce::String(keyNumber);
        juce::ImageButton* lockButton = new juce::ImageButton(lockButtonName);
        setLockButtonImage(lockButton);
        addAndMakeVisible(lockButton);
        lockButtons.push_back(std::unique_ptr<juce::ImageButton>(lockButton));
    }
    
    randomizeButton.onClick = [&]() { processor.randomize_samples(); };
    addAndMakeVisible(randomizeButton);
    addAndMakeVisible(keyboardComponent);

    setSize(1220, 250);

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
    int keyboardHeight = 150;

    int buttonHeight = 30;
    int buttonWidth = keyboardWidth;
    
    int keyboardXCoord = LEFT_MARGIN_SIZE;
    int keyboardYCoord = TOP_MARGIN_SIZE + buttonHeight + 5;
    
    int buttonXCoord = LEFT_MARGIN_SIZE;
    int buttonYCoord = TOP_MARGIN_SIZE;

    randomizeButton.setBounds(buttonXCoord, buttonYCoord, buttonWidth, buttonHeight);
    keyboardComponent.setBounds(keyboardXCoord, keyboardYCoord, keyboardWidth, keyboardHeight);

    for (
         int keyNumber = keyboardComponent.getRangeStart();
         keyNumber < 75; // keyboardComponent.getRangeEnd()-1;
         keyNumber++
    ) {
        float lockButtonXCoord = keyboardXCoord + keyNumber*keyboardComponent.getKeyWidth();
        float lockButtonWidth = keyboardComponent.getKeyWidth();
        lockButtons[keyNumber]->setBounds(lockButtonXCoord, 200, lockButtonWidth, 12);
    }
}
