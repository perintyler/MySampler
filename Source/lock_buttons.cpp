/* lock_buttons.cpp */

#include "lock_buttons.h"
#include "BinaryData.h"
#include "piano.h"

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
    const float yCoord =
          isBlackKey
        ? keyYCoord + 0.12*blackKeyHeight
        : blackKeyHeight + 0.5*(keyHeight-blackKeyHeight) - 0.5*buttonSize;
        
    lockButton->setSize(buttonSize, buttonSize);
    lockButton->setCentrePosition(xCoord, yCoord);
}

void addAndMakeLockButtonsVisible(juce::MidiKeyboardComponent& keyboard, Piano960Processor& processor)
{
    for (int keyNumber = keyboard.getRangeStart();
         keyNumber <= keyboard.getRangeEnd();
         keyNumber++
    ) {
        juce::String lockButtonName = juce::String("lock-button") + juce::String(keyNumber);
        juce::ImageButton* lockButton = new juce::ImageButton(lockButtonName);
        lockButton->setToggleable(true);
        lockButton->setClickingTogglesState(true);
        
        lockButton->onClick = [keyNumber, lockButton, &processor] {
            if (processor.isKeyLocked(keyNumber))
                processor.unlockKey(keyNumber);
            else
                processor.lockKey(keyNumber);
        };

        layoutLockButton(
            lockButton, keyNumber,
            keyboard.getRectangleForKey(keyNumber),
            keyboard.getBlackNoteWidth(),
            keyboard.getBlackNoteLength()
        );
        
        setLockButtonImage(lockButton, !piano::isBlackNote(keyNumber), false);

        keyboard.addAndMakeVisible(lockButton);
    }
}
