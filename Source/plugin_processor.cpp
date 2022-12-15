// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - Piano960 | VST3, AU - - - - - - - - - - - - - - - - - - - -
// - - Created by Tyler Perin  - - - - - - - - - - - - - - - - - -
// - - Copyright © 2022 Sound Voyager. All rights reserved.- - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//   plugin_processor.cpp
//   ~~~~~~~~~~~~~~~~~~~~
//
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#include "plugin_processor.h"
#include "plugin_editor.h"

Piano960Processor::Piano960Processor()
    : AudioProcessor (BusesProperties().withInput("Input",  juce::AudioChannelSet::stereo(), true)
                                       .withOutput("Output", juce::AudioChannelSet::stereo(), true))
{
    for (auto i = 0; i < NUM_VOICES; ++i)
        synthesiser.addVoice (new juce::SamplerVoice());
}

void Piano960Processor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    midiCollector.reset (sampleRate);
    synthesiser.setCurrentPlaybackSampleRate (sampleRate);
}

bool Piano960Processor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}

void Piano960Processor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals; // What is this?
    
    // TODO: investigate if i actually need this (the plugin only recieves midi date)
    // clear output channels that didn't contain input data since
    // they aren't guaranteed to be empty (they may contain garbage)
    for (auto i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    midiCollector.removeNextBlockOfMessages (midiMessages, buffer.getNumSamples());
    keyboardState.processNextMidiBuffer (midiMessages, 0, buffer.getNumSamples(), true);
    synthesiser.renderNextBlock (buffer, midiMessages, 0, buffer.getNumSamples());
}

void Piano960Processor::randomize_samples()
{
    synthesiser.clearSounds();
    for (int keyNumber = piano::C3; keyNumber < piano::C7; ++keyNumber)
        synthesiser.addSound(getRandomSamplerSound(keyNumber));
}

juce::AudioProcessorEditor* Piano960Processor::createEditor()
{
    return new Piano960Editor (*this);
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Piano960Processor();
}
