// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//   plugin_editor.h
//   ~~~~~~~~~~~~~~~
//
// This file declares the `Piano960Editor` class, which is
// responsible for the plugin's user interface.
//
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_audio_utils/juce_audio_utils.h>

#include "plugin_processor.h"

const juce::Colour BACKGROUND_COLOR = juce::Colours::grey;

const int LEFT_MARGIN_SIZE = 10; // pixels

const int TOP_MARGIN_SIZE = 5; // pixels

const juce::String RANDOMIZE_BUTTON_LABEL { "randomize" };

class Piano960Editor: public juce::AudioProcessorEditor {
public:
    
    Piano960Editor(Piano960Processor&);
    
    ~Piano960Editor() override = default;

    void paint(juce::Graphics&) override;

    void resized() override;
    
private:
    
    Piano960Processor& audioProcessor;
    
    juce::MidiKeyboardComponent keyboardComponent;
    
    juce::TextButton randomizeButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Piano960Editor)
};
