/* logs.cpp */

#include "logs.h"

/** A `NonDebugLogger`  is just like a `juce::FileLogger`, except log messages don't
 ** get written to the debug stream (i.e. stdout)
 **/
class NonDebugLogger: public juce::FileLogger {
public:
    NonDebugLogger(const juce::String pathToFile, const juce::String& welcomeMessage = "")
        : juce::FileLogger(juce::File { pathToFile }, welcomeMessage)
    {}

    void logMessage (const juce::String& message) override
    {
        juce::FileOutputStream out (getLogFile().getFullPathName(), 256);
        out << message << juce::newLine;
    }
};

NonDebugLogger badSampleLogger("/Users/tylerperin/garage/Piano960/logs/bad-samples.txt");

void logs::newBadSample(juce::String sampleName)
{
    badSampleLogger.logMessage(sampleName);
}

