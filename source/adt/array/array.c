#include "array.h"

#include <float.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef HAS_X86_64
#include <stdio.h>
#include <time.h>
#endif

#ifdef HAS_MISCELLANEOUS
#include "byte_utils.h"
#endif

#ifdef HAS_BIT_UTILS
#include "bit_utils.h"
#endif

#ifdef HAS_MATH
#include "utils_math.h"
#endif

#ifdef HAS_CORE
#include "core_driver.h"
#endif

#ifdef HAS_TIME
#include "time_mcal.h" /*For Rand Num Generator*/
#endif                 /*HAS_TIME*/

#ifdef HAS_MCU

#ifdef HAS_CLOCK
#include "clock.h"
#endif /*HAS_CLOCK*/

#endif /*HAS_MCU*/

#include "data_utils.h"
#ifdef HAS_STREAM
#include "debug_info.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

// array_index_next(9, 10)->0
// array_index_next(0, 10)->1
// array_index_next(100, 10)->0
uint32_t array_index_next(uint32_t cur_index, uint32_t size) {
    uint32_t new_index = cur_index;
    if(cur_index < size) {
        if(cur_index < (size - 1)) {
            new_index++;
        } else {
            new_index = 0;
        }
    } else {
        new_index = 0;
    }
    return new_index;
}

// array_index_prev(0,10) ->9
// array_index_prev(9,10) ->8
// array_index_prev(100,10) ->9
uint32_t array_index_prev(uint32_t cur_index, uint32_t size) {
    uint32_t new_index = cur_index;
    if(cur_index < size) {
        if(0 < new_index) {
            new_index--;
        } else {
            new_index = size - 1;
        }

    } else {
        new_index = size - 1;
    }
    return new_index;
}

/*
 Note: assume caller calls free().
 */
uint8_t* memdup(const uint8_t* const data, uint32_t size) {
    uint8_t* out_new_mem = NULL;
    if(0 < size) {
        if(data) {
            out_new_mem = (uint8_t*)malloc(size);
            if(out_new_mem) {
                memcpy((void*)out_new_mem, (void*)data, size);
            }
        }
    }
    return out_new_mem;
}

bool is_arr_pat(const uint8_t* const arr, uint32_t size, uint8_t patt) {
    bool res = true;
    uint32_t i = 0;
    for(i = 0; i < size; i++) {
        if(patt != arr[i]) {
            res = false;
        }
    }
    return res;
}

#ifdef HAS_ARRAY_EXT
bool array_pat_set(uint8_t* arr, uint32_t size, uint8_t patt) {
    bool res = false;
    if(arr) {
        if(0 < size) {
            uint32_t i = 0;
            for(i = 0; i < size; i++) {
                arr[i] = patt;
            }
            res = true;
        }
    }
    return res;
}
#endif

bool array_max_cont(const uint8_t* const arr, uint32_t size, uint8_t patt, uint32_t* max_cont_patt) {
    bool res = false;
#if 0
    if(is_ram_addr((uint32_t)arr) && is_ram_addr((uint32_t)(arr + size))) {
        res = true;
    } else {
        LOG_ERROR(ARRAY, "Not a RAM");
        res = false;
    }
#else
    res = true;
#endif
    if(res) {
        res = true;
        if(arr && (0 < size) && max_cont_patt) {
            res = true;
            uint32_t cur_cont_pat = 0;
            uint32_t max_cont_pat = 0;
            uint8_t prev_elem = 0xFF;
            uint32_t i = 0;
            for(i = 0; i < size; i++) {

                if(patt == arr[i]) {
                    cur_cont_pat++;
                    if(prev_elem != arr[i]) {
                        cur_cont_pat = 1;
                    }
                } else {
                    cur_cont_pat = 0;
                }
                prev_elem = arr[i];
                max_cont_pat = MAX(max_cont_pat, cur_cont_pat);
            }
            *max_cont_patt = max_cont_pat;
        }
    }
    return res;
}

