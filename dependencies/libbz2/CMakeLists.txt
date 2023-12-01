cmake_minimum_required(VERSION 3.16)

project(KArchive-libbz2 VERSION "1.0.8" LANGUAGES C)

add_library(ka_libbz2 STATIC
    blocksort.c
    huffman.c
    crctable.c
    randtable.c
    compress.c
    decompress.c
    bzlib.h bzlib_private.h bzlib.c
)
add_library(KArchive::libbz2 ALIAS ka_libbz2)

set_target_properties(ka_libbz2 PROPERTIES VERSION "${PROJECT_VERSION}")

target_include_directories(ka_libbz2 PUBLIC .)

target_compile_definitions(ka_libbz2 PRIVATE
    _FILE_OFFSET_BITS=64
)

# Activate POSIX APIs.
if(CMAKE_SYSTEM_NAME MATCHES "^(AIX|OS400)$")
    target_compile_definitions(ka_libbz2 PRIVATE _ALL_SOURCE)
endif()
if(NOT CMAKE_SYSTEM_NAME MATCHES "BSD|Darwin|Windows")
    target_compile_definitions(ka_libbz2 PRIVATE _XOPEN_SOURCE=700)
endif()
