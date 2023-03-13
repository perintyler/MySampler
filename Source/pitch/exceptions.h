/* pitch/pitch_detection_exceptions.h */

#pragma once

#include <exception>

struct FrequencyNotDetectedException : public std::exception 
{
    const char * what () const throw () 
    {
        return "The sample's fundemental frequency could not be reliably detected";
    }
};

struct PitchDetectionModelLoadingError : public std::exception 
{
    const char * what () const throw ()
    {
        return "The pitch detection model could not be loaded";
    }
};

struct InvalidFrequencyException : public std::exception
{
    const char * what () const throw () 
    {
        return "The detected frequency does not match to a valid MIDI note";
    }
};