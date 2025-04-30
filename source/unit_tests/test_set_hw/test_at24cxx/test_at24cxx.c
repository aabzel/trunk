#include "test_at24cxx.h"

#include "array.h"
#include "at24cxx_drv.h"
#include "at24cxx_read_drv.h"
#include "at24cxx_write_drv.h"
#include "debug_info.h"
#include "log.h"
#include "unit_test_check.h"

static bool test_at24cxx_write_byte_one(uint8_t num, uint16_t address, uint8_t patt) {
    LOG_INFO(TEST, "%s() WriteRead Addr 0x%04x, Pattern:0x%x", __FUNCTION__, address, patt);

    uint8_t data_byte = 0;
    ASSERT_TRUE(at24cxx_write_byte(num, address, patt));
    data_byte = 0;
    ASSERT_TRUE(at24cxx_read_byte(num, address, &data_byte));

    LOG_INFO(TEST, "DataRead 0x%x", data_byte);
    ASSERT_EQ(data_byte, patt);

    return true;
}

static bool test_at24cxx_address(uint8_t num, uint16_t address) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    uint8_t orig_data = 0;
    ASSERT_TRUE(at24cxx_read_byte(num, address, &orig_data));

    ASSERT_TRUE(test_at24cxx_write_byte_one(num, address, 0x55));
    ASSERT_TRUE(test_at24cxx_write_byte_one(num, address, 0xAA));

    ASSERT_TRUE(at24cxx_write_byte(num, address, orig_data));
    return res;
}

bool test_at24cxx_connect(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    ASSERT_TRUE(at24cxx_is_connected(AT24C02_TEST_INSTANCE));
    return res;
}

bool test_at24cxx_read(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    uint8_t data[128];
    ASSERT_TRUE(at24cxx_read(AT24C02_TEST_INSTANCE, 0, data, 128));
    print_hex(data, 128);
    return res;
}

bool test_at24cxx_read_null(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    ASSERT_FALSE(at24cxx_read(AT24C02_TEST_INSTANCE, 0, NULL, 12));
    return res;
}

bool test_at24cxx_read0(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    uint8_t data[128];
    ASSERT_FALSE(at24cxx_read(AT24C02_TEST_INSTANCE, 0, data, 0));
    return res;
}

#define TEST_RW_LEN 2
static bool test_at24cxx_write2_one(uint8_t patt) {
    LOG_INFO(TEST, "%s() WriteRead Pattern:0x%x", __FUNCTION__, patt);
    uint8_t data_backup[TEST_RW_LEN];

    uint8_t data_write[TEST_RW_LEN];
    uint8_t data_read[TEST_RW_LEN];

    memset(data_backup, 0, sizeof(data_backup));
    ASSERT_TRUE(at24cxx_read(AT24C02_TEST_INSTANCE, 0, data_backup, TEST_RW_LEN));

    ASSERT_TRUE(at24cxx_write_ctrl(AT24C02_TEST_INSTANCE, true));
    ASSERT_TRUE(at24cxx_erase(AT24C02_TEST_INSTANCE, 0, TEST_RW_LEN));

    ASSERT_TRUE(array_pat_set(data_write, TEST_RW_LEN, patt));

    ASSERT_TRUE(at24cxx_write(AT24C02_TEST_INSTANCE, 0, data_write, TEST_RW_LEN));

    memset(data_read, 0, sizeof(data_read));
    ASSERT_TRUE(at24cxx_read(AT24C02_TEST_INSTANCE, 0, data_read, TEST_RW_LEN));

    LOG_INFO(TEST, "DataWrite");

    print_mem(data_write, TEST_RW_LEN, true, false, true, true);

    LOG_INFO(TEST, "DataRead");
    print_mem(data_read, TEST_RW_LEN, true, false, true, true);

    ASSERT_TRUE(array_is_equal(data_write, data_read, TEST_RW_LEN));
    LOG_INFO(TEST, "DataMatch!");

    ASSERT_TRUE(at24cxx_write(AT24C02_TEST_INSTANCE, 0, data_backup, TEST_RW_LEN));
    return true;
}

