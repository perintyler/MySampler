#pragma once

#include <string>

namespace config 
{
    std::string getSamplesDirectory();

    std::string getTestDataDirectory();

    std::string getPathToCREPEModel();
    
    std::string getPathToSPICEModel();
}