cmake_minimum_required(VERSION 3.16)

project(KArchive-libz VERSION "1.2.12" LANGUAGES C)

add_library(ka_libz STATIC
    adler32.c
    compress.c
    crc32.c
    deflate.c
    gzclose.c
    gzlib.c
    gzread.c
    gzwrite.c
    inffast.c
    inflate.c
    inftrees.c
    trees.c
    uncompr.c
    zutil.c
)
add_library(KArchive::libz ALIAS ka_libz)

set_target_properties(ka_libz PROPERTIES VERSION "${PROJECT_VERSION}")

target_include_directories(ka_libz PUBLIC .)

target_compile_definitions(ka_libz PRIVATE
    _FILE_OFFSET_BITS=64
)

# Activate POSIX APIs.
if(CMAKE_SYSTEM_NAME MATCHES "^(AIX|OS400)$")
    target_compile_definitions(ka_libz PRIVATE _ALL_SOURCE)
endif()
if(NOT CMAKE_SYSTEM_NAME MATCHES "BSD|Darwin|Windows")
    target_compile_definitions(ka_libz PRIVATE _XOPEN_SOURCE=700)
endif()
