/*** MySampler | Source/sampler.cpp ***/

#include <cmath>
#include <string>
#include <random>
#include <algorithm>
#include <assert.h>

#include <juce_audio_formats/juce_audio_formats.h>

#include "logs.h"
#include "paths.h"
#include "config.h"
#include "presets.h"
#include "sound_source.h"
#include "pitch_detection/pitch_detection.h"
#include "sampler.h"

#ifdef SAMPLES_DIRECTORY
  const std::string PATH_TO_SAMPLES_DIRECTORY { SAMPLES_DIRECTORY };
#else
  const std::string PATH_TO_SAMPLES_DIRECTORY { "/usr/local/include/MySampler/samples" };
#endif

// ------------------------------------------------------------------------------------------
namespace { // ------------------ START OF ANONYMOUS NAMESPACE ------------------------------
// ------------------------------------------------------------------------------------------

using SampleReader = std::unique_ptr<juce::AudioFormatReader>;

static std::random_device randomDevice;
static std::mt19937 numberGenerator(randomDevice()); // Mersenne Twister
static std::uniform_real_distribution<double> uniformDistribution(0.0, 1.0); // unit interval uniform distribution

//
// Randomly selects a file from a nested directory of sample-packs
//  - https://stackoverflow.com/questions/58400066/how-to-quickly-pick-a-random-file-from-a-folder-tree
//
juce::String getPathToRandomSample(const std::set<SoundSource>& sound_sources)
{
    assert(!sound_sources.empty());
    SoundSource soundsource = std::vector<SoundSource>(sound_sources.begin(), sound_sources.end()).at(
        static_cast<int>(uniformDistribution(numberGenerator) * sound_sources.size())
    );
    
    std::filesystem::path soundsource_directory = 
        std::filesystem::path(PATH_TO_SAMPLES_DIRECTORY)
      / std::filesystem::path(soundSourceToString(soundsource)
    );

    using directory_iterator = std::filesystem::recursive_directory_iterator;
    int numSamplesInDirectory = 0;
    
    for (const std::filesystem::directory_entry& entry : directory_iterator(soundsource_directory)) {
        if (entry.path().extension() == ".wav") {
            numSamplesInDirectory++;
        }
    }
    
    std::string path;
    int numSamplesTraversed = 0;
    int randomSampleIndex = static_cast<int>(uniformDistribution(numberGenerator) * numSamplesInDirectory);
    assert(randomSampleIndex < numSamplesInDirectory);

    for (const std::filesystem::directory_entry &entry: directory_iterator(soundsource_directory)) {
        if (entry.path().extension() == ".wav") {
            if (numSamplesTraversed == randomSampleIndex) {
                path = entry.path().string();
                break;
            } else {
                numSamplesTraversed++;
            }
        }
    }

    return juce::String { path };
}

bool validateSample(juce::File& sample, juce::String pathToFile)
{
    if (!sample.existsAsFile()) {
        std::cerr << "wav file does not exist: " << pathToFile.toStdString() << std::endl;
        return false;
    } else if (sample.getFileExtension() != ".wav") {
        std::cerr << "sample is not a wav file: " << pathToFile.toStdString() << std::endl;
        return false;
    }

    return true;
}

// --------------------------------------------------------------------------------------
} // ---------------------------- END OF ANONYMOUS NAMESPACE ----------------------------
// --------------------------------------------------------------------------------------

RandomSampler::RandomSampler(Note firstNote, Note lastNote)
    : synthesiser()
    , firstNote(firstNote)
    , lastNote(lastNote)
{
    for (SoundSource soundsource : DEFAULT_SOUND_SOURCES) {
        sound_sources.insert(soundsource);
    }

    for (Note note = firstNote; note <= lastNote; note = static_cast<Note>(note+1)) {
        lockedKeys.insert({note, false});
    }

    for (auto i = 0; i < NUM_SYNTH_VOICES; ++i) {
        synthesiser.addVoice(new juce::SamplerVoice()); // woah. just noticed this new
        continue;
    }
    
    #ifdef TESTMODE
      randomizeAll(false); // randomize samples, but don't pitch shift
    #else
      randomizeAll();
    #endif
}

RandomSampler::RandomSampler() 
    : RandomSampler(FIRST_NOTE, LAST_NOTE)
{}

RandomSampler::~RandomSampler()
{
    synthesiser.clearSounds();
}

const Sample& RandomSampler::getSample(Note note) const
{
    return samples.get(note);
}
    
