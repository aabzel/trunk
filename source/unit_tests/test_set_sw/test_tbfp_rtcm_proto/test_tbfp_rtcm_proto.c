#include "test_tbfp_rtcm_proto.h"

#ifdef X86_64
#include <stdio.h>
#endif

#include "fifo_char.h"
#ifdef HAS_LORA
#include "lora_drv.h"
#endif
#include "log.h"
#include "test_rtcm3_proto.h"
#include "tbfp_protocol.h"
#include "rtcm3_protocol.h"
#include "system.h"
#include "unit_test_check.h"

bool test_tbfp_tunnel(void){
    LOG_DEBUG(TBFP,"%s():", __FUNCTION__);
#ifdef HAS_LORA
    set_log_level(RTCM, LOG_LEVEL_INFO);
    uint8_t BigRtcm3Message[60]={};
    EXPECT_TRUE(array_incr(BigRtcm3Message,sizeof(BigRtcm3Message)));
    EXPECT_TRUE(rtcm3_generate_frame(BigRtcm3Message, sizeof(BigRtcm3Message)));
    EXPECT_TRUE( is_rtcm3_frame(BigRtcm3Message, sizeof(BigRtcm3Message)));
    uint32_t i=0;
    EXPECT_TRUE(tbfp_protocol_init(&TbfpProtocol[IF_LORA], IF_LORA, 0xA5) ) ;
    EXPECT_TRUE(tbfp_protocol_init(&TbfpProtocol[IF_SX1262], IF_SX1262, 0x1E));
    EXPECT_TRUE(fifo_init(&LoRaInterface.FiFoLoRaCharTx, &LoRaTxBuff[0], sizeof(LoRaTxBuff)));
    set_log_level(TBFP, LOG_LEVEL_DEBUG); /* uncomment in case of test fail*/
    set_log_level(LORA, LOG_LEVEL_DEBUG); /* uncomment in case of test fail*/
    uint8_t number_tx_frame = 11;
    for(i=0; i<number_tx_frame; i++){
        LOG_INFO(TBFP,"SendBigFrame %u",i);
        EXPECT_TRUE(tbfp_send(BigRtcm3Message, sizeof(BigRtcm3Message), IF_LORA, 0, ACK_NO_NEED));
        uint32_t count =0, cnt=0;
        do{
            LOG_DEBUG(TBFP,"TxPart:%u", cnt++);
            lora_transmit_from_queue(10,0, 1,MAX_LORA_PAYLOAD_SIZE);
            count = fifo_get_count(&LoRaInterface.FiFoLoRaCharTx);
        }while(MAX_LORA_PAYLOAD_SIZE<count );
    }
    lora_transmit_from_queue(10,0, 1,1);
    set_log_level(TBFP, LOG_LEVEL_INFO); /* uncomment in case of test fail*/
    EXPECT_EQ(number_tx_frame, TbfpProtocol[IF_LORA].rx_pkt_cnt);
    LOG_INFO(TBFP,"OK");
    return true;
#else
    return false;
#endif
}


bool test_tbfp_rtcm_path(void) {
#ifdef X86_64
    LOG_DEBUG(TBFP,"%s():", __FUNCTION__);
#endif
    uint32_t i=0;
    EXPECT_TRUE( set_log_level(TBFP , LOG_LEVEL_INFO ));
    EXPECT_TRUE( set_log_level(RTCM, LOG_LEVEL_INFO ));
    EXPECT_TRUE(tbfp_protocol_init(&TbfpProtocol[IF_LOOPBACK], IF_LOOPBACK,0xA5));
    EXPECT_TRUE(rtcm3_protocol_init(&Rtcm3Protocol[IF_LOOPBACK], IF_LOOPBACK, false));
    for (i=1; i<500;i++) {
        EXPECT_TRUE_NUM(tbfp_send((uint8_t* )rtcm3_message, sizeof(rtcm3_message), IF_LOOPBACK, 0,ACK_NO_NEED),i);
        EXPECT_EQ(i,Rtcm3Protocol[IF_LOOPBACK].rx_pkt_cnt);
    }

    return true;
}

