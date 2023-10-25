/*** MySampler | Source/logs.cpp ***/

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#include "logs.h"
#include "paths.h"

static void writeToLogfile(std::string message)
{
    #ifdef LOGFILE_PATH
      std::ofstream logfile;
      logfile.open(LOGFILE_PATH);
      logfile << message << std::endl;
      logfile.close();
    #endif
}

static void logJSON(std::string messageType, std::map<std::string, std::string> content)
{
    std::stringstream stringstream;
    stringstream << "{\"type\": \"" << messageType << "\"";
    assert(!content.empty());
    
    for (const auto& [jsonKey, jsonValue] : content) {
        stringstream << ", \"" << jsonKey << "\": \"" << jsonValue << "\"";
    }

    stringstream << "}";
    
    writeToLogfile(stringstream.str());
}

void debug(std::vector<std::string> messages)
{
    #if defined(DEBUG) && defined(VERBOSE)
      for (const std::string& msg : messages) {
        std::cout << msg;
      }
      std::cout << std::endl;
    #endif
}

void debug(std::string message)
{
    debug({message});
}

void logBadSample(std::string path)
{
    logJSON("bad sample", {{"path", path}});
}

void logGoodSample(std::string path)
{
    logJSON("good sample", {{"path", path}});
}

