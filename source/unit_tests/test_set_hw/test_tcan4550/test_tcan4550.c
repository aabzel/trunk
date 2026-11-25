#include "test_tcan4550.h"

#include <string.h>
#include <gpio.h>

#include "TCAN_hl.h"
#include "tcan4550_diag.h"
#include "tcan4550_drv.h"
#include "unit_test_check.h"
#include "tcan4550_reg.h"

bool test_can_detect(void) {
    LOG_INFO(AES, "%s()", __FUNCTION__);
    EXPECT_TRUE( is_tcan4550_connected());
    return true;
}

bool test_can_lock(void){
    LOG_INFO(AES, "%s()", __FUNCTION__);
    tCanRegCCctrl_t ctrl_reg;
    ctrl_reg.word =0;

    EXPECT_TRUE( tcan4550_set_lock(true));
    EXPECT_TRUE( is_tcan4550_protected_reg_locked(&ctrl_reg));
    EXPECT_FALSE(is_tcan4550_protected_reg_unlock(&ctrl_reg));

    EXPECT_TRUE( tcan4550_set_lock(false));
    EXPECT_FALSE( is_tcan4550_protected_reg_locked(&ctrl_reg));
    EXPECT_TRUE(is_tcan4550_protected_reg_unlock(&ctrl_reg));
    return true;
}

static bool test_can_write_one(uint16_t addr, uint32_t write_val) {
    LOG_INFO(AES, "%s()", __FUNCTION__);
    uint32_t read_reg=0;
    EXPECT_TRUE( tcan4550_write_reg(addr, write_val)) ;
    EXPECT_TRUE( tcan4550_read_reg(addr, &read_reg)) ;
    ASSERT_EQ(write_val, read_reg);
    return true;
}



bool test_can_write(void) {
    LOG_INFO(AES, "%s()", __FUNCTION__);
    EXPECT_TRUE(test_can_write_one(ADDR_TEST_REGISTERS,0x55555555));
    EXPECT_TRUE(test_can_write_one(ADDR_TEST_REGISTERS,0xAAAAAAAA));
    EXPECT_TRUE(test_can_write_one(ADDR_TEST_REGISTERS,0x12345678));
    EXPECT_TRUE(test_can_write_one(ADDR_TEST_REGISTERS,0x87654321));
    return true;
}

bool test_can_read_word(void) {
    LOG_INFO(AES, "%s()", __FUNCTION__);
    uint32_t read_dev_id0_4 = 0;
    EXPECT_TRUE( tcan4550_read(ADDR_DEVICE_ID0, 1, (uint8_t *)&read_dev_id0_4, sizeof(read_dev_id0_4)));
    ASSERT_EQ(0x5443414E, read_dev_id0_4);
    return true;
}

bool test_can_types(void) {
    LOG_INFO(AES, "%s()", __FUNCTION__);
    ASSERT_EQ(4, sizeof(tCanRegRev_t));
    ASSERT_EQ(4, sizeof(tCanRegStatus_t));
    ASSERT_EQ(4, sizeof(tCanRegModeOpPinCfg_t));
    ASSERT_EQ(4, sizeof(tCanRegTxBufCfg_t));
    ASSERT_EQ(4, sizeof(tCanRegFiFo0Stat_t));
    ASSERT_EQ(4, sizeof(tCanRegFiFo1Stat_t));
    ASSERT_EQ(4, sizeof(tCanRegTxBufElmSzCfg_t));
    ASSERT_EQ(4, sizeof(tCanRegCCctrl_t));
    ASSERT_EQ(4, sizeof(tCanRegIntEn_t));
    ASSERT_EQ(4, sizeof(tCanRegBitTime_t));
    ASSERT_EQ(4, sizeof(tCanRegDataBitTime_t));
    ASSERT_EQ(4, sizeof(tCanRegGloFiltCfg_t));
    ASSERT_EQ(4, sizeof(tCanRegStdIdFiltCfg_t));
    ASSERT_EQ(4, sizeof(tCanRegRxBufFiFoElemSzCgf_t));
    ASSERT_EQ(4, sizeof(tCanRegProtStat_t));
    ASSERT_EQ(4, sizeof(tCanRegExtIdFiltCfg_t));
    ASSERT_EQ(4, sizeof(tCanRegRxFifo0Cfg_t));
    ASSERT_EQ(4, sizeof(tCanRegTxEventFifoCgf_t));
    ASSERT_EQ(4, sizeof(tCanRegRxFifo1Cfg_t));
    ASSERT_EQ(4, sizeof(tCanRegRxBufCgf_t));
    ASSERT_EQ(4, sizeof(tCanRegIntLine_t));

    ASSERT_EQ(4, sizeof(tCan4550SidFilter_t));
    ASSERT_EQ(4, sizeof(TxBuffW1_t));
    ASSERT_EQ(4, sizeof(HeaderCom_t));
    ASSERT_EQ(4, sizeof(W0_t));

    uint8_t i=0;
    for(i=0;i<8;i++){
        ASSERT_EQ(i,bytes_2_dlc(i));
    }
    ASSERT_EQ(9,bytes_2_dlc(9));
    ASSERT_EQ(15,bytes_2_dlc(100));
    ASSERT_EQ(15,bytes_2_dlc(64));
    ASSERT_EQ(11,bytes_2_dlc(20));

    for(i=0;i<8;i++){
        ASSERT_EQ(    i, dlc_2_bytes(bytes_2_dlc(i)));
    }



    return true;
}

