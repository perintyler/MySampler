/*** Piano960 | app.cpp ***/

#include <assert.h>

#include <juce_graphics/juce_graphics.h>
#include <functional>

#include "app.h"
#include "presets.h"

const juce::Colour BACKGROUND_COLOR = juce::Colours::grey;

const int HORIZONTAL_MARGIN_SIZE = 10; // pixels

const float PLUGIN_HEIGHT = 250.0;

App::App(AudioProcessor& audioProcessor) 
    : AudioProcessorEditor (&audioProcessor)
    , processor (audioProcessor)
    , view (std::make_unique<MainView>(
        processor.getKeyboardState(),
        [&processor = processor]() { processor.sampler.randomize(); }, // randomize button click callback
        [&processor = processor]() { processor.sampler.randomize(); }, // save button click callback

        // save presets
        [&processor = processor](std::string presetName) 
        {
            const SampleSet lockedSamples = processor.sampler.getLockedSamples();

            if (lockedSamples.length() == 0)
                return false;

            savePreset(presetName, processor.sampler.getLockedSamples()); 
            return true;
        },

        [&processor = processor](Note note) {                              // lock key button click callback
            if (processor.sampler.isKeyLocked(note)) {
                processor.sampler.unlockKey(note);
            } else {
                processor.sampler.lockKey(note);
            }
        }
    ))
{
    setSize(view->getMinimumWidth() + 2*HORIZONTAL_MARGIN_SIZE, PLUGIN_HEIGHT);

    addAndMakeVisible(view.get());

    setResizable(false, false);
    
    processor.randomizeSamples();
}

/** Render the UI
 **/
void App::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    g.setColour(BACKGROUND_COLOR);
}

/** Layout subcomponents
 **/
void App::resized()
{
    view->setBounds(getLocalBounds());
}
