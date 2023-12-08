cmake_minimum_required(VERSION 3.16)

project(KArchive-libLZMA VERSION "5.4.5" LANGUAGES C)

include(CheckCSourceCompiles)
include(CheckIncludeFile)
include(CheckSymbolExists)
include(CheckTypeSize)
include(CheckStructHasMember)
include(TestBigEndian)
include(CMakePushCheckState)

check_include_file(inttypes.h HAVE_INTTYPES_H)
check_include_file(stdint.h HAVE_STDINT_H)
check_include_file(byteswap.h HAVE_BYTESWAP_H)
check_include_file(limits.h HAVE_LIMITS_H)
check_include_file(memory.h HAVE_MEMORY_H)
check_include_file(strings.h HAVE_STRINGS_H)
check_include_file(cpuid.h HAVE_CPUID_H)
check_include_file(string.h HAVE_STRING_H)
check_include_file(sys/sysctl.h HAVE_SYS_SYSCTL_H)
check_include_file(stdbool.h HAVE_STDBOOL_H)
check_include_file(immintrin.h HAVE_IMMINTRIN_H)
check_include_file(CommonCrypto/CommonDigest.h HAVE_COMMONCRYPTO_COMMONDIGEST_H)
check_include_file(dlfcn.h HAVE_DLFCN_H)
check_include_file(fcntl.h HAVE_FCNTL_H)
check_include_file(minix/config.h HAVE_MINIX_CONFIG_H)
check_include_file(sha256.h HAVE_SHA256_H)
check_include_file(sha2.h HAVE_SHA2_H)
check_include_file(stdio.h HAVE_STDIO_H)
check_include_file(stdlib.h HAVE_STDLIB_H)
check_include_file(sys/byteorder.h HAVE_SYS_BYTEORDER_H)
check_include_file(sys/capsicum.h HAVE_SYS_CAPSICUM_H)
check_include_file(sys/endian.h HAVE_SYS_ENDIAN_H)
check_include_file(sys/param.h HAVE_SYS_PARAM_H)
check_include_file(sys/stat.h HAVE_SYS_STAT_H)
check_include_file(sys/time.h HAVE_SYS_TIME_H)
check_include_file(sys/types.h HAVE_SYS_TYPES_H)
check_include_file(unistd.h HAVE_UNISTD_H)
check_include_file(wchar.h HAVE_WCHAR_H)

check_symbol_exists(clock_gettime time.h HAVE_CLOCK_GETTIME)
check_symbol_exists(clock_gettime time.h HAVE_CLOCK_GETTIME_LIBRT)
check_symbol_exists(CLOCK_MONOTONIC time.h HAVE_CLOCK_MONOTONIC)
check_symbol_exists(pthread_condattr_setclock pthread.h HAVE_PTHREAD_CONDATTR_SETCLOCK)
check_symbol_exists(getopt_long getopt.h HAVE_GETOPT_LONG)
check_symbol_exists(optreset getopt.h HAVE_OPTRESET)
check_symbol_exists(posix_fadvise fcntl.h HAVE_POSIX_FADVISE)
check_struct_has_member("struct stat" st_atim.tv_nsec "sys/types.h;sys/stat.h" HAVE_STRUCT_STAT_ST_ATIM_TV_NSEC)
check_struct_has_member("struct stat" st_atimespec.tv_nsec "sys/types.h;sys/stat.h" HAVE_STRUCT_STAT_ST_ATIMESPEC_TV_NSEC)
check_struct_has_member("struct stat" st_atimensec "sys/types.h;sys/stat.h" HAVE_STRUCT_STAT_ST_ATIMENSEC)
check_symbol_exists(futimens "sys/types.h;sys/stat.h" HAVE_FUTIMENS)
check_symbol_exists(futimes "sys/time.h" HAVE_FUTIMES)
check_symbol_exists(futimesat "sys/time.h" HAVE_FUTIMESAT)
check_symbol_exists(utimes "sys/time.h" HAVE_UTIMES)
check_symbol_exists(_futime "sys/utime.h" HAVE__FUTIME)
check_symbol_exists(utime "utime.h" HAVE_UTIME)

check_c_source_compiles("#include<byteswap.h>\nint main(void){bswap_16(0);return 0;}" HAVE_BSWAP_16)
check_c_source_compiles("#include<byteswap.h>\nint main(void){bswap_32(0);return 0;}" HAVE_BSWAP_32)
check_c_source_compiles("#include<byteswap.h>\nint main(void){bswap_64(0);return 0;}" HAVE_BSWAP_64)

