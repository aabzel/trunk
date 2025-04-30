#include "test_rtcm3_proto.h"

#include "log.h"

#include "rtcm3_protocol.h"
#ifndef X86_64
#include "uart_drv.h"
#endif
#include "system.h"
#include "unit_test_check.h"

const uint8_t rtcm3_message25[25] = {0xD3, 0x00, 0x13, 0x3E, 0xD0, 0x00, 0x03, 0x86, 0xA5, 0x7F, 0x83, 0x07, 0x85,
                                     0x1F, 0xDA, 0xD8, 0x0B, 0x0C, 0x35, 0xF9, 0x18, 0xAC, 0xDB, 0xE9, 0xF2};

const uint8_t rtcm3_message[36] = {0xD3, 0x00, 0x1E, 0x44, 0x60, 0x00, 0x1C, 0x77, 0xD7, 0x82, 0x00, 0x00,
                                   0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
                                   0x54, 0x50, 0x7C, 0x15, 0x9E, 0x12, 0x2C, 0xDA, 0x60, 0x6A, 0x26, 0x5D};

const uint8_t rtcm3_message2[] = {0xD3, 0x00, 0x13, 0x3E, 0xD0, 0x00, 0x03, 0x86, 0xA2, 0x16, 0xA1, 0x25, 0x85,
                                  0x13, 0x8B, 0xFB, 0xA2, 0x0C, 0x3C, 0xE2, 0x79, 0x9D, 0x0C, 0x17, 0xFB, 0xD3,
                                  0x00, 0x08, 0x4C, 0xE0, 0x00, 0x8A, 0x00, 0x00, 0x00, 0x00, 0xA8, 0xF7, 0x2A};

bool test_rtcm3_proto_1(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    uint8_t i = 0;
#ifndef X86_64
    EXPECT_TRUE(uart_deinit(1));
#endif
    EXPECT_TRUE(is_rtcm3_frame((uint8_t*)rtcm3_message25, sizeof(rtcm3_message25)));
    EXPECT_TRUE(is_rtcm3_frame((uint8_t*)rtcm3_message, sizeof(rtcm3_message)));
    rtcm3_reset_rx(&Rtcm3Protocol[IF_UART1], WAIT_INIT);
    Rtcm3Protocol[IF_UART1].rx_pkt_cnt = 0;
    for(i = 0; i < sizeof(rtcm3_message); i++) {
        rtcm3_proc_byte(&Rtcm3Protocol[IF_UART1], rtcm3_message[i]);
    }
    EXPECT_EQ(0, Rtcm3Protocol[IF_UART1].load_len);
    EXPECT_EQ(1, Rtcm3Protocol[IF_UART1].rx_pkt_cnt);

    return true;
}

bool test_rtcm3_types(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    EXPECT_EQ(1, sizeof(Interfaces_t));
    EXPECT_EQ(2, sizeof(Rtcm3Len_t));
    EXPECT_EQ(3, sizeof(Rtcm3Header_t)); /*error on work NetTop returns 4*/
#ifndef X86_64
    EXPECT_EQ(1, sizeof(RxState_t));
#endif
    return true;
}

bool test_rtcm3_array(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    Rtcm3Protocol[IF_LORA].rx_pkt_cnt = 0;
    rtcm3_reset_rx(&Rtcm3Protocol[IF_LORA], WAIT_INIT);
    EXPECT_TRUE(rtcm3_proc_array((uint8_t*)rtcm3_message2, sizeof(rtcm3_message2), IF_LORA));
    EXPECT_EQ(2, Rtcm3Protocol[IF_LORA].rx_pkt_cnt);
    return true;
}
