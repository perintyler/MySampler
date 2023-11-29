cmake_minimum_required(VERSION 3.16)

project("unit-tests")

file(GLOB test_sources 
    "${CMAKE_SOURCE_DIR}/Tests/*.cpp" 
    "${CMAKE_SOURCE_DIR}/Tests/JsonCpp/jsoncpp.cpp"
    "${CMAKE_SOURCE_DIR}/Tests/JsonCpp/json/*.h"
)

target_compile_definitions(audio-plugin PRIVATE TESTMODE=1)

add_executable(unit-tests ${test_sources})

target_compile_definitions(unit-tests PUBLIC 
  CATCH_USE_STDLIB_MODULE=ON
  CATCH_DEVELOPMENT_BUILD=ON
  CATCH_BUILD_TESTING=ON
  CATCH_BUILD_EXAMPLES=ON
  CATCH_ENABLE_WERROR=OFF
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        audio-plugin
        Catch2::Catch2
)
