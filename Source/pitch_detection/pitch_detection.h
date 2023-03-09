/* pitch_detection/pitch_detection.h */

#pragma once

#include <string>

#include "pitch_detection/exceptions.h"

#if defined(YIN_ALGO)
  #include "pitch_detection/yin.h"
#elif defined(SPICE_MODEL)
  #include "pitch_detection/spice.h"
#else
  #include "pitch_detection/crepe.h"
#endif

namespace pitch_detection 
{
    #if defined(YIN_ALGO)
      const std::string ALGORITHM_NAME = "YIN";
    #elif defined(SPICE_MODEL)
      const std::string ALGORITHM_NAME = "SPICE";
    #elif defined(CREPE_MODEL)
      const std::string ALGORITHM_NAME = "CREPE";
    #else
      const std::string ALGORITHM_NAME = "UNKNOWN";
    #endif
}

