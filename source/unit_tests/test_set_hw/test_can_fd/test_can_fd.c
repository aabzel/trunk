#include "test_can_fd.h"

#include "can_fd_mcal.h"
#include "can_mcal.h"
#include "time_mcal.h"
#include "array.h"
#include "log.h"
#include "unit_test_check.h"
#include "common_diag.h"

#define TEST_CAN_NUM 0
#define TEST_CAN_NUM2 5

#define CAN_TX_ID 0x04
#define CAN_TX_SIZE 64
static bool test_can_fd_loopback_pair(uint8_t tx_num, uint8_t rx_num){
    LOG_INFO(CAN, "%s()", __FUNCTION__);
    bool res = true;
    log_level_get_set(CAN_FD, LOG_LEVEL_DEBUG);
    log_level_get_set(ARRAY, LOG_LEVEL_DEBUG);
    CanHandle_t* Node = CanGetNode(rx_num);
    ASSERT_NE(0,Node);
    memset(Node->RxMessage.data,0,sizeof(CanMessage_t));
    Node->rx_done = false;

    CanMessage_t TxFrame;
    TxFrame.mesg_buff_idx = 1 ;
    TxFrame.bit_rate_switch = CAN_FD_BIT_RATE_SWITCH_ON;
    TxFrame.id_type = CAN_FRAME_ID_STANDARD ;
    TxFrame.identifier.standard = CAN_TX_ID ;
    TxFrame.size = CAN_TX_SIZE ;
    TxFrame.frame_type = CAN_TX_FRAME_DATA ;

    ASSERT_TRUE( array_incr(TxFrame.data, CAN_TX_SIZE, 0)   );

    LOG_INFO(CAN,"Tx,%s", CanMessageToStr(&TxFrame)    );
    ASSERT_TRUE( can_fd_send(tx_num, &TxFrame)  );
    ASSERT_TRUE( wait_in_loop_ms(300)  );

    ASSERT_TRUE(Node->rx_done);
    ASSERT_EQ( CAN_TX_SIZE, Node->RxMessage.size);
    ASSERT_EQ( CAN_TX_ID, Node->RxMessage.identifier.standard);
    ASSERT_EQ_MEM(TxFrame.data, Node->RxMessage.data, CAN_TX_SIZE)
  //  ASSERT_EQ( CAN_FRAME_ID_STANDARD, Node->RxMessage.id_type);

    log_level_get_set(ARRAY, LOG_LEVEL_INFO);
    log_level_get_set(CAN_FD, LOG_LEVEL_INFO);
    return res;
}

bool test_can_fd_hash(void){
    LOG_INFO(CAN, "%s()", __FUNCTION__);
    bool res = true;
    log_level_get_set(CAN_FD, LOG_LEVEL_DEBUG);

    log_level_get_set(CAN_FD, LOG_LEVEL_INFO);
    return res;
}

bool test_can_fd_types(void) {
    LOG_INFO(CAN, "%s()", __FUNCTION__);
    bool res = true;
    log_level_get_set(CAN_FD, LOG_LEVEL_DEBUG);


    log_level_get_set(CAN_FD, LOG_LEVEL_INFO);
    return res;
}

/*
 tsr can_fd+
 tsr can_fd_cfg
 */

bool test_can_fd_cfg(void) {
    LOG_INFO(CAN, "%s()", __FUNCTION__);
    bool res = true;
    log_level_get_set(CAN_FD, LOG_LEVEL_DEBUG);

    log_level_get_set(CAN_FD, LOG_LEVEL_INFO);
    return res;
}

/*
 tsr can_fd+
 tsr can_fd_send_std
 */
bool test_can_fd_send_std(void) {
    LOG_INFO(CAN, "%s()", __FUNCTION__);
    log_level_get_set(CAN_FD, LOG_LEVEL_DEBUG);
    bool res = true;
    CanMessage_t Frame = {0};
    Frame.mesg_buff_idx = 1 ;
    Frame.bit_rate_switch = CAN_FD_BIT_RATE_SWITCH_ON;
    Frame.size = 64 ;
    Frame.id_type = CAN_FRAME_ID_STANDARD;
    Frame.frame_type = CAN_TX_FRAME_DATA ;
    Frame.identifier.standard = 0x010;
    ASSERT_TRUE( array_incr( Frame.data, 64, 0) );

    ASSERT_TRUE(  can_fd_send(TEST_CAN_NUM,  &Frame ));
    log_level_get_set(CAN_FD, LOG_LEVEL_INFO);
    return res;
}



bool test_can_fd_baudrate(void) {
    LOG_INFO(CAN, "%s()", __FUNCTION__);
    log_level_get_set(CAN_FD, LOG_LEVEL_DEBUG);
    bool res = true;
    uint32_t get_baud_rate = 0;
    uint32_t set_baud_rate = 3000000;

    ASSERT_TRUE(can_fd_baudrate_set(TEST_CAN_NUM, set_baud_rate));
    ASSERT_TRUE(can_fd_baudrate_get(TEST_CAN_NUM, &get_baud_rate));
    ASSERT_EQ(set_baud_rate, get_baud_rate);
    log_level_get_set(CAN_FD, LOG_LEVEL_INFO);
    return res;
}

bool test_can_fd_clock(void){
    LOG_INFO(CAN, "%s()", __FUNCTION__);
    bool res = true;
    log_level_get_set(CAN_FD, LOG_LEVEL_DEBUG);
    log_level_get_set(CAN_FD, LOG_LEVEL_INFO);
    return res;
}

/*
 tsr can_fd_loopback+
 * */
bool test_can_fd_loopback_0_5(void){
    LOG_INFO(CAN, "%s()", __FUNCTION__);
    log_level_get_set(CAN_FD, LOG_LEVEL_DEBUG);
    bool res = true;

    ASSERT_TRUE(test_can_fd_loopback_pair(0,  5));

    log_level_get_set(CAN_FD, LOG_LEVEL_INFO);
    return res;
}

bool test_can_fd_loopback_5_0(void){
    LOG_INFO(CAN, "%s()", __FUNCTION__);
    bool res = true;
    log_level_get_set(CAN_FD, LOG_LEVEL_DEBUG);
    ASSERT_TRUE(test_can_fd_loopback_pair(5,  0));
    log_level_get_set(CAN_FD, LOG_LEVEL_INFO);
    return res;
}

