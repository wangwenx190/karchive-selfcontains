cmake_minimum_required(VERSION 3.16)

project(KArchive-libz VERSION "1.3.0" LANGUAGES C)

include(CheckIncludeFile)

check_include_file(unistd.h Z_HAVE_UNISTD_H)
check_include_file(stdarg.h Z_HAVE_STDARG_H)

add_library(ka_libz STATIC
    adler32.c
    compress.c
    crc32.h crc32.c
    deflate.h deflate.c
    gzclose.c
    gzguts.h
    gzlib.c
    gzread.c
    gzwrite.c
    infback.c
    inffast.h inffast.c
    inffixed.h
    inflate.h inflate.c
    inftrees.h inftrees.c
    trees.h trees.c
    uncompr.c
    zlib.h
    zutil.h zutil.c
)
add_library(KArchive::libz ALIAS ka_libz)

configure_file(zconf.h.in ${PROJECT_BINARY_DIR}/zconf.h @ONLY)
target_sources(ka_libz PRIVATE ${PROJECT_BINARY_DIR}/zconf.h)

set_target_properties(ka_libz PROPERTIES VERSION "${PROJECT_VERSION}")

target_include_directories(ka_libz PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}"
)

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
