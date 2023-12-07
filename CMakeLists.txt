cmake_minimum_required(VERSION 3.16)

project(KArchive-SelfContains LANGUAGES C CXX)

option(KARCHIVE_BUILD_STATIC "Build static library." OFF)

include(GNUInstallDirs)

if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(NOT DEFINED BUILD_SHARED_LIBS)
    if(EMSCRIPTEN)
        set(BUILD_SHARED_LIBS OFF)
    else()
        set(BUILD_SHARED_LIBS ON)
    endif()
endif()

# Only enable LTCG/LTO for shared release builds.
if(NOT DEFINED CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE AND BUILD_SHARED_LIBS)
    if(EMSCRIPTEN)
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE OFF)
    else()
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
    endif()
endif()

if(NOT DEFINED CMAKE_DEBUG_POSTFIX)
    if(WIN32)
        set(CMAKE_DEBUG_POSTFIX "d")
    else()
        set(CMAKE_DEBUG_POSTFIX "_debug")
    endif()
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_C_VISIBILITY_PRESET "hidden")
set(CMAKE_CXX_VISIBILITY_PRESET "hidden")
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

set(CMAKE_INSTALL_RPATH "")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH OFF)

if(NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}")
endif()

if(NOT DEFINED CMAKE_LIBRARY_OUTPUT_DIRECTORY)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
endif()

if(NOT DEFINED CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
endif()

if(NOT "x${CMAKE_C_FLAGS}" STREQUAL "x")
    if(MSVC)
        string(REGEX REPLACE "[/|-]W[0|1|2|3|4]" " " CMAKE_C_FLAGS ${CMAKE_C_FLAGS})
        string(REGEX REPLACE "[/|-]W[0|1|2|3|4]" " " CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
    else()
        string(REGEX REPLACE "-W[all|extra]" " " CMAKE_C_FLAGS ${CMAKE_C_FLAGS})
        string(REGEX REPLACE "-W[all|extra]" " " CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
    endif()
endif()

if(MSVC)
    add_compile_options(/options:strict /bigobj /utf-8 /Zc:__cplusplus /guard:cf- /guard:ehcont-)
    add_link_options(/CETCOMPAT:NO /GUARD:NO /LARGEADDRESSAWARE /WX)
else()
    add_compile_options(-pthread)
    add_link_options(-pthread)
    if(NOT APPLE)
        add_link_options(-Wl,--fatal-warnings -Wl,--no-undefined -Wl,--as-needed -Wl,-z,defs)
    endif()
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(MSVC)
        add_compile_options(/Gw /Gy /Zc:inline /QIntel-jcc-erratum)
        add_link_options(/DEBUG /OPT:REF /OPT:ICF /OPT:LBR)
    elseif(NOT EMSCRIPTEN)
        add_compile_options(-ffunction-sections -fdata-sections)
        if(APPLE)
            add_link_options(-Wl,-dead_strip)
        else()
            add_link_options(-Wl,--strip-all -Wl,--gc-sections -Wl,-O3)
        endif()
    endif()
endif()

string(APPEND CMAKE_C_FLAGS " -w ")
string(APPEND CMAKE_CXX_FLAGS " -w ")

if(NOT MSVC)
    string(APPEND CMAKE_C_FLAGS " -fpermissive ")
    string(APPEND CMAKE_CXX_FLAGS " -fpermissive ")
endif()

add_subdirectory(dependencies)
add_subdirectory(src)