#ifdef HAS_ARRAY_EXT
bool array_incr(uint8_t* const arr, uint32_t size) {
    bool res = false;
    uint32_t i = 0;
    if(arr) {
        if(0 < size) {
            for(i = 1; i < size; i++) {
                arr[i] = (uint8_t)i;
            }
            res = true;
        }
    }
    return res;
}

bool array_incr_u32(uint32_t* arr, uint32_t size) {
    bool res = false;
    uint32_t i = 0;
    if(arr && (0 < size)) {
        for(i = 0; i < size; i++) {
            arr[i] = (uint32_t)i + 1;
        }
        res = true;
    }
    return res;
}

bool array_rand(uint8_t* arr, uint32_t size) {
    bool res = false;
    uint32_t i = 0;
#ifdef HAS_TIME
    srand(time_get_ms32());
#endif

    if(arr && (0 < size)) {
        for(i = 0; i < size; i++) {
            arr[i] = (uint8_t)(rand() % 255);
        }
        res = true;
    }
    return res;
}

bool array_u8_rand(uint8_t* const arr, uint32_t size, uint8_t min, uint8_t max) {
    bool res = false;
    uint32_t i = 0;
#ifdef HAS_TIME
    srand(time_get_ms32());
#endif

    if(arr && (0 < size)) {
        for(i = 0; i < size; i++) {
            arr[i] = (uint8_t)(rand() % max) + 1;
        }
        res = true;
    }
    return res;
}

bool is_array_equal(uint8_t* array1, uint8_t* array2, uint32_t size, uint32_t* match, uint32_t* diff) {
    LOG_DEBUG(ARRAY, "%s():", __FUNCTION__);
    bool res = false;
    if(array1 && array2 && match && diff) {
        uint32_t i = 0;
        for(i = 0; i < size; i++) {
            if(array1[i] == array2[i]) {
                (*match)++;
            } else {
                (*diff)++;
            }
        }
        if((*match) == size) {
            res = true;
        } else {
            res = false;
#ifdef HAS_ARRAY_DIAG
            LOG_ERROR(ARRAY, "Match:%u", *match);
            LOG_ERROR(ARRAY, "Arr1");
            print_mem(array1, size, true, false, true, true);
            LOG_ERROR(ARRAY, "Arr2");
            print_mem(array2, size, true, false, true, true);
#endif
        }
    }
    return res;
}

bool array_cmp(const uint8_t* const arr1, const uint8_t* const arr2, uint32_t size) {
    bool res = false;
    uint32_t i = 0;
    uint32_t cnt = 0;
    for(i = 0; i < size; i++) {
        if(arr1[i] != arr2[i]) {
            res = false;
        } else {
            cnt++;
        }
    }

    if(cnt == size) {
        res = true;
    } else {
        res = false;
    }

    return res;
}
#endif

uint32_t arr_sum(const uint8_t* const arr, uint32_t num) {
    uint32_t sum = 0;
    uint32_t i;
    for(i = 0; i < num; i++) {
        sum += arr[i];
    }
    return sum;
}

int32_t arr_sum_i8(const int8_t* const arr, uint32_t size) {
    int32_t sum = 0;
    if(arr) {
        if(size) {
#ifdef HAS_LOG
            LOG_INFO(ARRAY, "i8ArraySum:%u", size);
#endif
            uint32_t i;
            for(i = 0; i < size; i++) {
                sum += arr[i];
            }
        }
    }
    return sum;
}

uint32_t arr_i8_sum_vals(const int8_t* const arr, uint32_t num, int8_t val) {
    uint32_t sum = 0;
    uint32_t i;
    for(i = 0; i < num; i++) {
        if(val == arr[i]) {
            sum++;
        }
    }
    return sum;
}

double arr_sum_double(const double* const arr, uint32_t num) {
    double sum = 0.0;
    uint32_t i = 0;
    for(i = 0; i < num; i++) {
        sum += arr[i];
    }
    return sum;
}

