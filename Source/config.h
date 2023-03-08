#pragma once

#include <string>

namespace config {
  
    bool useYIN();
    bool useSPICE();
    bool useCREPE();

    std::string getSamplesDirectory();
    std::string getTestDataDirectory();

    std::string getPathToCREPEModel();
    std::string getPathToSPICEModel();
}