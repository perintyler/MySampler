/*** Piano960 | app.h ***/

#pragma once

#include <memory>

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_audio_utils/juce_audio_utils.h>

#include "audio_processor.h"
#include "main_view.h"

class App: public juce::AudioProcessorEditor {
public:
    
    App(AudioProcessor&);
    
    virtual ~App() override = default;

    void paint(juce::Graphics&) override;

    void resized() override;
    
private:

    AudioProcessor& processor;
    
    std::unique_ptr<MainView> view;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(App)
};
