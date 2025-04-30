#include "test_tbfp.h"

#include "crc8_sae_j1850.h"
#include "log.h"
#include "protocol.h"
#include "storage_types.h"
#include "system.h"
#include "tbfp.h"
#include "unit_test_check.h"

static const uint8_t tbfp_message1[] = {0xA5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0};
static const uint8_t tbfp_message2[] = {0xA5, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x9f};
static const uint8_t tbfp_message29[] = {0xA5, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x90, 0x73, 0xCB, 0xCB, 0x5E, 0x8A,
                                         0xF8, 0x00, 0x00, 0x80, 0xAE, 0xFE, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
                                         0x80, 0x76, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x76, 0x40, 0x5a};

bool test_tbfp_types(void) {
    bool res = true;
    LOG_DEBUG(TBFP, "%s():", __FUNCTION__);
    set_log_level(TBFP, LOG_LEVEL_DEBUG);
    EXPECT_EQ(1, sizeof(IfRetx_t));
    EXPECT_EQ(1, sizeof(TbfpPayloadId_t));
    EXPECT_EQ(1, sizeof(StorageAccess_t));
    EXPECT_EQ(1, sizeof(TbfpFrameFlags_t));
    EXPECT_EQ(8, sizeof(StorageFrameHeader_t));
    EXPECT_EQ(7, sizeof(TbfpHeader_t));
    EXPECT_EQ(TBFP_SIZE_HEADER, sizeof(TbfpHeader_t));
    EXPECT_EQ(TBFP_SIZE_OVERHEAD, TBFP_SIZE_HEADER + TBFP_SIZE_CRC);

    uint32_t cnt = tbfp_get_cnt();
    LOG_DEBUG(TBFP, "Spot %u Node", cnt);
    EXPECT_GR(0, cnt);

    set_log_level(TBFP, LOG_LEVEL_INFO);

    return res;
}

bool test_tbfp_proto_0(void) {
    bool res = true;
    LOG_DEBUG(TBFP, "%s():", __FUNCTION__);
    set_log_level(TBFP, LOG_LEVEL_PARANOID);
    set_log_level(CRC8, LOG_LEVEL_PARANOID);

    TbfpHandle_t* Node = TbfpInterfaceToNode(IF_LOOPBACK);
    EXPECT_NE(NULL, Node);
    ASSERT_TRUE(tbfp_init_one(Node->num));

    uint32_t init_pkt_cnt = Node->rx_pkt_cnt;
    uint32_t i = 0;
    for(i = 0; i < sizeof(tbfp_message1); i++) {
        cli_printf(" %u" CRLF, i);
        ASSERT_TRUE(tbfp_proc_byte(Node, tbfp_message1[i]));
    }
    EXPECT_EQ(init_pkt_cnt + 1, Node->rx_pkt_cnt);

    set_log_level(TBFP, LOG_LEVEL_INFO);
    set_log_level(CRC8, LOG_LEVEL_INFO);
    return res;
}

bool test_tbfp_proto_1(void) {
    bool res = true;
    LOG_DEBUG(TBFP, "%s():", __FUNCTION__);
    set_log_level(TBFP, LOG_LEVEL_PARANOID);
    set_log_level(CRC8, LOG_LEVEL_PARANOID);
    TbfpHandle_t* Node = TbfpInterfaceToNode(IF_LOOPBACK);
    ASSERT_NE(NULL, Node);

    ASSERT_TRUE(tbfp_init_one(Node->num));
    EXPECT_TRUE(is_tbfp_protocol((uint8_t*)tbfp_message1, sizeof(tbfp_message1), IF_LOOPBACK));
    EXPECT_TRUE(is_tbfp_protocol((uint8_t*)tbfp_message2, sizeof(tbfp_message2), IF_LOOPBACK));

    set_log_level(TBFP, LOG_LEVEL_INFO);
    set_log_level(CRC8, LOG_LEVEL_INFO);
    return res;
}

bool test_tbfp_proto_2(void) {
    bool res = true;
    LOG_DEBUG(TBFP, "%s():", __FUNCTION__);
    set_log_level(TBFP, LOG_LEVEL_PARANOID);
    set_log_level(CRC8, LOG_LEVEL_PARANOID);
    uint32_t i = 0;
    TbfpHandle_t* Node = TbfpInterfaceToNode(IF_LOOPBACK);
    ASSERT_NE(NULL, Node);

    ASSERT_TRUE(tbfp_init_one(Node->num));
    uint32_t init_pkt_cnt = Node->rx_pkt_cnt;
    for(i = 0; i < sizeof(tbfp_message2); i++) {
        // cli_printf("\n%s(): %u", __FUNCTION__, i);
        EXPECT_TRUE_NUM(tbfp_proc_byte(Node, tbfp_message2[i]), i);
    }
    EXPECT_EQ(init_pkt_cnt + 1, Node->rx_pkt_cnt);

    set_log_level(TBFP, LOG_LEVEL_INFO);
    set_log_level(CRC8, LOG_LEVEL_INFO);

    return res;
}

