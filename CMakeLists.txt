# Policies <= CMP0128 default to NEW
# 3.20 - because is used NEWLINE_STYLE in the file(GENERATE) command
# 3.22 - because is used CMP0127: cmake_dependent_option() supports full Condition Syntax
cmake_minimum_required(VERSION 3.22...3.27 FATAL_ERROR)

project(HelloWorld LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(RESOLVE_TINYORM FetchContent CACHE STRING
    "How to resolve the TinyORM library, allowed values are FetchContent, VcpkgManifest, \
or None"
)

# Use proper vcpkg.json.FetchContent.example or vcpkg.json.VcpkgManifest.example
# Eg. don't mix the FetchContent method with the vcpkg.json.VcpkgManifest.example

# FetchContent method
if(RESOLVE_TINYORM STREQUAL "FetchContent")
    set(FETCHCONTENT_QUIET OFF)
    include(FetchContent)

    FetchContent_Declare(TinyOrm
        GIT_REPOSITORY https://github.com/silverqx/TinyORM.git
        GIT_TAG        origin/main
        OVERRIDE_FIND_PACKAGE
    )

    # Here you can configure TinyORM CMake options
#    set(TOM_EXAMPLE ON)

# No logic needed for the vcpkg manifest method
#elseif(RESOLVE_TINYORM STREQUAL "VcpkgManifest")

# Build or Install tree by CMAKE_PREFIX_PATH
elseif(RESOLVE_TINYORM STREQUAL "None" OR RESOLVE_TINYORM STREQUAL "Manual")
#    list(APPEND CMAKE_PREFIX_PATH "O:/Code/c/qMedia/tinyorm.org/TinyORM/TinyORM-builds-cmake/build-debug")
#    list(APPEND CMAKE_PREFIX_PATH "O:/Code/c/qMedia/TinyORM/TinyORM-builds-cmake/build-TinyORM-Desktop_Qt_6_5_3_MSVC2022_64bit-Debug")
endif()

add_executable(HelloWorld
  main.cpp
)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(TinyOrm 0.35.0 CONFIG REQUIRED)

target_link_libraries(HelloWorld
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        TinyOrm::TinyOrm
)

install(TARGETS HelloWorld)
if(MSVC AND BUILD_SHARED_LIBS)
    install(FILES "$<TARGET_PDB_FILE:HelloWorld>" TYPE BIN OPTIONAL)
endif()
