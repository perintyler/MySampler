/* pitch_detection/exceptions.h */

#pragma once

#include <exception>

namespace pitch_detection 
{
    struct FrequencyNotDetectedException : public std::exception 
    {
        const char * what () const throw () 
        {
            return "The sample's fundemental frequency could not be reliably detected";
        }
    };

    struct ModelLoadingError : public std::exception 
    {
        const char * what () const throw ()
        {
            return "The pitch detection model could not be loaded";
        }
    };
}