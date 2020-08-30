# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

set(LIB_DIR ${CMAKE_SOURCE_DIR}/../../../cppLibs)

set(OPENBLAS_DIR ${LIB_DIR}/openblas)

add_library(openblas
        SHARED
        IMPORTED)

set_target_properties(
        # Specifies the target library.
        openblas
        # Specifies the parameter you want to define.
        PROPERTIES IMPORTED_LOCATION
        # Provides the path to the library you want to import.
        ${OPENBLAS_DIR}/${ANDROID_ABI}/lib/libopenblas.a)

include_directories(${OPENBLAS_DIR}/include)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

set(MAT_DIR ${SRC_DIR}/mat)
add_subdirectory(${MAT_DIR})

include_directories(
        ${MAT_DIR}
)

find_library( # Sets the name of the path variable.
        log-lib
        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

add_library(
        audio
        SHARED
        main.cpp
        ${MAT_DIR}/matrix.cpp
)

target_link_libraries( # Specifies the target library.
        audio
        openblas
        mat
        # Links the target library to the log library
        # included in the NDK.
        android
        ${log-lib})