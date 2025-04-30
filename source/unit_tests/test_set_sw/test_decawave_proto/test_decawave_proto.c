#include "test_decawave_proto.h"

#include "decawave.h"
#include "log.h"
#include "system.h"
#include "unit_test_check.h"

bool test_decawave_types(void) {
    bool res = true;
    LOG_DEBUG(DECAWAVE, "%s():", __FUNCTION__);
    set_log_level(DECAWAVE, LOG_LEVEL_DEBUG);
    EXPECT_EQ(10, sizeof(DecaWaveHeader_t));
    EXPECT_EQ(DECAWAVE_HEADER_SIZE, sizeof(DecaWaveHeader_t));

    EXPECT_EQ(9, sizeof(PollPayload_t));
    EXPECT_EQ(1, sizeof(DwcaMess_t));
    EXPECT_EQ(1, sizeof(UwbRole_t));

    set_log_level(DECAWAVE, LOG_LEVEL_INFO);

    return res;
}

bool test_decawave_nodes(void) {
    bool res = true;
    LOG_DEBUG(DECAWAVE, "%s():", __FUNCTION__);
    set_log_level(DECAWAVE, LOG_LEVEL_DEBUG);

    EXPECT_NE(0, DecaWaveGetConfig(1));
    EXPECT_NE(0, DecaWaveGetNode(1));

    set_log_level(DECAWAVE, LOG_LEVEL_INFO);
    return res;
}

// static const uint8_t arr_empty[] = {0x41, 0x61, 0x01, 0x00, 0x0A, 0x00, 0x02, 0x00, 0x00, 0x00, 0x31, 0x4};

static const uint8_t arr_poll[] = {0x41, DECA_POLL, 0x01, 0x00, 0x0A, 0x00, 0x02, 0x00, 0x0A, 0x00, UWB_VAR_SHARE_DIST,
                                   0x0,  0x0,       0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x1,  0x31, 0x47};

static const uint8_t resp_poll[] = {0x41, DECA_RESP_POLL, 0x01, 0x00, 0x0A, 0x00, 0x02, 0x00, 0x00, 0x00, 0x36, 0x5f};

static const uint8_t arr_resp[] = {
    0x41, DECA_RESP, 0x01, 0x00, 0x0A, 0x00, 0x02, 0x00, 0x09, 0x00, UWB_VAR_INITIATOR_T_LOOP,
    0x01, 0x20,      0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x13, 0xed};

static const uint8_t arr_final[] = {
    0x41, DECA_FINAL, 0x01, 0x00, 0x0A, 0x00, 0x02, 0x00, 0x11, 0x00, UWB_VAR_RESPONDER_TIMINGS,
    0x01, 0x20,       0x2,  0x0,  0x0,  0x0,  0x0,  0x0, /*responer T Delay*/
    0x01, 0x10,       0x0,  0x22, 0x0,  0x0,  0x0,  0x0, /*responer  T loop*/
    0x30, 0xd6};

bool test_decawave_proc_final(void) {
    bool res = true;
    LOG_DEBUG(DECAWAVE, "%s():", __FUNCTION__);
    set_log_level(DECAWAVE, LOG_LEVEL_DEBUG);

    EXPECT_TRUE(decawave_proc(1, arr_final, sizeof(arr_final)));

    set_log_level(DECAWAVE, LOG_LEVEL_INFO);

    return res;
}

bool test_decawave_proc_resp(void) {
    bool res = true;
    LOG_DEBUG(DECAWAVE, "%s():", __FUNCTION__);
    set_log_level(DECAWAVE, LOG_LEVEL_DEBUG);

    EXPECT_TRUE(decawave_proc(1, arr_resp, sizeof(arr_resp)));

    set_log_level(DECAWAVE, LOG_LEVEL_INFO);

    return res;
}

bool test_decawave_proc_resp_poll(void) {
    bool res = true;
    LOG_DEBUG(DECAWAVE, "%s():", __FUNCTION__);
    set_log_level(DECAWAVE, LOG_LEVEL_DEBUG);
    EXPECT_TRUE(decawave_proc(1, resp_poll, sizeof(resp_poll)));
    set_log_level(DECAWAVE, LOG_LEVEL_INFO);
    return res;
}

bool test_decawave_proc_poll(void) {
    bool res = true;
    LOG_DEBUG(DECAWAVE, "%s():", __FUNCTION__);
    set_log_level(DECAWAVE, LOG_LEVEL_DEBUG);

    EXPECT_TRUE(decawave_proc(1, arr_poll, sizeof(arr_poll)));

    set_log_level(DECAWAVE, LOG_LEVEL_INFO);

    return res;
}
