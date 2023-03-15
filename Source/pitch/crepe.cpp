/*** Piano960 | pitch/crepe.cpp ***/

/***************************************************************************************************************

-----------Subgraph-0 has 71 tensors and 32 nodes------------
1 Inputs: [0] -> 4096B (0.00MB)
1 Outputs: [64] -> 1440B (0.00MB)

Tensor  ID Name                      Type            AllocType          Size (Bytes/MB)    Shape      MemAddr-Offset  
Tensor   0 serving_default_input:0   kTfLiteFloat32  kTfLiteArenaRw     4096     / 0.00 [1,1024] [0, 4096)
Tensor   1 model_4/conv1/BiasAdd/... kTfLiteFloat32  kTfLiteMmapRo      4096     / 0.00 [1024] [88956208, 88960304)
Tensor   2 model_4/conv2/BiasAdd/... kTfLiteFloat32  kTfLiteMmapRo      512      / 0.00 [128] [88955684, 88956196)
Tensor   3 model_4/conv3/BiasAdd/... kTfLiteFloat32  kTfLiteMmapRo      512      / 0.00 [128] [88955160, 88955672)
Tensor   4 model_4/conv4/BiasAdd/... kTfLiteFloat32  kTfLiteMmapRo      512      / 0.00 [128] [88954636, 88955148)
Tensor   5 model_4/conv5/BiasAdd/... kTfLiteFloat32  kTfLiteMmapRo      1024     / 0.00 [256] [88953600, 88954624)
Tensor   6 model_4/conv6/BiasAdd/... kTfLiteFloat32  kTfLiteMmapRo      2048     / 0.00 [512] [88951540, 88953588)
Tensor   7 model_4/conv1/Conv2D      kTfLiteFloat32  kTfLiteMmapRo      2097152  / 2.00 [1024,512,1,1] [86854376, 88951528)
Tensor   8 model_4/conv2/Conv2D      kTfLiteFloat32  kTfLiteMmapRo      33554432 / 32.00 [128,64,1,1024] [53299932, 86854364)
Tensor   9 model_4/conv3/Conv2D      kTfLiteFloat32  kTfLiteMmapRo      4194304  / 4.00 [128,64,1,128] [49105616, 53299920)
Tensor  10 model_4/conv4/Conv2D      kTfLiteFloat32  kTfLiteMmapRo      4194304  / 4.00 [128,64,1,128] [44911300, 49105604)
Tensor  11 model_4/conv5/Conv2D      kTfLiteFloat32  kTfLiteMmapRo      8388608  / 8.00 [256,64,1,128] [36522680, 44911288)
Tensor  12 model_4/conv6/Conv2D      kTfLiteFloat32  kTfLiteMmapRo      33554432 / 32.00 [512,64,1,256] [2968236, 36522668)
Tensor  13 model_4/classifier/Bia... kTfLiteFloat32  kTfLiteMmapRo      1440     / 0.00 [360] [2966784, 2968224)
Tensor  14 model_4/transpose/tran... kTfLiteInt32    kTfLiteMmapRo      16       / 0.00 [4] [2966756, 2966772)
Tensor  15 model_4/input-reshape/... kTfLiteInt32    kTfLiteMmapRo      4        / 0.00 [1] [2966740, 2966744)
Tensor  16 model_4/input-reshape/... kTfLiteInt32    kTfLiteMmapRo      4        / 0.00 [1] [2966724, 2966728)
Tensor  17 model_4/input-reshape/... kTfLiteInt32    kTfLiteMmapRo      4        / 0.00 (null) [2966740, 2966744)
Tensor  18 model_4/input-reshape/... kTfLiteInt32    kTfLiteMmapRo      4        / 0.00 (null) [2966704, 2966708)
Tensor  19 model_4/flatten/Const     kTfLiteInt32    kTfLiteMmapRo      8        / 0.00 [2] [2966684, 2966692)
Tensor  20 model_4/conv1-BN/Fused... kTfLiteFloat32  kTfLiteMmapRo      4096     / 0.00 [1024] [2962576, 2966672)
Tensor  21 model_4/conv1-BN/Fused... kTfLiteFloat32  kTfLiteMmapRo      4096     / 0.00 [1024] [2958468, 2962564)
Tensor  22 model_4/conv2-BN/Fused... kTfLiteFloat32  kTfLiteMmapRo      512      / 0.00 [128] [2957944, 2958456)
Tensor  23 model_4/conv2-BN/Fused... kTfLiteFloat32  kTfLiteMmapRo      512      / 0.00 [128] [2957420, 2957932)
Tensor  24 model_4/conv3-BN/Fused... kTfLiteFloat32  kTfLiteMmapRo      512      / 0.00 [128] [2956896, 2957408)
Tensor  25 model_4/conv3-BN/Fused... kTfLiteFloat32  kTfLiteMmapRo      512      / 0.00 [128] [2956372, 2956884)
Tensor  26 model_4/conv4-BN/Fused... kTfLiteFloat32  kTfLiteMmapRo      512      / 0.00 [128] [2955848, 2956360)
Tensor  27 model_4/conv4-BN/Fused... kTfLiteFloat32  kTfLiteMmapRo      512      / 0.00 [128] [2955324, 2955836)
Tensor  28 model_4/conv5-BN/Fused... kTfLiteFloat32  kTfLiteMmapRo      1024     / 0.00 [256] [2954288, 2955312)
Tensor  29 model_4/conv5-BN/Fused... kTfLiteFloat32  kTfLiteMmapRo      1024     / 0.00 [256] [2953252, 2954276)
Tensor  30 model_4/conv6-BN/Fused... kTfLiteFloat32  kTfLiteMmapRo      2048     / 0.00 [512] [2951192, 2953240)
Tensor  31 model_4/conv6-BN/Fused... kTfLiteFloat32  kTfLiteMmapRo      2048     / 0.00 [512] [2949132, 2951180)
Tensor  32 model_4/classifier/MatMul kTfLiteFloat32  kTfLiteMmapRo      2949120  / 2.81 [360,2048] [0, 2949120)
Tensor  33 model_4/input-reshape/... kTfLiteInt32    ...itePersistentRo 8        / 0.00 [2] [-1, -1)
Tensor  34 model_4/input-reshape/... kTfLiteInt32    ...itePersistentRo 4        / 0.00 (null) [-1, -1)
Tensor  35 model_4/input-reshape/... kTfLiteInt32    kTfLiteArenaRw     16       / 0.00 [4] [4096, 4112)
Tensor  36 model_4/input-reshape/... kTfLiteFloat32  kTfLiteDynamic     4096     / 0.00 [1,1024,1,1] [-1, -1)
Tensor  37 model_4/conv1/Relu;mod... kTfLiteFloat32  kTfLiteArenaRw     1048576  / 1.00 [1,256,1,1024] [-1, -1)
Tensor  38 model_4/conv1-BN/Fused... kTfLiteFloat32  kTfLiteArenaRw     1048576  / 1.00 [1,256,1,1024] [-1, -1)
Tensor  39 model_4/conv1-BN/Fused... kTfLiteFloat32  kTfLiteArenaRw     1048576  / 1.00 [1,256,1,1024] [-1, -1)
Tensor  40 model_4/conv1-maxpool/... kTfLiteFloat32  kTfLiteArenaRw     524288   / 0.50 [1,128,1,1024] [-1, -1)
Tensor  41 model_4/conv2/Relu;mod... kTfLiteFloat32  kTfLiteArenaRw     65536    / 0.06 [1,128,1,128] [-1, -1)
Tensor  42 model_4/conv2-BN/Fused... kTfLiteFloat32  kTfLiteArenaRw     65536    / 0.06 [1,128,1,128] [-1, -1)
Tensor  43 model_4/conv2-BN/Fused... kTfLiteFloat32  kTfLiteArenaRw     65536    / 0.06 [1,128,1,128] [-1, -1)
Tensor  44 model_4/conv2-maxpool/... kTfLiteFloat32  kTfLiteArenaRw     32768    / 0.03 [1,64,1,128] [-1, -1)
Tensor  45 model_4/conv3/Relu;mod... kTfLiteFloat32  kTfLiteArenaRw     32768    / 0.03 [1,64,1,128] [-1, -1)
Tensor  46 model_4/conv3-BN/Fused... kTfLiteFloat32  kTfLiteArenaRw     32768    / 0.03 [1,64,1,128] [-1, -1)
Tensor  47 model_4/conv3-BN/Fused... kTfLiteFloat32  kTfLiteArenaRw     32768    / 0.03 [1,64,1,128] [-1, -1)
Tensor  48 model_4/conv3-maxpool/... kTfLiteFloat32  kTfLiteArenaRw     16384    / 0.02 [1,32,1,128] [-1, -1)
Tensor  49 model_4/conv4/Relu;mod... kTfLiteFloat32  kTfLiteArenaRw     16384    / 0.02 [1,32,1,128] [-1, -1)
Tensor  50 model_4/conv4-BN/Fused... kTfLiteFloat32  kTfLiteArenaRw     16384    / 0.02 [1,32,1,128] [-1, -1)
Tensor  51 model_4/conv4-BN/Fused... kTfLiteFloat32  kTfLiteArenaRw     16384    / 0.02 [1,32,1,128] [-1, -1)
Tensor  52 model_4/conv4-maxpool/... kTfLiteFloat32  kTfLiteArenaRw     8192     / 0.01 [1,16,1,128] [-1, -1)
Tensor  53 model_4/conv5/Relu;mod... kTfLiteFloat32  kTfLiteArenaRw     16384    / 0.02 [1,16,1,256] [-1, -1)
Tensor  54 model_4/conv5-BN/Fused... kTfLiteFloat32  kTfLiteArenaRw     16384    / 0.02 [1,16,1,256] [-1, -1)
Tensor  55 model_4/conv5-BN/Fused... kTfLiteFloat32  kTfLiteArenaRw     16384    / 0.02 [1,16,1,256] [-1, -1)
Tensor  56 model_4/conv5-maxpool/... kTfLiteFloat32  kTfLiteArenaRw     8192     / 0.01 [1,8,1,256] [-1, -1)
Tensor  57 model_4/conv6/Relu;mod... kTfLiteFloat32  kTfLiteArenaRw     16384    / 0.02 [1,8,1,512] [-1, -1)
Tensor  58 model_4/conv6-BN/Fused... kTfLiteFloat32  kTfLiteArenaRw     16384    / 0.02 [1,8,1,512] [-1, -1)
Tensor  59 model_4/conv6-BN/Fused... kTfLiteFloat32  kTfLiteArenaRw     16384    / 0.02 [1,8,1,512] [-1, -1)
Tensor  60 model_4/conv6-maxpool/... kTfLiteFloat32  kTfLiteArenaRw     8192     / 0.01 [1,4,1,512] [-1, -1)
Tensor  61 model_4/transpose/tran... kTfLiteFloat32  kTfLiteArenaRw     8192     / 0.01 [1,1,4,512] [-1, -1)
Tensor  62 model_4/flatten/Reshape   kTfLiteFloat32  kTfLiteArenaRw     8192     / 0.01 [1,2048] [-1, -1)
Tensor  63 model_4/classifier/Mat... kTfLiteFloat32  kTfLiteArenaRw     1440     / 0.00 [1,360] [-1, -1)
Tensor  64 StatefulPartitionedCall:0 kTfLiteFloat32  kTfLiteArenaRw     1440     / 0.00 [1,360] [-1, -1)
Tensor  65 (nil)                     kTfLiteNoType   kTfLiteMemNone     0        / 0.00 (null) [-1, -1)
Tensor  66 (nil)                     kTfLiteNoType   kTfLiteMemNone     0        / 0.00 (null) [-1, -1)
Tensor  67 (nil)                     kTfLiteNoType   kTfLiteMemNone     0        / 0.00 (null) [-1, -1)
Tensor  68 (nil)                     kTfLiteNoType   kTfLiteMemNone     0        / 0.00 (null) [-1, -1)
Tensor  69 (nil)                     kTfLiteNoType   kTfLiteMemNone     0        / 0.00 (null) [-1, -1)
Tensor  70 (nil)                     kTfLiteNoType   kTfLiteMemNone     0        / 0.00 (null) [-1, -1)

***************************************************************************************************************/

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