void RandomSampler::addSoundSource(SoundSource soundsource)
{
    sound_sources.insert(soundsource);
}

void RandomSampler::removeSoundSource(SoundSource soundsource)
{
    std::set<SoundSource>::iterator iterator = sound_sources.find(soundsource);

    if (iterator != sound_sources.end()) {
        sound_sources.erase(iterator);
    } else {
        std::cerr << "tried to erase a sound source that doesn't exist";
    }
}

bool RandomSampler::isKeyLocked(Note note) const
{
    return lockedKeys.at(note) == true;
}

void RandomSampler::lockKey(Note note)
{
    debug({"locking key: ", std::to_string(note)});
    lockedKeys[note] = true;
}

void RandomSampler::unlockKey(Note note)
{
    debug({"unlocking key: ", std::to_string(note)});
    lockedKeys[note] = false;
}

void RandomSampler::toggleLock(Note note)
{
    jassert(lockedKeys.count(note) == 1);

    if (isKeyLocked(note)) {
        lockKey(note);
    } else {
        unlockKey(note);
    }
}

bool RandomSampler::isReady() const
{
    return samples.length() == (lastNote - firstNote);
}

const SampleSet& RandomSampler::getAllSamples() const
{ 
    return samples; 
}

const SampleSet RandomSampler::getLockedSamples() const
{
    return samples.filter([this](Note note, const Sample&) {
        return isKeyLocked(note);
    });
}

void RandomSampler::setSamples(const SampleSet& newSamples)
{
    samples.clear();

    for (const auto& [note, sample] : newSamples) {
        samples.set(note, sample.filepath, sample.rootNote);
    }
}

std::set<SoundSource> RandomSampler::getSoundSourcesForKey(Note key)
{
    if (isLowEnd(key)) {
        return std::set{SoundSource::BASS};
    } else if (isHighEnd(key)) {
        return sound_sources; // TODO: figure out what sounds work best for high-end notes
    } else {
        return sound_sources;
    }
}

void RandomSampler::randomizeSound(Note key, bool pitch_shift)
{
    juce::File randomSample;
    int rootNoteOfSample;
    juce::String pathToFile;
    std::string sampleName;
    juce::WavAudioFormat wavFormat;
    std::unique_ptr<juce::AudioFormatReader> audioReader;
    bool foundValidSample = false;

    while (!foundValidSample) {

        pathToFile = getPathToRandomSample(getSoundSourcesForKey(key));
        sampleName = pathToFile.toStdString();
        juce::File randomSample(pathToFile);

        if (!validateSample(randomSample, pathToFile)) {
            logBadSample(pathToFile.toStdString());
            continue;
        }

        audioReader = std::unique_ptr<juce::AudioFormatReader>(
            wavFormat.createReaderFor(randomSample.createInputStream().release(), true)
        );
        
        juce::AudioSampleBuffer buffer;
        int bufferSize = static_cast<int>(audioReader->lengthInSamples);
        buffer.setSize(audioReader->numChannels, bufferSize);
        audioReader->read(&buffer, 0, bufferSize, 0, true, true);

        if (!pitch_shift) {
            rootNoteOfSample = key;
            foundValidSample = true;
        } else {
            try {
                rootNoteOfSample = detectNote(buffer, audioReader->sampleRate, 0, sampleName);
                foundValidSample = true;
            } catch (PitchDetectionException) {
                logBadSample(pathToFile.toStdString());
            }
        }
    }

    samples.set(key, sampleName, rootNoteOfSample);

    juce::BigInteger keyRange;
    keyRange.setRange(key, key+1, true);

    debug({
        "setting sample (root=", std::to_string(rootNoteOfSample), ") ", 
        "for note ", std::to_string(key), ": ", pathToFile.toStdString()
    });

    synthesiser.addSound(
        juce::SynthesiserSound::Ptr(new juce::SamplerSound(
            pathToFile, *audioReader, keyRange, rootNoteOfSample, ATTACK, RELEASE, SUSTAIN
        ))
    );
}

void RandomSampler::randomizeAll(bool pitch_shift /* = true */)
{
    bool soundsAlreadyExist = samples.length() > 0;

    for (Note key = firstNote; key <= lastNote; key = key+1) 
    {
        if (isKeyLocked(key)) {
            debug({"skipping locked key", std::to_string(key)});
            continue;
        }
        
        if (soundsAlreadyExist) {
            int soundIndex = key - firstNote;
            synthesiser.removeSound(soundIndex);
        }

        randomizeSound(key, pitch_shift);
    }
}
