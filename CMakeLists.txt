# This only builds the unit tests. The build VSTs/AUs, refer to the README. 

cmake_minimum_required(VERSION 3.15)

project(Piano960 VERSION 0.0.1)


# ====================================================================================

# -----------------------------------
# --- INSTALL TESTFILES & SAMPLES --- 
# -----------------------------------

# https://stackoverflow.com/questions/11096471/how-can-i-install-a-hierarchy-of-files-using-cmake

# https://stackoverflow.com/questions/17381910/cmake-install-installing-configuration-files

set(PIANO960_INSTALLED_SAMPLES_DIR "${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}/samples")

install(
   DIRECTORY   ${CMAKE_CURRENT_SOURCE_DIR}/Resources/
   DESTINATION ${PIANO960_INSTALLED_SAMPLES_DIR}
)

# file(GLOB TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Tests/test-data/*.wav")

# install(
#     DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Tests/test-data/
#     DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}/test-data
# )

# FILES       TEST_FILES # "${CMAKE_CURRENT_SOURCE_DIR}/Tests/test-data/*"
# DESTINATION include

# ====================================================================================


# TODO: always do this. its never gonna be a subdirectory
# Only do these if this is the main project,
# and not if it is included through add_subdirectory.
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # Let's nicely support folders in IDE's
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED YES)
    set(CMAKE_CXX_EXTENSIONS NO)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag("-march=native" COMPILER_SUPPORTS_MARCH_NATIVE)
    if(COMPILER_SUPPORTS_MARCH_NATIVE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
    endif()

    if(MSVC)
        CHECK_CXX_COMPILER_FLAG("/arch:AVX2" COMPILER_OPT_ARCH_AVX2_SUPPORTED)
        if(COMPILER_OPT_ARCH_AVX2_SUPPORTED)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:AVX2")
        endif()
    endif()

    if(NOT APPLE)
        include(CheckIPOSupported)
        check_ipo_supported(RESULT TOBANTEAUDIO_BUILD_LTO)
        if(TOBANTEAUDIO_BUILD_LTO)
            message(STATUS "tobanteAudio: LTO is available.")
            set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
        endif()
    endif()
endif()

# ====================================================================================



list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Libraries/JUCE EXCLUDE_FROM_ALL)
juce_add_module(${CMAKE_SOURCE_DIR}/Libraries/ff_meters)

# ====================================================================================

add_subdirectory(Source)

# ====================================================================================

# --------------
# --- CONFIG --- 
# --------------

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.h.in ${CMAKE_BINARY_DIR}/config.h)
include_directories(${CMAKE_BINARY_DIR})

# ====================================================================================

# ---------------------------------
# --- INCLUDE TESTING FRAMEWORK --- 
# ---------------------------------

# ! add_subdirectory(${CMAKE_SOURCE_DIR}/Libraries/wave)

list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/Catch2/contrib")
enable_testing()
add_subdirectory(${CMAKE_SOURCE_DIR}/Libraries/Catch2 EXCLUDE_FROM_ALL)
include(CTest)
include(Catch)
add_subdirectory(Tests)
