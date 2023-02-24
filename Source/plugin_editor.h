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

const juce::Colour BACKGROUND_COLOR = juce::Colours::grey;

const int HORIZONTAL_MARGIN_SIZE = 10; // pixels

const int VERTICAL_MARGIN_SIZE = 5; // pixels

const int FIRST_MIDI_NOTE = 24;

const int LAST_MIDI_NOTE = 48;

const float WHITE_KEY_WIDTH = 40.0;

const float BLACK_KEY_WIDTH_RATIO = 1.0;

const juce::String RANDOMIZE_BUTTON_LABEL { "randomize" };

const juce::String SAVE_BUTTON_LABEL { "save" };

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
    
    juce::TextButton saveButton;

    std::vector<std::unique_ptr<juce::ImageButton>> lockButtons;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Piano960Editor)
};
