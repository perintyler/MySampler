// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//   pitch_detection.h
//   ~~~~~~~~~~~~~~~~~
//
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#pragma once

#include <exception>

static const float PITCH_DETECTION_TOLERANCE = 0.10f;

struct FrequencyNotDetectedException : public std::exception {
    const char * what () const throw ();
};

float getFundementalFrequency(const float* signal, int bufferSize, int sampleRate, bool doubleCheck = false);
