/* plugin_editor.h */

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
//
// This file declares the `Piano960Editor` class, which is
// responsible for laying out and rendering the plugin's
// user interface.
//
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#pragma once

#include <map>

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_audio_utils/juce_audio_utils.h>

#include "audio_processor.h"
#include "midi.h"

const midi::MidiNumber FIRST_MIDI_NOTE = midi::C2;

const midi::MidiNumber LAST_MIDI_NOTE = midi::C8;

class App: public juce::AudioProcessorEditor {
public:
    
    App(AudioProcessor&);
    
    ~App() override = default;

    void paint(juce::Graphics&) override;

    void resized() override;
    
private:

    AudioProcessor& processor;
    
    juce::MidiKeyboardComponent keyboard;
    
    juce::TextButton randomizeButton;
    
    juce::TextButton saveButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(App)
};
