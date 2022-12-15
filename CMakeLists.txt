cmake_minimum_required(VERSION 3.15)

project(Piano960 VERSION 0.0.1)

###
# ============= Define Compiler Flags ===============
###

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

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

endif()


###
# ================== Install Samples ====================
###

set(PIANO960_INSTALLATION_DIR "${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}")

set(PIANO960_SAMPLES_DIR "${PIANO960_INSTALLATION_DIR}/samples")

install(
   DIRECTORY   ${CMAKE_CURRENT_SOURCE_DIR}/Resources/
   DESTINATION ${PIANO960_SAMPLES_DIR}
)

###
# ================== Configuration Files ====================
###

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Config/paths.h.in ${CMAKE_BINARY_DIR}/paths.h)
include_directories(${CMAKE_BINARY_DIR})

###
# =============== Build JUCE framework =================
###

# TODO: only build the individual/neccessary JUCE modules that are used by the plugin

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Libraries/JUCE EXCLUDE_FROM_ALL)
juce_add_module(${CMAKE_SOURCE_DIR}/Libraries/ff_meters)

###
# ====================== Build Plugin  ====================
###

# include source code
add_subdirectory(Source)

###
# =================== Build Unit Tests ===================
###

list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/Catch2/contrib")
enable_testing()
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Libraries/Catch2 EXCLUDE_FROM_ALL)
include(CTest)
include(Catch)
add_subdirectory(Tests)
