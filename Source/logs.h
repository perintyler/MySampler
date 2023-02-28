/* logs.h */

#pragma once

#include <juce_core/juce_core.h>

namespace logs {
    void newGoodSample (const juce::String& sampleName);
    void newBadSample  (const juce::String& sampleName);
    void debug         (const juce::String& message);
}
