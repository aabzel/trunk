#include "test_eeprom.h"

#include <string.h>

#include "data_utils.h"
#include "eeprom_mcal.h"
#include "log.h"
#include "microcontroller_const.h"
#include "std_includes.h"
#include "unit_test_check.h"

#define EEPROM_TEST_BLOCK_SIZE 73U

static bool test_eeprom_byte_write_one_val(const uint32_t phy_addr, uint8_t byte_write) {
    bool res = true;
    LOG_INFO(TEST, "%s() Addr:0x%x,dWord:0x%02x", __FUNCTION__, phy_addr, byte_write);
    uint8_t byte_read = 0;
    ASSERT_TRUE(eeprom_byte_write(phy_addr, byte_write));
    ASSERT_TRUE(eeprom_byte_read(phy_addr, &byte_read));

    LOG_INFO(TEST, "Addr:0x%08x,ReadByte:0x%08x", phy_addr, byte_write);
    ASSERT_EQ(byte_write, byte_read);
    return res;
}

static bool test_eeprom_write_dword_one_val(const uint32_t phy_addr, uint32_t dword_write) {
    bool res = true;
    LOG_INFO(TEST, "%s() Addr:0x%x,dWord:0x%08x", __FUNCTION__, phy_addr, dword_write);
    uint32_t dword_read = 0;
    ASSERT_TRUE(eeprom_dword_erase(phy_addr));

    ASSERT_TRUE(eeprom_dword_write(phy_addr, dword_write));
    ASSERT_TRUE(eeprom_dword_read(phy_addr, &dword_read));

    LOG_INFO(TEST, "Addr:0x%08x,ReadWord:0x%08x", phy_addr, dword_read);
    ASSERT_EQ(dword_write, dword_read);
    return res;
}

static bool test_eeprom_write_dword_one(const uint32_t phy_addr) {
    bool res = true;
    LOG_INFO(TEST, "%s() Addr:0x%08x", __FUNCTION__, phy_addr);

    ASSERT_TRUE(test_eeprom_write_dword_one_val(phy_addr, 0xAAAAAAAA));
    ASSERT_TRUE(test_eeprom_write_dword_one_val(phy_addr, 0x55555555));
    return res;
}

static bool test_eeprom_byte_write_one(const uint32_t phy_addr) {
    bool res = true;
    LOG_INFO(TEST, "%s() Addr:0x%08x", __FUNCTION__, phy_addr);

    ASSERT_TRUE(test_eeprom_byte_write_one_val(phy_addr, 0xAA));
    ASSERT_TRUE(test_eeprom_byte_write_one_val(phy_addr, 0x55));
    return res;
}

bool test_eeprom_write_dword(void) {
    bool res = true;
    LOG_INFO(TEST, "%s()", __FUNCTION__);

    log_level_get_set(EEPROM, LOG_LEVEL_DEBUG);

    ASSERT_TRUE(test_eeprom_write_dword_one(ROM_START + 3 * 1024));
    ASSERT_TRUE(test_eeprom_write_dword_one(ROM_START + 4 * 1024));

    log_level_get_set(EEPROM, LOG_LEVEL_INFO);
    return res;
}

bool test_eeprom_byte_write(void) {
    bool res = true;
    LOG_INFO(TEST, "%s()", __FUNCTION__);

    log_level_get_set(EEPROM, LOG_LEVEL_DEBUG);

    ASSERT_TRUE(test_eeprom_byte_write_one(ROM_START + 3 * 1024 + 5));
    ASSERT_TRUE(test_eeprom_byte_write_one(ROM_START + 4 * 1024 + 6));

    log_level_get_set(EEPROM, LOG_LEVEL_INFO);
    return res;
}

/*
 tsr eeprom_read
 */
bool test_eeprom_read(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    log_level_get_set(EEPROM, LOG_LEVEL_DEBUG);

    uint8_t DataRead[EEPROM_TEST_BLOCK_SIZE] = {0};
    memset(DataRead, 0x00, sizeof(DataRead));
    ASSERT_TRUE(eeprom_mcal_read(ROM_START, DataRead, EEPROM_TEST_BLOCK_SIZE));
    log_level_get_set(EEPROM, LOG_LEVEL_INFO);
    return res;
}

