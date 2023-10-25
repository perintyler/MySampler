/*** Piano960 | lockable_keys.h */

#pragma once

#include <functional>
#include <memory>
#include <map>

#include <juce_graphics/juce_graphics.h>
#include <juce_audio_utils/juce_audio_utils.h>

#include "../config.h"
#include "../notes.h"
#include "../audio_processor.h"
#include "icon_button.h"

class KeyToolbar: public juce::Component {
public:
    const static int HEIGHT = 100;
    const static int WIDTH = 13;
    const static int BUTTON_SIZE = 12;
        
    KeyToolbar(Note, AudioProcessor&);
    ~KeyToolbar();

    void resized() override;
    
    void paint(juce::Graphics&) override;
private:
    void loadIcons();
    void setCallbacks();

private:
    Note key;
    AudioProcessor& processor;
    ImageButtonPointer shuffleButton;
    ImageButtonPointer lockButton;
    ImageButtonPointer likeButton;
    ImageButtonPointer deleteButton;
    ImageButtonPointer uploadButton;
};

class LockableKeys: public juce::MidiKeyboardComponent
{
public:
    static constexpr float WHITE_KEY_WIDTH = 40.0;

    static constexpr float BLACK_KEY_WIDTH_RATIO = 1.0;

    LockableKeys(AudioProcessor&);

    ~LockableKeys() override;

    void resized() override;

private:
    void layoutToolbar(Note, std::unique_ptr<KeyToolbar>&);

    std::map<Note, std::unique_ptr<KeyToolbar>> toolbars;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LockableKeys);
};
