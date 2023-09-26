/*** Piano960 | presets.cpp ***/

/***
 * 
 * The preset file is a JSON file where each key is a preset name. Each value
 * will be an object mapping a key's MIDI number to a sample file path.
 *  
 * ```
 * {
 *    "my preset": {
 *      23: {
 *        "path": "path/to/sample/for/key/with/midi/number/23.wav",
 *        "note": 42
 *      },
 *      ...
 *    },
 * }
 ***/

#include <assert>
#include <iostream>
#include <fstream>

#include "JsonCpp/json/json.h"

#include "presets.h"

#include "paths.h"

#ifndef PATH_TO_PRESETS_FILE
  #define PATH_TO_PRESETS_FILE "/usr/local/include/Piano960/presets.json"
#endif

