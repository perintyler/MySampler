/*** Piano960 | pitch/crepe.cpp ***/

#ifdef CREPE_MODEL

#include <memory>

#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/model.h"
#include "tensorflow/lite/tools/gen_op_registration.h"
#include "tensorflow/lite/delegates/nnapi/nnapi_delegate.h"
#include "tensorflow/lite/delegates/gpu/delegate.h"
#include "tensorflow/lite/optional_debug_tools.h"

#include "crepe.h"
#include "exceptions.h"

#ifdef PATH_TO_CREPE_MODEL
  const std::string CREPE_TFLITE_FILE { PATH_TO_CREPE_MODEL };
#else
  const std::string CREPE_TFLITE_FILE { "/usr/local/include/Piano960/crepe-models/model-full.tflite" };
#endif

static const bool VERBOSE = false;

std::unique_ptr<tflite::FlatBufferModel> model { };
std::unique_ptr<tflite::Interpreter> interpreter { };
std::unique_ptr<tflite::InterpreterOptions> options { };

bool pitch_detection::model_is_loaded()
{
    return model.get() != nullptr;
}

void pitch_detection::load_model()
{
    assert(!pitch_detection::model_is_loaded());

    tflite::StderrReporter error_reporter;
    model = tflite::FlatBufferModel::BuildFromFile(CREPE_TFLITE_FILE.c_str(), &error_reporter);

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

#endif