bool test_eeprom_erase(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    log_level_get_set(EEPROM, LOG_LEVEL_DEBUG);

    LOG_INFO(EEPROM, "0x%08x", ROM_START);
    ASSERT_TRUE(eeprom_mcal_erase(ROM_START, EEPROM_TEST_BLOCK_SIZE));
    ASSERT_TRUE(is_eeprom_spare(ROM_START, EEPROM_TEST_BLOCK_SIZE));

    log_level_get_set(EEPROM, LOG_LEVEL_INFO);
    return res;
}

bool test_eeprom_write(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    log_level_get_set(EEPROM, LOG_LEVEL_DEBUG);

    uint8_t DataRead[EEPROM_TEST_BLOCK_SIZE] = {0};
    memset(DataRead, 0x00, sizeof(DataRead));

    uint8_t DataWrite[EEPROM_TEST_BLOCK_SIZE] = {0};
    memset(DataWrite, 0x55, sizeof(DataWrite));

    ASSERT_TRUE(eeprom_mcal_write(ROM_START, DataWrite, EEPROM_TEST_BLOCK_SIZE));

    ASSERT_TRUE(eeprom_mcal_read(ROM_START, DataRead, EEPROM_TEST_BLOCK_SIZE));
    // memcpy(DataRead, (uint8_t*)addr_spare_piece, sizeof(DataRead));

    EXPECT_EQ_MEM(DataRead, DataWrite, EEPROM_TEST_BLOCK_SIZE);

    log_level_get_set(EEPROM, LOG_LEVEL_INFO);

    return res;
}

#ifdef HAS_TEST_EEPROM_WRITE
/*
tsr eeprom_write
*/
bool test_eeprom_write_safe(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    log_level_get_set(EEPROM, LOG_LEVEL_DEBUG);
    uint32_t addr_spare_piece = 0xFFFFFFFF;
    ASSERT_TRUE(eeprom_get_first_addr_spare_piece(EEPROM_TEST_BLOCK_SIZE, &addr_spare_piece));

    EXPECT_NE(0xFFFFFFFF, addr_spare_piece);
    LOG_INFO(EEPROM, "0x%08x", addr_spare_piece);
    // addr_spare_piece = EepromConfig.sector_for_test;
    ASSERT_TRUE(is_eeprom_spare(addr_spare_piece, EEPROM_TEST_BLOCK_SIZE));

    // EXPECT_FALSE(is_eeprom_fs_addr(addr_spare_piece));

    ASSERT_TRUE(eeprom_mcal_erase(addr_spare_piece, EEPROM_TEST_BLOCK_SIZE));
    ASSERT_TRUE(is_eeprom_spare(addr_spare_piece, EEPROM_TEST_BLOCK_SIZE));

    uint8_t DataRead[EEPROM_TEST_BLOCK_SIZE] = {0};
    memset(DataRead, 0x00, sizeof(DataRead));

    uint8_t DataWrite[EEPROM_TEST_BLOCK_SIZE] = {0};
    memset(DataWrite, 0x55, sizeof(DataWrite));

    ASSERT_TRUE(eeprom_mcal_write(addr_spare_piece, DataWrite, EEPROM_TEST_BLOCK_SIZE));

    ASSERT_TRUE(eeprom_mcal_read(addr_spare_piece, DataRead, EEPROM_TEST_BLOCK_SIZE));
    // memcpy(DataRead, (uint8_t*)addr_spare_piece, sizeof(DataRead));

    EXPECT_EQ_MEM(DataRead, DataWrite, EEPROM_TEST_BLOCK_SIZE);

    ASSERT_TRUE(eeprom_mcal_erase(addr_spare_piece, EEPROM_TEST_BLOCK_SIZE));
    ASSERT_TRUE(is_eeprom_spare(addr_spare_piece, EEPROM_TEST_BLOCK_SIZE));

    log_level_get_set(EEPROM, LOG_LEVEL_INFO);
    return res;
}
#endif
