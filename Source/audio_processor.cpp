// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//   plugin_processor.cpp
//   ~~~~~~~~~~~~~~~~~~~~
//
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#include "audio_processor.h"
#include "app.h"
#include "logs.h"
#include "pitch_detection_v2.h"

AudioProcessor::AudioProcessor()
    : juce::AudioProcessor ( BusesProperties().withOutput("Output", juce::AudioChannelSet::stereo(), true) )
{
    for (auto i = 0; i < NUM_VOICES; ++i)
        synthesiser.addVoice (new juce::SamplerVoice());
        
    for (int midiNumber = FIRST_MIDI_NOTE; midiNumber <= LAST_MIDI_NOTE; midiNumber++)
        lockedKeys[midiNumber] = false;

    #ifdef PITCH_DETECTION_V2
    if (!pitch_detection_v2::model_is_loaded()) { pitch_detection_v2::load_model(); }
    #endif
}

void AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    midiCollector.reset (sampleRate);
    synthesiser.setCurrentPlaybackSampleRate (sampleRate);
}

bool AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainInputChannelSet() == juce::AudioChannelSet::disabled()
     || layouts.getMainOutputChannelSet() == juce::AudioChannelSet::disabled())
    {
        return false;
    }
 
    return layouts.getMainInputChannelSet() == layouts.getMainOutputChannelSet();
}

void AudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
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

void AudioProcessor::randomize_samples()
{
    synthesiser.clearSounds();
    for (midi::MidiNumber midiNumber = FIRST_MIDI_NOTE; midiNumber <= LAST_MIDI_NOTE; midiNumber++) {
        if (!isKeyLocked(midiNumber)) {
            juce::SamplerSound* sound = getRandomSamplerSound(midiNumber);
            sampleNames[midiNumber] = sound->getName();
            synthesiser.addSound(sound);
        }
    }
}

bool AudioProcessor::isKeyLocked(midi::MidiNumber midiNumber) const
{
    jassert(lockedKeys.count(midiNumber));
    return lockedKeys.at(midiNumber) == true;
}

void AudioProcessor::lockKey(midi::MidiNumber midiNumber)
{
    jassert(lockedKeys.count(midiNumber));
    lockedKeys[midiNumber] = true;
}

void AudioProcessor::unlockKey(midi::MidiNumber midiNumber)
{
    jassert(lockedKeys.count(midiNumber));
    lockedKeys[midiNumber] = false;
}

void AudioProcessor::logSamples() const
{
    for (midi::MidiNumber midiNumber = FIRST_MIDI_NOTE; midiNumber <= LAST_MIDI_NOTE; midiNumber++) {
        juce::String sampleName = sampleNames.at(midiNumber);
        if (isKeyLocked(midiNumber)) {
            logs::newGoodSample(sampleName);
        } else {
            logs::newBadSample(sampleName);
        }
    }
}

juce::AudioProcessorEditor* AudioProcessor::createEditor()
{
    return new App (*this);
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AudioProcessor();
}
