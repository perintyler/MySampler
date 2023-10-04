/*** MySampler | Source/sampler.h ***/

#pragma once

#include <map>

#include <juce_audio_devices/juce_audio_devices.h>

#include "notes.h"
#include "sample.h"
#include "sample_set.h"
#include "sound_source.h"

/***
 ** A synthesizer that generates a sound source for each key using a different 
 ** random sample from MySampler's installed sample set. A key's sample can be
 ** locked/unlocked (using the `lockKey` and `unlockKey` functions), meaning the
 ** key's sound source won't be re-randomized every time `RandomSampler::randomize` 
 ** is called.
 ***/
class RandomSampler
{
public:
    juce::Synthesiser synthesiser; // make this private

    RandomSampler(Note firstNote, Note lastNote);

    RandomSampler();

    bool isKeyLocked(Note) const;

    void lockKey(Note);

    void unlockKey(Note);

    const Sample& getSample(Note) const;

    void addSoundSource(SoundSource);

    void removeSoundSource(SoundSource);

    void randomize(bool pitch_shift = true);

    bool isReady() const;

    const SampleSet& getAllSamples() const;

    const SampleSet getLockedSamples() const;

    void setSamples(const SampleSet&);

private:
    Note firstNote;
    Note lastNote;
    SampleSet samples {};
    std::map<Note, bool> lockedKeys {};
    std::set<SoundSource> sound_sources {};
};