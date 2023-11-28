/*** Piano960 | Source/gui/keyboard.cpp */

#include <assert.h>
#include <utility>
#include <utility>
#include <memory>

#include <juce_gui_extra/juce_gui_extra.h>
#include "BinaryData.h"

#include "./lockable_keys.h"
#include "../notes.h"
#include "../logs.h"

static const juce::MidiKeyboardComponent::Orientation DEFAULT_ORIENTATION 
  = juce::MidiKeyboardComponent::horizontalKeyboard;

static const juce::Colour BLACK = juce::Colour::fromRGB(
  juce::uint8(256), juce::uint8(256), juce::uint8(256)
);

static const juce::Colour WHITE = juce::Colour::fromRGB(
  juce::uint8(0), juce::uint8(0), juce::uint8(0)
);

// -----------------------------------------------------------------------

KeyToolbar::KeyToolbar(Note note, AudioProcessor& p)
        : key (note)
        , processor (p)
        , shuffleButton(new juce::ImageButton())
        , lockButton(new juce::ImageButton())
        , likeButton(new juce::ImageButton())
        , deleteButton(new juce::ImageButton())
        , uploadButton(new juce::ImageButton())
{
    lockButton->setToggleable(true);
    lockButton->setClickingTogglesState(true);

    shuffleButton->setSize(KeyToolbar::BUTTON_SIZE, KeyToolbar::BUTTON_SIZE);
    lockButton->setSize(KeyToolbar::BUTTON_SIZE, KeyToolbar::BUTTON_SIZE);
    likeButton->setSize(KeyToolbar::BUTTON_SIZE, KeyToolbar::BUTTON_SIZE);
    deleteButton->setSize(KeyToolbar::BUTTON_SIZE, KeyToolbar::BUTTON_SIZE);
    uploadButton->setSize(KeyToolbar::BUTTON_SIZE, KeyToolbar::BUTTON_SIZE);

    loadIcons();
    setCallbacks();

    addAndMakeVisible(shuffleButton);
    addAndMakeVisible(lockButton);
    addAndMakeVisible(likeButton);
    addAndMakeVisible(deleteButton);
    addAndMakeVisible(uploadButton);
}

void KeyToolbar::setCallbacks()
{
    shuffleButton->onClick = [&key=key, &processor=processor]() {
        processor.sampler.randomizeSound(key);
    };

    lockButton->onClick = [&key=key, &processor=processor]() { 
        processor.sampler.toggleLock(key);
    };

    likeButton->onClick = [&key=key, &processor=processor]() {
        logGoodSample(processor.sampler.getSample(key).filepath.string());
    };

    deleteButton->onClick = [&key=key, &processor=processor]() {
        logBadSample(processor.sampler.getSample(key).filepath.string());
    };

    uploadButton->onClick = [&key=key, &processor=processor]() {
        // TODO
    };
}

void KeyToolbar::loadIcons()
{
    setButtonIcon(shuffleButton, BLACK, {
      BinaryData::shuffle_icon_png, BinaryData::shuffle_icon_pngSize
    });

    setToggleButtonIcons(lockButton, BLACK, 
      {BinaryData::locked_icon_png, BinaryData::locked_icon_pngSize}, 
      {BinaryData::unlocked_icon_png, BinaryData::unlocked_icon_pngSize}
    );

    setButtonIcon(likeButton, BLACK,
      {BinaryData::heart_icon_png, BinaryData::heart_icon_pngSize}
    );

    setButtonIcon(deleteButton, BLACK,
      {BinaryData::delete_icon_png, BinaryData::delete_icon_pngSize}
    );

    setButtonIcon(uploadButton, BLACK,
      {BinaryData::upload_icon_png, BinaryData::upload_icon_pngSize}
    );
}

KeyToolbar::~KeyToolbar()
{
    shuffleButton.deleteAndZero();
    lockButton.deleteAndZero();
    deleteButton.deleteAndZero();
    likeButton.deleteAndZero();
    uploadButton.deleteAndZero();
}

void KeyToolbar::resized()
{
    juce::FlexBox flexbox;
    
    flexbox.flexDirection = juce::FlexBox::Direction::column;
    flexbox.flexWrap = juce::FlexBox::Wrap::wrap;
    flexbox.justifyContent = juce::FlexBox::JustifyContent::spaceAround;
    flexbox.alignContent = juce::FlexBox::AlignContent::center;

    for (const auto child : getChildren()) {
        flexbox.items.add(
            juce::FlexItem(*child)
                .withMinWidth(KeyToolbar::BUTTON_SIZE)
                .withMinHeight(KeyToolbar::BUTTON_SIZE)
        );
    }

    flexbox.performLayout(juce::Rectangle<int>{
        0, 0, KeyToolbar::WIDTH, KeyToolbar::HEIGHT
    });
}

void KeyToolbar::paint(juce::Graphics& graphics)
{
    graphics.fillAll(juce::Colours::burlywood);
}

// -----------------------------------------------------------------------

LockableKeys::LockableKeys(AudioProcessor& processor)
    : juce::MidiKeyboardComponent(processor.getKeyboardState(), DEFAULT_ORIENTATION)
{
    setAvailableRange(FIRST_NOTE, LAST_NOTE);
    setScrollButtonsVisible(false);
    setKeyWidth(LockableKeys::WHITE_KEY_WIDTH);
    setBlackNoteWidthProportion(LockableKeys::BLACK_KEY_WIDTH_RATIO);
    setBufferedToImage(true);

    for (Note note = FIRST_NOTE; note <= LAST_NOTE; note++) 
    {
        std::unique_ptr<KeyToolbar> keyToolbar = std::make_unique<KeyToolbar>(note, processor);
        
        toolbars[note] = std::make_unique<KeyToolbar>(note, processor);
        toolbars[note]->setComponentID(noteToString(note) + "-toolbar");
        
        addAndMakeVisible(toolbars[note].get());
    }
}

LockableKeys::~LockableKeys()
{
    // removeAllChangeListeners();
    for (auto &[note, keyToolbar]: toolbars) {
        keyToolbar.reset();
    }
    toolbars.clear();
    clearKeyMappings();
}

void LockableKeys::layoutToolbar(Note key, std::unique_ptr<KeyToolbar>& toolbar)
{
    const juce::Rectangle keyBounds = getRectangleForKey(key);

    float xCoord, yCoord;
    if (isBlackKey(key)) {
        xCoord = keyBounds.getX() + keyBounds.getWidth()/2 - KeyToolbar::WIDTH/2 - 1;
        yCoord = keyBounds.getY();
    } else {
        xCoord = keyBounds.getX() + 1;
        yCoord = keyBounds.getY() + keyBounds.getHeight() - KeyToolbar::HEIGHT;
    }
    
    toolbar->setBounds(xCoord, yCoord, KeyToolbar::WIDTH, KeyToolbar::HEIGHT);
}

void LockableKeys::resized()
{
    juce::MidiKeyboardComponent::resized();
    for (auto &[key, keyToolbar]: toolbars) {
        layoutToolbar(key, keyToolbar);
    }
}
