cmake_minimum_required(VERSION 3.16)

project(KArchive-SelfContains LANGUAGES C CXX)

option(KARCHIVE_BUILD_STATIC "Build static library." OFF)
option(KARCHIVE_NEED_INSTALL "Enable install." ON)

if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(NOT DEFINED CMAKE_DEBUG_POSTFIX)
    if(WIN32)
        set(CMAKE_DEBUG_POSTFIX "d")
    else()
        set(CMAKE_DEBUG_POSTFIX "_debug")
    endif()
endif()

if(MINGW)
    set(CMAKE_STATIC_LIBRARY_PREFIX "")
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(qmsetup QUIET)
if(NOT TARGET qmsetup::library)
    set(_qms_source_dir "${CMAKE_CURRENT_SOURCE_DIR}/qmsetup")
    include("${_qms_source_dir}/cmake/modules/InstallPackage.cmake")
    set(_qms_package_path)
    qm_install_package(qmsetup
        SOURCE_DIR ${_qms_source_dir}
        BUILD_TYPE Release
        RESULT_PATH _qms_package_path
    )
    find_package(qmsetup REQUIRED PATHS ${_qms_package_path})
    set(qmsetup_DIR ${_qms_package_path} CACHE PATH "" FORCE)
endif()

qm_import(Filesystem)
qm_init_directories()

qm_import(CompilerOptions)
qm_compiler_no_warnings()
qm_compiler_dont_export_by_default()
if(NOT "x${CMAKE_BUILD_TYPE}" STREQUAL "xDebug")
    qm_compiler_eliminate_dead_code()
endif()

add_subdirectory(dependencies)
add_subdirectory(src)