static bool test_at24cxx_write_one(uint8_t patt) {
    LOG_INFO(TEST, "%s() WriteRead Pattern:0x%x", __FUNCTION__, patt);
    uint8_t data_backup[AT24CXX_PAGE_BUFFER_SIZE + 3];

    uint8_t data_write[AT24CXX_PAGE_BUFFER_SIZE + 3];
    uint8_t data_read[AT24CXX_PAGE_BUFFER_SIZE + 3];

    memset(data_backup, 0, sizeof(data_backup));
    ASSERT_TRUE(at24cxx_read(AT24C02_TEST_INSTANCE, 0, data_backup, AT24CXX_PAGE_BUFFER_SIZE));

    ASSERT_TRUE(at24cxx_write_ctrl(AT24C02_TEST_INSTANCE, true));
    ASSERT_TRUE(at24cxx_erase(AT24C02_TEST_INSTANCE, 0, AT24CXX_PAGE_BUFFER_SIZE));

    ASSERT_TRUE(array_pat_set(data_write, AT24CXX_PAGE_BUFFER_SIZE, patt));

    ASSERT_TRUE(at24cxx_write(AT24C02_TEST_INSTANCE, 0, data_write, AT24CXX_PAGE_BUFFER_SIZE));

    memset(data_read, 0, sizeof(data_read));
    ASSERT_TRUE(at24cxx_read(AT24C02_TEST_INSTANCE, 0, data_read, AT24CXX_PAGE_BUFFER_SIZE));

    LOG_INFO(TEST, "DataWrite");

    print_mem(data_write, AT24CXX_PAGE_BUFFER_SIZE, true, false, true, true);

    LOG_INFO(TEST, "DataRead");
    print_mem(data_read, AT24CXX_PAGE_BUFFER_SIZE, true, false, true, true);

    ASSERT_TRUE(array_is_equal(data_write, data_read, AT24CXX_PAGE_BUFFER_SIZE));
    LOG_INFO(TEST, "DataMatch!");

    ASSERT_TRUE(at24cxx_write(AT24C02_TEST_INSTANCE, 0, data_backup, AT24CXX_PAGE_BUFFER_SIZE));
    return true;
}

bool test_at24cxx_write(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);

    log_level_t log_level = log_level_get_set(AT24C, LOG_LEVEL_DEBUG);

    ASSERT_TRUE(test_at24cxx_write_one(0xAA));
    ASSERT_TRUE(test_at24cxx_write_one(0x55));

    log_level_get_set(AT24C, log_level);

    return true;
}

bool test_at24cxx_write2(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);

    log_level_t log_level = log_level_get_set(AT24C, LOG_LEVEL_DEBUG);

    ASSERT_TRUE(test_at24cxx_write2_one(0xAA));
    ASSERT_TRUE(test_at24cxx_write2_one(0x55));

    log_level_get_set(AT24C, log_level);

    return true;
}

bool test_at24cxx_write_inc(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);

    log_level_t log_level = log_level_get_set(AT24C, LOG_LEVEL_DEBUG);

    uint8_t data_backup[AT24CXX_PAGE_BUFFER_SIZE];
    uint8_t data_write[AT24CXX_PAGE_BUFFER_SIZE];
    uint8_t data_read[AT24CXX_PAGE_BUFFER_SIZE];

    memset(data_backup, 0, sizeof(data_backup));
    ASSERT_TRUE(at24cxx_read(AT24C02_TEST_INSTANCE, 0, data_backup, AT24CXX_PAGE_BUFFER_SIZE));
    /*backup ^^^^^^ */

    uint16_t a = 0;
    for(a = 0; a < AT24CXX_PAGE_BUFFER_SIZE; a++) {
        data_write[a] = a;
        ASSERT_TRUE(at24cxx_write_byte(AT24C02_TEST_INSTANCE, a, (uint8_t)a));
    }

    memset(data_read, 0, sizeof(data_backup));
    ASSERT_TRUE(at24cxx_read(AT24C02_TEST_INSTANCE, 0, data_read, AT24CXX_PAGE_BUFFER_SIZE));

    LOG_INFO(TEST, "DataWrite");
    print_mem(data_write, AT24CXX_PAGE_BUFFER_SIZE, true, false, true, true);
    LOG_INFO(TEST, "DataRead");
    print_mem(data_read, AT24CXX_PAGE_BUFFER_SIZE, true, false, true, true);

    ASSERT_TRUE(array_is_equal(data_write, data_read, AT24CXX_PAGE_BUFFER_SIZE));
    LOG_INFO(TEST, "DataMatch!");
    /*restore  vvvvvv*/
    ASSERT_TRUE(at24cxx_write(AT24C02_TEST_INSTANCE, 0, data_backup, AT24CXX_PAGE_BUFFER_SIZE));
    return true;

    log_level_get_set(AT24C, log_level);

    return true;
}

