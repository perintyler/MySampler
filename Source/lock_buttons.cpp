/* lock_buttons.cpp */

#include "lock_buttons.h"
#include "BinaryData.h"
#include "midi.h"

const int LOCK_BUTTON_OFFSET = 2; // pixels

const juce::Colour BLACK = juce::Colour::fromRGB(juce::uint8(256), juce::uint8(256), juce::uint8(256));
const juce::Colour WHITE = juce::Colour::fromRGB(juce::uint8(0), juce::uint8(0), juce::uint8(0));

void setLockButtonImage(juce::ImageButton* lockButton, bool isBlack, bool isLocked)
{
   juce::Image unlockedImage = juce::ImageFileFormat::loadFrom(
        BinaryData::unlockedwhite_png,
        BinaryData::unlockedwhite_pngSize
    ).convertedToFormat(juce::Image::PixelFormat::RGB);
    
    juce::Image lockedImage = juce::ImageFileFormat::loadFrom(
        BinaryData::lockedwhite_png,
        BinaryData::lockedwhite_pngSize
    ).convertedToFormat(juce::Image::PixelFormat::RGB);
    
    juce::Colour color = WHITE; // isBlack ? BLACK : WHITE;

    lockButton->setImages(
        true,                                // resizeButtonNowToFitThisImage
        true,                                // rescaleImagesWhenButtonSizeChanges
        true,                                // preserveImageProportions
        unlockedImage,                       // normal image
        1.0,                                 // imageOpacityWhenNormal
        color,                               // overlayColourWhenNormal
        unlockedImage,                       // overImage
        0.5,                                 // imageOpacityWhenOver
        color,                               // overlayColourWhenOver
        lockedImage,                         // downImage
        1.0,                                 // imageOpacityWhenDown
        color,                               // overlayColourWhenDown
        false                                // hitTestAlphaThreshold
    );
}

void layoutLockButton(
    juce::ImageButton* lockButton,
    midi::MidiNumber midiNumber,
    const juce::Rectangle<float> keyBounds,
    float blackKeyWidth,
    float blackKeyHeight
) {
    const bool isBlackKey = midi::isBlackNote(midiNumber);
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

void addAndMakeLockButtonsVisible(juce::MidiKeyboardComponent& keyboard, Piano960Processor& processor)
{
    for (midi::MidiNumber midiNumber = keyboard.getRangeStart();
         midiNumber <= keyboard.getRangeEnd();
         midiNumber++
    ) {
        juce::String lockButtonName = juce::String("lock-button") + juce::String(midiNumber);
        juce::ImageButton* lockButton = new juce::ImageButton(lockButtonName);
        lockButton->setToggleable(true);
        lockButton->setClickingTogglesState(true);
        
        lockButton->onClick = [midiNumber, lockButton, &processor] {
            if (processor.isKeyLocked(midiNumber))
                processor.unlockKey(midiNumber);
            else
                processor.lockKey(midiNumber);
        };

        layoutLockButton(
            lockButton, midiNumber, keyboard.getRectangleForKey(midiNumber),
            keyboard.getBlackNoteWidth(), keyboard.getBlackNoteLength()
        );
        
        setLockButtonImage(lockButton, !midi::isBlackNote(midiNumber), false);

        keyboard.addAndMakeVisible(lockButton);
    }
}
