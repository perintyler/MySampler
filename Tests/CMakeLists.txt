project("unit-tests")

file(GLOB test_sources "${CMAKE_SOURCE_DIR}/Tests/*.cpp" "${CMAKE_SOURCE_DIR}/Tests/test_utils.h")

add_executable(unit-tests ${test_sources})

target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        Piano960Plugin
        Catch2::Catch2
)

