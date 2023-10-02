cmake_minimum_required(VERSION 3.16)

project(Source)

if(DEFINED PRODUCTION)
    set(PRODUCT_NAME "MySampler")
else()
    set(PRODUCT_NAME "MySampler-Development")
endif()

juce_add_plugin(MySamplerPlugin
    VERSION 0.0.1
    FORMATS AU VST3
    PRODUCT_NAME PRODUCT_NAME
    COMPANY_NAME "Sound Voyager"
    COMPANY_WEBSITE "soundvoyager.xyz"
    PLUGIN_MANUFACTURER_CODE Svyg # A four-character manufacturer id with at least one upper-case character.
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE # Does the editor need keyboard focus?
    VST3_CATEGORIES Instrument Sampler
    COPY_PLUGIN_AFTER_BUILD TRUE # TODO: only set this to true for apple OS
)

juce_add_binary_data(MySamplerPluginBinaryData SOURCES
    ../Assets/icons/locked-black.png
    ../Assets/icons/locked-white.png
    ../Assets/icons/unlocked-black.png 
    ../Assets/icons/unlocked-white.png
)

file(GLOB MySamplerPlugin_SOURCES 
    "*.h" "*.cpp" "pitch_detection/*.h" "pitch_detection/*.cpp" "gui/*.h" "gui/*.cpp" "JsonCpp/jsoncpp.cpp" "JsonCpp/json/*.h")

if(PITCH_DETECTION STREQUAL "YIN")
    list(APPEND MySamplerPlugin_SOURCES "pitch_detection/yin.h")
    list(APPEND MySamplerPlugin_SOURCES "pitch_detection/yin.cpp")
elseif(PITCH_DETECTION STREQUAL "SPICE")
    list(APPEND MySamplerPlugin_SOURCES "pitch_detection/spice.h")
    list(APPEND MySamplerPlugin_SOURCES "pitch_detection/spice.cpp")
else()
    list(APPEND MySamplerPlugin_SOURCES "pitch_detection/crepe.h")
    list(APPEND MySamplerPlugin_SOURCES "pitch_detection/crepe.cpp")
endif()

include(CMakePrintHelpers)
cmake_print_variables(MySamplerPlugin_SOURCES)

target_sources(MySamplerPlugin PRIVATE ${MySamplerPlugin_SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${MySamplerPlugin_SOURCES})

target_include_directories(MySamplerPlugin PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(MySamplerPlugin PUBLIC ${CMAKE_SOURCE_DIR}/Libraries)
target_include_directories(MySamplerPlugin PUBLIC ${CMAKE_SOURCE_DIR}/Libraries/JUCE/modules)

target_compile_definitions(MySamplerPlugin
    PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
)

set(MySamplerPlugin_LIBRARIES
    MySamplerPluginBinaryData
    juce::juce_audio_utils
    juce::juce_dsp
    ff_meters
)

if(PITCH_DETECTION STREQUAL "CREPE")
    list(APPEND MySamplerPlugin_LIBRARIES "tensorflow-lite")
    list(APPEND MySamplerPlugin_LIBRARIES "soxr")
    list(APPEND MySamplerPlugin_LIBRARIES "soxr-lsr")
elseif(PITCH_DETECTION STREQUAL "SPICE")
    list(APPEND MySamplerPlugin_LIBRARIES "tensorflow-lite")
endif()

cmake_print_variables(MySamplerPlugin_LIBRARIES)

target_link_libraries(MySamplerPlugin PRIVATE ${MySamplerPlugin_LIBRARIES})

