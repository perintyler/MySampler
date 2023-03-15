/*** Piano960 | main_view.h ***/

#pragma once

#include <memory>

#include <juce_graphics/juce_graphics.h>

#include "lockable_keys.h"

class MainView : public juce::Component, private juce::Timer {
public:
    
    MainView(
        juce::MidiKeyboardState& keyboardState,
        std::function<void()> onRandomizeButtonClicked, 
        std::function<void()> onSaveButtonClicked,
        OnKeyLockStateChange onLockButtonClicked
    );
    
    ~MainView() override = default;

    void resized() override;

    float getMinimumWidth() const;

private:

    void timerCallback() override;

    std::unique_ptr<juce::TextButton> randomizeButton;
    
    std::unique_ptr<juce::TextButton> saveButton;

    std::unique_ptr<LockableKeys> keyboard;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainView)
};
