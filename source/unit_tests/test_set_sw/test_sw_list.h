#ifndef TEST_SW_LIST_H
#define TEST_SW_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "unit_test.h"

#ifndef HAS_UNIT_TEST
#error "It is needed HAS_UNIT_TEST option for that component"
#endif

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif

#ifdef HAS_TEST_CALIBRATION_DATA
#include "test_calibration_data.h"
#else
#define TEST_SUIT_CALIBRATION_DATA
#endif

#ifdef HAS_TEST_ALLOCATOR
#include "test_allocator.h"
#else
#define TEST_SUIT_ALLOCATOR
#endif

#ifdef HAS_TEST_ARRAY
#include "test_array.h"
#else
#define TEST_SUIT_ARRAY
#endif

#ifdef HAS_TEST_SUIT_AES256
#include "test_aes.h"
#else
#define TEST_SUIT_AES256
#endif

#ifdef HAS_TEST_SUIT_CONVERT
/*Not Fit in Flash Memory. Test it on PC*/
#include "test_convert.h"
#else
#define TEST_SUIT_CONVERT
#endif

#ifdef HAS_TEST_CLI
#include "test_cli.h"
#else
#define TEST_SUIT_CLI
#endif

#ifdef HAS_TEST_SUIT_CRC
#include "test_crc.h"
#else
#define TEST_SUIT_CRC
#endif

#ifdef HAS_TEST_SUIT_KEYBOARD
#include "test_keyboard.h"
#else
#define TEST_SUIT_KEYBOARD
#endif

#ifdef HAS_TEST_SUIT_KEEPASS
#include "test_keepass.h"
#else
#define TEST_SUIT_KEEPASS
#endif

#ifdef HAS_TEST_SUIT_WAV
#include "test_wav.h"
#else
#define TEST_SUIT_WAV
#endif

#ifdef HAS_TEST_SUIT_CALENDAR
#include "test_calendar.h" /*Too Long test Perform on PC*/
#else
#define TEST_SUIT_CALENDAR
#endif

#ifdef HAS_TEST_SUIT_CALCULATOR
#include "test_calculator.h"
#else
#define TEST_SUIT_CALCULATOR
#endif

#ifdef HAS_TEST_SUIT_UBLOX_PROTO
#include "test_ublox_proto.h"
#else
#define TEST_SUIT_UBLOX_PROTO
#endif

#ifdef HAS_TEST_SUIT_NMEA_PROTO
#include "test_nmea_proto.h"
#else
#define TEST_SUIT_NMEA_PROTO
#endif

#ifdef HAS_TEST_SUIT_STRING_UTILS
#include "test_string_utils.h"
#else
#define TEST_SUIT_STRING_UTILS
#endif

#ifdef HAS_TEST_SUIT_RTCM3_PROTO
#include "test_rtcm3_proto.h"
#else
#define TEST_SUIT_RTCM3_PROTO
#endif

#ifdef HAS_TEST_SUIT_AUTO_VERSION
#include "test_auto_version.h"
#else
#define TEST_SUIT_AUTO_VERSION
#endif

#ifdef HAS_TEST_SUIT_GNSS
#include "test_gnss.h"
#else
#define TEST_SUIT_GNSS
#endif

#ifdef HAS_TEST_SUIT_TBFP
#include "test_tbfp.h"
#else
#define TEST_SUIT_TBFP
#endif

#ifdef HAS_TEST_SUIT_TBFP_RTCM
#include "test_tbfp_rtcm_proto.h"
#else
#define TEST_SUIT_TBFP_RTCM_STACK
#endif

#ifdef HAS_TEST_SUIT_PHYSICS
#include "test_physics.h"
#else
#define TEST_SUIT_PHYSICS
#endif

#include "test_libc.h"

#ifdef HAS_TEST_SUIT_LIFO
#include "test_lifo_array.h"
#include "test_lifo_indexer.h"
#else
#define TEST_SUIT_LIFO_ARRAY
#define TEST_SUIT_LIFO_INDEXER
#endif

#ifdef HAS_TEST_SUIT_FIFO
#include "test_fifo_array.h"
#include "test_fifo_char.h"
#include "test_fifo_indexer.h"
#else
#define TEST_SUIT_FIFO_ARRAY
#define TEST_SUIT_FIFO_CHAR
#define TEST_SUIT_FIFO_INDEXER
#endif

#include "unit_test_check.h"

#ifdef HAS_TEST_SUIT_SYSTEM
#include "test_system.h"
#else
#define TEST_SUIT_SYSTEM_SW
#endif

#ifdef HAS_TEST_SUIT_MEMORY
#include "test_memory.h"
#else
#define TEST_SUIT_MEMORY
#endif

