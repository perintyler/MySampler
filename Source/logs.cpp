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

#ifndef NO_LOG
static NonDebugLogger goodSampleLogger("/var/log/Piano960/good-samples.txt");
static NonDebugLogger badSampleLogger("/var/log/Piano960/bad-samples.txt");
#endif

void logs::newGoodSample(const juce::String& sampleName)
{
    #ifndef NO_LOG
    goodSampleLogger.logMessage(sampleName);
    #endif
}

void logs::newBadSample(const juce::String& sampleName)
{
    #ifndef NO_LOG
    badSampleLogger.logMessage(sampleName);
    #endif
}

void logs::debug(const juce::String& message)
{
    #if !defined(NO_LOG) && !defined(PRODUCTION)
    juce::Logger::outputDebugString(message);
    #endif
}