bool test_tbfp_proto_auto(void) {
    bool res = true;
    LOG_INFO(TBFP, "%s():", __FUNCTION__);
    set_log_level(TBFP, LOG_LEVEL_DEBUG);
    uint8_t tbfp_generated[10] = {};
    memset(tbfp_generated, 0, sizeof(tbfp_generated));
    EXPECT_TRUE(tbfp_generate_frame(tbfp_generated, sizeof(tbfp_generated), IF_LOOPBACK));
    EXPECT_TRUE(is_tbfp_protocol((uint8_t*)tbfp_generated, sizeof(tbfp_generated), IF_LOOPBACK));
    set_log_level(TBFP, LOG_LEVEL_INFO);
    return res;
}

bool test_tbfp_proto_overlen(void) {
    bool res = true;
    LOG_DEBUG(TBFP, "%s():", __FUNCTION__);
    set_log_level(TBFP, LOG_LEVEL_DEBUG);
    uint32_t i = 0;
    TbfpHandle_t* Node = TbfpInterfaceToNode(IF_LOOPBACK);
    ASSERT_NE(NULL, Node);

    ASSERT_TRUE(tbfp_init_one(Node->num));
    uint8_t tbfp_message[512] = {0};
    tbfp_message[0] = 0xA5;
    tbfp_message[1] = 0xFF; /*incorrect length*/
    for(i = 0; i < sizeof(tbfp_message); i++) {
        EXPECT_TRUE(tbfp_proc_byte(Node, tbfp_message[i]));
    }
    set_log_level(TBFP, LOG_LEVEL_INFO);
    return res;
}

bool test_tbfp_proto_29(void) {
    bool res = true;
    LOG_DEBUG(TBFP, "%s():", __FUNCTION__);
    set_log_level(TBFP, LOG_LEVEL_PARANOID);
    set_log_level(CRC8, LOG_LEVEL_PARANOID);

    uint32_t i = 0;
    TbfpHandle_t* Node = TbfpInterfaceToNode(IF_LOOPBACK);
    ASSERT_NE(NULL, Node);

    ASSERT_TRUE(tbfp_init_one(Node->num));

    uint32_t init_pkt_cnt = Node->rx_pkt_cnt;
    for(i = 0; i < sizeof(tbfp_message29); i++) {
        cli_printf("%u" CRLF, i);
        EXPECT_TRUE(tbfp_proc_byte(Node, tbfp_message29[i]));
    }
    EXPECT_EQ(init_pkt_cnt + 1, Node->rx_pkt_cnt);

    for(i = 0; i < sizeof(tbfp_message2); i++) {
        cli_printf("%u" CRLF, i);
        EXPECT_TRUE(tbfp_proc_byte(Node, tbfp_message2[i]));
    }
    EXPECT_EQ(init_pkt_cnt + 2, Node->rx_pkt_cnt);

    set_log_level(TBFP, LOG_LEVEL_INFO);
    set_log_level(CRC8, LOG_LEVEL_INFO);
    return res;
}

bool test_tbfp_proto_flow_ctrl(void) {
    bool res = true;
    LOG_DEBUG(TBFP, "%s():", __FUNCTION__);
    set_log_level(TBFP, LOG_LEVEL_DEBUG);
    TbfpHandle_t* Node = TbfpInterfaceToNode(IF_LOOPBACK);
    ASSERT_NE(NULL, Node);

    ASSERT_TRUE(tbfp_init_one(Node->num));

    EXPECT_TRUE(tbfp_send_chat((uint8_t*)"12", 2, IF_LOOPBACK, 0, ACK_NO_NEED));
    EXPECT_EQ(0, Node->Flow.prev_s_num);

    EXPECT_TRUE(tbfp_send_chat((uint8_t*)"34", 2, IF_LOOPBACK, 0, ACK_NO_NEED));
    EXPECT_EQ(1, Node->Flow.prev_s_num);

    EXPECT_TRUE(tbfp_send_chat((uint8_t*)"56", 2, IF_LOOPBACK, 0, ACK_NO_NEED));
    EXPECT_EQ(2, Node->Flow.prev_s_num);
    //    EXPECT_EQ(3, Node->Flow.s_num);
    EXPECT_EQ(3, Node->Flow.cur);
    EXPECT_EQ(3, Node->Flow.maximum_continuous);
    set_log_level(TBFP, LOG_LEVEL_INFO);
    return res;
}

