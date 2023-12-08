cmake_minimum_required(VERSION 3.16)

project(KArchive VERSION "5.245.0" LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core)

if(KARCHIVE_BUILD_STATIC)
    add_library(KF6Archive STATIC)
else()
    add_library(KF6Archive SHARED)
endif()
add_library(KF6::Archive ALIAS KF6Archive)

set_target_properties(KF6Archive PROPERTIES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION}"
)

target_sources(KF6Archive PRIVATE
    karchive_export.h
    config-compression.h
    loggingcategory.h loggingcategory.cpp
    karchiveentry.h karchivefile.h karchivedirectory.h
    karchive.h karchive_p.h karchive.cpp
    kar.h kar.cpp
    kcompressiondevice.h kcompressiondevice_p.h kcompressiondevice.cpp
    kfilterbase.h kfilterbase.cpp
    kgzipfilter.h kgzipfilter.cpp
    klimitediodevice_p.h klimitediodevice.cpp
    knonefilter.h knonefilter.cpp
    ktar.h ktar.cpp
    kzipfileentry.h kzip.h kzip.cpp
    krcc.h krcc.cpp
    kbzip2filter.h kbzip2filter.cpp
    kxzfilter.h kxzfilter.cpp
    k7zip.h k7zip.cpp
    kzstdfilter.h kzstdfilter.cpp
)

target_compile_definitions(KF6Archive PRIVATE
    KARCHIVE_BUILD_LIBRARY
)

if(KARCHIVE_BUILD_STATIC)
    target_compile_definitions(KF6Archive PUBLIC
        KARCHIVE_BUILD_STATIC
    )
endif()

target_include_directories(KF6Archive PUBLIC .)

target_link_libraries(KF6Archive PUBLIC
    Qt6::Core
)

target_link_libraries(KF6Archive PRIVATE
    KArchive::libbz2
    KArchive::libLZMA
    KArchive::libz
    KArchive::libzstd
)
