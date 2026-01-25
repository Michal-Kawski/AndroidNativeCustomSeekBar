# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html.
# For more examples on how to use CMake, see https://github.com/android/ndk-samples.

# Sets the minimum CMake version required for this project.
cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)

# Declares the project name. The project name can be accessed via ${ PROJECT_NAME},
# Since this is the top level CMakeLists.txt, the project name is also accessible
# with ${CMAKE_PROJECT_NAME} (both CMake variables are in-sync within the top level
# build script scope).
project("customseekbar")

# ---- Paths for headers and source files ----
set(CPP_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(CPP_INCLUDE ${CPP_ROOT}/include)
set(CPP_SRC ${CPP_ROOT}/src)

# ---- Find all source files ----
file(GLOB_RECURSE CPP_SOURCES
        ${CPP_SRC}/*.cpp
)

# ---- Skia paths ----
set(SKIA_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/third_parties/skia)
set(SKIA_INCLUDE ${SKIA_ROOT}/include)

# Select proper ABI of libskia.a depending on architecture
if (ANDROID_ABI STREQUAL "x86_64")
    set(SKIA_LIB ${SKIA_ROOT}/lib/x86_64/libskia.a)
elseif (ANDROID_ABI STREQUAL "arm64-v8a")
    set(SKIA_LIB ${SKIA_ROOT}/lib/arm64-v8a/libskia.a)
else()
    message(FATAL_ERROR "Unsupported ABI: ${ANDROID_ABI}")
endif()

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
#
# In this top level CMakeLists.txt, ${CMAKE_PROJECT_NAME} is used to define
# the target library name; in the sub-module's CMakeLists.txt, ${PROJECT_NAME}
# is preferred for the same purpose.
#
# In order to load a library into your app from Java/Kotlin, you must call
# System.loadLibrary() and pass the name of the library defined here;
# for GameActivity/NativeActivity derived applications, the same library name must be
# used in the AndroidManifest.xml file.
add_library(${CMAKE_PROJECT_NAME} SHARED
        # List C/C++ source files with relative paths to this CMakeLists.txt.
        native-lib.cpp
        ${CPP_SOURCES})

# Include header files of skia library
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        ${CPP_INCLUDE}
        ${SKIA_ROOT}
        ${SKIA_INCLUDE}
)

# Specifies libraries CMake should link to your target library. You
# can link libraries from various origins, such as libraries defined in this
# build script, prebuilt third-party libraries, or Android system libraries.
target_link_libraries(${CMAKE_PROJECT_NAME}
        # List libraries link to the target library
        ${SKIA_LIB}
        EGL
        GLESv2
        android
        log)