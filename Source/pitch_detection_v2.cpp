/* pitch_detection_v2.cpp */

tensorflow::SavedModelBundle load_model()
{
    tensorflow::SavedModelBundle model;
    tensorflow::Status status = tensorflow::LoadSavedModel(
        tensorflow::SessionOptions(), 
        tensorflow::RunOptions(), 
        "/usr/local/include/Piano960/model/model.pb", 
        {tensorflow::kSavedModelTagServe}, 
        &model
    );
    return model;
}

float pitch_detection_v2::getFundementalFrequency(const float* signal, int bufferSize, int sampleRate)
{
    return 0.0;
}
