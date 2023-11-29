cmake_minimum_required(VERSION 3.16)

project("unit-tests")

add_definitions( 
  -dCATCH_USE_STDLIB_MODULE=ON
  -dCATCH_DEVELOPMENT_BUILD=ON
  -dCATCH_BUILD_TESTING=ON
  -dCATCH_BUILD_EXAMPLES=ON
  -dCATCH_ENABLE_WERROR=OFF
)

file(GLOB test_sources 
    "${CMAKE_SOURCE_DIR}/Tests/*.cpp" 
    "${CMAKE_SOURCE_DIR}/Tests/JsonCpp/jsoncpp.cpp"
    "${CMAKE_SOURCE_DIR}/Tests/JsonCpp/json/*.h"
)

target_compile_definitions(audio-plugin PRIVATE TESTMODE=1)

add_executable(unit-tests ${test_sources})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        audio-plugin
        Catch2::Catch2
)
