/* logs.cpp */

#include "logs.h"

/** A `NonDebugLogger`  is just like a `juce::FileLogger`, except log messages don't
 ** get written to the debug stream (i.e. stdout)
 **/
class NonDebugLogger: public juce::FileLogger {
public:
    NonDebugLogger(juce::String pathToFile, const juce::String& welcomeMessage = "")
        : juce::FileLogger(juce::File { pathToFile }, welcomeMessage)
    {}

    void logMessage (const juce::String& message) override
    {
        juce::FileOutputStream out (getLogFile().getFullPathName(), 256);
        out << message << juce::newLine;
    }
};

static NonDebugLogger goodSampleLogger("/var/log/Piano960/good-samples.txt");
static NonDebugLogger badSampleLogger("/var/log/Piano960/bad-samples.txt");

void logs::newGoodSample(const juce::String& sampleName)
{
    goodSampleLogger.logMessage(sampleName);
}

void logs::newBadSample(const juce::String& sampleName)
{
    badSampleLogger.logMessage(sampleName);
}

void logs::debug(const juce::String& message)
{
    juce::Logger::outputDebugString(message);
}

