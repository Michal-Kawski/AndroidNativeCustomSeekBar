cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(native_tests)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(native_tests
        ../../main/cpp/src/Core/SeekProxy.cpp
        Unittests/SeekProxyTests.cpp
)

target_include_directories(native_tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../main/cpp/include
)

target_link_libraries(native_tests
        gtest
        gmock
        gtest_main
)

enable_testing()