bool array_is_equal_ext(const uint8_t* const array1,
		                const uint8_t* const array2,
						const uint32_t size,
						uint32_t* const diff) {
#ifdef HAS_LOG
    LOG_DEBUG(ARRAY, "%s():", __FUNCTION__);
#endif
    bool res = false;
    if(size) {
        if(array1 && array2) {
            uint32_t match = 0;
            uint32_t l_diff = 0;
            uint32_t i = 0;
            for(i = 0; i < size; i++) {
                if(array1[i] == array2[i]) {
                    match++;
                } else {
                    l_diff++;
#ifdef HAS_LOG
                    LOG_DEBUG(ARRAY, "Diff i=%u,0x%02x!=0x%02x", i, array1[i], array2[i]);
#endif
                }
            }
            if(match == size) {
                res = true;
            } else {
                res = false;
                if(diff) {
                    *diff = l_diff;
                }
            }
        }
    } else {
        res = true;
    }
    return res;
}

bool array_is_equal(const uint8_t* const array1, const uint8_t* const array2, uint32_t size) {
#ifdef HAS_LOG
    LOG_DEBUG(ARRAY, "%s():", __FUNCTION__);
#endif
    bool res = false;
    uint32_t diff = 0;
    res = array_is_equal_ext(array1, array2, size, &diff);
    return res;
}

#ifdef HAS_ARRAY_EXT
bool array_shift_right(uint8_t* arr, uint32_t size, uint32_t shift) {
    LOG_DEBUG(ARRAY, "%s(): Shift:%u", __FUNCTION__, shift);
    bool res = false;
    if(arr) {
        if(size) {
            if((shift < size) && (0 < shift)) {
                LOG_DEBUG(ARRAY, "ShiftNumbers:%u");
                uint32_t i = 0;
                for(i = (size - shift); shift <= i; i--) {
                    LOG_DEBUG(ARRAY, "a[%u]=a[%u]", i, i - shift);
                    arr[i] = arr[i - shift];
                }
                memset(arr, 0, shift);
                res = true;
            } else if(size <= shift) {
                memset(arr, 0, size);
                res = true;
            } else {
                res = true;
            }
        }
    }
    return res;
}
// 1 2 3 4 5 6 7; 1
// 0 1 2 3 4 5 6
bool array_s16_shift_right(int16_t* const arr, uint32_t size, uint32_t shift) {
    LOG_DEBUG(ARRAY, "%s(): Shift:%u", __FUNCTION__, shift);
    bool res = false;
    if(arr) {
        if(size) {
            if(shift < size) {
                LOG_DEBUG(ARRAY, "ShiftNumbers:%u");
                uint32_t i = 0;
                for(i = (size - shift); shift <= i; i--) {
                    LOG_DEBUG(ARRAY, "a[%u]=a[%u]", i, i - shift);
                    arr[i] = arr[i - shift];
                }
                memset(arr, 0, shift);
                res = true;
            } else if(size <= shift) {
                memset(arr, 0, size);
                res = true;
            } else {
                res = true;
            }
        }
    }
    return res;
}

#endif

#ifdef HAS_ARRAY_EXT
bool array_add_front(uint8_t* arr, uint32_t size, uint8_t* prefix, uint32_t prefix_size) {
    LOG_DEBUG(ARRAY, "%s():", __FUNCTION__);
    bool res = false;
    if(prefix_size < size) {
        res = array_shift_right(arr, size, prefix_size);
        if(res) {
            memcpy(arr, prefix, prefix_size);
            res = true;
        }
    }
    return res;
}

bool array_s16_add_front(int16_t* const arr, uint32_t size, int16_t value) {
    bool res = false;
    if(arr) {
        if(size) {
            res = array_s16_shift_right(arr, size, 1); // -->
            if(res) {
                arr[0] = value;
            }
        }
    }
    return res;
}
#endif

