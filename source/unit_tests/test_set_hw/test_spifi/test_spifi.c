#include "test_spifi.h"

#include "debug_info.h"
#include "spifi_mcal.h"
#include "unit_test_check.h"


bool test_spifi_types(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    ASSERT_EQ(4, sizeof(SpiFiRegMcmd_t));
    ASSERT_EQ(4, sizeof(SpiFiRegData_t));
    ASSERT_EQ(4, sizeof(SpiFiRegClimit_t));
    ASSERT_EQ(4, sizeof(SpiFiRegIdata_t));
    ASSERT_EQ(4, sizeof(SpiFiRegAddress_t));
    ASSERT_EQ(4, sizeof(SpiFiRegCmd_t));
    ASSERT_EQ(4, sizeof(SpiFiRegStat_t));
    ASSERT_EQ(4, sizeof(SpiFiRegCtrl_t));
    ASSERT_EQ(4, sizeof(SpiFiData_t));
    return res;
}

bool test_spifi_read(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    bool res = true;
    uint8_t data[128]={0};
    ASSERT_TRUE(spifi_read(0,TEST_ADDESS, data, 128));
    print_hex(data, 128);
    return res;
}

static bool test_spifi_write_one(uint32_t address, uint8_t patt) {
    LOG_INFO(TEST, "%s() Addr: 0x%x Pattern:0x%x", __FUNCTION__, address, patt);
    uint8_t data_write[SPIFI_PAGE_SIZE]={0};
    uint8_t data_read[SPIFI_PAGE_SIZE]={0};

    ASSERT_TRUE(spifi_write_ctrl(1,true));

    ASSERT_TRUE(spifi_erase_sector(1,address));
    ASSERT_TRUE(spifi_write_ctrl(1,true));
    ASSERT_TRUE(array_pat_set(data_write, SPIFI_PAGE_SIZE, patt));

    ASSERT_TRUE(spifi_page_program(1,address, data_write, SPIFI_PAGE_SIZE));
    LOG_INFO(TEST, "WriteOk!");

    memset(data_read, 0, sizeof(data_read));
    ASSERT_TRUE(spifi_read(1,address, data_read, SPIFI_PAGE_SIZE));

    ASSERT_TRUE(array_is_equal(data_write, data_read, SPIFI_PAGE_SIZE));
    LOG_INFO(TEST, "DataMatch!");
    return true;
}


bool test_spifi_write(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);

    ASSERT_TRUE(test_spifi_write_one(TEST_ADDESS, 0xAA));
    ASSERT_TRUE(test_spifi_write_one(TEST_ADDESS, 0x55));


    return true;
}
