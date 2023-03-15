/*** Piano960 | pitch/exceptions.h ***/

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
        return "Tensorflow pitch detection model could not be loaded";
    }
};

struct NoteDoesNotExistException : public std::exception
{
    const char * what () const throw () 
    {
        return "Frequency falls outside the range of valid MIDI notes";
    }
};