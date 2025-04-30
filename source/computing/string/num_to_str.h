#ifndef NUM_TO_STR_H
#define NUM_TO_STR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_NUM_DIAG
#error "+HAS_NUM_DIAG"
#endif

#ifndef MAX_INT64_STR_LEN_10
#define MAX_INT64_STR_LEN_10 (sizeof("-18446744073709551614") - 1U)
#endif

#define MAX_INT32_STR_LEN_10 (sizeof("-4294967295") - 1U)
#define MAX_INT64_STR_LEN_16 (sizeof(uint64_t) * 2U)
#define MAX_INT32_STR_LEN_16 (sizeof(uint32_t) * 2U)
#define MAX_INT16_STR_LEN_16 (sizeof(uint16_t) * 2U)
#define MAX_INT8_STR_LEN_16 (sizeof(uint8_t) * 2U)

bool PrintReg32(uint32_t value);

const char* rx_ftoa(float float_v);
const char* rx_dtoa(double d);
const char* DoubleToStr(double value);
const char* uint32ToStr(uint32_t value);
const char* bool2test_status(bool val);
const char* bool2name(bool val);
const char* ltoa32_(int32_t s32_data, char s32_stringified[], uint8_t s32_base, uint32_t* s32_len);
const char* ltoa64_(int64_t s64_data, char s64_stringified[], uint8_t s64_base, uint32_t* s64_len);
const char* utoa32_(uint32_t u32_data, char u32_stringified[], uint8_t u32_base, uint32_t* u32_len);
const char* utoa64_(uint64_t u64_data, char u64_stringified[], uint8_t u64_base, uint32_t* u64_len);
const char* rx_ltoa32(int32_t ltoa32_data);
const char* rx_ltoa64(int64_t ltoa64_data);
const char* rx_utoa32(uint32_t utoa32_data);
const char* rx_utoa64(uint64_t utoa64_data);
const char* utoa_hex32(uint32_t u32_hex_data);
const char* utoa_hex64(uint64_t u64_hex_data);
const char* ltoa_hex32(int32_t s32_hex_data);
const char* ltoa_hex64(int64_t s64_hex_data);

#ifdef HAS_BIN_2_STR
const char* utoa_bin8_plain(uint8_t u8_bin_data);
const char* utoa_bin8(uint8_t u8_bin_data);
const char* utoa_bin16(uint16_t u16_bin_data);
const char* utoa_bin16_plain(uint16_t u16_bin_data);
const char* utoa_bin24(uint32_t u32_bin_data);
const char* utoa_bin24_plain(uint32_t u32_bin_data);
const char* utoa_bin32(uint32_t u32_bin_data);
const char* utoa_bin64(uint64_t u64_bin_data);
#endif

bool array2str(const uint8_t* const buff, uint32_t buff_len, char* const out_array, uint16_t array_size);

char* HexQWord2Str(uint32_t qword);
char* HexQWordToStr(uint64_t qword);
char* HexQWordRevToStr(uint64_t qword);

#ifdef __cplusplus
}
#endif

#endif /* NUM_TO_STR_H */