#ifdef HAS_TEST_SUIT_PLANETARIUM
#include "test_planetarium.h"
#else
#define TEST_SUIT_PLANETARIUM
#endif

#ifdef HAS_TEST_SUIT_SOUND_LOCALIZATION
#include "test_sound_localization.h"
#else
#define TEST_SUIT_SOUND_LOCALIZATION
#endif

#ifdef HAS_TEST_SUIT_SW_NVRAM
#include "test_sw_nvram.h"
#else
#define TEST_SUIT_SW_NVRAM
#endif

#ifdef HAS_TEST_SUIT_MODULATOR
#include "test_modulator.h"
#else
#define TEST_SUIT_MODULATOR
#endif

#ifdef HAS_TEST_SUIT_FLOAT
#include "float_utils_test.h"
#else
#define TEST_SUIT_UTILS_FLOAT
#endif

#ifdef HAS_TEST_SUIT_UTILS
#include "bit_utils_test.h"
#include "byte_utils_test.h"
#include "data_utils_test.h"
#else
#define TEST_SUIT_UTILS_BIT
#define TEST_SUIT_UTILS_BYTE
#define TEST_SUIT_UTILS_DATA
#endif

#ifdef HAS_TEST_SUIT_FAT_FS
#include "test_fat_fs.h"
#else
#define TEST_SUIT_FAT_FS
#endif

#ifdef HAS_TEST_SUIT_UTILS_TIME
#include "test_time_utils.h"
#else
#define TEST_SUIT_UTILS_TIME
#endif

#ifdef HAS_TEST_SUIT_RDS
#include "test_rds_proto.h"
#else
#define TEST_SUIT_RDS
#endif

#ifdef HAS_TEST_SUIT_LC3
#include "test_lc3.h"
#else
#define TEST_SUIT_LC3
#endif

#ifdef HAS_TEST_SUIT_MATH
#include "test_math.h"
#else
#define TEST_SUIT_MATH
#endif

#ifdef HAS_TEST_SUIT_PASTILDA
#include "test_pastilda.h"
#else
#define TEST_SUIT_PASTILDA
#endif

#ifdef HAS_TEST_SUIT_RTCM3_PATH
#include "test_rtcm_path.h"
#else
#define TEST_SUIT_RTCM3_PATH
#endif

#ifdef HAS_TEST_SUIT_SHA256
#include "test_sha256.h"
#else
#define TEST_SUIT_SHA256
#endif

#ifdef HAS_TEST_SUIT_SALSA20
#include "test_salsa20.h"
#else
#define TEST_SUIT_SALSA20
#endif

#ifdef HAS_TEST_SUIT_SOLVER
#include "test_solver.h"
#else
#define TEST_SUIT_SOLVER
#endif

#ifdef HAS_TEST_SUIT_FFT
#include "test_fft.h"
#else
#define TEST_SUIT_FFT
#endif

#ifdef HAS_TEST_SUIT_DFT
#include "test_dft.h"
#else
#define TEST_SUIT_DFT
#endif

#ifdef HAS_TEST_SUIT_HASHSET
#include "test_hashset.h"
#else
#define TEST_SUIT_HASHSET
#endif

#ifdef HAS_TEST_SUIT_SET
#include "test_set.h"
#else
#define TEST_SUIT_SET
#endif

#ifdef HAS_TEST_SUIT_BASE16
#include "test_base16.h"
#else
#define TEST_SUIT_BASE16
#endif

#ifdef HAS_TEST_SUIT_BASE64
#include "test_base64.h"
#else
#define TEST_SUIT_BASE64
#endif

#ifdef HAS_TEST_SUIT_ISO_TP
#include "test_iso_tp.h"
#else
#define TEST_SUIT_ISO_TP
#endif


#ifdef HAS_TEST_SUIT_BT1026
#include "test_bt1026.h"
#else
#define TEST_SUIT_BT1026
#endif

#ifdef HAS_TEST_SUIT_CSV
#include "test_csv.h"
#else
#define TEST_SUIT_CSV
#endif

#ifdef HAS_TEST_SUIT_CROSS_DETECT
#include "test_cross_detect.h"
#else
#define TEST_SUIT_CROSS_DETECT
#endif

#ifdef HAS_TEST_SUIT_FONT
#include "test_font.h"
#else
#define TEST_SUIT_FONT
#endif

#ifdef HAS_TEST_SUIT_DS_TWR
#include "test_ds_twr.h"
#else
#define TEST_SUIT_DS_TWR
#endif

#ifdef HAS_TEST_SUIT_RLE
#include "test_rle.h"
#else
#define TEST_SUIT_RLE
#endif

