/* Piano960 | plugin_processor.h */

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
//
// This file declares the `AudioProcessor` class, which is
// responsible for processing MIDI input and producing audio
// output.
//
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#pragma once

#include <map>

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_devices/juce_audio_devices.h>

#include "pitch_detection/pitch.h"
#include "samples.h"
#include "logs.h"
#include "config.h"


class AudioProcessor: public juce::AudioProcessor 
{
public:

    RandomSampler sampler;

    AudioProcessor();
    
    ~AudioProcessor() override = default;
    
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    
    void releaseResources() override;

    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    
    juce::AudioProcessorEditor* createEditor() override;

    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return juce::String{PLUGIN_NAME}; }

    bool acceptsMidi() const override { return true; }
    
    bool producesMidi() const override { return false; }
    
    bool isMidiEffect() const override { return false; }
    
    double getTailLengthSeconds() const override { return 0.0; }

    int getNumPrograms() override { return 1; }
    
    int getCurrentProgram() override { return 0; }
    
    void setCurrentProgram(int index) override {}
    
    const juce::String getProgramName(int index) override { return {}; }
    
    void changeProgramName(int index, const juce::String& newName) override {}

    void getStateInformation(juce::MemoryBlock&) override {}
    
    void setStateInformation(const void* data, int sizeInBytes) override {}

    juce::MidiKeyboardState& getKeyboardState() { return keyboardState; }
    
    juce::Synthesiser& synthesiser() { return sampler.synthesiser; }

    void randomizeSamples() { sampler.randomize(); }
    
    void logSamples() const;

private:

    juce::MidiKeyboardState keyboardState;

    juce::MidiMessageCollector midiCollector;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioProcessor)
};
