// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - Piano960 | VST3, AU - - - - - - - - - - - - - - - - - - - -
// - - Created by Tyler Perin  - - - - - - - - - - - - - - - - - -
// - - Copyright © 2022 Sound Voyager. All rights reserved.- - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
//   pitch_detection.h
//   ~~~~~~~~~~~~~~~~~
//
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#pragma once

float getFundementalFrequency(const float* signal, int bufferSize, int sampleRate);
