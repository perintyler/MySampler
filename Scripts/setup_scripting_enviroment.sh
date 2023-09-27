#!/bin/bash

SCRIPT=$(realpath "$0");
SCRIPT_DIR=$(dirname "$SCRIPT");
REPO_PATH=$(dirname "$SCRIPT_DIR");

SCRIPTING_REQUIREMENTS_FILE=$SCRIPT_DIR/requirements.txt;
PYTHON_ENV_DIRECTORY=$REPO_PATH/env;

sudo apt-get install -y libxcursor-dev libxrandr-dev libxinerama-dev libxi-dev libasound2-dev;

if [ ! -d "$PYTHON_ENV_DIRECTORY" ]; then
  python3 -m venv env;
  python -m pip install -r $SCRIPTING_REQUIREMENTS_FILE;
fi

. env/bin/activate;
