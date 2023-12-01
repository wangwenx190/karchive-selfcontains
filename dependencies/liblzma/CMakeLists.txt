cmake_minimum_required(VERSION 3.16)

project(KArchive-libLZMA VERSION "5.2.5" LANGUAGES C)

include(CheckCSourceCompiles)
include(CheckIncludeFile)
include(CheckSymbolExists)
include(CheckTypeSize)
include(TestBigEndian)

check_include_file(inttypes.h HAVE_INTTYPES_H)
check_include_file(stdint.h HAVE_STDINT_H)
check_include_file(byteswap.h HAVE_BYTESWAP_H)
check_include_file(limits.h HAVE_LIMITS_H)
check_include_file(memory.h HAVE_MEMORY_H)
check_include_file(strings.h HAVE_STRINGS_H)
set(HAVE_STRING_H 1)
check_include_file(sys/sysctl.h HAVE_SYS_SYSCTL_H)
check_include_file(stdbool.h HAVE_STDBOOL_H)
if(NOT HAVE_STDBOOL_H)
    check_type_size(_Bool _BOOL)
endif()

check_c_source_compiles(
    "#include<byteswap.h>\nint main(void){bswap_16(0);return 0;}"
    HAVE_BSWAP_16
)
check_c_source_compiles(
    "#include<byteswap.h>\nint main(void){bswap_32(0);return 0;}"
    HAVE_BSWAP_32
)
check_c_source_compiles(
    "#include<byteswap.h>\nint main(void){bswap_64(0);return 0;}"
    HAVE_BSWAP_64
)

test_big_endian(WORDS_BIGENDIAN)

set(HAVE_CHECK_CRC64 1)
set(HAVE_CHECK_SHA256 1)

set(HAVE_DECODER_ARM 1)
set(HAVE_DECODER_ARMTHUMB 1)
set(HAVE_DECODER_DELTA 1)
set(HAVE_DECODER_IA64 1)
set(HAVE_DECODER_LZMA1 1)
set(HAVE_DECODER_LZMA2 1)
set(HAVE_DECODER_POWERPC 1)
set(HAVE_DECODER_SPARC 1)
set(HAVE_DECODER_X86 1)

set(HAVE_ENCODER_ARM 1)
set(HAVE_ENCODER_ARMTHUMB 1)
set(HAVE_ENCODER_DELTA 1)
set(HAVE_ENCODER_IA64 1)
set(HAVE_ENCODER_LZMA1 1)
set(HAVE_ENCODER_LZMA2 1)
set(HAVE_ENCODER_POWERPC 1)
set(HAVE_ENCODER_SPARC 1)
set(HAVE_ENCODER_X86 1)

set(HAVE_MF_BT2 1)
set(HAVE_MF_BT3 1)
set(HAVE_MF_BT4 1)
set(HAVE_MF_HC3 1)
set(HAVE_MF_HC4 1)

add_library(ka_libLZMA STATIC)
add_library(KArchive::libLZMA ALIAS ka_libLZMA)

set_target_properties(ka_libLZMA PROPERTIES VERSION "${PROJECT_VERSION}")

