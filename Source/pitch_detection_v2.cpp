/* pitch_detection_v2.cpp */

/** Notes
 * 
 *  -- tensorflow's c++ interface seems to be the path of least resistance, since we're loading
 *     protobuf files generated by tensorflow, but it comes at the cost of build complexity
 *  -- https://stackoverflow.com/questions/56837288/tensorflow-lite-c-api-example-for-inference
 *  -- model is currently installed to /usr/local by cmake, but this doesn't seem right. Investigate.
 *  -- SPICE Model: https://www.tensorflow.org/hub/tutorials/spice
 *  -- "The SPICE model needs as input an audio file at a sampling rate of 16kHz 
 *      and with only one channel (mono).
 **/

#include <cassert>

#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/model.h"
#include "tensorflow/lite/tools/gen_op_registration.h"

const float MINIMUM_CONFIDENCE_THRESHOLD = 0.8;

const int SPICE_MODEL_SAMPLE_RATE = 16000;

const int SPICE_MODEL_NUM_CHANNELS = 1;

// the constants below were taken from https://tfhub.dev/google/spice/2

const float PT_OFFSET = 25.58;

const float PT_SLOPE = 63.07;

const float FMIN = 10.0;

const float BINS_PER_OCTAVE = 12.0;

std::unique_ptr<tflite::FlatBufferModel> model { };
std::unique_ptr<tflite::Interpreter> interpreter { };

bool pitch_detection_v2::model_is_loaded()
{
    return model.get() != nullptr;
}
