cmake_minimum_required(VERSION 3.16)

project(MySampler C CXX)


# ============= Define Compiler Flags ===============


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(ABSL_PROPAGATE_CXX_STD 1)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

# ================== Installation ====================

set(MYSAMPLER_INSTALLATION_PATH "include/${PROJECT_NAME}")

set(MYSAMPLER_INSTALLATION_DIR "${CMAKE_INSTALL_PREFIX}/${MYSAMPLER_INSTALLATION_PATH}")

message("| MySampler  will be installedsamples to ${MYSAMPLER_INSTALLATION_DIR}/samples")

install(
  DIRECTORY   ${CMAKE_CURRENT_SOURCE_DIR}/Assets/samples
  DESTINATION ${MYSAMPLER_INSTALLATION_PATH}
)

message("| CREPE pitch detection model will be installed to ${MYSAMPLER_INSTALLATION_DIR}/Models/crepe-models")

install(
  DIRECTORY   ${CMAKE_CURRENT_SOURCE_DIR}/Models/crepe-models
  DESTINATION ${MYSAMPLER_INSTALLATION_PATH}
)

message("| SPICE pitch detection model will be installed to ${MYSAMPLER_INSTALLATION_DIR}/Models/spice-models")

install(
  DIRECTORY   ${CMAKE_CURRENT_SOURCE_DIR}/Models/spice-models
  DESTINATION ${MYSAMPLER_INSTALLATION_PATH}
)

message("| presets will be installed to ${MYSAMPLER_INSTALLATION_DIR}/presets.json")

install(
  FILES ${CMAKE_CURRENT_SOURCE_DIR}/presets.json
  DESTINATION ${MYSAMPLER_INSTALLATION_PATH}
)

set(PITCH_DETECTION_CACHE_FILE "${MYSAMPLER_INSTALLATION_DIR}/pitch_detection_cache.json")
message("| pitch detection cachefile will be installed to ${PITCH_DETECTION_CACHE_FILE}")

install(
  FILES ${CMAKE_CURRENT_SOURCE_DIR}/pitch_detection_cache.json
  DESTINATION ${MYSAMPLER_INSTALLATION_PATH}
)

# ============= Define Pre-Compiler Variables ===============


if(PITCH_DETECTION STREQUAL "CREPE")
  add_compile_definitions(CREPE_MODEL)
elseif(PITCH_DETECTION STREQUAL "SPICE")
  add_compile_definitions(SPICE_MODEL)
else()
  add_compile_definitions(YIN_ALGO)
endif()


# ================== Configuration Files ====================

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Source/paths.h.in ${CMAKE_BINARY_DIR}/paths.h)
include_directories(${CMAKE_BINARY_DIR})

# =============== Build JUCE framework =================


# TODO: only build the individual/neccessary JUCE modules that are used by the plugin
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Libraries/JUCE EXCLUDE_FROM_ALL)
juce_add_module(${CMAKE_SOURCE_DIR}/Libraries/ff_meters)


# =============== Build Tensorflow =================


if(PITCH_DETECTION STREQUAL "CREPE" OR PITCH_DETECTION STREQUAL "SPICE")
    add_subdirectory(
      "${CMAKE_SOURCE_DIR}/Libraries/tensorflow/tensorflow/lite"
      "${CMAKE_CURRENT_BINARY_DIR}/tensorflow-lite" 
      EXCLUDE_FROM_ALL
    )
endif()


# =============== Build libsoxr (Resampling Library) =================


if(PITCH_DETECTION STREQUAL "CREPE")
    list (APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/Libraries/soxr/cmake/Modules)
    add_subdirectory("${CMAKE_SOURCE_DIR}/Libraries/soxr" EXCLUDE_FROM_ALL)
endif()


# ====================== Print CMake Variables ====================


include(CMakePrintHelpers)
cmake_print_variables(CMAKE_CURRENT_SOURCE_DIR)

# ====================== Build Plugin  ====================


add_subdirectory(Source)


# =================== Build Unit Tests ===================

list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/Catch2/contrib")
enable_testing()
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Libraries/Catch2 EXCLUDE_FROM_ALL)
include(CTest)
include(Catch)
add_subdirectory(Tests)
