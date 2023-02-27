/* logs.h */

#pragma once

#include <juce_core/juce_core.h>

namespace logs {
    void newBadSample  (juce::String);
    void newGoodSample (juce::String);
    void debug         (juce::String);
}