const float CREPE_MODEL_SAMPLE_RATE = 16000;

const float CLASSIFICATION_TENSOR_ID = 63;

const float CONFIDENCE_TENSOR_ID = 64;

const bool VERBOSE = false;

#ifdef PATH_TO_CREPE_MODEL
  const std::string CREPE_TFLITE_FILE { PATH_TO_CREPE_MODEL };
#else
  const std::string CREPE_TFLITE_FILE { "/usr/local/include/Piano960/crepe-models/model-full.tflite" };
#endif

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
    if (interpreterBuildResults != kTfLiteOk) { throw PitchDetectionModelLoadingError(); };

    if (VERBOSE) {
        tflite::PrintInterpreterState(interpreter.get());
    }
}

/** The CREPE model expects 1024-sample frames of the audio with hop 
 ** length of 10 milliseconds
 * 
 * 
 * pandas implementation from crepe repo below
 * 
 * ```
 * # make 1024-sample frames of the audio with hop length of 10 milliseconds
 * hop_length = int(model_srate * step_size / 1000)
 * n_frames = 1 + int((len(audio) - 1024) / hop_length)
 * frames = as_strided(audio, shape=(1024, n_frames),
 *                     strides=(audio.itemsize, hop_length * audio.itemsize))
 * frames = frames.transpose().copy()
 * ```
 * 
 * - https://github.com/marl/crepe/blob/d714d9ec88319af477301942efa82d604f1fd84b/crepe/core.py#L200
 **/