bool test_at24cxx_write0(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    uint32_t data = 0x5500ffff;
    ASSERT_FALSE(at24cxx_write(AT24C02_TEST_INSTANCE, 0, (uint8_t*)&data, 0));
    return true;
}

bool test_at24cxx_write_null(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    ASSERT_FALSE(at24cxx_write(AT24C02_TEST_INSTANCE, 0, NULL, 12));
    return true;
}

#define TEMP_SIZE 128
bool test_at24cxx_errase(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    uint8_t data_backup[TEMP_SIZE + 3] = {0};
    uint8_t data_read[TEMP_SIZE + 4] = {0};

    memset(data_backup, 0, sizeof(data_backup));
    ASSERT_TRUE(at24cxx_read(AT24C02_TEST_INSTANCE, 0, data_backup, TEMP_SIZE));

    memset(data_read, 0x55, sizeof(data_read));

    ASSERT_TRUE(at24cxx_write(AT24C02_TEST_INSTANCE, 0, data_read, TEMP_SIZE));
    memset(data_read, 0, sizeof(data_read));

    ASSERT_TRUE(at24cxx_erase(AT24C02_TEST_INSTANCE, 0, TEMP_SIZE));
    ASSERT_TRUE(at24cxx_read(AT24C02_TEST_INSTANCE, 0, data_read, TEMP_SIZE));

    LOG_INFO(TEST, "DataRead");
    print_mem(data_read, TEMP_SIZE, true, false, true, true);

    ASSERT_TRUE(is_arr_pat(data_read, TEMP_SIZE, 0xff));

    ASSERT_TRUE(at24cxx_write(AT24C02_TEST_INSTANCE, 0, data_backup, TEMP_SIZE));

    return true;
}

#define AT24C02_TEST_ADDR 2
#define AT24C02_PAGE_SIZE 8
bool test_at24cxx_write_page(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    uint8_t page[AT24C02_PAGE_SIZE] = {0};
    uint8_t data_read[AT24C02_PAGE_SIZE] = {0};

    uint8_t data_backup[AT24C02_PAGE_SIZE] = {0};

    memset(data_backup, 0, sizeof(data_backup));
    ASSERT_TRUE(at24cxx_read(AT24C02_TEST_INSTANCE, AT24C02_TEST_ADDR, data_backup, AT24C02_PAGE_SIZE));

    memset(data_read, 0, AT24C02_PAGE_SIZE);

    memset(page, 0x12, AT24C02_PAGE_SIZE);

    ASSERT_TRUE(at24cxx_write_page(AT24C02_TEST_INSTANCE, AT24C02_TEST_ADDR, page));

    ASSERT_TRUE(at24cxx_read(AT24C02_TEST_INSTANCE, AT24C02_TEST_ADDR, data_read, AT24C02_PAGE_SIZE));

    LOG_INFO(TEST, "DataRead");
    print_mem(data_read, 8, true, false, true, true);
    ASSERT_TRUE(is_arr_pat(data_read, AT24C02_PAGE_SIZE, 0x12));

    ASSERT_TRUE(at24cxx_write_page(AT24C02_TEST_INSTANCE, AT24C02_TEST_ADDR, data_backup));

    return true;
}

bool test_at24cxx_write_byte(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    uint16_t addr = 0;
    for(addr = 0; addr < 256; addr++) {
        LOG_INFO(TEST, "Offset %u", addr);
        ASSERT_TRUE(test_at24cxx_address(AT24C02_TEST_INSTANCE, addr));
    }
    return true;
}
