#include "byte_utils_test.h"

#include "byte_utils.h"
#include "data_utils.h"
#include "log.h"
#include "unit_test_check.h"

const uint8_t ExpAarray3[] = {0x33, 0x22, 0x11};
const uint8_t ExpAarray4[] = {0x44, 0x33, 0x22, 0x11};

bool test_array_reverse(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    uint8_t array3[3] = {0x11, 0x22, 0x33};
    ASSERT_TRUE(reverse_byte_order_array(array3, sizeof(array3)));
    EXPECT_EQ_MEM(array3, ExpAarray3, 3);

    uint8_t array4[4] = {0x11, 0x22, 0x33, 0x44};
    ASSERT_TRUE(reverse_byte_order_array(array4, sizeof(array4)));
    EXPECT_EQ_MEM(array4, ExpAarray4, 4);
    return res;
}

bool test_reverse_byte_order64(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_EQ(0x8877665544332211, reverse_byte_order_uint64(0x1122334455667788));
    ASSERT_EQ(0x0123456789abcdef, reverse_byte_order_uint64(0xefcdab8967452301));
    return true;
}

static bool test_reverse_byte_order32(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_EQ(0x44332211, reverse_byte_order_uint32(0x11223344));
    return true;
}

static bool test_reverse_byte_order24(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_EQ(0x00443322, reverse_byte_order_uint24(0x00223344));
    ASSERT_EQ(0x00112233, reverse_byte_order_uint24(0x00332211));

    uint32_t val24bit = 0x00112233;
    uint32_t val24bit_be = 0;
    uint8_t buff1[3] = {0};
    uint8_t buff2[3] = {0};
    buff1[0] = (val24bit >> 16) & 0xFF;
    buff1[1] = (val24bit >> 8) & 0xFF;
    buff1[2] = (val24bit & 0xFF);

    val24bit_be = reverse_byte_order_uint24(val24bit);
    ASSERT_EQ(0x00332211, val24bit_be);
    val24bit_be = val24bit_be;
    memcpy(buff2, &val24bit_be, 3);
    ASSERT_EQ(0, memcmp(buff1, buff2, 3));

    return true;
}

static bool test_reverse_byte_order16(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_EQ(0x2211, reverse_byte_order_uint16(0x1122));
    return true;
}

bool test_byte_reverse(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE(test_reverse_byte_order32());
    ASSERT_TRUE(test_reverse_byte_order24());
    ASSERT_TRUE(test_reverse_byte_order16());
    return true;
}

bool test_byte_type_sizes(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_EQ(1, sizeof(Type8Union_t));
    ASSERT_EQ(2, sizeof(Type16Union_t));
    ASSERT_EQ(4, sizeof(Type32Union_t));
    ASSERT_EQ(8, sizeof(Type64Union_t));
    return true;
}
/*
tsr copy_rev+
*/
bool test_byte_copy_rev(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    uint8_t array[8] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
    ASSERT_EQ(0x1122, copy_and_rev16(array));
    ASSERT_EQ(0x11223344, copy_and_rev32(array));
    ASSERT_EQ_U64(0x1122334455667788, copy_and_rev64(array));
    return true;
}