target_sources(ka_libLZMA PRIVATE
  common/mythread.h
  common/sysdefs.h
  common/tuklib_cpucores.c
  common/tuklib_cpucores.h
  common/tuklib_integer.h
  liblzma/check/check.c
  liblzma/check/crc32_fast.c
  liblzma/check/crc32_table.c
  liblzma/check/crc64_fast.c
  liblzma/check/crc64_table.c
  liblzma/check/sha256.c
  liblzma/common/alone_decoder.c
  liblzma/common/alone_encoder.c
  liblzma/common/auto_decoder.c
  liblzma/common/block_buffer_decoder.c
  liblzma/common/block_buffer_encoder.c
  liblzma/common/block_decoder.c
  liblzma/common/block_encoder.c
  liblzma/common/block_header_decoder.c
  liblzma/common/block_header_encoder.c
  liblzma/common/block_util.c
  liblzma/common/common.c
  liblzma/common/easy_buffer_encoder.c
  liblzma/common/easy_decoder_memusage.c
  liblzma/common/easy_encoder.c
  liblzma/common/easy_encoder_memusage.c
  liblzma/common/easy_preset.c
  liblzma/common/filter_buffer_decoder.c
  liblzma/common/filter_buffer_encoder.c
  liblzma/common/filter_common.c
  liblzma/common/filter_decoder.c
  liblzma/common/filter_encoder.c
  liblzma/common/filter_flags_decoder.c
  liblzma/common/filter_flags_encoder.c
  liblzma/common/hardware_cputhreads.c
  liblzma/common/index.c
  liblzma/common/index_decoder.c
  liblzma/common/index_encoder.c
  liblzma/common/index_hash.c
  liblzma/common/outqueue.c
  liblzma/common/stream_buffer_decoder.c
  liblzma/common/stream_buffer_encoder.c
  liblzma/common/stream_decoder.c
  liblzma/common/stream_encoder.c
  liblzma/common/stream_encoder_mt.c
  liblzma/common/stream_flags_common.c
  liblzma/common/stream_flags_decoder.c
  liblzma/common/stream_flags_encoder.c
  liblzma/common/vli_decoder.c
  liblzma/common/vli_encoder.c
  liblzma/common/vli_size.c
  liblzma/delta/delta_common.c
  liblzma/delta/delta_decoder.c
  liblzma/delta/delta_encoder.c
  liblzma/lz/lz_decoder.c
  liblzma/lz/lz_encoder.c
  liblzma/lz/lz_encoder_mf.c
  liblzma/lzma/fastpos_table.c
  liblzma/lzma/lzma2_decoder.c
  liblzma/lzma/lzma2_encoder.c
  liblzma/lzma/lzma_decoder.c
  liblzma/lzma/lzma_encoder.c
  liblzma/lzma/lzma_encoder_optimum_fast.c
  liblzma/lzma/lzma_encoder_optimum_normal.c
  liblzma/lzma/lzma_encoder_presets.c
  liblzma/rangecoder/price_table.c
  liblzma/simple/arm.c
  liblzma/simple/armthumb.c
  liblzma/simple/ia64.c
  liblzma/simple/powerpc.c
  liblzma/simple/simple_coder.c
  liblzma/simple/simple_decoder.c
  liblzma/simple/simple_encoder.c
  liblzma/simple/sparc.c
  liblzma/simple/x86.c
)

configure_file(config.h.in "${PROJECT_BINARY_DIR}/config.h" @ONLY)
target_sources(ka_libLZMA PRIVATE "${PROJECT_BINARY_DIR}/config.h")

target_include_directories(ka_libLZMA PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/common"
    "${CMAKE_CURRENT_SOURCE_DIR}/liblzma"
    "${CMAKE_CURRENT_SOURCE_DIR}/liblzma/api"
    "${CMAKE_CURRENT_SOURCE_DIR}/liblzma/check"
    "${CMAKE_CURRENT_SOURCE_DIR}/liblzma/common"
    "${CMAKE_CURRENT_SOURCE_DIR}/liblzma/delta"
    "${CMAKE_CURRENT_SOURCE_DIR}/liblzma/lz"
    "${CMAKE_CURRENT_SOURCE_DIR}/liblzma/lzma"
    "${CMAKE_CURRENT_SOURCE_DIR}/liblzma/rangecoder"
    "${CMAKE_CURRENT_SOURCE_DIR}/liblzma/simple"
)

if(WIN32)
    target_compile_definitions(ka_libLZMA PRIVATE MYTHREAD_VISTA)
else()
    target_compile_definitions(ka_libLZMA PRIVATE MYTHREAD_POSIX)
endif()

target_compile_definitions(ka_libLZMA PRIVATE
    _FILE_OFFSET_BITS=64
)

# Activate POSIX APIs.
if(CMAKE_SYSTEM_NAME MATCHES "^(AIX|OS400)$")
    target_compile_definitions(ka_libLZMA PRIVATE _ALL_SOURCE)
endif()
if(NOT CMAKE_SYSTEM_NAME MATCHES "BSD|Darwin|Windows")
    target_compile_definitions(ka_libLZMA PRIVATE _XOPEN_SOURCE=700)
endif()
