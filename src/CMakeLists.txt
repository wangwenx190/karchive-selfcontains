cmake_minimum_required(VERSION 3.16)

project(KArchive VERSION "5.248.0" LANGUAGES CXX)

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
    SOVERSION "${PROJECT_VERSION_MAJOR}"
)

if(WIN32 AND NOT KARCHIVE_BUILD_STATIC)
    qm_add_win_rc_enhanced(KF6Archive
        NAME "KArchive"
        VERSION "${PROJECT_VERSION}"
        DESCRIPTION "Qt addon providing access to numerous types of archives"
        COPYRIGHT "Copyright (C) KDE"
        COMPANY "KDE"
    )
endif()

set(HEADERS
    karchive_export.h
    config-compression.h
    loggingcategory.h
    karchiveentry.h karchivefile.h karchivedirectory.h
    karchive.h karchive_p.h
    kar.h
    kcompressiondevice.h kcompressiondevice_p.h
    kfilterbase.h
    kgzipfilter.h
    klimitediodevice_p.h
    knonefilter.h
    ktar.h
    kzipfileentry.h kzip.h
    krcc.h
    kbzip2filter.h
    kxzfilter.h
    k7zip.h
    kzstdfilter.h
)
target_sources(KF6Archive PRIVATE ${HEADERS})

target_sources(KF6Archive PRIVATE
    loggingcategory.cpp
    karchive.cpp
    kar.cpp
    kcompressiondevice.cpp
    kfilterbase.cpp
    kgzipfilter.cpp
    klimitediodevice.cpp
    knonefilter.cpp
    ktar.cpp
    kzip.cpp
    krcc.cpp
    kbzip2filter.cpp
    kxzfilter.cpp
    k7zip.cpp
    kzstdfilter.cpp
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

set(_deps_visibility PRIVATE)
set(_targets KF6Archive)
if(KARCHIVE_BUILD_STATIC)
    set(_deps_visibility PUBLIC)
    list(APPEND _targets ka_libbz2 ka_libLZMA ka_libz ka_libzstd)
endif()

target_link_libraries(KF6Archive ${_deps_visibility}
    KArchive::libbz2
    KArchive::libLZMA
    KArchive::libz
    KArchive::libzstd
)

if(KARCHIVE_ENABLE_INSTALL)
    include(GNUInstallDirs)
    install(TARGETS ${_targets}
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    )
    if(MSVC AND NOT KARCHIVE_BUILD_STATIC)
        install(FILES "$<TARGET_PDB_FILE:KF6Archive>" DESTINATION "${CMAKE_INSTALL_BINDIR}" OPTIONAL)
    endif()
    install(FILES ${HEADERS} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
endif()