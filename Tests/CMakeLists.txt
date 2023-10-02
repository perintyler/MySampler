cmake_minimum_required(VERSION 3.16)

project("unit-tests")

file(GLOB test_sources 
    "${CMAKE_SOURCE_DIR}/Tests/*.cpp" 
    "${CMAKE_SOURCE_DIR}/Tests/JsonCpp/jsoncpp.cpp"
    "${CMAKE_SOURCE_DIR}/Tests/JsonCpp/json/*.h"
)

target_compile_definitions(MySamplerPlugin PRIVATE TESTMODE=1)

add_executable(unit-tests ${test_sources})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        MySamplerPlugin
        Catch2::Catch2
)

