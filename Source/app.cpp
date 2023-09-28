/*** Piano960 | app.cpp ***/

#include <assert.h>

#include <juce_graphics/juce_graphics.h>
#include <functional>

#include "app.h"
#include "presets.h"

const juce::Colour BACKGROUND_COLOR = juce::Colours::grey;

const int HORIZONTAL_MARGIN_SIZE = 10; // pixels

const float PLUGIN_HEIGHT = 500.0;

App::App(AudioProcessor& audioProcessor) 
    : AudioProcessorEditor (&audioProcessor)
    , processor (audioProcessor)
    , view (std::make_unique<MainView>(processor.getKeyboardState(),
    
        // called when the randomize button is clicked
        [&processor = processor]() 
        { 
            processor.sampler.randomize(); 
        },
    
        // called when the user clicks the save button on the new preset dialog
        [&processor=processor, &view=view](std::string presetName) 
        {
            const SampleSet lockedSamples = processor.sampler.getLockedSamples();
    
            if (lockedSamples.length() == 0) {
                return false;
            } else {
                savePreset(presetName, processor.sampler.getLockedSamples());
                view->refresh();
                return true;
            }
        },
    
        // called when the lock button on a key is clicked/unclicked (i.e. locked/unlocked)
        [&processor = processor](Note note) {
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

/** Renders the UI
 **/
void App::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    g.setColour(BACKGROUND_COLOR);
}

/** Lays out subcomponents
 **/
void App::resized()
{
    view->setBounds(getLocalBounds());
}
