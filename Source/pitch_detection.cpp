// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - Piano960 | VST3, AU - - - - - - - - - - - - - - - - - - - -
// - - Created by Tyler Perin  - - - - - - - - - - - - - - - - - -
// - - Copyright © 2022 Sound Voyager. All rights reserved.- - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//   pitch_detection.cpp
//   ~~~~~~~~~~~~~~~~~~~
//
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#include <cassert>

#include "pitch_detection.h"

static const float PITCH_DETECTION_TOLERANCE = 0.10f;

float getPositionOfQuadraticPeak(const float* buffer, unsigned int startIndex, int bufferSize)
{
    assert(startIndex >= 0 && startIndex <= bufferSize);

    if (startIndex == 0 || startIndex == (bufferSize-1))
        return startIndex;
    
    unsigned int x0 = (startIndex   < 1         ) ? startIndex   : startIndex-1;
    unsigned int x2 = (startIndex+1 < bufferSize) ? startIndex+1 : startIndex;
    
    if (x0 == startIndex) {
        return (buffer[startIndex] <= buffer[x2]) ? startIndex : x2;
    } else if (x2 == startIndex) {
        return (buffer[startIndex] <= buffer[x0]) ? startIndex : x0;
    }
    
    float s0 = buffer[x0];
    float s1 = buffer[startIndex];
    float s2 = buffer[x2];
    
    return startIndex + 0.5*(s0 - s2) / (s0 - 2.0*s1 + s2);
}

// TODO: find minimal sample in `getFundementalFrequency` loop
unsigned int getIndexOfMinimumSample(const float *buffer, int bufferSize)
{
    unsigned int indexOfMinimumSample = 0;
    float minimumSample = buffer[0];
    for (int index = 0; index < bufferSize; index++)
    {
        indexOfMinimumSample = (minimumSample < buffer[index]) ? indexOfMinimumSample : index;
        minimumSample        = (minimumSample < buffer[index]) ? minimumSample        : buffer[index];
    }
    return indexOfMinimumSample;
}

// helper function
float getFundementalFrequency(float positionOfQuadraticPeak, int sampleRate)
{
    assert(positionOfQuadraticPeak > 0);
    return static_cast<float>(sampleRate) / positionOfQuadraticPeak;
}

/**
 * This function implements the YIN Pitch Dection algorithm.
 *   - http://audition.ens.fr/adc/pdf/2002_JASA_YIN.pdf
 **/
float getFundementalFrequency(const float* signal, int bufferSize, int sampleRate)
{
    int period;
    float delta = 0.0;
    float rollingSum = 0.0;
    float processedSignal[bufferSize];
    processedSignal[0] = 1.0;
        
    for (int tau = 1; tau < bufferSize; tau++) {
        processedSignal[tau] = 0.0;

        for (int shiftedIndex = 0; shiftedIndex < bufferSize; shiftedIndex++) {
            delta = signal[shiftedIndex] - signal[shiftedIndex + tau];
            processedSignal[tau] += (delta * delta);
        }
        
        rollingSum += processedSignal[tau];
        
        if (rollingSum != 0) processedSignal[tau] *= tau / rollingSum;
        else                 processedSignal[tau] = 1.0;

        period = tau - 3;
        
        if ((tau > 4) && (processedSignal[period] < PITCH_DETECTION_TOLERANCE)
                      && (processedSignal[period] < processedSignal[period + 1]))
        {
            float peakPosition = getPositionOfQuadraticPeak(processedSignal, period, bufferSize);
            return getFundementalFrequency(peakPosition, sampleRate);
        }
    }

    // TODO: compute min sample in the for loop above rather than iterating through the buffer again
    int indexOfMinSample = getIndexOfMinimumSample(processedSignal, bufferSize);
    float peakPosition = getPositionOfQuadraticPeak(processedSignal, indexOfMinSample, bufferSize);
    return getFundementalFrequency(peakPosition, sampleRate);
}
