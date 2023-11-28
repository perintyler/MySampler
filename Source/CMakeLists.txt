cmake_minimum_required(VERSION 3.16)

project(Source)

if(DEFINED PRODUCTION)
    set(PRODUCT_NAME "MySampler")
else()
    set(PRODUCT_NAME "MySampler-Debug")
endif()

juce_add_mysampler(mysampler
    VERSION 0.0.1
    FORMATS AU VST3 Standalone
    PRODUCT_NAME PRODUCT_NAME
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
)

juce_add_binary_data(mysamplerBinaryData SOURCES
    ../Assets/icons/locked_icon.png
    ../Assets/icons/unlocked_icon.png 
    ../Assets/icons/delete_icon.png
    ../Assets/icons/upload_icon.png
    ../Assets/icons/heart_icon.png
    ../Assets/icons/shuffle_icon.png
)

file(GLOB mysampler_SOURCES 
    "*.h" "*.cpp" "pitch_detection/*.h" "pitch_detection/*.cpp" "gui/*.h" "gui/*.cpp" "JsonCpp/jsoncpp.cpp" "JsonCpp/json/*.h")

if(PITCH_DETECTION STREQUAL "YIN")
    list(APPEND mysampler_SOURCES "pitch_detection/yin.h")
    list(APPEND mysampler_SOURCES "pitch_detection/yin.cpp")
elseif(PITCH_DETECTION STREQUAL "SPICE")
    list(APPEND mysampler_SOURCES "pitch_detection/spice.h")
    list(APPEND mysampler_SOURCES "pitch_detection/spice.cpp")
else()
    list(APPEND mysampler_SOURCES "pitch_detection/crepe.h")
    list(APPEND mysampler_SOURCES "pitch_detection/crepe.cpp")
endif()

include(CMakePrintHelpers)
cmake_print_variables(mysampler_SOURCES)

target_sources(mysampler PRIVATE ${mysampler_SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${mysampler_SOURCES})

target_include_directories(mysampler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(mysampler PUBLIC ${CMAKE_SOURCE_DIR}/Libraries)
target_include_directories(mysampler PUBLIC ${CMAKE_SOURCE_DIR}/Libraries/JUCE/modules)

target_compile_definitions(mysampler
    PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
)

set(mysampler_LIBRARIES
    mysamplerBinaryData
    juce::juce_gui_extra
    juce::juce_audio_utils
    juce::juce_dsp
    ff_meters
)

if(PITCH_DETECTION STREQUAL "CREPE")
    list(APPEND mysampler_LIBRARIES "tensorflow-lite")
    list(APPEND mysampler_LIBRARIES "soxr")
    list(APPEND mysampler_LIBRARIES "soxr-lsr")
elseif(PITCH_DETECTION STREQUAL "SPICE")
    list(APPEND mysampler_LIBRARIES "tensorflow-lite")
endif()

cmake_print_variables(mysampler_LIBRARIES)

target_link_libraries(mysampler PRIVATE ${mysampler_LIBRARIES})

