# Policies <= CMP0128 default to NEW
# Maximum version allowed for the minimum version is 3.22 because of Ubuntu 22.04 LTS so
# currently can't use the target_sources(FILE_SET) 😔
# Minimum version must always correspond to the version that is in the latest Ubuntu LTS
# 3.20 - because is used NEWLINE_STYLE in the file(GENERATE) command
# 3.22 - because is used CMP0127: cmake_dependent_option() supports full Condition Syntax
cmake_minimum_required(VERSION 3.22...3.30 FATAL_ERROR)

project(HelloWorld LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(RESOLVE_TINYORM FetchContent CACHE STRING
    "How to resolve the TinyORM library, allowed values are FetchContent, VcpkgManifest, \
or None (Manual)"
)
# Populate drop-down combo box for CMake GUI-s
set_property(CACHE RESOLVE_TINYORM
    PROPERTY STRINGS FetchContent VcpkgManifest Manual None
)

# Use proper vcpkg.json.FetchContent.example or vcpkg.json.VcpkgManifest.example
# Eg. don't mix the FetchContent method with the vcpkg.json.VcpkgManifest.example

# FetchContent method
if(RESOLVE_TINYORM STREQUAL "FetchContent")
    set(FETCHCONTENT_QUIET OFF)
    include(FetchContent)

    # To avoid long paths problem on Windows
    # set(FETCHCONTENT_BASE_DIR "O:/FetchContent/HelloWorld")

    FetchContent_Declare(TinyOrm
        GIT_REPOSITORY https://github.com/silverqx/TinyORM.git
        GIT_TAG        origin/main
        # GIT_TAG        origin/silverqx-develop
        OVERRIDE_FIND_PACKAGE
    )

    # Here you can configure TinyORM CMake options
#    set(TOM_EXAMPLE ON)

# No logic needed for the vcpkg manifest method
# If you want to test the HEAD_REF set set(VCPKG_USE_HEAD_VERSION ON) before vcpkg_from_github() and
# set the HEAD_REF to branch to test, eg. develop
#elseif(RESOLVE_TINYORM STREQUAL "VcpkgManifest")

# Build or Install tree by CMAKE_PREFIX_PATH
elseif(RESOLVE_TINYORM STREQUAL "None" OR RESOLVE_TINYORM STREQUAL "Manual")
   # list(APPEND CMAKE_PREFIX_PATH "O:/Code/c/qMedia/tinyorm.org/TinyORM/TinyORM-builds-cmake/build-debug")
   # list(APPEND CMAKE_PREFIX_PATH "O:/Code/c/qMedia/TinyORM/TinyORM-builds-cmake/build-TinyORM-Desktop_Qt_6_7_2_MSVC2022_64bit-Debug")
   # list(APPEND CMAKE_PREFIX_PATH "E:/c/qMedia/TinyORM/TinyORM-builds-cmake/build-cmake-debug")
   # list(APPEND CMAKE_PREFIX_PATH "E:/c/qMedia/TinyORM/TinyORM-builds-cmake/build-ninja-multi")
endif()

add_executable(HelloWorld
  main.cpp
)

target_compile_definitions(HelloWorld PUBLIC PROJECT_TINYORM_HELLOWORLD_TINYDRIVERS)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(TinyOrm 0.37.3 CONFIG REQUIRED)

target_link_libraries(HelloWorld
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        TinyOrm::TinyOrm
)

install(TARGETS HelloWorld)
if(MSVC AND BUILD_SHARED_LIBS)
    install(FILES "$<TARGET_PDB_FILE:HelloWorld>" TYPE BIN OPTIONAL)
endif()
