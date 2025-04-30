#include "test_rtcm_path.h"

#include <string.h>

#include "sys_config.h"
#include "unit_test_check.h"
#include "rtcm3_protocol.h"
#include "test_rtcm3_proto.h" /*To Save memory on targe*/
#include "uart_drv.h"
 


bool test_rtcm3_path(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    uint32_t init_rx_pkt_cnt = Rtcm3Protocol[IF_LORA].rx_pkt_cnt;
    EXPECT_TRUE( rtcm3_proc_array((uint8_t*)rtcm3_message2, sizeof(rtcm3_message2), IF_LORA));
    ASSERT_EQ( init_rx_pkt_cnt+2,Rtcm3Protocol[IF_LORA].rx_pkt_cnt);

    EXPECT_EQ_MEM(&VerifyUartTx[UART_NUM_ZED_F9P][0],&rtcm3_message2[25],14);

    return true;
}
