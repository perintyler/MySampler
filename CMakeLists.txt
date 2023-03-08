cmake_minimum_required(VERSION 3.16)

project(Piano960 C CXX)


# ============= Define Compiler Flags ===============



set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()


# ================== Installation ====================


set(PIANO960_INSTALLATION_DIR "${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}")

# install samples
install(
   DIRECTORY   ${CMAKE_CURRENT_SOURCE_DIR}/Resources
   DESTINATION ${PIANO960_INSTALLATION_DIR}
)

# install crepe pitch detection models
install(
  DIRECTORY   ${CMAKE_CURRENT_SOURCE_DIR}/Models/crepe-models
  DESTINATION ${PIANO960_INSTALLATION_DIR}
)

# install spice pitch detection model
install(
  DIRECTORY   ${CMAKE_CURRENT_SOURCE_DIR}/Models/spice-models
  DESTINATION ${PIANO960_INSTALLATION_DIR}
)


# ============= Define Pre-Compiler Variables ===============


if(${PITCH_DETECTION} STREQUAL "CREPE")
  add_compile_definitions(CREPE_MODEL)
elseif(${PITCH_DETECTION} STREQUAL "SPICE")
  add_compile_definitions(SPICE_MODEL)
else()
  add_compile_definitions(YIN_ALGO)
endif()


# ================== Configuration Files ====================


configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Config/paths.h.in ${CMAKE_BINARY_DIR}/paths.h)
include_directories(${CMAKE_BINARY_DIR})


# =============== Build JUCE framework =================


# TODO: only build the individual/neccessary JUCE modules that are used by the plugin
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Libraries/JUCE EXCLUDE_FROM_ALL)
juce_add_module(${CMAKE_SOURCE_DIR}/Libraries/ff_meters)


# =============== Build Tensorflow =================


if(NOT ${PITCH_DETECTION} STREQUAL "YIN")
    add_subdirectory(
      "${CMAKE_SOURCE_DIR}/Libraries/tensorflow/tensorflow/lite"
      "${CMAKE_CURRENT_BINARY_DIR}/tensorflow-lite" 
      EXCLUDE_FROM_ALL
    )
endif()


# ====================== Print CMake Variables ====================


include(CMakePrintHelpers)
cmake_print_variables(${CMAKE_CURRENT_SOURCE_DIR})


# ====================== Build Plugin  ====================


add_subdirectory(Source)


# =================== Build Unit Tests ===================


list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/Catch2/contrib")
enable_testing()
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Libraries/Catch2 EXCLUDE_FROM_ALL)
include(CTest)
include(Catch)
add_subdirectory(Tests)