#ifdef HAS_TEST_SUIT_IIR
#include "test_iir.h"
#else
#define TEST_SUIT_IIR
#endif

#ifdef HAS_TEST_SUIT_FIR
#include "test_fir.h"
#else
#define TEST_SUIT_FIR
#endif

#ifdef HAS_TEST_SUIT_CIRCULAR_BUFFER
#include "test_circular_buffer_indexer.h"
#else
#define TEST_SUIT_CIRCULAR_BUFFER
#endif

#ifdef HAS_TEST_SUIT_DECAWAVE_PROTO
#include "test_decawave_proto.h"
#else
#define TEST_SUIT_DECAWAVE_PROTO
#endif

#ifdef HAS_TEST_SUIT_DECAWAVE_NATIVE
#include "test_decawave_native.h"
#else
#define TEST_SUIT_DECAWAVE_NATIVE
#endif

#ifdef HAS_TEST_SUIT_PROTOCOL
#include "test_protocol.h"
#else
#define TEST_SUIT_PROTOCOL
#endif

#ifdef HAS_TEST_SUIT_BPSK
#include "test_bpsk.h"
#else
#define TEST_SUIT_BPSK
#endif

#ifdef HAS_TEST_SUIT_HEX_BIN
#include "test_hex_bin.h"
#else
#define TEST_SUIT_HEX_BIN
#endif

#ifdef HAS_TEST_SUIT_SCHMITT_TRIGGER
#include "test_schmitt_trigger.h"
#else
#define TEST_SUIT_SCHMITT_TRIGGER
#endif

#ifdef HAS_TEST_SUIT_DDS
#include "test_dds.h"
#else
#define TEST_SUIT_DDS
#endif

#ifdef HAS_TEST_SUIT_UDS
#include "test_uds.h"
#else
#define TEST_SUIT_UDS
#endif

#ifdef HAS_TEST_SUIT_SOCKET
#include "test_socket.h"
#else
#define TEST_SUIT_SOCKET
#endif

#ifdef HAS_TEST_PYRAMID_ACCEL_CALIB
#include "test_pyramid_accel_calib.h"
#else
#define TEST_SUIT_PYRAMID_ACCEL_CALIB
#endif


bool test_sprintf_minus(void);
bool test_general(void);
bool test_c_types(void);
bool test_array_init(void);
bool test_64bit_mult(void);
bool test_struct_copy(void);
#ifdef HAS_EXTRA_TEST
bool test_print_name(void);
#define TEST_SUIT_EXTRA     {"PrintName", test_print_name},
#else
#define TEST_SUIT_EXTRA
#endif
bool test_utoa_bin8(void);
bool test_snprintf_d(void);
bool test_snprintf_f(void);
bool test_snprintf_small_double(void);
bool test_sprintf_u64(void);
bool test_sprintf_long(void);

#ifdef HAS_MCU
bool test_float_to_uint16(void);
#define TEST_TYPE_CONVERT_FLOAT {"flt_u16", test_float_to_uint16},
#else
#define TEST_TYPE_CONVERT_FLOAT
#endif

bool test_visibility(void);
bool test_int_overflow(void);
bool test_bit_shift(void);
bool test_double_to_uint16(void);
bool test_type_transformation(void);
bool test_array(void);
bool test_memset(void);
bool test_memcpy(void);
bool test_snprintf(void);
bool test_pointers(void);
bool test_endian(void);
bool test_swap_xor(void);
bool test_bit_fields(void);
bool test_uspec_behavior(void);
bool test_struct_size(void) ;

#define TEST_TYPE_CONVERT TEST_TYPE_CONVERT_FLOAT {"dbl_u16", test_double_to_uint16},

