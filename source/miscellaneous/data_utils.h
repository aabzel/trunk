#ifndef MISC_DATA_UTILS_H
#define MISC_DATA_UTILS_H

#include "std_includes.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "data_types.h"

#ifdef HAS_UTILS_EXT
#include "bit_utils.h"
#endif

#ifdef HAS_MATH
#include "utils_math.h"
#endif

#define SWAP(a, b)          \
    __extension__({         \
        __typeof__(a) temp; \
        temp = a;           \
        a = b;              \
        b = temp;           \
    })

#define BYTE_PS_2_BPS(BYTE_PS) ((BYTE_PS)*8)

#ifndef MIN
#define MIN(n, m) (((n) < (m)) ? (n) : (m))
#endif

#ifndef MAX
#define MAX(n, m) (((n) < (m)) ? (m) : (n))
#endif


/*TODO: check that DENOMINATOR is not 0.0*/
#define FRACTION_TO_PERCENTAGE(NUMERATOR, DENOMINATOR) ((double)(((double)100 * NUMERATOR) / ((double)DENOMINATOR)))

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

#define LIMIT_VALUE(MIN_VAL, MAX_VAL, VALUE)                                                                           \
    do {                                                                                                               \
        if((VALUE) < (MIN_VAL)) {                                                                                      \
            (VALUE) = (MIN_VAL);                                                                                       \
        }                                                                                                              \
        if((MAX_VAL) < (VALUE)) {                                                                                      \
            (VALUE) = (MAX_VAL);                                                                                       \
        }                                                                                                              \
    } while(0);

#define DATA_UPDATE(NODE, VAL)                                                                                         \
    do {                                                                                                               \
        NODE.cur = (VAL);                                                                                              \
        NODE.max = MAX(NODE.max, (VAL));                                                                               \
        NODE.min = MIN(NODE.min, (VAL));                                                                               \
    } while(0);

/* Compile time assert */
/* Note we need the 2 concats below because arguments to ##
 * are not expanded, so we need to expand __LINE__ with one indirection
 * before doing the actual concatenation. */
#define ASSERT_CONCAT_(a, b) a##b
#define ASSERT_CONCAT(a, b) ASSERT_CONCAT_(a, b)
#define ct_assert(e)                                                                                                   \
    {                                                                                                                  \
        enum { ASSERT_CONCAT(assert_line_, __LINE__) = 1 / (!!(e)) };                                                  \
    }

double limit_value_double(double min_val, double max_val, double in_value);
bool data_u64_update(U64Value_t* const Node, uint64_t val);
bool data_u32_init(U32Value_t* const Node);
bool data_u64_init(U64Value_t* const Node);
bool double_val_reset(DoubleValue_t* const double_val);
bool float_val_reset(FloatValue_t* const Node) ;
bool is_around_int_val(int32_t center, int32_t value, uint32_t delta);
bool mem_scan(uint8_t* base, uint32_t size, float* usage_pec, uint32_t* spare, uint32_t* busy);
bool swap8(uint8_t* const u8_x, uint8_t* const  u8_y);
bool swap_16(uint16_t* u16_x, uint16_t* u16_y);
bool toggle_bool(bool on_off);
bool swap_f(float* const u8_x, float* const u8_y);
const char* get_spaces_str(uint32_t spaces_length);
float ms2Hz(uint16_t ms);
int16_t max16(int16_t max16_x1, int16_t max16_x2);
int16_t min16(int16_t min16_x1, int16_t min16_x2);
int32_t int32_range_limiter(int32_t in_val, int32_t min, int32_t max);
int32_t max32(int32_t max32_x1, int32_t max32_x2);
int32_t min32(int32_t min32_x1, int32_t min32_x2);
int8_t int32_limiter(int32_t in_val);
int8_t int8_limiter(int32_t in_val);
int8_t max8(int8_t max8_x1, int8_t max8_x2);
int8_t min8(int8_t min8_x1, int8_t min8_x2);
uint16_t max16u(uint16_t max16u_x1, uint16_t max16u_x2);
uint16_t min16u(uint16_t min16u_x1, uint16_t min16u_x2);
uint16_t swap16(uint16_t u16_num);
bool swap_u32_xor(uint32_t *const  a, uint32_t *const b);
uint32_t ceil4byte(uint32_t val);
uint32_t max32u(uint32_t max32u_x1, uint32_t max32u_x2);
uint32_t min32u(uint32_t min32u_x1, uint32_t min32u_x2);
uint32_t swap32(uint32_t u32_num);
uint64_t max64u(uint64_t max64u_x1, uint64_t max64u_x2);
uint64_t min64u(uint64_t min64u_x1, uint64_t min64u_x2);
uint8_t Bits2Bytes(uint8_t bits_cnt);
uint8_t extract_digit(uint32_t in_num, uint8_t digit_index);
uint8_t max8u(uint8_t max8u_x1, uint8_t max8u_x2);
uint8_t min8u(uint8_t min8u_x1, uint8_t min8u_x2);
uint8_t uint16_to_uint8_limiter(uint16_t in_val);
uint8_t uint8_limiter(uint8_t in_val, uint8_t up_val);
uint32_t uint32_limiter(uint32_t in_val, uint32_t max);

#ifdef __cplusplus
}
#endif

#endif /* MISC_DATA_UTILS_H */
