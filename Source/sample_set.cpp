/*** MySampler | Source/sample_set.h ***/

#include "sample_set.h"

bool SampleSet::has(Note key) const
{
    return find(key) != end();
}

const Sample& SampleSet::get(Note note) const 
{
    assert(count(note) != 0);
    return at(note);
}

int SampleSet::length() const
{
    return static_cast<int>(size());
}

void SampleSet::set(Note key, std::filesystem::path filepath, Note rootNote)
{
    std::string sampleName = filepath.stem().string();
    insert_or_assign(key, Sample{sampleName, filepath, rootNote});
}

std::vector<NoteAndSample> SampleSet::asVector() const
{
    return std::vector<NoteAndSample>(begin(), end());
}

SampleSet SampleSet::filter(SampleFilterFunction isSampleIncluded) const
{
    SampleSet filtered;
    
    for (auto iterator = begin(); iterator != end(); iterator++) {
        Note note = iterator->first;
        const Sample& sample = iterator->second;

        if (isSampleIncluded(note, sample)) {
            filtered.set(note, sample.filepath, sample.rootNote);
        }
    }

    return filtered;
}

void SampleSet::filterInPlace(SampleFilterFunction isSampleIncluded)
{
    for (auto iterator = begin(); iterator != end();) {
        if (!isSampleIncluded(iterator->first, iterator->second)) {
            erase(iterator++);
        } else {
            ++iterator;
        }
    }
}

void SampleSet::pretty_print() const
{
    std::cout << "\n\n";
    std::cout << " _________________________________________________" << std::endl;
    std::cout << "| SampleSet" << std::endl;
    std::cout << "| ---------" << std::endl;

    for (auto iterator = begin(); iterator != end(); iterator++) {
        std::cout << " | - " << std::to_string(iterator->first) << ": ";
        iterator->second.pretty_print();
    }

    std::cout << "__________________________________________________";
    std::cout << "\n\n";
}
