/* pitch_detection_v2.h */

#pragma once

namespace pitch_detection_v2 
{ 
    float getFundementalFrequency(const float* signal, int bufferSize, int sampleRate);
}
