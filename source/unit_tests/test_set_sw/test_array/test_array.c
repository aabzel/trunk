#include "test_array.h"

#include "array.h"
#include "log.h"
#include "unit_test_check.h"

const uint8_t array1[] = {0, 0, 0, 2, 3, 4};

bool test_array_index(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_EQ(1, array_index_next(0, 10));
    ASSERT_EQ(1, array_index_next(0, 2));
    ASSERT_EQ(0, array_index_next(1, 2));
    ASSERT_EQ(0, array_index_next(9, 10));
    ASSERT_EQ(0, array_index_next(100, 10));

    ASSERT_EQ(9, array_index_prev(0, 10));
    ASSERT_EQ(8, array_index_prev(9, 10));
    ASSERT_EQ(9, array_index_prev(100, 10));

    return true;
}

bool test_array_con_pat(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    uint32_t max_cont_patt = 0;
    ASSERT_TRUE(array_max_cont((uint8_t*)array1, sizeof(array1), 0, &max_cont_patt));
    ASSERT_EQ(3, max_cont_patt);
    return true;
}

static const uint8_t exp_array[] = {1, 2, 3, 4, 5, 6, 7, 8};
bool test_array_add_front(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    uint8_t array[10] = {4, 5, 6, 7, 8};
    uint8_t prefix[3] = {1, 2, 3};
    ASSERT_TRUE(array_add_front(array, sizeof(array), prefix, sizeof(prefix)));
    ASSERT_TRUE(array_is_equal(exp_array, array, 8));
    return true;
}

static const uint8_t exp_array3[] = {3, 4, 5, 6, 7, 8};
static const uint8_t exp_array23[] = {2, 3, 4, 5, 6, 7, 8};
bool test_array_insert_first(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    uint8_t array[10] = {4, 5, 6, 7, 8};
    ASSERT_TRUE(array_u8_insert_first(array, sizeof(array), 3));
    ASSERT_TRUE(array_is_equal(exp_array3, array, 6));

    ASSERT_TRUE(array_u8_insert_first(array, sizeof(array), 2));
    ASSERT_TRUE(array_is_equal(exp_array23, array, 7));
    return true;
}

static const uint8_t exp_shifted_array[10] = {0, 0, 0, 4, 5, 6, 7, 8};
static const uint8_t exp_shifted_array2[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static const uint8_t init_array[10] = {4, 5, 6, 7, 8};
bool test_array_shift_right(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);

    set_log_level(SYS, LOG_LEVEL_DEBUG);
    uint8_t array[10] = {4, 5, 6, 7, 8};
    memset(array, 0, sizeof(array));

    memcpy(array, init_array, 5);

    ASSERT_TRUE(array_shift_right(array, sizeof(array), 3));
    ASSERT_TRUE(array_is_equal(exp_shifted_array, array, 8));

    memset(array, 0, sizeof(array));
    memcpy(array, init_array, 5);
    ASSERT_TRUE(array_shift_right(array, sizeof(array), sizeof(array)));
    ASSERT_TRUE(array_is_equal(exp_shifted_array2, array, 10));

    memset(array, 0, sizeof(array));
    memcpy(array, init_array, 5);
    ASSERT_TRUE(array_shift_right(array, sizeof(array), sizeof(array) * 20));
    ASSERT_TRUE(array_is_equal(exp_shifted_array2, array, 10));

    memset(array, 0, sizeof(array));
    memcpy(array, init_array, 5);
    ASSERT_TRUE(array_shift_right(array, sizeof(array), 0));
    ASSERT_TRUE(array_is_equal(init_array, array, 10));

    LOG_INFO(TEST, "%s(): Ok", __FUNCTION__);
    set_log_level(SYS, LOG_LEVEL_INFO);
    return true;
}

static const uint8_t bit_array1[] = {1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0};

static const uint8_t bit_array2[] = {1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1};

bool test_array_bit_to_hex(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(SYS, LOG_LEVEL_DEBUG);

    uint8_t hex_data[5] = {0};
    ASSERT_TRUE(array_bit_array_to_hex(bit_array2, sizeof(bit_array2), hex_data, sizeof(hex_data)));
    ASSERT_EQ(0xE4, hex_data[0]);
    ASSERT_EQ(0x38, hex_data[1]);
    ASSERT_EQ(0x50, hex_data[2]);

    ASSERT_TRUE(array_bit_array_to_hex(bit_array1, sizeof(bit_array1), hex_data, sizeof(hex_data)));
    ASSERT_EQ(0xE4, hex_data[0]);
    ASSERT_EQ(0x38, hex_data[1]);

    LOG_INFO(TEST, "%s(): Ok", __FUNCTION__);
    set_log_level(SYS, LOG_LEVEL_INFO);
    return true;
}

bool test_array_i8_mult(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(SYS, LOG_LEVEL_DEBUG);

    int8_t TestArray1[4] = {-1, 1, -1, 1};
    int8_t array2[4] = {-1, -1, 1, 1};
    int8_t mult_arr[4] = {0};
    ASSERT_TRUE(array_i8_mult(TestArray1, array2, mult_arr, 4));

    ASSERT_EQ(1, mult_arr[0]);
    ASSERT_EQ(-1, mult_arr[1]);
    ASSERT_EQ(-1, mult_arr[2]);
    ASSERT_EQ(1, mult_arr[3]);

    LOG_INFO(TEST, "%s(): Ok", __FUNCTION__);
    set_log_level(SYS, LOG_LEVEL_INFO);
    return true;
}

bool test_array_i8_mult_sum(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(SYS, LOG_LEVEL_DEBUG);

    int8_t TestArray1[4] = {-1, 1, -1, 1};
    int8_t array2[4] = {-1, -1, 1, 1};
    ASSERT_EQ(0, array_i8_mult_sum(TestArray1, array2, 4));

    int8_t array11[4] = {1, 1, 1, 1};
    int8_t array22[4] = {2, 2, 2, 2};
    ASSERT_EQ(8, array_i8_mult_sum(array11, array22, 4));

    LOG_INFO(TEST, "%s(): Ok", __FUNCTION__);
    set_log_level(SYS, LOG_LEVEL_INFO);
    return true;
}