#ifdef HAS_ARRAY_EXT
bool uniq_array(const uint8_t* const addr, uint32_t len) {
    bool res = false;
    uint16_t cnt = 0;
    if(addr && (0 < len)) {
        uint32_t i = 0;
        for(i = 0; i < len; i++) {
            if(0 == addr[i]) {
                cnt++;
            }
        }
        if(cnt < len) {
            res = true;
        }
    }
    return res;
}
#endif

#ifdef HAS_ARRAY_EXT
/*
 all elements equal - true
 not all elements equal - false
 * 11111111111- true*/
/*33333333333- true*/
/*13114116111- fasle*/
bool array_is_same(const uint8_t* const addr, uint32_t len) {
    bool res = false;
    if(addr && (0 < len)) {
        res = true;
        uint32_t i = 0;
        for(i = 0; i < len; i++) {
            if(addr[0] != addr[i]) {
                res = false;
                break;
            }
        }
    }
    return res;
}
#endif

#ifdef HAS_ARRAY_EXT
uint32_t array_double_max_index(const double* const arr, uint32_t size) {
    uint32_t i = 0;
    uint32_t max_i = 0;
    double cur_max = -DBL_MAX;
    for(i = 0; i < size; i++) {
        if(cur_max < arr[i]) {
            max_i = i;
            cur_max = arr[i];
        }
    }
    return max_i;
}
#endif

bool array_reverse_float(float* const in_out_array, uint32_t len) {
    bool res = false;
    if(in_out_array && (0 < len)) {
        res = true;
        uint32_t i = 0;
        for(i = 0; i < len / 2; i++) {
            res = swap_f(&in_out_array[i], &in_out_array[len - i - 1]) && res;
        }
    }

    return res;
}

bool array_reverse_bytes(uint8_t* const in_out_array, uint32_t len) {
    bool res = false;
    if(in_out_array && (0 < len)) {
        res = true;
        uint32_t i = 0;
        for(i = 0; i < len / 2; i++) {
            res = swap8(&in_out_array[i], &in_out_array[len - i - 1]) && res;
        }
    }

    return res;
}

bool array_u16_item_reverse_bytes(uint16_t* const in_out_array, uint32_t size) {
    bool res = false;
    if(in_out_array) {
        if(size) {
            uint32_t i = 0;
            for(i = 0; i < size; i++) {
                uint16_t word = in_out_array[i];
                in_out_array[i] = reverse_byte_order_uint16(word);
                res = true;
            }
        }
    }
    return res;
}

bool array_u32_item_reverse_bytes(uint32_t* const in_out_array, uint32_t size) {
    bool res = false;
    if(in_out_array) {
        if(size) {
            uint32_t i = 0;
            for(i = 0; i < size; i++) {
                uint32_t qword = in_out_array[i];
                in_out_array[i] = reverse_byte_order_uint32(qword);
                res = true;
            }
        }
    }
    return res;
}

bool array_max_double(double const* const data, uint32_t size, uint32_t* const index, double* const max_val) {
    bool res = false;
    if(data) {
        if(size) {
            if(max_val) {
                if(index) {
                    res = true;
                }
            }
        }
    }

    if(res) {
        res = false;
        double cur_max_val = data[0];
        uint32_t index_of_max = 0;
        uint32_t i = 0;
        for(i = 0; i < size; i++) {
            if(cur_max_val < data[i]) {
                cur_max_val = data[i];
                index_of_max = i;
                res = true;
            }
        }

        *max_val = cur_max_val;
        *index = index_of_max;
    }
    return res;
}

#ifdef HAS_ARRAY_EXT
static int compare_u8(const void* a, const void* b) {
    uint8_t data1 = *(uint8_t*)a;
    uint8_t data2 = *(uint8_t*)b;
    int ret = 0;

    if(data1 < data2) // a < b
        ret = -1;
    else if(data1 == data2) // a == b
        ret = 0;
    else
        ret = 1; // a > b

    return ret;
}

bool array_u8_sort(uint8_t* const arr, uint32_t size) {
    bool res = false;
    if(arr) {
        if(size) {
            res = true;
            qsort(arr, size, 1, compare_u8);
        }
    }
    return res;
}
#endif

