/* plugin_editor.h */

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
//
// This file declares the `Piano960Editor` class, which is
// responsible for laying out and rendering the plugin's
// user interface.
//
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_audio_utils/juce_audio_utils.h>

#include "lockable_keys.h"
#include "audio_processor.h"
#include "midi.h"

class App: public juce::AudioProcessorEditor {
public:
    
    App(AudioProcessor&);
    
    ~App() override = default;

    void paint(juce::Graphics&) override;

    void resized() override;
    
private:

    AudioProcessor& processor;
    
    juce::TextButton randomizeButton;
    
    juce::TextButton saveButton;

    LockableKeys keyboard;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(App)
};
