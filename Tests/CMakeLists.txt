cmake_minimum_required(VERSION 3.16)

project("unit-tests")

# list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/Catch2/contrib")
# list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

# set(CATCH_BUILD_EXAMPLES ON)
# set(CATCH_ENABLE_WERROR OFF)

# include(Catch)
# include(CTest)

target_compile_definitions(Catch2 PUBLIC CATCH_USE_STDLIB_MODULE=ON)
# target_compile_definitions(Catch2 PUBLIC CATCH_DEVELOPMENT_BUILD=ON)
# target_compile_definitions(Catch2 PUBLIC CATCH_BUILD_TESTING=ON)
# target_compile_definitions(Catch2 PUBLIC CATCH_ENABLE_WERROR=OFF)
# target_compile_features(Catch2 PRIVATE cxx_std_23)

# add_library(catch2 INTERFACE)

# enable_testing()

file(GLOB test_sources "${CMAKE_SOURCE_DIR}/Tests/*.cpp")

target_compile_definitions(audio-plugin PRIVATE TESTMODE=1)

add_executable(unit-tests ${test_sources})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        audio-plugin
        jsoncpp_lib
        Catch2::Catch2
)

include(CTest)
include(Catch)

# catch_discover_tests(unit-tests)

