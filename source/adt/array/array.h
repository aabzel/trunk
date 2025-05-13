#ifndef ARRAY_API_H
#define ARRAY_API_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include "std_includes.h"

#include "array_types.h"
#ifdef HAS_ARRAY_DIAG
#include "array_diag.h"
#endif

#ifndef HAS_ARRAY
#error "+HAS_ARRAY"
#endif

#ifndef MAX
#define MAX(n, m) (((n) < (m)) ? (m) : (n))
#endif


#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

bool array_s8_add_front_zeros(int8_t* const SampleArray, uint32_t array_size,int32_t offset);

bool array_s16_shift_right(int16_t* const arr, uint32_t size, uint32_t shift);
bool array_s16_add_front_zeros(int16_t* const SampleArray, uint32_t array_size,int32_t offset);
bool array_s16_add_front(int16_t* arr, uint32_t size, int16_t value) ;
bool array_i8_mult(const int8_t* const array1, const int8_t* const array2, int8_t* const mult_array, uint32_t size);
bool array_i16_decimation_2(int16_t* const arr, uint32_t size);

bool array_s32_add_front_zeros(int32_t* const  SampleArray, uint32_t array_size,int32_t offset);

uint32_t inc_index(uint32_t cur, uint32_t max, bool* const overflow);
uint32_t arr_i8_sum_vals(const int8_t* const arr, uint32_t num, int8_t val);
bool array_bit_array_to_hex(const uint8_t* const bit_array, uint32_t bit_array_size, uint8_t* const data, uint32_t size);
bool array_u8_shift_left(uint8_t* const data, uint32_t size, uint32_t cnt);
bool array_u8_del_indices(uint8_t* const data, uint32_t size, uint32_t index, uint32_t cnt);
bool array_u8_del_index(uint8_t* const data, uint32_t size, uint32_t index);
bool array_u8_insert_first(uint8_t* const arr, uint32_t size, uint8_t value);
bool array_u8_rand(uint8_t* const arr, uint32_t size, uint8_t min, uint8_t max);
bool array_u8_sort(uint8_t* const arr, uint32_t size);
bool array_add_front(uint8_t* arr, uint32_t size, uint8_t* prefix, uint32_t prefix_size);
bool array_is_equal(const uint8_t* const array1, const uint8_t* const array2, uint32_t size);
bool array_is_equal_ext(const uint8_t* const array1, const uint8_t* const array2, const uint32_t size, uint32_t* const diff);
bool array_is_same(const uint8_t* const addr, uint32_t len);
bool array_pat_set(uint8_t* arr, uint32_t size, uint8_t patt);
bool array_rand(uint8_t* arr, uint32_t size);
bool array_incr(uint8_t* const arr, uint32_t size);
bool array_incr_u32(uint32_t* arr, uint32_t size);
bool array_cmp(const uint8_t* const arr1, const uint8_t* const arr2, uint32_t size);
bool array_max_cont(const uint8_t* const arr, uint32_t size, uint8_t patt, uint32_t* max_cont_patt);
bool array_max_double(double const* const data, uint32_t size, uint32_t* const index, double* const max_val);
bool array_reverse_bytes(uint8_t* const in_out_array, uint32_t len);
bool array_reverse_float(float* const in_out_array, uint32_t len);
bool array_u16_item_reverse_bytes(uint16_t* const in_out_array, uint32_t len);
bool array_u32_item_reverse_bytes(uint32_t* const in_out_array, uint32_t len);
bool array_shift_right(uint8_t* arr, uint32_t size, uint32_t shift);
bool uniq_array(const uint8_t* const addr, uint32_t len);
bool is_arr_pat(const uint8_t* const arr, uint32_t size, uint8_t patt);
bool is_array_equal(uint8_t* array1, uint8_t* array2, uint32_t size, uint32_t* match, uint32_t* diff);
int32_t array_i8_mult_sum(const int8_t* const array1, const int8_t* array2, uint32_t size);
uint32_t array_double_max_index(const double* const arr, uint32_t size);
uint32_t array_index_prev(uint32_t cur_index, uint32_t size);
uint32_t array_index_next(uint32_t cur_index, uint32_t size);
uint32_t arr_sum(const uint8_t* const arr, uint32_t num);
int32_t arr_sum_i8(const int8_t* const arr, uint32_t num);
double arr_sum_double(const double* const arr, uint32_t num);
uint8_t* memdup(const uint8_t* mem, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif /* ARRAY_API_H */
