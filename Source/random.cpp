/* random.cpp */

#include "random.h"

#include <random>
#include <filesystem>
#include <cassert>

static std::random_device randomDevice;
static std::mt19937 numberGenerator(randomDevice()); // Mersenne Twister
static std::uniform_real_distribution<double> uniformDistribution(0.0, 1.0); // unit interval uniform distribution

std::string getPathToRandomFile(const std::string& directory)
{
    std::string path;
    int numFilesTraversed = 1;
    std::filesystem::recursive_directory_iterator fileIterator(directory);
    
    for (const std::filesystem::directory_entry &entry: fileIterator) {
        if (!std::filesystem::is_directory(entry)) {
            if (uniformDistribution(numberGenerator) < (1.0 / numFilesTraversed)) {
               path = entry.path().string();
            }
            numFilesTraversed++;
        }
    }

    return path;
}
