/* config.cpp */

#include "config.h"
#include "paths.h"

std::string config::getSamplesDirectory()
{
    #ifdef SAMPLES_DIRECTORY
      return std::string { SAMPLES_DIRECTORY };
    #else
      return std::string { "/usr/local/include/Piano960/Resources" };
    #endif
}

std::string config::getTestDataDirectory()
{
    #ifdef TEST_DATA_DIRECTORY
      return std::string { TEST_DATA_DIRECTORY };
    #else
      return std::string { "Tests/test-data" };
    #endif
}

std::string config::getPathToCREPEModel()
{
    #ifdef PATH_TO_YIN_MODEL
      return std::string { PATH_TO_CREPE_MODEL };
    #else
      return std::string { "/usr/local/include/Piano960/crepe-models/model-full.tflite" };
    #endif
}

std::string config::getPathToSPICEModel()
{
    #ifdef PATH_TO_YIN_MODEL
      return std::string { PATH_TO_SPICE_MODEL };
    #else
      return std::string { "/usr/local/include/Piano960/spice-models/spice.tflite" };
    #endif
}

