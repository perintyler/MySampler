#!/bin/bash

SCRIPT=$(realpath "$0");
SCRIPT_DIR=$(dirname "$SCRIPT");
REPO_PATH=$(dirname "$SCRIPT_DIR");
UNIT_TEST_BUILD=$REPO_PATH/build/Tests/unit-tests;

bash $SCRIPT_DIR/clear_terminal.sh;
valgrind $UNIT_TEST_BUILD --leak-check=full;