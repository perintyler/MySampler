cmake_minimum_required(VERSION 3.16)

project(Source)

juce_add_plugin(Piano960Plugin
    VERSION 0.0.1
    FORMATS AU VST3
    PRODUCT_NAME "Piano960"
    COMPANY_NAME soundvoyager
    COMPANY_WEBSITE "soundvoyager.xyz"
    PLUGIN_MANUFACTURER_CODE Svyg # A four-character manufacturer id with at least one upper-case character.
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE # Does the editor need keyboard focus?
    VST3_CATEGORIES Instrument Sampler
    COPY_PLUGIN_AFTER_BUILD APPLE # copy to default plugin location for IOS
)

juce_add_binary_data(Piano960PluginBinaryData SOURCES
    ../Assets/locked-black.png
    ../Assets/locked-white.png
    ../Assets/unlocked-black.png 
    ../Assets/unlocked-white.png
)

# TODO: automatically set Piano960Plugin_SOURCES to be all .h/.cpp files inside the Source directory
set(Piano960Plugin_SOURCES 
    app.h
    app.cpp
    audio_processor.h
    audio_processor.cpp
    samples.h
    samples.cpp
    lockable_keys.cpp
    lockable_keys.h
    logs.cpp
    logs.h
    pitch/exceptions.h
    pitch/pitch.h
    pitch/pitch.cpp
    pitch/notes.h
    pitch/notes.cpp
    pitch/semitones.h
    pitch/semitones.cpp
)

if(PITCH_DETECTION STREQUAL "YIN")
    list(APPEND Piano960Plugin_SOURCES "pitch/yin.h")
    list(APPEND Piano960Plugin_SOURCES "pitch/yin.cpp")
elseif(PITCH_DETECTION STREQUAL "SPICE")
    list(APPEND Piano960Plugin_SOURCES "pitch/spice.h")
    list(APPEND Piano960Plugin_SOURCES "pitch/spice.cpp")
else()
    list(APPEND Piano960Plugin_SOURCES "pitch/crepe.h")
    list(APPEND Piano960Plugin_SOURCES "pitch/crepe.cpp")
endif()

message("Source Files: ${Piano960Plugin_SOURCES}")

target_sources(Piano960Plugin PRIVATE ${Piano960Plugin_SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${Piano960Plugin_SOURCES})

target_include_directories(Piano960Plugin PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Piano960Plugin PUBLIC ${CMAKE_SOURCE_DIR}/Libraries)
target_include_directories(Piano960Plugin PUBLIC ${CMAKE_SOURCE_DIR}/Libraries/JUCE/modules)

target_compile_definitions(Piano960Plugin
    PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
)

set(Piano960Plugin_LIBRARIES
    Piano960PluginBinaryData
    juce::juce_audio_utils
    juce::juce_dsp
    ff_meters
)

if(PITCH_DETECTION STREQUAL "CREPE" OR PITCH_DETECTION STREQUAL "SPICE")
    list(APPEND Piano960Plugin_LIBRARIES "tensorflow-lite")
endif()

message("Libraries: ${Piano960Plugin_LIBRARIES}")

target_link_libraries(Piano960Plugin PRIVATE ${Piano960Plugin_LIBRARIES})

