/*** Piano960 | app.cpp ***/

#include <assert.h>

#include <juce_graphics/juce_graphics.h>
#include <functional>

#include "app.h"

const juce::Colour BACKGROUND_COLOR = juce::Colours::grey;

const int HORIZONTAL_MARGIN_SIZE = 10; // pixels

const float PLUGIN_HEIGHT = 250.0;

App::App(AudioProcessor& audioProcessor) 
    : AudioProcessorEditor (&audioProcessor)
    , processor (audioProcessor)
    , view (std::make_unique<MainView>(
        processor.getKeyboardState(),
        [this]() { processor.sampler.randomize(); }, // randomize button click callback
        [this]() { processor.sampler.randomize(); }, // save button click callback
        [this](Note note) {                              // lock key button click callback
            if (this->processor.sampler.isKeyLocked(note)) {
                this->processor.sampler.unlockKey(note);
            } else {
                this->processor.sampler.lockKey(note);
            }
        }
    ))
{
    setSize(view->getMinimumWidth() + 2*HORIZONTAL_MARGIN_SIZE, PLUGIN_HEIGHT);

    addAndMakeVisible(view.get());

    setResizable(false, false);
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
