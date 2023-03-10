/* pitch_detection/crepe.cpp */

#include <memory>

#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/model.h"
#include "tensorflow/lite/tools/gen_op_registration.h"
#include "tensorflow/lite/delegates/nnapi/nnapi_delegate.h"
#include "tensorflow/lite/delegates/gpu/delegate.h"
#include "tensorflow/lite/optional_debug_tools.h"

#include "pitch_detection/crepe.h"
#include "pitch_detection/exceptions.h"
#include "config.h"

std::unique_ptr<tflite::FlatBufferModel> model { };
std::unique_ptr<tflite::Interpreter> interpreter { };
std::unique_ptr<tflite::InterpreterOptions> options { };

static const bool VERBOSE = false;

bool pitch_detection::model_is_loaded()
{
    return model.get() != nullptr;
}

void pitch_detection::load_model()
{
    assert(!pitch_detection::model_is_loaded());

    tflite::StderrReporter error_reporter;
    model = tflite::FlatBufferModel::BuildFromFile(config::getPathToCREPEModel().c_str(), &error_reporter);

    tflite::ops::builtin::BuiltinOpResolver resolver;  
    options = std::make_unique<tflite::InterpreterOptions>();
    options->SetEnsureDynamicTensorsAreReleased();

    tflite::InterpreterBuilder builder(*model.get(), resolver, options.get());
    auto interpreterBuildResults = builder(&interpreter);
    if (interpreterBuildResults != kTfLiteOk) { throw pitch_detection::ModelLoadingError(); };

    auto allocationResults = interpreter->AllocateTensors();
    if (allocationResults != kTfLiteOk) { throw pitch_detection::ModelLoadingError(); };

    if (VERBOSE) {
        tflite::PrintInterpreterState(interpreter.get());
    }
}

float pitch_detection::getFundementalFrequency(juce::AudioBuffer<float>& buffer, int sampleRate)
{
    return 0.0;
}
