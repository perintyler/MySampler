/*** Piano960 | plugin_processor.cpp ***/

#include <assert.h>
#include <string>

#include "config.h"
#include "audio_processor.h"
#include "logs.h"
#include "pitch_detection/pitch_detection.h"
#include "gui/app.h"

AudioProcessor::AudioProcessor()
    : juce::AudioProcessor (BusesProperties().withOutput("Output", juce::AudioChannelSet::stereo(), true))
    , sampler (FIRST_NOTE, LAST_NOTE)
    , keyboardState ()
    , midiCollector ()
{
    loadPitchDetectionModel();
}

void AudioProcessor::releaseResources()
{
    keyboardState.allNotesOff(0);

    // synthesiser().clearSounds();

    for (auto i = 0; i < NUM_SYNTH_VOICES; ++i) {
        synthesiser().removeVoice(i);
    }
}

void AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    midiCollector.reset(sampleRate);
    synthesiser().setCurrentPlaybackSampleRate(sampleRate);
}

bool AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    return true;
    // if (layouts.getMainInputChannelSet() == juce::AudioChannelSet::disabled()
    //  || layouts.getMainOutputChannelSet() == juce::AudioChannelSet::disabled())
    // {
    //     return false;
    // }
 
    // return layouts.getMainInputChannelSet() == layouts.getMainOutputChannelSet();
}

void AudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    // https://forum.juce.com/t/when-to-use-scopednodenormals-and-when-to-not/37112
    juce::ScopedNoDenormals noDenormals;
    
    // clear output channels that didn't contain input data since
    // they aren't guaranteed to be empty (they may contain garbage)
    for (auto i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    midiCollector.removeNextBlockOfMessages (midiMessages, buffer.getNumSamples());
    keyboardState.processNextMidiBuffer (midiMessages, 0, buffer.getNumSamples(), true);
    synthesiser().renderNextBlock (buffer, midiMessages, 0, buffer.getNumSamples());
}

// void AudioProcessor::logSamples() const
// {
//     for (Note note = FIRST_MIDI_NOTE; note <= LAST_MIDI_NOTE; note++) {
//         const Sample& sample = sampler.getSample(note);
//         if (sampler.isKeyLocked(note)) {
//             logs::newGoodSample(sample.name);
//         } else {
//             logs::newBadSample(sample.name);
//         }
//     }
// }

juce::AudioProcessorEditor* AudioProcessor::createEditor()
{
    return new App(*this);
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AudioProcessor();
}
