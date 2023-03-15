/*** Piano960 | plugin_processor.cpp ***/

#include <assert.h>
#include <string>

#include "audio_processor.h"
#include "app.h"
#include "logs.h"
#include "pitch/pitch.h"

AudioProcessor::AudioProcessor()
    : juce::AudioProcessor (BusesProperties().withOutput("Output", juce::AudioChannelSet::stereo(), true))
    , keyboardState ()
    , midiCollector ()
    , synthesiser ()
{
    for (auto i = 0; i < NUM_VOICES; ++i)
        synthesiser.addVoice (new juce::SamplerVoice());
        
    for (int midiNumber = FIRST_MIDI_NOTE; midiNumber <= LAST_MIDI_NOTE; midiNumber++)
        lockedKeys[midiNumber] = false;

    loadPitchDetectionModel();

    #ifndef TESTMODE
    randomizeSamples();
    #endif
}

void AudioProcessor::releaseResources()
{
    keyboardState.allNotesOff(0);

    synthesiser.clearSounds();
    sampleNames.clear();
    lockedKeys.clear();

    for (auto i = 0; i < NUM_VOICES; ++i) {
        synthesiser.removeVoice(i);
    }
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
    // juce::ScopedNoDenormals noDenormals; // What is this?
    
    // TODO: investigate if i actually need this (the plugin only recieves midi date)
    // clear output channels that didn't contain input data since
    // they aren't guaranteed to be empty (they may contain garbage)
    for (auto i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    midiCollector.removeNextBlockOfMessages (midiMessages, buffer.getNumSamples());
    keyboardState.processNextMidiBuffer (midiMessages, 0, buffer.getNumSamples(), true);
    synthesiser.renderNextBlock (buffer, midiMessages, 0, buffer.getNumSamples());
}

void AudioProcessor::randomizeSamples()
{
    synthesiser.clearSounds();
    for (Note note = FIRST_MIDI_NOTE; note <= LAST_MIDI_NOTE; note++) {
        if (!isKeyLocked(note)) {
            juce::SynthesiserSound::Ptr sound = getRandomSamplerSound(note);
            sampleNames[note] = static_cast<juce::SamplerSound*>(sound.get())->getName();
            synthesiser.addSound(sound);
        }
    }
}

bool AudioProcessor::isKeyLocked(Note note) const
{
    jassert(lockedKeys.count(note));
    return lockedKeys.at(note) == true;
}

void AudioProcessor::lockKey(Note note)
{
    jassert(lockedKeys.count(note));
    lockedKeys[note] = true;
}

void AudioProcessor::unlockKey(Note note)
{
    jassert(lockedKeys.count(note));
    lockedKeys[note] = false;
}

void AudioProcessor::logSamples() const
{
    for (Note note = FIRST_MIDI_NOTE; note <= LAST_MIDI_NOTE; note++) {
        juce::String sampleName = sampleNames.at(note);
        if (isKeyLocked(note)) {
            logs::newGoodSample(sampleName);
        } else {
            logs::newBadSample(sampleName);
        }
    }
}

juce::AudioProcessorEditor* AudioProcessor::createEditor()
{
    return new App(*this);
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AudioProcessor();
}
