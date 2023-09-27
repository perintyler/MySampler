#!/bin/bash

# cachefile is installed by CMake
PATH_TO_CACHEFILE=/usr/local/include/Piano960/pitch_detection_cache.json;

# delete existing cachefile
rm $PATH_TO_CACHEFILE;

# re-create cachefile and write an empty object to it
echo "{}" > "$PATH_TO_CACHEFILE";