void pitch_detection::create1024SampleFrames(juce::AudioBuffer<float>& buffer, int sampleRate)
{
    // TODO
}

/**
 * ```
 * frames -= np.mean(frames, axis=1)[:, np.newaxis]
 * frames /= np.clip(np.std(frames, axis=1)[:, np.newaxis], 1e-8, None)
 * ```
 * 
 * - https://github.com/marl/crepe/blob/d714d9ec88319af477301942efa82d604f1fd84b/crepe/core.py#L207
 **/
void pitch_detection::normalizeAudio(juce::AudioBuffer<float>& buffer, int sampleRate)
{
    // TODO
}

// model requires single channel audio with a sample rate of 16000
void pitch_detection::downSampleAudio(juce::AudioBuffer<float>& buffer, int sampleRate)
{
    if(sampleRate < CREPE_MODEL_SAMPLE_RATE || buffer.getNumChannels() == 0) {
        throw BadAudioException();
    } else if (sampleRate == CREPE_MODEL_SAMPLE_RATE) {
        return;
    }
    
    float sampleRateRatio = CREPE_MODEL_SAMPLE_RATE / sampleRate;
    int numSamplesAfterDownSampling = sampleRateRatio*buffer.getNumSamples();

    for (int newSignalIndex = 0; newSignalIndex < numSamplesAfterDownSampling; newSignalIndex += 1)
    {
        int oldSignalIndex = static_cast<int>(std::round(sampleRateRatio*newSignalIndex));
        for (int channelIndex = 0; channelIndex < buffer.getNumChannels(); channelIndex++) {
            float newSample = buffer.getSample(channelIndex, oldSignalIndex);
            buffer.setSample(channelIndex, newSignalIndex, newSample);
        }
    }

    buffer.setSize(buffer.getNumChannels(), numSamplesAfterDownSampling);
}

