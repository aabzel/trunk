#include "test_flash.h"

#include <stdbool.h>
#include <stdint.h>
#ifdef CC26XX
#include <flash.h>
#include <vims.h>
#endif
#include <string.h>

#include "data_utils.h"
#include "flash_mcal.h"
//#include "flash_fs.h"
#include "log.h"
#include "log_utils.h"
#include "unit_test_check.h"

/*
tsr flash_write
*/
#define BLOCK_SIZE 129U

#ifdef HAS_TEST_FLASH_WRITE
bool test_flash_write(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    uint32_t spare_page = flash_get_first_spare_page();
    EXPECT_NE(0xFFFFFFFF, spare_page);
    LOG_INFO(LG_FLASH, "0x%08x", spare_page);
    // spare_page = FlashConfig.sector_for_test;
    ASSERT_TRUE(is_flash_spare(spare_page, FlashConfig.sector_size));

    // EXPECT_FALSE(is_flash_fs_addr(spare_page));

    ASSERT_TRUE(flash_erase_sector(spare_page));
    ASSERT_TRUE(is_flash_spare(spare_page, FlashConfig.sector_size));

    uint8_t DataRead[BLOCK_SIZE] = {0};
    memset(DataRead, 0x00, sizeof(DataRead));

    uint8_t DataWrite[BLOCK_SIZE] = {0};
    memset(DataWrite, 0x55, sizeof(DataWrite));

    ASSERT_TRUE(flash_wr(spare_page, DataWrite, BLOCK_SIZE));

    ASSERT_TRUE(flash_read_(spare_page, DataRead, BLOCK_SIZE));
    memcpy(DataRead, (uint8_t*)spare_page, sizeof(DataRead));

    EXPECT_EQ_MEM(DataRead, DataWrite, BLOCK_SIZE);

    ASSERT_TRUE(flash_erase_sector(spare_page));
    ASSERT_TRUE(is_flash_spare(spare_page, FlashConfig.sector_size));

    return res;
}
#endif

bool test_flash_legal_change(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;

    ASSERT_FALSE(flash_is_legal_change(0x00, 0x11));
    ASSERT_FALSE(flash_is_legal_change(0xaa, 0xff));
    ASSERT_TRUE(flash_is_legal_change(0x55, 0x00));
    ASSERT_TRUE(flash_is_legal_change(0x00, 0x00));
    ASSERT_TRUE(flash_is_legal_change(0x55, 0x55));
    ASSERT_TRUE(flash_is_legal_change(0xFF, 0xFF));

    return res;
}
