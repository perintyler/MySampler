/*** Piano960 | pitch/exceptions.h ***/

#pragma once

#include <exception>

struct PitchDetectionException : public std::exception
{};

struct FrequencyNotDetectedException : PitchDetectionException 
{
    const char * what () const throw () 
    {
        return "The sample's fundemental frequency could not be reliably detected";
    }
};

struct PitchDetectionModelLoadingError : PitchDetectionException 
{
    const char * what () const throw ()
    {
        return "Tensorflow pitch detection model could not be loaded";
    }
};

struct NoteDoesNotExistException : PitchDetectionException
{
    const char * what () const throw () 
    {
        return "Frequency falls outside the range of valid MIDI notes";
    }
};

struct BadAudioException : PitchDetectionException
{
    const char * what () const throw () 
    {
        return "Audio quality is too bad to work with";
    }
};