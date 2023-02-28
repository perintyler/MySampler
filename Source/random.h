/* random.h */

#pragma once

#include <string>

// selects a random file from a nested directory structure using reservoir sampling
std::string getPathToRandomFile(const std::string& directory);