# Check for __attribute__((__constructor__)) support.
# This needs -Werror because some compilers just warn
# about this being unsupported.
cmake_push_check_state()
set(CMAKE_REQUIRED_FLAGS "-Werror")
check_c_source_compiles("__attribute__((__constructor__))\nstatic void my_constructor_func(void){return;}\nint main(void){return 0;}" HAVE_FUNC_ATTRIBUTE_CONSTRUCTOR)
cmake_pop_check_state()

check_c_source_compiles("#include <immintrin.h>\nint main(void){__m128i x={0};_mm_movemask_epi8(x);return 0;}" HAVE__MM_MOVEMASK_EPI8)
check_c_source_compiles("#include <immintrin.h>\n#if defined(__e2k__) && __iset__ < 6\n#   error\n#endif\n#if (defined(__GNUC__) || defined(__clang__)) && !defined(__EDG__)\n__attribute__((__target__(\"ssse3,sse4.1,pclmul\")))\n#endif\n__m128i my_clmul(__m128i a){const __m128i b=_mm_set_epi64x(1,2);return _mm_clmulepi64_si128(a,b,0);}\nint main(void){return 0;}" HAVE_USABLE_CLMUL)

test_big_endian(WORDS_BIGENDIAN)

set(HAVE_CHECK_CRC32 1)
set(HAVE_CHECK_CRC64 1)
set(HAVE_CHECK_SHA256 1)

set(HAVE_MF_HC3 1)
set(HAVE_MF_HC4 1)
set(HAVE_MF_BT2 1)
set(HAVE_MF_BT3 1)
set(HAVE_MF_BT4 1)

set(HAVE_ENCODER_X86 1)
set(HAVE_ENCODER_ARM 1)
set(HAVE_ENCODER_ARMTHUMB 1)
set(HAVE_ENCODER_ARM64 1)
set(HAVE_ENCODER_POWERPC 1)
set(HAVE_ENCODER_IA64 1)
set(HAVE_ENCODER_SPARC 1)
set(HAVE_ENCODER_LZMA1 1)
set(HAVE_ENCODER_LZMA2 1)
set(HAVE_ENCODER_DELTA 1)

set(HAVE_DECODER_X86 1)
set(HAVE_DECODER_ARM 1)
set(HAVE_DECODER_ARMTHUMB 1)
set(HAVE_DECODER_ARM64 1)
set(HAVE_DECODER_POWERPC 1)
set(HAVE_DECODER_IA64 1)
set(HAVE_DECODER_SPARC 1)
set(HAVE_DECODER_LZMA1 1)
set(HAVE_DECODER_LZMA2 1)
set(HAVE_DECODER_DELTA 1)

set(HAVE_LZIP_DECODER 1)

set(HAVE_DELTA_CODER 1)
set(SIMPLE_ENCODERS 1)
set(SIMPLE_DECODERS 1)
set(HAVE_ENCODERS 1)
set(HAVE_DECODERS 1)

set(HAVE_VISIBILITY 0)

if(WIN32)
    set(MYTHREAD_VISTA 1)
else()
    set(MYTHREAD_POSIX 1)
endif()

if(NOT "x${CMAKE_BUILD_TYPE}" STREQUAL "xDebug")
    set(NDEBUG 1)
endif()

set(HAVE_CONFIG_H 1)

