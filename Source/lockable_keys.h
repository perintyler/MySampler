/* LockableKeyboard.h */

#pragma once

#include <functional>
#include <memory>
#include <map>

#include <juce_graphics/juce_graphics.h>
#include <juce_audio_utils/juce_audio_utils.h>

#include "midi.h"

const midi::MidiNumber FIRST_MIDI_NOTE = midi::C2;

const midi::MidiNumber LAST_MIDI_NOTE = midi::C8;

using ImageButtonPointer = juce::Component::SafePointer<juce::ImageButton>;

using OnKeyLockStateChange = std::function<void(midi::MidiNumber)>;

class LockableKeys: public juce::MidiKeyboardComponent
{
public:
    LockableKeys(juce::MidiKeyboardState&, OnKeyLockStateChange);

    ~LockableKeys() override;

    void resized() override;

private:
    void setLockButtonImage(ImageButtonPointer&, midi::MidiNumber);

    void layoutLockButton(ImageButtonPointer&, midi::MidiNumber);

    std::map<midi::MidiNumber, ImageButtonPointer> lockButtons;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LockableKeys);
};
