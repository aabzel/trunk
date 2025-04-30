#include "test_lifo_array.h"

#include <stdint.h>
#include <string.h>

#include "data_utils.h"
#include "lifo_array.h"
#include "lifo_array_diag.h"
#include "log.h"
#include "unit_test_check.h"

bool test_lifo_array(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    Array_t Array[2];
    Array_t node;
    LifoArray_t LifoArray;
    ASSERT_TRUE(lifo_arr_init(&LifoArray, Array, ARRAY_SIZE(Array)));

    char text1[20] = "text1";
    Array_t node1 = {
        .size = strlen(text1),
        .pArr = text1,
    };
    ASSERT_TRUE(lifo_arr_push(&LifoArray, node1));

    ASSERT_TRUE(lifo_arr_peek(&LifoArray, &node));
    ASSERT_STREQ("text1", node.pArr);

    char text2[20] = "text2";
    Array_t node2 = {
        .size = strlen(text2),
        .pArr = text2,
    };
    ASSERT_TRUE(lifo_arr_push(&LifoArray, node2));

    ASSERT_TRUE(lifo_arr_peek(&LifoArray, &node));
    ASSERT_STREQ("text2", node.pArr);

    ASSERT_TRUE(lifo_arr_pull(&LifoArray, &node));
    ASSERT_STREQ("text2", node.pArr);

    ASSERT_TRUE(lifo_arr_pull(&LifoArray, &node));
    ASSERT_STREQ("text1", node.pArr);

    return true;
}

bool test_lifo_array_types(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    return true;
}

bool test_lifo_array_packing(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);

    return true;
}