bool array_u8_insert_first(uint8_t* const data, uint32_t size, uint8_t value) {
    bool res = false;
    if(data) {
        if(size) {
            uint32_t i = 0;
            for(i = (size - 1); 0 < i; i--) {
                data[i + 1] = data[i];
            }
            data[1] = data[0];
            data[0] = value;
            res = true;
        }
    }
    return res;
}

#warning TODO Test array_u8_shift_left
bool array_u8_shift_left(uint8_t* const data, uint32_t size, uint32_t cnt) {
    bool res = false;
#ifdef HAS_LOG
    LOG_DEBUG(ARRAY, "Shift Left,Size:%u,Pos:%u", size, cnt);
#endif
    if(data) {
        if(0 < size) {
            if(0 < cnt) {
                if(cnt < size) {
                    uint32_t i = 0;
                    for(i = 0; i < size; i++) {
                        if((i + cnt) < size) {
                            data[i] = data[i + cnt];
                        }
                    }
                    memset(&data[size - cnt], 0, cnt);
                } else {
                    memset(data, 0, size);
                }
                res = true;
            }
        }
    }
    return res;
}

#warning TODO Test array_u8_del_indices
bool array_u8_del_indices(uint8_t* const data, uint32_t size, uint32_t index, uint32_t cnt) {
    bool res = false;
#ifdef HAS_LOG
    LOG_DEBUG(ARRAY, "Del,Index:%u,Size:%u,Cnt:%u", index, size, cnt);
#endif
    if(data) {
        if(0 < size) {
            if(index < size) {
                if(0 < cnt) {
                    uint32_t i = 0;
                    (void)i;
                    if(size == (index + cnt)) {
#ifdef HAS_LOG
                        LOG_DEBUG(ARRAY, "DeleteFromEnd");
#endif
                        for(i = index; i < (index + cnt); i++) {
                            data[i] = 0;
                        }
                    } else if(0 == index) {
#ifdef HAS_LOG
                        LOG_DEBUG(ARRAY, "DeleteFromFront");
#endif
                        res = array_u8_shift_left(data, size, cnt);

                    } else {
#ifdef HAS_LOG
                        LOG_DEBUG(ARRAY, "DeleteFromMiddle");
#endif
                        res = array_u8_shift_left(&data[index], size - index, cnt);
                    }
                }
            }
        }
    }
    return res;
}

bool array_u8_del_index(uint8_t* const data, uint32_t size, uint32_t index) {
    bool res = false;
#ifdef HAS_LOG
    LOG_DEBUG(ARRAY, "Del,Index:%u,Size:%u", index, size);
#endif
    if(data) {
        if(0 < size) {
            if(index < size) {
                if(index < (size - 1)) {
                    uint32_t i = 0;
                    uint32_t remain = size - index - 1;
                    for(i = 0; i < remain; i++) {
                        data[index + i] = data[index + i + 1];
                    }
                }
                data[size - 1] = 0;
                res = true;
            }
        }
    }
    return res;
}

bool array_bit_array_to_hex(const uint8_t* const bit_array, uint32_t bit_array_size, uint8_t* const hex_data,
                            uint32_t size) {
    bool res = false;
    uint8_t byte_cnt = bit_array_size / 8;
    uint8_t bits_rest = bit_array_size % 8;
#ifdef HAS_LOG
    LOG_INFO(ARRAY, "BitArray,Byte:%u Byte,Rest:%u bit", byte_cnt, bits_rest);
#endif
    if(bit_array) {
        if(bit_array_size) {
            if(hex_data) {
                if(byte_cnt < size) {
                    res = true;
                }
            }
        }
    }

    int32_t bit_num = 0;
    if(res) {
        uint32_t byte_num = 0;
        for(byte_num = 0; byte_num < byte_cnt; byte_num++) {
            hex_data[byte_num] = 0;
            for(bit_num = 7; 0 <= bit_num; bit_num--) {
                if(1 == bit_array[8 * byte_num + 7 - bit_num]) {
                    SET_BIT_NUM(hex_data[byte_num], bit_num);
                } else {
                    RESET_BIT_NUM(hex_data[byte_num], bit_num);
                }
            }
        }

        if(bits_rest) {
            for(bit_num = 0; bit_num < bits_rest; bit_num++) {
                if(1 == bit_array[8 * byte_cnt + bit_num]) {
                    SET_BIT_NUM(hex_data[byte_cnt], 7 - bit_num);
                } else {
                    RESET_BIT_NUM(hex_data[byte_cnt], 7 - bit_num);
                }
            }
        }
    }
    return res;
}

