/* LockableKeyboard.h */

#pragma once

#include <functional>
#include <memory>
#include <map>

#include <juce_graphics/juce_graphics.h>
#include <juce_audio_utils/juce_audio_utils.h>

#include "pitch/notes.h"

const NoteID FIRST_MIDI_NOTE = C2;

const NoteID LAST_MIDI_NOTE = C8;

using ImageButtonPointer = juce::Component::SafePointer<juce::ImageButton>;

using OnKeyLockStateChange = std::function<void(NoteID)>;

class LockableKeys: public juce::MidiKeyboardComponent
{
public:
    LockableKeys(juce::MidiKeyboardState&, OnKeyLockStateChange);

    ~LockableKeys() override;

    void resized() override;

private:
    void setLockButtonImage(ImageButtonPointer&, NoteID);

    void layoutLockButton(ImageButtonPointer&, NoteID);

    std::map<NoteID, ImageButtonPointer> lockButtons;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LockableKeys);
};
