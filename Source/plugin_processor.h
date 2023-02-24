/* plugin_processor.h */

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
//
// This file declares the `Piano960Processor` class, which is
// responsible for processing MIDI input and producing audio
// output.
//
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#pragma once

#include <map>

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_devices/juce_audio_devices.h>

#include "midi.h"
#include "samples.h"

const int NUM_VOICES = 8;

const juce::String PLUGIN_NAME { "Piano960" };

class Piano960Processor: public juce::AudioProcessor {
public:

    Piano960Processor();
    
    ~Piano960Processor() override = default;
    
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    
    void releaseResources() override {}

    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    
    juce::AudioProcessorEditor* createEditor() override;

    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return PLUGIN_NAME; }

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
    
    void randomize_samples();

    bool isKeyLocked(int keyNumber) const;
    
    void lockKey(int keyNumber);
    
    void unlockKey(int keyNumber);
    
    void logSamples() const;
    
private:
    
    juce::MidiKeyboardState keyboardState;

    juce::MidiMessageCollector midiCollector;

    juce::Synthesiser synthesiser;
    
    std::unordered_map<int, bool> lockedKeys {};

    std::unordered_map<int, juce::String> sampleNames {};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Piano960Processor)
};