bool test_tbfp_proto_flow_ctrl2(void) {
    bool res = true;
    LOG_DEBUG(TBFP, "%s():", __FUNCTION__);
    set_log_level(TBFP, LOG_LEVEL_DEBUG);
    // uint16_t prev_s_num = 0;
    // uint32_t max_flow = 0;
    uint32_t sn = 0;

    FlowCrtl_t Node;
    EXPECT_TRUE(protocol_flow_init(&Node));

    set_log_level(TBFP, LOG_LEVEL_PARANOID);
    EXPECT_TRUE(protocol_check_flow_control(TBFP, &Node, sn, IF_LOOPBACK));
    EXPECT_EQ(0, Node.prev_s_num);
    EXPECT_EQ(1, Node.cur);

    sn = 1;
    EXPECT_TRUE(protocol_check_flow_control(TBFP, &Node, sn, IF_LOOPBACK));
    EXPECT_EQ(1, Node.prev_s_num);
    EXPECT_EQ(2, Node.cur);

    sn = 5;
    EXPECT_TRUE(protocol_check_flow_control(TBFP, &Node, sn, IF_LOOPBACK));
    EXPECT_EQ(5, Node.prev_s_num);
    EXPECT_EQ(1, Node.cur);

    sn = 1;
    EXPECT_FALSE(protocol_check_flow_control(TBFP, &Node, sn, IF_LOOPBACK));
    EXPECT_EQ(1, Node.prev_s_num);
    EXPECT_EQ(1, Node.cur);
    set_log_level(TBFP, LOG_LEVEL_INFO);
    return res;
}
/*LoopAll Awailable if in that test*/
bool test_tbfp_interfaces(void) {
    bool res = true;
    LOG_DEBUG(TBFP, "%s():", __FUNCTION__);
    uint8_t array[299];
    memset(array, 0x55, sizeof(array));
    set_log_level(TBFP, LOG_LEVEL_DEBUG);
#ifdef HAS_UART1
    EXPECT_TRUE(tbfp_send_payload(array, sizeof(array), IF_UART1, 0, ACK_NO_NEED, FRAME_ID_CHAT));
#endif
#ifdef HAS_RS232
    EXPECT_TRUE(tbfp_send_payload(array, sizeof(array), IF_RS232, 0, ACK_NO_NEED, FRAME_ID_CHAT));
#endif
#ifdef HAS_LORA
    EXPECT_TRUE(tbfp_send_payload(array, sizeof(array), IF_LORA, 0, ACK_NO_NEED, FRAME_ID_CHAT));
#endif
#ifdef HAS_CAN
    EXPECT_TRUE(tbfp_send_payload(array, sizeof(array), IF_CAN, 0, ACK_NO_NEED, FRAME_ID_CHAT));
#endif

    EXPECT_TRUE(tbfp_send_payload(array, sizeof(array), IF_LOOPBACK, 0, ACK_NO_NEED, FRAME_ID_CHAT));
#ifdef HAS_UWB
    EXPECT_TRUE(tbfp_send_payload(array, sizeof(array), IF_UWB, 0, ACK_NO_NEED, FRAME_ID_CHAT));
#endif
    set_log_level(TBFP, LOG_LEVEL_INFO);
    return res;
}

