#include "test_mx25r6435f.h"

#include "debug_info.h"
#include "mx25r6435f_drv.h"
#include "unit_test_check.h"

bool test_mx25r6435f_types(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    ASSERT_EQ(3, sizeof(RegIdentification_t));
    ASSERT_EQ(3, sizeof(Mx25Addr_t));
    ASSERT_EQ(1, sizeof(Mx25BlockSize_t));

    return res;
}

bool test_mx25r6435f_form_addr(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    uint8_t buff[3] = {0xFF, 0xFF, 0xFF};
    ASSERT_TRUE(pack_24bit_big_endian(0x00654321, buff));
    ASSERT_EQ(0x65, buff[0]);
    ASSERT_EQ(0x43, buff[1]);
    ASSERT_EQ(0x21, buff[2]);
    return res;
}

bool test_mx25r6435f_read(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    uint8_t data[128];
    ASSERT_TRUE(mx25r6435f_read(0, data, 128));
    print_hex(data, 128);
    return res;
}

static bool test_mx25r6435f_write_one(uint32_t address, uint8_t patt) {
    LOG_INFO(TEST, "%s() Addr: 0x%x Pattern:0x%x", __FUNCTION__, address, patt);
    uint8_t data_write[MX25R6435F_PAGE_SIZE];
    uint8_t data_read[MX25R6435F_PAGE_SIZE];

    ASSERT_TRUE(mx25r6435f_write_enable(true));

    ASSERT_TRUE(mx25r6435f_erase_sector(address));
    ASSERT_TRUE(mx25r6435f_write_enable(true));
    ASSERT_TRUE(array_pat_set(data_write, MX25R6435F_PAGE_SIZE, patt));

    ASSERT_TRUE(mx25r6435f_page_program(address, data_write, MX25R6435F_PAGE_SIZE));
    LOG_INFO(TEST, "WriteOk!");

    memset(data_read, 0, sizeof(data_read));
    ASSERT_TRUE(mx25r6435f_read(address, data_read, MX25R6435F_PAGE_SIZE));

    ASSERT_TRUE(array_is_equal(data_write, data_read, MX25R6435F_PAGE_SIZE));
    LOG_INFO(TEST, "DataMatch!");
    return true;
}

bool test_mx25r6435f_write(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);

    ASSERT_TRUE(test_mx25r6435f_write_one(0, 0xAA));
    ASSERT_TRUE(test_mx25r6435f_write_one(0, 0x55));

    ASSERT_TRUE(test_mx25r6435f_write_one(1280, 0xAA));
    ASSERT_TRUE(test_mx25r6435f_write_one(1280, 0x55));

    return true;
}
