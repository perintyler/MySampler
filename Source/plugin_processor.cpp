// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//   plugin_processor.cpp
//   ~~~~~~~~~~~~~~~~~~~~
//
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#include "plugin_processor.h"
#include "plugin_editor.h"

Piano960Processor::Piano960Processor()
    : AudioProcessor (BusesProperties().withOutput("Output", juce::AudioChannelSet::stereo(), true))
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
    if (layouts.getMainInputChannelSet() == juce::AudioChannelSet::disabled()
     || layouts.getMainOutputChannelSet() == juce::AudioChannelSet::disabled())
    {
        return false;
    }
 
    return layouts.getMainInputChannelSet() == layouts.getMainOutputChannelSet();
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
    for (int keyNumber = FIRST_MIDI_NOTE; keyNumber <= LAST_MIDI_NOTE; ++keyNumber)
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