unset(HAVE_SMALL)

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
  liblzma/check/crc32_table_be.h
  liblzma/check/crc32_table_le.h
  liblzma/check/crc64_table_be.h
  liblzma/check/crc64_table_le.h
  liblzma/check/sha256.c
  liblzma/common/alone_decoder.h
  liblzma/common/alone_decoder.c
  liblzma/common/alone_encoder.c
  liblzma/common/auto_decoder.c
  liblzma/common/block_buffer_decoder.c
  liblzma/common/block_buffer_encoder.h
  liblzma/common/block_buffer_encoder.c
  liblzma/common/block_decoder.h
  liblzma/common/block_decoder.c
  liblzma/common/block_encoder.h
  liblzma/common/block_encoder.c
  liblzma/common/block_header_decoder.c
  liblzma/common/block_header_encoder.c
  liblzma/common/block_util.c
  liblzma/common/common.h
  liblzma/common/common.c
  liblzma/common/easy_buffer_encoder.c
  liblzma/common/easy_decoder_memusage.c
  liblzma/common/easy_encoder.c
  liblzma/common/easy_encoder_memusage.c
  liblzma/common/easy_preset.h
  liblzma/common/easy_preset.c
  liblzma/common/file_info.c
  liblzma/common/filter_buffer_decoder.c
  liblzma/common/filter_buffer_encoder.c
  liblzma/common/filter_common.h
  liblzma/common/filter_common.c
  liblzma/common/filter_decoder.h
  liblzma/common/filter_decoder.c
  liblzma/common/filter_encoder.h
  liblzma/common/filter_encoder.c
  liblzma/common/filter_flags_decoder.c
  liblzma/common/filter_flags_encoder.c
  liblzma/common/hardware_cputhreads.c
  liblzma/common/hardware_physmem.c
  liblzma/common/index.h
  liblzma/common/index.c
  liblzma/common/index_decoder.h
  liblzma/common/index_decoder.c
  liblzma/common/index_encoder.h
  liblzma/common/index_encoder.c
  liblzma/common/index_hash.c
  liblzma/common/lzip_decoder.c
  liblzma/common/lzip_decoder.h
  liblzma/common/microlzma_encoder.c
  liblzma/common/microlzma_decoder.c
  liblzma/common/outqueue.h
  liblzma/common/outqueue.c
  liblzma/common/stream_buffer_decoder.c
  liblzma/common/stream_buffer_encoder.c
  liblzma/common/stream_decoder.h
  liblzma/common/stream_decoder.c
  liblzma/common/stream_encoder.c
  liblzma/common/stream_decoder_mt.c
  liblzma/common/stream_encoder_mt.c
  liblzma/common/stream_flags_common.h
  liblzma/common/stream_flags_common.c
  liblzma/common/stream_flags_decoder.c
  liblzma/common/stream_flags_encoder.c
  liblzma/common/vli_decoder.c
  liblzma/common/vli_encoder.c
  liblzma/common/vli_size.c
  liblzma/delta/delta_common.h
  liblzma/delta/delta_common.c
  liblzma/delta/delta_decoder.h
  liblzma/delta/delta_decoder.c
  liblzma/delta/delta_encoder.h
  liblzma/delta/delta_encoder.c
  liblzma/delta/delta_private.h
  liblzma/lz/lz_decoder.h
  liblzma/lz/lz_decoder.c
  liblzma/lz/lz_encoder.h
  liblzma/lz/lz_encoder.c
  liblzma/lz/lz_encoder_hash.h
  liblzma/lz/lz_encoder_hash_table.h
  liblzma/lz/lz_encoder_mf.c
  liblzma/lzma/fastpos.h
  liblzma/lzma/fastpos_table.c
  liblzma/lzma/lzma_encoder_private.h
  liblzma/lzma/lzma2_decoder.h
  liblzma/lzma/lzma2_decoder.c
  liblzma/lzma/lzma2_encoder.h
  liblzma/lzma/lzma2_encoder.c
  liblzma/lzma/lzma_decoder.h
  liblzma/lzma/lzma_decoder.c
  liblzma/lzma/lzma_encoder.h
  liblzma/lzma/lzma_encoder.c
  liblzma/lzma/lzma_encoder_optimum_fast.c
  liblzma/lzma/lzma_encoder_optimum_normal.c
  liblzma/lzma/lzma_encoder_presets.c
  liblzma/rangecoder/price.h
  liblzma/rangecoder/price_table.c
  liblzma/rangecoder/range_common.h
  liblzma/rangecoder/range_decoder.h
  liblzma/rangecoder/range_encoder.h
  liblzma/simple/arm.c
  liblzma/simple/arm64.c
  liblzma/simple/armthumb.c
  liblzma/simple/ia64.c
  liblzma/simple/powerpc.c
  liblzma/simple/simple_coder.h
  liblzma/simple/simple_coder.c
  liblzma/simple/simple_decoder.h
  liblzma/simple/simple_decoder.c
  liblzma/simple/simple_encoder.h
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

target_compile_definitions(ka_libLZMA PRIVATE
    HAVE_CONFIG_H
    TUKLIB_SYMBOL_PREFIX=lzma_
)

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