#define TEST_SUIT_SW                                                  \
    {"struct_size", test_struct_size},                                  \
    {"array_init", test_array_init},                                  \
    {"bit_fields", test_bit_fields},                                  \
    {"swap_xor", test_swap_xor},                                  \
    {"c_types", test_c_types},                                        \
    {"memset", test_memset},                                          \
    {"snprintf", test_snprintf},                                          \
    {"memcpy", test_memcpy},                                          \
    {"bit_shift", test_bit_shift},                                        \
    {"int_overflow", test_int_overflow},                                        \
    {"sprintf_minus", test_sprintf_minus},                            \
    {"endian", test_endian},                                          \
    {"snprintf_d", test_snprintf_d},                                            \
    {"snprintf_f", test_snprintf_f},                                            \
    {"sprintf_u64", test_sprintf_u64},                              \
    {"snprintf_small_double", test_snprintf_small_double},                  \
    {"sprintf_long", test_sprintf_long},                              \
    {"struct_copy", test_struct_copy},                                \
    {"visibility", test_visibility},                                  \
    {"uspec_behavior", test_uspec_behavior},                          \
    {"pointers", test_pointers},                                      \
    {"array", test_array},                                            \
    {"64bit_mult", test_64bit_mult},                                  \
    {"utoa_bin8", test_utoa_bin8},                                    \
    {"type_transform", test_type_transformation},                     \
    { "general", test_general},                                       \
    TEST_SUIT_EXTRA                                                   \
    TEST_SUIT_AES256                                                  \
    TEST_SUIT_ALLOCATOR                                               \
    TEST_SUIT_LIBC                                                    \
    TEST_SUIT_ARRAY                                                   \
    TEST_SUIT_AUTO_VERSION                                            \
    TEST_SUIT_BASE16                                                  \
    TEST_SUIT_BASE64                                                  \
    TEST_SUIT_BPSK                                                    \
    TEST_SUIT_PROTOCOL                                                \
    TEST_SUIT_BT1026                                                  \
    TEST_SUIT_CALENDAR                                                \
    TEST_SUIT_CALCULATOR                                              \
    TEST_SUIT_CIRCULAR_BUFFER                                         \
    TEST_SUIT_CLI                                                     \
    TEST_SUIT_CONVERT                                                 \
    TEST_SUIT_CRC                                                     \
    TEST_SUIT_CROSS_DETECT                                            \
    TEST_SUIT_CSV                                                     \
    TEST_SUIT_DECAWAVE_PROTO                                          \
    TEST_SUIT_DECAWAVE_NATIVE                                         \
    TEST_SUIT_DFT                                                     \
    TEST_SUIT_FFT                                                     \
    TEST_SUIT_DDS                                                     \
    TEST_SUIT_DS_TWR                                                  \
    TEST_SUIT_FAT_FS                                                  \
    TEST_SUIT_FIFO_ARRAY                                              \
    TEST_SUIT_FIFO_CHAR                                               \
    TEST_SUIT_FIFO_INDEXER                                            \
    TEST_SUIT_GNSS                                                    \
    TEST_SUIT_FIR                                                     \
    TEST_SUIT_FONT                                                    \
    TEST_SUIT_HASHSET                                                 \
    TEST_SUIT_HEX_BIN                                                 \
    TEST_SUIT_ISO_TP                                                  \
    TEST_SUIT_IIR                                                     \
    TEST_SUIT_KEEPASS                                                 \
    TEST_SUIT_KEYBOARD                                                \
    TEST_SUIT_LC3                                                     \
    TEST_SUIT_LIFO_ARRAY                                              \
    TEST_SUIT_LIFO_INDEXER                                            \
    TEST_SUIT_MATH                                                    \
    TEST_SUIT_MEMORY                                                  \
    TEST_SUIT_MODULATOR                                               \
    TEST_SUIT_NMEA_PROTO                                              \
    TEST_SUIT_PASTILDA                                                \
    TEST_SUIT_PHYSICS                                                 \
    TEST_SUIT_PLANETARIUM                                             \
    TEST_SUIT_PYRAMID_ACCEL_CALIB                                     \
    TEST_SUIT_RDS                                                     \
    TEST_SUIT_RLE                                                     \
    TEST_SUIT_RTCM3_PATH                                              \
    TEST_SUIT_RTCM3_PROTO                                             \
    TEST_SUIT_SALSA20                                                 \
    TEST_SUIT_SCHMITT_TRIGGER                                         \
    TEST_SUIT_SET                                                     \
    TEST_SUIT_SHA256                                                  \
    TEST_SUIT_SOCKET                                                  \
    TEST_SUIT_SOLVER                                                  \
    TEST_SUIT_SOUND_LOCALIZATION                                      \
    TEST_SUIT_STRING_UTILS                                            \
    TEST_SUIT_SW_NVRAM                                                \
    TEST_SUIT_SYSTEM_SW                                               \
    TEST_SUIT_TBFP                                              \
    TEST_SUIT_TBFP_RTCM_STACK                                         \
    TEST_SUIT_UTILS_BIT                                               \
    TEST_SUIT_UTILS_BYTE                                              \
    TEST_SUIT_UTILS_DATA                                              \
    TEST_SUIT_UTILS_FLOAT                                             \
    TEST_SUIT_UTILS_TIME                                              \
    TEST_SUIT_UDS                                                     \
    TEST_SUIT_WAV                                                 \
    TEST_TYPE_CONVERT                                                 \
    TEST_SUIT_UBLOX_PROTO

#ifdef __cplusplus
}
#endif

#endif /*TEST_SW_LIST_H*/