static bool test_can_set_bitrate_one(uint32_t bit_rate){
    uint32_t read_bit_rate = 0.0;
    EXPECT_TRUE( tcan4550_set_bit_rate(  bit_rate));
    read_bit_rate = tcan4550_get_bit_rate();
    ASSERT_EQ(bit_rate,read_bit_rate);
    return true;
}

bool test_can_rate(void){
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    uint32_t orig_bit_rate;
    orig_bit_rate = tcan4550_get_bit_rate();
    LOG_INFO(CAN,"Orig bit rate %u",orig_bit_rate );
    EXPECT_TRUE(test_can_set_bitrate_one(10000));
    EXPECT_TRUE(test_can_set_bitrate_one(20000));
    EXPECT_TRUE(test_can_set_bitrate_one(50000));
    EXPECT_TRUE(test_can_set_bitrate_one(125000));
    EXPECT_TRUE(test_can_set_bitrate_one(250000));
    EXPECT_TRUE(test_can_set_bitrate_one(500000));
#ifdef SET_800K_UNDEF_BUG
    EXPECT_TRUE(test_can_set_bitrate_one(800000));
#endif
    EXPECT_TRUE(test_can_set_bitrate_one(1000000));
    LOG_WARNING(CAN,"Set default bit rate %u",CAN_BAUD_RATE_DFLT );
    EXPECT_TRUE( tcan4550_set_bit_rate(  CAN_BAUD_RATE_DFLT));
    return true;
}

static bool test_can_address(uint16_t addr) {
    uint32_t orig_reg=0;
    EXPECT_TRUE( tcan4550_read_reg(addr, &orig_reg)) ;

    EXPECT_TRUE(test_can_write_one(addr,0xAAAAAAAA));
    EXPECT_TRUE(test_can_write_one(addr,0x55555555));
    EXPECT_TRUE(test_can_write_one(addr,0x12345678));

    EXPECT_TRUE( tcan4550_write_reg(addr, orig_reg)) ;
    return true;
}

bool test_can_mram(void){
    uint16_t addr=0;
    for(addr=ADDR_MRAM; addr<=(ADDR_MRAM+MRAM_SZ-4); addr+=5){
        EXPECT_TRUE( test_can_address(  addr ));
    }
    return true;
}

bool test_can_send_std(void){
    uint32_t id= 0x123;
    uint64_t data64 = 0x112233445566;
    EXPECT_TRUE( init_tcan());
    EXPECT_TRUE( tcan4550_send_std(id, data64,1));
    EXPECT_TRUE( tcan4550_send_std(id, data64,2));
    EXPECT_TRUE( tcan4550_send_std(id, data64,4));
    EXPECT_TRUE( tcan4550_send_std(id, data64,8));
    return true;
}

bool test_can_send_ext(void){
    uint32_t id= 0x123;
    uint64_t data64 = 0x112233445566;
    EXPECT_TRUE( init_tcan());
    EXPECT_TRUE( tcan4550_send_ext(id, data64,1));
    EXPECT_TRUE( tcan4550_send_ext(id, data64,2));
    EXPECT_TRUE( tcan4550_send_ext(id, data64,4));
    EXPECT_TRUE( tcan4550_send_ext(id, data64,8));
    return true;
}
