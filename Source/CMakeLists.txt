cmake_minimum_required(VERSION 3.16)

project(Source)

# ====================== Plugin Name ========================

if(DEFINED PRODUCTION)
    set(PRODUCT_NAME "MySampler")
else()
    set(PRODUCT_NAME "MySampler-Debug")
endif()

# ====================== Plugin Formats ========================

if (NOT DEFINED MYSAMPLER_FORMATS)
  list(APPEND MYSAMPLER_FORMATS AU)
  list(APPEND MYSAMPLER_FORMATS VST3)
  list(APPEND MYSAMPLER_FORMATS Standalone)
endif()

message("<> INFO: building plugin for formats: ${MYSAMPLER_FORMATS} <>")

# ====================== JUCE Configuration ========================

juce_add_plugin(audio-plugin
    VERSION 0.0.1
    FORMATS "${MYSAMPLER_FORMATS}"
    PRODUCT_NAME "${PRODUCT_NAME}"
    COMPANY_NAME "Sound Voyager"
    COMPANY_WEBSITE "soundvoyager.xyz"
    PLUGIN_MANUFACTURER_CODE Svyg
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT TRUE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE # Does the editor need keyboard focus?
    VST3_CATEGORIES Instrument Sampler
    COPY_PLUGIN_AFTER_BUILD TRUE # TODO: only set this to true for apple OS
    # FILE_SHARING_ENABLED TRUE
    # NEEDS_CURL TRUE# 
)

juce_add_binary_data(audio-pluginBinaryData SOURCES
    ../Assets/icons/locked_icon.png
    ../Assets/icons/unlocked_icon.png 
    ../Assets/icons/delete_icon.png
    ../Assets/icons/upload_icon.png
    ../Assets/icons/heart_icon.png
    ../Assets/icons/shuffle_icon.png
)

target_compile_definitions(audio-plugin
    PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
)

# ====================== Source Files ========================

file(GLOB audio-plugin_SOURCES 
    "*.h" "*.cpp" "pitch_detection/*.h" "pitch_detection/*.cpp" "gui/*.h" "gui/*.cpp" "JsonCpp/jsoncpp.cpp" "JsonCpp/json/*.h")

if(PITCH_DETECTION STREQUAL "YIN")
    list(APPEND audio-plugin_SOURCES "pitch_detection/yin.h")
    list(APPEND audio-plugin_SOURCES "pitch_detection/yin.cpp")
elseif(PITCH_DETECTION STREQUAL "SPICE")
    list(APPEND audio-plugin_SOURCES "pitch_detection/spice.h")
    list(APPEND audio-plugin_SOURCES "pitch_detection/spice.cpp")
else()
    list(APPEND audio-plugin_SOURCES "pitch_detection/crepe.h")
    list(APPEND audio-plugin_SOURCES "pitch_detection/crepe.cpp")
endif()

include(CMakePrintHelpers)
cmake_print_variables(audio-plugin_SOURCES)

target_sources(audio-plugin PRIVATE ${audio-plugin_SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${audio-plugin_SOURCES})

target_include_directories(audio-plugin PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(audio-plugin PUBLIC ${CMAKE_SOURCE_DIR}/Libraries)
target_include_directories(audio-plugin PUBLIC ${CMAKE_SOURCE_DIR}/Libraries/JUCE/modules)

# ====================== Target Libraries ========================

set(audio-plugin_LIBRARIES
    audio-pluginBinaryData
    juce::juce_audio_utils
    juce::juce_dsp
    ff_meters
)

if(PITCH_DETECTION STREQUAL "CREPE")
    list(APPEND audio-plugin_LIBRARIES "tensorflow-lite")
    list(APPEND audio-plugin_LIBRARIES "soxr")
    list(APPEND audio-plugin_LIBRARIES "soxr-lsr")
elseif(PITCH_DETECTION STREQUAL "SPICE")
    list(APPEND audio-plugin_LIBRARIES "tensorflow-lite")
endif()

cmake_print_variables(audio-plugin_LIBRARIES)

# ====================== Target Libraries ========================

target_link_libraries(audio-plugin PRIVATE ${audio-plugin_LIBRARIES})
set_target_properties(audio-pluginBinaryData PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

