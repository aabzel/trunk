#include "test_fifo_array.h"

#ifdef X86_64
#include <stdio.h>
#endif
#include <stdint.h>
#include <string.h>

#include "data_utils.h"
#include "fifo_array.h"
#include "unit_test_check.h"

const uint8_t exp_arr_4_5[9] = {1, 2, 3, 4, 1, 2, 3, 4, 5};
const uint8_t arr5[5] = {1, 2, 3, 4, 5};
const uint8_t arr4[4] = {1, 2, 3, 4};
const uint8_t arr3[3] = {1, 2, 3};
const uint8_t arr2[2] = {1, 2};

bool test_fifo_array(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    FifoArray_t FiFoArr;
    Array_t NodeHeap[5];
    ASSERT_TRUE(fifo_arr_init(&FiFoArr, &NodeHeap[0], ARRAY_SIZE(NodeHeap)));
    ASSERT_EQ(5, fifo_arr_get_size(&FiFoArr));
    ASSERT_EQ(0, fifo_arr_get_count(&FiFoArr));

    Array_t rdNode;
    Array_t peekNode;
    ASSERT_FALSE(fifo_arr_peek(&FiFoArr, &peekNode));
    ASSERT_FALSE(fifo_arr_pull(&FiFoArr, &rdNode));

    Array_t wrNode;
    wrNode.pArr = (uint8_t*)arr2;
    wrNode.size = 2;
    ASSERT_TRUE(fifo_arr_push(&FiFoArr, wrNode));
    ASSERT_TRUE(fifo_arr_peek(&FiFoArr, &peekNode));
    ASSERT_EQ(2, peekNode.size);

    wrNode.pArr = (uint8_t*)arr3;
    wrNode.size = 3;
    ASSERT_TRUE(fifo_arr_push(&FiFoArr, wrNode));
    ASSERT_TRUE(fifo_arr_peek(&FiFoArr, &peekNode));
    ASSERT_EQ(2, peekNode.size);

    wrNode.pArr = (uint8_t*)arr5;
    wrNode.size = 5;
    ASSERT_TRUE(fifo_arr_push(&FiFoArr, wrNode));
    ASSERT_TRUE(fifo_arr_peek(&FiFoArr, &peekNode));
    ASSERT_EQ(2, peekNode.size);

    ASSERT_EQ(3, fifo_arr_get_count(&FiFoArr));

    ASSERT_TRUE(fifo_arr_pull(&FiFoArr, &rdNode));
    ASSERT_EQ(2, rdNode.size);
    ASSERT_EQ_MEM(arr2, rdNode.pArr, 2);

    ASSERT_TRUE(fifo_arr_peek(&FiFoArr, &peekNode));
    ASSERT_EQ(3, peekNode.size);
    ASSERT_TRUE(fifo_arr_pull(&FiFoArr, &rdNode));
    ASSERT_EQ(3, rdNode.size);
    ASSERT_EQ_MEM(arr3, rdNode.pArr, 3);

    ASSERT_TRUE(fifo_arr_peek(&FiFoArr, &peekNode));
    ASSERT_EQ(5, peekNode.size);
    ASSERT_TRUE(fifo_arr_pull(&FiFoArr, &rdNode));
    ASSERT_EQ(5, rdNode.size);
    ASSERT_EQ_MEM(arr5, rdNode.pArr, 5);

    ASSERT_EQ(0, fifo_arr_get_count(&FiFoArr));

    ASSERT_FALSE(fifo_arr_pull(&FiFoArr, &rdNode));
    return true;
}

bool test_fifo_array_types(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
#ifdef HAS_CLANG
    ASSERT_EQ(16, sizeof(Array_t));
#endif
#ifdef HAS_GCC
    ASSERT_EQ(8, sizeof(Array_t));
#endif
    return true;
}

bool test_fifo_array_packing(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    uint8_t buf[10];

    FifoArray_t FiFoArr;
    Array_t NodeHeap[40] = {0};
    ASSERT_TRUE(fifo_arr_init(&FiFoArr, &NodeHeap[0], ARRAY_SIZE(NodeHeap)));

    Array_t wrNode;
    wrNode.pArr = (uint8_t*)arr4;
    wrNode.size = 4;
    ASSERT_TRUE(fifo_arr_push(&FiFoArr, wrNode));
    wrNode.pArr = (uint8_t*)arr5;
    wrNode.size = 5;
    ASSERT_TRUE(fifo_arr_push(&FiFoArr, wrNode));
    uint32_t buff_len = 0;
    ASSERT_TRUE(fifo_arr_pack_frame(buf, sizeof(buf), &FiFoArr, &buff_len));
    ASSERT_EQ(9, buff_len);
    ASSERT_EQ_MEM(exp_arr_4_5, buf, 9);
    return true;
}
