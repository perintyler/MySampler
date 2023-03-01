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

#include "plugin_processor.h"
#include "midi.h"

const midi::MidiNumber FIRST_MIDI_NOTE = midi::C0;

const midi::MidiNumber LAST_MIDI_NOTE = midi::C3;

const juce::Colour BACKGROUND_COLOR = juce::Colours::grey;

class App: public juce::AudioProcessorEditor {
public:
    
    App(Piano960Processor&);
    
    ~App() override = default;

    void paint(juce::Graphics&) override;

    void resized() override;
    
private:

    Piano960Processor& processor;
    
    juce::MidiKeyboardComponent keyboard;
    
    juce::TextButton randomizeButton;
    
    juce::TextButton saveButton;

    std::vector<std::unique_ptr<juce::ImageButton>> lockButtons;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(App)
};
