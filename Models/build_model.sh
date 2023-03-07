#!/bin/bash

MODEL_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd );
CREPE_DIR=$MODEL_DIR/crepe;
CREPE_MODELS_DIR=$MODEL_DIR/crepe-models;

function setup_enviroment()
{
    rm $CREPE_MODELS_DIR/*.tflite; # delete any already built models

    pushd $MODEL_DIR;
    python3.8 -m venv env;
    . env/bin/activate;
    popd;

    python3.8 -m pip install --upgrade pip;
    python3.8 -m pip install -r $CREPE_DIR/requirements.txt;
    python3.8 -m pip install tensorflow;
}

function build_models()
{
    pushd $CREPE_DIR;
    python3.8 setup.py install
    popd;

    cp $CREPE_DIR/crepe/model-full.h5 $CREPE_MODELS_DIR;
    cp $CREPE_DIR/crepe/model-large.h5 $CREPE_MODELS_DIR;
    cp $CREPE_DIR/crepe/model-medium.h5 $CREPE_MODELS_DIR;
    cp $CREPE_DIR/crepe/model-small.h5 $CREPE_MODELS_DIR;
    cp $CREPE_DIR/crepe/model-tiny.h5 $CREPE_MODELS_DIR;

    python3.8 $MODEL_DIR/convert_h5_to_tflite.py
}

function cleanup()
{
    deactivate;
    rm $CREPE_DIR/crepe/*.h5;
    rm $CREPE_DIR/crepe/*.h5.bz2;
    rm $CREPE_MODELS_DIR/*.h5
    rm -r $CREPE_DIR/build;
    rm -r $CREPE_DIR/dist;
    rm -r $CREPE_DIR/crepe.egg-info;
}

setup_enviroment;
build_models;
cleanup;

