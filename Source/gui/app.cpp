/*** Piano960 | app.cpp ***/

#include <assert.h>

#include <juce_graphics/juce_graphics.h>
#include <functional>

#include "app.h"
#include "../presets.h"

const juce::Colour BACKGROUND_COLOR = juce::Colours::grey;

const int VERTICAL_MARGIN_SIZE = 8; // pixels

const int HORIZONTAL_MARGIN_SIZE = 15; // pixels

const float PLUGIN_HEIGHT = 360.0;

App::App(AudioProcessor& audioProcessor) 
    : AudioProcessorEditor (&audioProcessor)
    , processor (audioProcessor)
    , view (std::make_unique<MainView>(processor))
{
    setSize(view->getMinimumWidth() + 2*HORIZONTAL_MARGIN_SIZE, PLUGIN_HEIGHT);

    addAndMakeVisible(view.get());

    setResizable(false, false);
    
    processor.randomizeSamples();
}

/*** Renders the UI ***/
void App::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    g.setColour(BACKGROUND_COLOR);
}

/*** Lays out subcomponents ***/
void App::resized()
{
    int xCoord = HORIZONTAL_MARGIN_SIZE;
    int yCoord = VERTICAL_MARGIN_SIZE;
    int width = getLocalBounds().getWidth() - 2*HORIZONTAL_MARGIN_SIZE;
    int height = getLocalBounds().getHeight() - 2*VERTICAL_MARGIN_SIZE;
    view->setBounds(xCoord, yCoord, width, height);
}