bool array_i8_mult(const int8_t* const array1, const int8_t* const array2, int8_t* const mult_array, uint32_t size) {
    bool res = false;
    if(array1) {
        if(array2) {
            if(mult_array) {
                if(size) {
                    res = true;
                }
            }
        }
    }

    if(res) {
        uint32_t i = 0;
        for(i = 0; i < size; i++) {
            mult_array[i] = array1[i] * array2[i];
        }
    }

    return res;
}

bool array_i16_decimation_2(int16_t* const data, uint32_t size) {
    bool res = false;
    if(data) {
        if(size) {
            if(0 == (1 & size)) {
                res = true;
            }
        }
    }

    if(res) {
        res = false;
        uint32_t i = 0;
        for(i = 0; i < (size / 2); i++) {
            data[i] = data[i * 2];
        }

        for(i = 0; i < (size / 2); i++) {
            data[size / 2 + i] = 0;
        }
    }
    return res;
}

uint32_t inc_index(uint32_t cur, uint32_t max, bool* const overflow) {
    cur++;
    if(cur < max) {
        // *overflow = false ;
    } else {
        cur = 0;
        *overflow = true;
    }
    return cur;
}

int32_t array_i8_mult_sum(const int8_t* const array1, const int8_t* array2, uint32_t size) {
    int32_t mult_sum = 0;
    bool res = false;
    if(array1) {
        if(array2) {
            if(size) {
                res = true;
            }
        }
    }

    if(res) {
        uint32_t i = 0;
        for(i = 0; i < size; i++) {
            mult_sum += array1[i] * array2[i];
        }
    }
    return mult_sum;
}

bool array_s8_add_front_zeros(int8_t* const data, uint32_t size, int32_t offset) {
    bool res = false;
    if(data) {
        if(size) {
            if(offset) {
                uint32_t i = 0;
                for(i = (size - 1); offset <= i; i--) {
                    data[i] = data[i - offset];
                }
                for(i = 0; i < offset; i++) {
                    data[i] = 0;
                }
                res = true;
            } else {
                res = true;
            }
        }
    }
    return res;
}

bool array_s16_add_front_zeros(int16_t* const data, uint32_t size, int32_t offset) {
    bool res = false;
    if(data) {
        if(size) {
            if(offset) {
                // LOG_INFO(ARRAY, "16bit,offset:%u,size:%u", offset,size);
                uint32_t i = 0;
                // uint32_t move_cnt = size - offset;
                // LOG_INFO(ARRAY, "move_cnt:%u", move_cnt);
                for(i = (size - 1); offset <= i; i--) {
                    data[i] = data[i - offset];
                }
                for(i = 0; i < offset; i++) {
                    data[i] = 0;
                }
                res = true;
            } else {
                res = true;
            }
        }
    }
    return res;
}

bool array_s32_add_front_zeros(int32_t* const data, uint32_t size, int32_t offset) {
    bool res = false;
    if(data) {
        if(size) {
            if(offset) {
                uint32_t i = 0;

                for(i = (size - 1); offset <= i; i--) {
                    data[i] = data[i - offset];
                }
                for(i = 0; i < offset; i++) {
                    data[i] = 0;
                }
                res = true;
            } else {
                res = true;
            }
        }
    }
    return res;
}