/** Turns the audio into a single channel signal by computing the mean sample amplitude 
 ** of all channels 
 **/
void pitch_detection::makeAudioMono(juce::AudioBuffer<float>& buffer) 
{
    if (buffer.getNumChannels() == 0) {
        throw BadAudioException();
    } else if (buffer.getNumChannels() == 1) {
        return;
    }

    for (int sampleIndex = 0; sampleIndex < buffer.getNumSamples(); sampleIndex++) 
    {
        float sumOfAllChannels = 0;
        for (int channelIndex = 0; channelIndex < buffer.getNumChannels(); channelIndex++) {
            sumOfAllChannels += buffer.getSample(channelIndex, sampleIndex);
        }
        float averagedSample = sumOfAllChannels / buffer.getNumChannels();
        buffer.setSample(0 /* index of first and only channel */, sampleIndex, averagedSample);
    }

    buffer.setSize(1 /* num channels */, buffer.getNumSamples());
}

void feedAudioIntoModel(juce::AudioBuffer<float>& buffer)
{
    assert(model);
    assert(interpreter);

    float* input = interpreter->typed_input_tensor<float>(0);
    for (int sampleIndex = 0; sampleIndex < buffer.getNumSamples(); sampleIndex++) {
        input[sampleIndex] = buffer.getSample(0, sampleIndex);
    }

    auto allocationResults = interpreter->AllocateTensors();
    if (allocationResults != kTfLiteOk) { throw PitchDetectionModelLoadingError(); };

    interpreter->Invoke();
}

float convertModelOutputToFrequency(float* classification_output, float* confidence_output)
{
    return 0.0; // TODO
}

float pitch_detection::getFundementalFrequency(juce::AudioBuffer<float>& buffer, int sampleRate)
{
    if (true) { return 1000.0; }
    downSampleAudio(buffer, sampleRate);
    normalizeAudio(buffer, sampleRate);
    create1024SampleFrames(buffer, sampleRate);
    feedAudioIntoModel(buffer);
    float* classification_output = interpreter->typed_output_tensor<float>(CLASSIFICATION_TENSOR_ID);
    float* confidence_output = interpreter->typed_output_tensor<float>(CONFIDENCE_TENSOR_ID);
    return convertModelOutputToFrequency(classification_output, confidence_output);
}

#endif
