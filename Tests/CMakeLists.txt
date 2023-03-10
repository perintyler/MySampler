cmake_minimum_required(VERSION 3.16)

project("unit-tests")

file(GLOB test_sources "${CMAKE_SOURCE_DIR}/Tests/*.cpp")

target_compile_definitions(Piano960Plugin PRIVATE TESTMODE=1)

add_executable(unit-tests ${test_sources})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Piano960Plugin
        Catch2::Catch2
)