#define TEST_STORAGE_WRITE 16U
bool tbfp_test_genegare_storage_write(const uint8_t num, uint8_t* const frame) {
    bool res = false;
    TbfpHandle_t* Node = TbfpGetNode(num);
    if(Node) {
        LOG_INFO(TBFP, "%s", TbfpNode2Str(Node));
        uint16_t payload_len = (uint16_t)sizeof(StorageFrameHeader_t) + TEST_STORAGE_WRITE;
        LOG_INFO(TBFP, "PayLoadLen:%u byte", payload_len);
        TbfpHeader_t Header;
        frame[0] = Node->preamble_val;
        Header.preamble = Node->preamble_val;
        Header.flags.ack_need = 1;
        Header.flags.crc_check_need = 1;
        Header.flags.lifetime = 4;
        Header.payload_id = FRAME_ID_STORAGE;
        Header.snum = 0x00FF;
        Header.len = payload_len;
        memcpy(frame, &Header, sizeof(TbfpHeader_t));
        StorageFrameHeader_t StorageData;
        StorageData.address = 0x0;
        StorageData.asic_num = 1;
        StorageData.operation = ACCESS_WRITE_ONLY;
        StorageData.size = TEST_STORAGE_WRITE; /* Bytes to read */

        memcpy(&frame[sizeof(TbfpHeader_t)], &StorageData, sizeof(StorageFrameHeader_t));
        uint32_t data_index = sizeof(TbfpHeader_t) + sizeof(StorageFrameHeader_t);

        memset(&frame[data_index], 0x55, TEST_STORAGE_WRITE);

        uint16_t frame_len = payload_len + sizeof(TbfpHeader_t);
        frame[frame_len] = crc8_sae_j1850_calc(frame, frame_len);
        LOG_INFO(TBFP, "StoreWriteFrame:%s", ArrayToStr(frame, frame_len + 1));
        res = true;
    }
    return res;
}

bool tbfp_test_genegare_storage_read(uint8_t num, uint8_t* const frame) {
    bool res = false;
    TbfpHandle_t* Node = TbfpGetNode(num);
    if(Node) {
        LOG_INFO(TBFP, "%s", TbfpNode2Str(Node));
        uint16_t payload_len = (uint16_t)sizeof(StorageFrameHeader_t);
        LOG_INFO(TBFP, "PayLoadLen:%u byte", payload_len);
        TbfpHeader_t Header;
        frame[0] = Node->preamble_val;
        Header.preamble = Node->preamble_val;
        Header.flags.ack_need = 1;
        Header.flags.crc_check_need = 0;
        Header.flags.lifetime = 15;
        Header.payload_id = FRAME_ID_STORAGE;
        Header.snum = 0x00FF;
        Header.len = payload_len;
        memcpy(frame, &Header, sizeof(TbfpHeader_t));
        StorageFrameHeader_t StorageData;
        StorageData.operation = ACCESS_READ_ONLY;
        StorageData.address = 0x0;
        StorageData.asic_num = 1;
        StorageData.size = 32; /* Bytes to read */

        memcpy(&frame[sizeof(TbfpHeader_t)], &StorageData, sizeof(StorageFrameHeader_t));

        uint16_t frame_len = payload_len + sizeof(TbfpHeader_t);
        frame[frame_len] = crc8_sae_j1850_calc(frame, frame_len);
        LOG_INFO(TBFP, "StoreReadFrame:%s", ArrayToStr(frame, frame_len + 1));
        res = true;
    }
    return res;
}

/*
 tsr tbfp_storage_write
 * */
bool test_tbfp_storage_write(void) {
    bool res = true;
    LOG_DEBUG(TEST, "%s():", __FUNCTION__);
    set_log_level(TBFP, LOG_LEVEL_DEBUG);
    set_log_level(STORAGE, LOG_LEVEL_DEBUG);

    uint8_t StorageWrite[100] = {0};
    EXPECT_TRUE(tbfp_test_genegare_storage_write(1, StorageWrite));

#ifdef HAS_PC
    TbfpHandle_t* Node = TbfpInterfaceToNode(IF_STDIO);
    EXPECT_NE(0, Node);

    EXPECT_TRUE(tbfp_rx(StorageWrite, sizeof(StorageWrite), IF_STDIO));
    set_log_level(TBFP, LOG_LEVEL_INFO);
    set_log_level(STORAGE, LOG_LEVEL_INFO);
#endif
    return res;
}

/*
 tsr tbfp_storage_read
 */
bool test_tbfp_storage_read(void) {
    bool res = true;
    LOG_DEBUG(TEST, "%s():", __FUNCTION__);
    set_log_level(TBFP, LOG_LEVEL_DEBUG);
    set_log_level(STORAGE, LOG_LEVEL_DEBUG);

    uint8_t StorageRead[100] = {0};
    EXPECT_TRUE(tbfp_test_genegare_storage_read(1, StorageRead));

#ifdef HAS_PC
    TbfpHandle_t* Node = TbfpInterfaceToNode(IF_STDIO);
    EXPECT_NE(0, Node);

    EXPECT_TRUE(tbfp_rx(StorageRead, sizeof(StorageRead), IF_STDIO));
    set_log_level(TBFP, LOG_LEVEL_INFO);
    set_log_level(STORAGE, LOG_LEVEL_INFO);
#endif
    return res;
}
