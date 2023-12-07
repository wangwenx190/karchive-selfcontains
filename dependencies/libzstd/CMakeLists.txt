cmake_minimum_required(VERSION 3.16)

project(KArchive-libzstd VERSION "1.5.5" LANGUAGES C)

add_library(ka_libzstd STATIC)
add_library(KArchive::libzstd ALIAS ka_libzstd)

set_target_properties(ka_libzstd PROPERTIES VERSION "${PROJECT_VERSION}")

target_sources(ka_libzstd PRIVATE
    zdict.h
    zstd.h
    zstd_errors.h
    common/allocations.h
    common/bits.h
    common/bitstream.h
    common/compiler.h
    common/cpu.h
    common/debug.c
    common/debug.h
    common/entropy_common.c
    common/error_private.c
    common/error_private.h
    common/fse.h
    common/fse_decompress.c
    common/huf.h
    common/mem.h
    common/pool.c
    common/pool.h
    common/portability_macros.h
    common/threading.c
    common/threading.h
    common/xxhash.c
    common/xxhash.h
    common/zstd_common.c
    common/zstd_deps.h
    common/zstd_internal.h
    common/zstd_trace.h
    compress/clevels.h
    compress/fse_compress.c
    compress/hist.c
    compress/hist.h
    compress/huf_compress.c
    compress/zstdmt_compress.c
    compress/zstdmt_compress.h
    compress/zstd_compress.c
    compress/zstd_compress_internal.h
    compress/zstd_compress_literals.c
    compress/zstd_compress_literals.h
    compress/zstd_compress_sequences.c
    compress/zstd_compress_sequences.h
    compress/zstd_compress_superblock.c
    compress/zstd_compress_superblock.h
    compress/zstd_cwksp.h
    compress/zstd_double_fast.c
    compress/zstd_double_fast.h
    compress/zstd_fast.c
    compress/zstd_fast.h
    compress/zstd_lazy.c
    compress/zstd_lazy.h
    compress/zstd_ldm.c
    compress/zstd_ldm.h
    compress/zstd_ldm_geartab.h
    compress/zstd_opt.c
    compress/zstd_opt.h
    decompress/huf_decompress.c
    decompress/zstd_ddict.c
    decompress/zstd_ddict.h
    decompress/zstd_decompress.c
    decompress/zstd_decompress_block.c
    decompress/zstd_decompress_block.h
    decompress/zstd_decompress_internal.h
    dictBuilder/cover.c
    dictBuilder/cover.h
    dictBuilder/divsufsort.c
    dictBuilder/divsufsort.h
    dictBuilder/fastcover.c
    dictBuilder/zdict.c
)

target_include_directories(ka_libzstd PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/common"
    "${CMAKE_CURRENT_SOURCE_DIR}/compress"
    "${CMAKE_CURRENT_SOURCE_DIR}/decompress"
    "${CMAKE_CURRENT_SOURCE_DIR}/dictBuilder"
)

target_compile_definitions(ka_libzstd PRIVATE
    _FILE_OFFSET_BITS=64
    XXH_NAMESPACE=ZSTD_ # Always hide XXHash symbols
    ZSTD_LEGACY_SUPPORT=0
    ZSTD_MULTITHREAD
)

if(MSVC)
    target_compile_definitions(ka_libzstd PRIVATE
        ZSTD_DISABLE_ASM
        ZSTD_HEAPMODE=0
        _CRT_SECURE_NO_WARNINGS
    )
else()
    target_sources(ka_libzstd PRIVATE
        decompress/huf_decompress_amd64.S
    )
endif()

# Activate POSIX APIs.
if(CMAKE_SYSTEM_NAME MATCHES "^(AIX|OS400)$")
    target_compile_definitions(ka_libzstd PRIVATE _ALL_SOURCE)
endif()
if(NOT CMAKE_SYSTEM_NAME MATCHES "BSD|Darwin|Windows")
    target_compile_definitions(ka_libzstd PRIVATE _XOPEN_SOURCE=700)
endif()
