/*** Piano960 | lockable_keys.h */

#pragma once

#include <functional>
#include <memory>
#include <map>

#include <juce_graphics/juce_graphics.h>
#include <juce_audio_utils/juce_audio_utils.h>

#include "../config.h"
#include "../audio_processor.h"

using ImageButtonPointer = juce::Component::SafePointer<juce::ImageButton>;

class LockableKeys: public juce::MidiKeyboardComponent
{
public:
    LockableKeys(AudioProcessor&);

    ~LockableKeys() override;

    void resized() override;

private:
    void setLockButtonImage(ImageButtonPointer&, Note);

    void layoutLockButton(ImageButtonPointer&, Note);

    std::map<Note, ImageButtonPointer> lockButtons;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LockableKeys);
};
