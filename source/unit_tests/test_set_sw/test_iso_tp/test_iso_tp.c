#include "test_iso_tp.h"

#include <stdio.h>


#include "log.h"
#include "iso_tp.h"
#include "num_to_str.h"
#include "none_blocking_pause.h"
#include "unit_test_check.h"
#include "super_cycle.h"
#include "byte_utils.h"

/* 49 days max*/
/*none blocking wait for self test and polling*/
bool iso_tp_wait_in_loop_ms(uint8_t nun) {
    bool res = false;
    IsoTpHandle_t* Node=IsoTpGetNode( 1);
    if(Node) {
        LOG_WARNING(ISO_TP, "WaitTxEnd!...");
        bool loop = true;

        while(loop) {
        	cli_printf("[%u]",Node->tx_rest_byte);
#ifdef HAS_SUPER_CYCLE
            super_cycle_iteration();
#endif

            if(Node->tx_rest_byte <=0) {
                res = true;
                LOG_WARNING(ISO_TP, "TxDoneWaitEnd!");
                loop = false;
                break;
            }

        }//while
        LOG_WARNING(ISO_TP, "TxEnd!!!");
    } else {
        res = true;
    }
    return res;
}

static bool test_iso_tp_send_custom(uint8_t* data, uint32_t size){
    bool res = true;
    LOG_DEBUG(ISO_TP, "%s():Size:%u Byte", __FUNCTION__,size);
    set_log_level(ISO_TP, LOG_LEVEL_DEBUG);

    ASSERT_TRUE( iso_tp_send(1, 0x18, data, size));

    ASSERT_TRUE(iso_tp_wait_in_loop_ms(1));

    IsoTpHandle_t* NodeTx=IsoTpGetNode( 1);
    ASSERT_NE(NULL,NodeTx);

    IsoTpHandle_t* NodeRx=IsoTpGetNode( 2);
    ASSERT_NE(NULL,NodeRx);

    ASSERT_TRUE(iso_tp_buff_print(  1 ,  size,ISO_TP_BUFF_TX));
	ASSERT_TRUE(iso_tp_buff_print(  2 ,  size,ISO_TP_BUFF_RX));


	ASSERT_TRUE(array_is_equal(NodeTx->TxData,NodeRx->RxData, size) );
    LOG_INFO(ISO_TP, "DataMatch! Size:%u Byte",size);
    set_log_level(ISO_TP, LOG_LEVEL_INFO);
    return res;
}


bool test_iso_tp_types(void) {
    bool res = true;
    LOG_DEBUG(ISO_TP, "%s():", __FUNCTION__);
    set_log_level(ISO_TP, LOG_LEVEL_DEBUG);
    EXPECT_EQ(8, sizeof(IsoTpFrame_t));
    EXPECT_EQ(1, sizeof(IsoTpSingleFrameHeader_t));
    EXPECT_EQ(2, sizeof(IsoTpFirstFrameHeader_t));
    EXPECT_EQ(3, sizeof(IsoTpFlowControlHeader_t));
    EXPECT_EQ(1, sizeof(IsoTpConsecutiveFrameHeader_t));

    IsoTpFirstFrameHeader_t FirstFrameHeader;
    FirstFrameHeader.word=0;
    FirstFrameHeader.data_len = 50;
    FirstFrameHeader.frame_id = ISO_TP_FRAME_CODE_FIRST_FRAME;
    FirstFrameHeader.word = reverse_byte_order_uint16(FirstFrameHeader.word);
    EXPECT_EQ(0x10, FirstFrameHeader.buff[0]);
    EXPECT_EQ(0x32, FirstFrameHeader.buff[1]);




    IsoTpFlowControlHeader_t FlowControlHeader;

    FlowControlHeader.frame_id = ISO_TP_FRAME_CODE_FLOW_CONTOL;
    FlowControlHeader.flow_status =FLOW_CONRTOL_FLAG_WAIT  ;
    FlowControlHeader.block_size = 3;
    FlowControlHeader.min_sep_time =100;
   // reverse_byte_order_array(FirstFrameHeader.buff,3);
    EXPECT_EQ(0x31, FlowControlHeader.buff[0]);
    EXPECT_EQ(3, FlowControlHeader.buff[1]);
    EXPECT_EQ(100, FlowControlHeader.buff[2]);


    set_log_level(ISO_TP, LOG_LEVEL_INFO);

    return res;
}


bool test_iso_tp_send_single_frame(void){
    bool res = true;
    LOG_DEBUG(ISO_TP, "%s():", __FUNCTION__);
    set_log_level(ISO_TP, LOG_LEVEL_DEBUG);
    static uint8_t data[10]={1,2,3,4,5,6};
    ASSERT_TRUE( iso_tp_send(1, 0x18, data, 6));

    ASSERT_TRUE( test_iso_tp_send_custom(data, 6));

    set_log_level(ISO_TP, LOG_LEVEL_INFO);
    return res;
}

bool test_iso_tp_send(void){

    LOG_DEBUG(ISO_TP, "%s():", __FUNCTION__);
    set_log_level(ISO_TP, LOG_LEVEL_DEBUG);
    uint8_t data[16]={17,16,15,14,13,7,8,9,10,11,12,13,14,15,16,17};

    ASSERT_TRUE( test_iso_tp_send_custom(data, sizeof(data)));

    set_log_level(ISO_TP, LOG_LEVEL_INFO);
    return true;
}

bool test_iso_tp_send_jumbo(void){
    bool res = true;
    LOG_DEBUG(ISO_TP, "%s():", __FUNCTION__);
    set_log_level(ISO_TP, LOG_LEVEL_DEBUG);
    static uint8_t data[50]={0};
    ASSERT_TRUE(  array_incr(data, sizeof(data)  )  ) ;

    ASSERT_TRUE( test_iso_tp_send_custom(data, sizeof(data)));

    set_log_level(ISO_TP, LOG_LEVEL_INFO);
    return res;
}


bool test_iso_tp_send_3(void){
    bool res = true;
    LOG_DEBUG(ISO_TP, "%s():", __FUNCTION__);
    set_log_level(ISO_TP, LOG_LEVEL_DEBUG);
    static uint8_t data[8*3]={0};
    ASSERT_TRUE(  array_incr(data, sizeof(data)  )  ) ;

    ASSERT_TRUE( test_iso_tp_send_custom(data, sizeof(data)));

    set_log_level(ISO_TP, LOG_LEVEL_INFO);
    return res;
}


bool test_iso_tp_diag(void){
    bool res = true;
    LOG_DEBUG(ISO_TP, "%s():", __FUNCTION__);

    char text[80]={0};
    uint64_t qword = 0x1102030405060708;
    sprintf(text,"%s", HexQWordToStr(qword));
    LOG_INFO(ISO_TP, "%s", text);
    ASSERT_STREQ("0x1102030405060708", text)


    return res;
}

bool test_iso_tp_send_4095(void){
    bool res = true;
    LOG_DEBUG(ISO_TP, "%s():", __FUNCTION__);
    set_log_level(ISO_TP, LOG_LEVEL_DEBUG);
    static uint8_t data[4095]={0};
    ASSERT_TRUE(  array_incr(data, sizeof(data)  )  ) ;

    ASSERT_TRUE( test_iso_tp_send_custom(data, sizeof(data)));

    set_log_level(ISO_TP, LOG_LEVEL_INFO);
    return res;
}
