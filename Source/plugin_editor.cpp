// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//   plugin_editor.cpp
//   ~~~~~~~~~~~~~~~~~
//
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#include "plugin_editor.h"
#include <juce_graphics/juce_graphics.h>
#include "BinaryData.h"

void setLockButtonImage(juce::ImageButton* lockButton, bool isBlack, bool isLocked)
{
    const char* imageData;
    int imageSize;
    juce::Colour color;
    
    if (isLocked && isBlack) {
        imageData = BinaryData::lockedblack_png;
        imageSize = BinaryData::lockedblack_pngSize;
        color = BLACK;
    } else if (isLocked && !isBlack) {
        imageData = BinaryData::lockedwhite_png;
        imageSize = BinaryData::lockedwhite_pngSize;
        color = WHITE;
    } else if (!isLocked && isBlack) {
        imageData = BinaryData::unlockedblack_png;
        imageSize = BinaryData::unlockedblack_pngSize;
        color = BLACK;
    } else { // unlocked and white
        imageData = BinaryData::unlockedwhite_png;
        imageSize = BinaryData::unlockedwhite_pngSize;
        color = WHITE;
    }

    juce::Image image = juce::ImageFileFormat::loadFrom(imageData, imageSize);
    lockButton->setImages(
        true,                                // resizeButtonNowToFitThisImage
        true,                                // rescaleImagesWhenButtonSizeChanges
        true,                                // preserveImageProportions
        image,                               // normal image
        1.0,                                 // imageOpacityWhenNormal
        color,                               // overlayColourWhenNormal
        image,                               // overImage
        1.0,                                 // imageOpacityWhenOver
        color,                               // overlayColourWhenOver
        image,                               // downImage
        1.0,                                 // imageOpacityWhenDown
        color,                               // overlayColourWhenDown
        true                                 // hitTestAlphaThreshold
    );
}

Piano960Editor::Piano960Editor(Piano960Processor& processor)
    : AudioProcessorEditor (&processor)
    , audioProcessor       (processor)
    , keyboardComponent    (audioProcessor.getKeyboardState(), juce::MidiKeyboardComponent::horizontalKeyboard)
    , randomizeButton      (RANDOMIZE_BUTTON_LABEL)
{

    randomizeButton.onClick = [&]() { processor.randomize_samples(); };

    keyboardComponent.setScrollButtonsVisible(false);
    keyboardComponent.setKeyWidth(WHITE_KEY_WIDTH);
    keyboardComponent.setBlackNoteWidthProportion(BLACK_KEY_WIDTH_RATIO);
    keyboardComponent.setAvailableRange(FIRST_MIDI_NOTE, LAST_MIDI_NOTE);
    
    addAndMakeVisible(randomizeButton);
    addAndMakeVisible(keyboardComponent, 0);

    for (
         int keyNumber = keyboardComponent.getRangeStart();
         keyNumber <= keyboardComponent.getRangeEnd();
         keyNumber++
    ) {
        juce::String lockButtonName = juce::String("lock-button") + juce::String(keyNumber);
        juce::ImageButton* lockButton = new juce::ImageButton(lockButtonName);
        keyboardComponent.addAndMakeVisible(lockButton);
        lockButtons.push_back(std::unique_ptr<juce::ImageButton>(lockButton));
    }
    
    const int pluginWidth = keyboardComponent.getTotalKeyboardWidth() + HORIZONTAL_MARGIN_SIZE*2;
    const int pluginHeight = 250;
    setSize(pluginWidth, pluginHeight);

//    processor.randomize_samples();
}

int Piano960Editor::getFirstMidiKey() const
{
    return keyboardComponent.getRangeStart();
}

int Piano960Editor::getLastMidiKey() const
{
    return keyboardComponent.getRangeEnd();
}

juce::ImageButton* Piano960Editor::getLockButton(int keyNumber) const
{
    int buttonIndex = keyNumber - keyboardComponent.getRangeStart();
    jassert(buttonIndex >= 0);
    jassert(buttonIndex < lockButtons.size());
    return lockButtons.at(buttonIndex).get();
}

// render the UI
void Piano960Editor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    g.setColour(BACKGROUND_COLOR);
    
    for (
         int keyNumber = keyboardComponent.getRangeStart();
         keyNumber <= keyboardComponent.getRangeEnd();
         keyNumber++
    ) {
        bool isBlackKey = piano::isBlackNote(keyNumber);
        setLockButtonImage(getLockButton(keyNumber), !isBlackKey, false);
    }
}

void layoutLockButton(
    juce::ImageButton* lockButton,
    const int keyNumber,
    const juce::Rectangle<float> keyBounds,
    const float blackKeyWidth,
    const float blackKeyHeight
) {
    const bool isBlackKey = piano::isBlackNote(keyNumber);
    const float keyXCoord = keyBounds.getX();
    const float keyYCoord = keyBounds.getY();
    const float keyWidth = isBlackKey ? blackKeyWidth : keyBounds.getWidth();
    const float keyHeight = isBlackKey ? blackKeyHeight : keyBounds.getHeight();

    const float buttonSize = 0.25*keyWidth;
    const float xCoord = keyXCoord + 0.5*(keyWidth-buttonSize) - LOCK_BUTTON_OFFSET;
    const float yCoord = isBlackKey
        ? keyYCoord + 0.12*blackKeyHeight
        : blackKeyHeight + 0.5*(keyHeight-blackKeyHeight) - 0.5*buttonSize;
        
    lockButton->setSize(buttonSize, buttonSize);
    lockButton->setCentrePosition(xCoord, yCoord);
}

// lay out the subcomponents
void Piano960Editor::resized()
{
    int keyboardWidth = getWidth() - 20;
    int keyboardHeight = 200;

    int buttonHeight = 30;
    int buttonWidth = keyboardWidth;
    
    int keyboardXCoord = HORIZONTAL_MARGIN_SIZE;
    int keyboardYCoord = VERTICAL_MARGIN_SIZE + buttonHeight + 5;
    
    int buttonXCoord = HORIZONTAL_MARGIN_SIZE;
    int buttonYCoord = VERTICAL_MARGIN_SIZE;

    randomizeButton.setBounds(buttonXCoord, buttonYCoord, buttonWidth, buttonHeight);
    keyboardComponent.setBounds(keyboardXCoord, keyboardYCoord, keyboardWidth, keyboardHeight);
    
    for (
         int keyNumber = keyboardComponent.getRangeStart();
         keyNumber <= keyboardComponent.getRangeEnd();
         keyNumber++
    ) {
        layoutLockButton(
            getLockButton(keyNumber), keyNumber,
            keyboardComponent.getRectangleForKey(keyNumber),
            keyboardComponent.getBlackNoteWidth(),
            keyboardComponent.getBlackNoteLength()
        );
    }
}
