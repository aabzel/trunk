#ifndef COMMON_DIAG_H
#define COMMON_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifdef HAS_FILE_API
#include "file_api.h"
#endif

#ifndef MASK_4BIT
#define MASK_4BIT  ((uint32_t)0x0000000FU )
#endif

#ifdef HAS_FILE_API
#define LOG_ERROR_LINE(FASIL) LOG_ERROR(FASIL,"%s:%u",file_path_to_file_name(__FILE__),__LINE__)
#endif

float diag_progress_log(uint32_t cur, uint32_t total, uint32_t parts);
char* uint2str(uint32_t val);
char* RfFreqToStr(uint32_t rf_freq);
char* HexWordToStr(uint16_t word);
char* QWordToStr(uint32_t qword);
char* BitRateToStr(double bit_s);
char* ByteRateToStr(double bit_s);
char* ByteToStr(uint8_t byte);

const char* UnsignedBigEndianToStr(const uint8_t* const memory, const uint32_t param_size);
const char* ProgressRealToStr(float cur, float total) ;
const char* ProgressFloatToStr(float cur, float total) ;
const char* ProgressToStr(uint32_t cur, uint32_t total);
const char* YesNoToStr(uint8_t status);
const char* BigValToStr(double big_val);
const char* OkToStr(bool status);
const char* ResToStr(bool res);
const char* OnOffToStr(uint8_t status);
const char* BitToAsterisk(const uint8_t bit);
const char* U8DecToStr(const void* const data);
const char* U8ToStr(const void* const data);
const char* U16DecToStr(const void* const data);
const char* U16ToStr(const void* const data);
const char* U32DecToStr(const void* const data);
const char* U32ToStr(const void* const data);
const char* u32valToStr(uint32_t val);

bool print_progress(uint32_t cur, uint32_t total);
bool hex2ascii(const uint8_t* const in_hex, uint32_t hex_len, uint8_t* out_ascii, uint32_t ascii_len);
bool common_diag(void);

#ifdef __cplusplus
}
#endif

#endif /* COMMON_DIAG_H */
