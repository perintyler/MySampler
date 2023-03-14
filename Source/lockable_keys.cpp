#include <assert.h>

#include "lockable_keys.h"
#include "BinaryData.h"
#include "pitch/notes.h"
#include "logs.h"

static const juce::MidiKeyboardComponent::Orientation DEFAULT_ORIENTATION 
    = juce::MidiKeyboardComponent::horizontalKeyboard;

static const juce::Colour BLACK = juce::Colour::fromRGB(
    juce::uint8(256), juce::uint8(256), juce::uint8(256));

static const juce::Colour WHITE = juce::Colour::fromRGB(
    juce::uint8(0), juce::uint8(0), juce::uint8(0));

static const int LOCK_BUTTON_OFFSET = 0; // 2; // pixels

static const float WHITE_KEY_WIDTH = 40.0;

static const float BLACK_KEY_WIDTH_RATIO = 1.0;

LockableKeys::LockableKeys(juce::MidiKeyboardState& state, OnKeyLockStateChange toggleLock)
    : juce::MidiKeyboardComponent(state, DEFAULT_ORIENTATION)
{
    setAvailableRange(FIRST_MIDI_NOTE, LAST_MIDI_NOTE);
    setScrollButtonsVisible(false);
    setKeyWidth(WHITE_KEY_WIDTH);
    setBlackNoteWidthProportion(BLACK_KEY_WIDTH_RATIO);
//    setBufferedToImage(true);

    for (Note note = FIRST_MIDI_NOTE; note <= LAST_MIDI_NOTE; note++) {
        juce::String lockButtonName = juce::String("lock-button") + juce::String(note);
        
        auto lockButton = juce::Component::SafePointer<juce::ImageButton>(
            new juce::ImageButton(lockButtonName)
        );

        lockButton->setComponentID(juce::String { note });
        lockButton->setToggleable(true);
        lockButton->setClickingTogglesState(true);
        lockButton->onClick = [note, toggleLock]() { toggleLock(note); };
        
        lockButtons.insert(std::pair<Note, ImageButtonPointer>(note, lockButton));
        setLockButtonImage(lockButton, note);
        addAndMakeVisible(lockButton);
    }
}

LockableKeys::~LockableKeys()
{
    for (auto &[note, lockButton]: lockButtons)
        lockButton.deleteAndZero();
}

void LockableKeys::setLockButtonImage(ImageButtonPointer& lockButton, Note note)
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
        true,            // resizeButtonNowToFitThisImage
        true,            // rescaleImagesWhenButtonSizeChanges
        true,            // preserveImageProportions
        unlockedImage,   // normal image
        1.0,             // imageOpacityWhenNormal
        color,           // overlayColourWhenNormal
        unlockedImage,   // overImage
        0.5,             // imageOpacityWhenOver
        color,           // overlayColourWhenOver
        lockedImage,     // downImage
        1.0,             // imageOpacityWhenDown
        color,           // overlayColourWhenDown
        false            // hitTestAlphaThreshold
    );
}

void LockableKeys::layoutLockButton(ImageButtonPointer& lockButton, Note note)
{
    const juce::Rectangle keyBounds = getRectangleForKey(note);
    const bool isBlackKey = isBlackNote(note);

    const float keyXCoord = keyBounds.getX();
    const float keyYCoord = keyBounds.getY();
    const float keyWidth = isBlackKey ? getBlackNoteWidth() : keyBounds.getWidth();
    const float keyHeight = isBlackKey ? getBlackNoteLength() : keyBounds.getHeight();

    const float buttonSize = 0.25*keyWidth;
    const float xCoord = keyXCoord + 0.5*(keyWidth-buttonSize) - LOCK_BUTTON_OFFSET;
    const float yCoord = 
          isBlackKey
        ? keyYCoord + 0.12*getBlackNoteLength()
        : getBlackNoteLength() + 0.5*(keyHeight-getBlackNoteLength()) - 0.5*buttonSize;
        
    lockButton->setSize(buttonSize, buttonSize);
    lockButton->setCentrePosition(xCoord, yCoord);
}

void LockableKeys::resized()
{
    juce::MidiKeyboardComponent::resized();
    for (auto &[note, lockButton]: lockButtons) {
        layoutLockButton(lockButton, note);
    }
}
