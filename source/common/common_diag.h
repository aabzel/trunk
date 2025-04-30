#ifndef COMMON_DIAG_H
#define COMMON_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

bool hex2ascii(uint8_t* in_hex, uint32_t hex_len, uint8_t* out_ascii, uint32_t ascii_len);
const char* YesNo2Str(uint8_t status);
const char* BigVal2Str(double big_val);
const char* Ok2Str(bool status);
const char* Bit2Str(uint8_t bit);
const char* OnOff2Str(uint8_t status);
const char* OnOffToStr(uint8_t status);
char* Array2Str(uint8_t* array, uint32_t len);
char* RfFreq2Str(uint32_t rf_freq);
char* HexWord2Str(uint16_t word);
char* QWord2Str(uint32_t qword);
char* BitRate2Str(double bit_s);
char* ByteRate2Str(double bit_s);
char* Byte2Str(uint8_t byte);
const char* u32val2Str(uint32_t val);
char* uint2str(uint32_t val);

#ifdef __cplusplus
}
#endif

#endif /* COMMON_DIAG_H */
