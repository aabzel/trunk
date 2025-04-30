#include "test_ds_twr.h"

#include <inttypes.h>
#include <stdint.h>
#include <string.h>

#include "data_utils.h"
#include "ds_twr.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "physics_const.h"
#include "unit_test_check.h"

bool test_ds_twr_const(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    LOG_INFO(DS_TWR, "TimerClock %llu Hz", DsTwrItem.timer_clock);
    ASSERT_EQ_U64(64000000000, DsTwrItem.timer_clock);
    ASSERT_EQ_DOUBLE(299702547.0, SPEED_OF_LIGHT_MPS);
    return true;
}

bool test_ds_twr_types(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_EQ(4, sizeof(uint32_t));
    ASSERT_EQ(8, sizeof(uint64_t));
    ASSERT_EQ(8, sizeof(double));
    // ASSERT_EQ(9, sizeof(PollPayload_t));
    ASSERT_EQ(16, sizeof(ResponderTiming_t));
    return true;
}

#define PROC_TIME_MS 50

#define TEST_TOF 20
#define T_DELAY 50
#define TIME_STAMP_DELAY 10

#define INITIATOR_T_DELAY T_DELAY
#define INITIATOR_T_LOOP_TIME (TEST_TOF + RESPONDER_T_DELAY_TIME + TEST_TOF)

#define RESPONDER_T_DELAY_TIME T_DELAY
#define RESPONDER_T_LOOP_TIME (TEST_TOF + RESPONDER_T_DELAY_TIME + TEST_TOF)

#define INITIATOR_TX_TIME1 1
#define INITIATOR_RX_TIME1 (INITIATOR_TX_TIME1 + 2 * TEST_TOF + RESPONDER_T_DELAY_TIME)
#define INITIATOR_TX_TIME2 (INITIATOR_RX_TIME1 + INITIATOR_T_DELAY)
#define INITIATOR_RX_TIME2 (INITIATOR_TX_TIME2 + (2 * TEST_TOF + RESPONDER_T_DELAY_TIME))

#define RESPONDER_RX_TIME1 (TEST_TOF + INITIATOR_TX_TIME1)
#define RESPONDER_TX_TIME1 (RESPONDER_RX_TIME1 + RESPONDER_T_DELAY_TIME)
#define RESPONDER_RX_TIME2 (INITIATOR_TX_TIME1 + TEST_TOF + RESPONDER_T_DELAY_TIME + RESPONDER_T_LOOP_TIME)
#define RESPONDER_TX_TIME2 (RESPONDER_RX_TIME2 + RESPONDER_T_DELAY_TIME)

bool test_ds_twr_initiator(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    Interfaces_t orig_interface = DsTwrItem.interface;
    DsTwrItem.interface = IF_BLACK_HOLE;

    bool res = true;
    set_log_level(DS_TWR, LOG_LEVEL_DEBUG);
    set_log_level(TBFP, LOG_LEVEL_DEBUG);
    set_log_level(SUPER_CYCLE, LOG_LEVEL_DEBUG);
    ASSERT_TRUE(ds_twr_reset(&DsTwrItem));
    ASSERT_EQ(DS_TWR_IDLE, DsTwrItem.state);

    ASSERT_TRUE(ds_twr_start(&DsTwrItem));
    ASSERT_TRUE(wait_in_loop_ms(PROC_TIME_MS));
    ASSERT_EQ(DS_TWR_INITIATOR_LOOP, DsTwrItem.state);

    ASSERT_TRUE(ds_twr_proc_tx_time(&DsTwrItem, INITIATOR_TX_TIME1)); // Tx
    ASSERT_TRUE(wait_in_loop_ms(PROC_TIME_MS));

    ASSERT_EQ(INITIATOR_TX_TIME1, DsTwrItem.initiator.tx_stamp);

    ASSERT_EQ(DS_TWR_INITIATOR_LOOP, DsTwrItem.state);

    DsTwrItem.start_ms = time_get_ms32();
    // SignalRxResp+Poll
    ASSERT_TRUE(fifo_push(&DsTwrItem.InputFifo, DS_TWR_INPUT_RX_PESPONSE_POLL));
    ASSERT_TRUE(wait_in_loop_ms(PROC_TIME_MS));
    ASSERT_EQ(DS_TWR_INITIATOR_LOOP, DsTwrItem.state);

    ASSERT_TRUE(ds_twr_proc_rx_time(&DsTwrItem, INITIATOR_RX_TIME1)); // Rx
    ASSERT_TRUE(wait_in_loop_ms(PROC_TIME_MS));

    ASSERT_EQ(INITIATOR_RX_TIME1, DsTwrItem.initiator.rx_stamp);
    ASSERT_EQ_U64(INITIATOR_T_LOOP_TIME, DsTwrItem.initiator.t_loop);

    ASSERT_TRUE(ds_twr_proc_tx_time(&DsTwrItem, INITIATOR_TX_TIME2)); // tx
    ASSERT_TRUE(wait_in_loop_ms(PROC_TIME_MS));
    ASSERT_EQ_U64(INITIATOR_T_DELAY, DsTwrItem.initiator.t_delay);

    ASSERT_EQ(DS_TWR_INITIATOR_WAIT_TIMING, DsTwrItem.state);
    // SignalRxTimings

    DsTwrItem.responder.t_delay = RESPONDER_T_DELAY_TIME;
    DsTwrItem.responder.t_loop = RESPONDER_T_LOOP_TIME;
    DsTwrItem.start_ms = time_get_ms32();
    ASSERT_TRUE(fifo_push(&DsTwrItem.InputFifo, DS_TWR_INPUT_RX_PESPONDER_TIMINGS));

    ASSERT_TRUE(wait_in_loop_ms(PROC_TIME_MS));
    ASSERT_TRUE(ds_twr_proc_rx_time(&DsTwrItem, INITIATOR_RX_TIME2)); // rx

    ASSERT_TRUE(wait_in_loop_ms(PROC_TIME_MS));

    ASSERT_EQ(DS_TWR_IDLE, DsTwrItem.state);

    DsTwrItem.interface = orig_interface;

    set_log_level(TEST, LOG_LEVEL_INFO);
    set_log_level(DS_TWR, LOG_LEVEL_INFO);
    set_log_level(TBFP, LOG_LEVEL_INFO);
    set_log_level(SUPER_CYCLE, LOG_LEVEL_INFO);
    return res;
}

bool test_ds_twr_responder(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    Interfaces_t orig_interface = DsTwrItem.interface;
    bool res = true;
    DsTwrItem.interface = IF_BLACK_HOLE;
    // set_log_level(DS_TWR, LOG_LEVEL_DEBUG);
    set_log_level(DS_TWR, LOG_LEVEL_PARANOID);
    set_log_level(TBFP, LOG_LEVEL_DEBUG);

    ASSERT_TRUE(ds_twr_reset(&DsTwrItem));

    DsTwrItem.start_ms = time_get_ms32();
    LOG_DEBUG(TBFP, "SignalRxPoll in State %s", DsTwrState2Str(DsTwrItem.state));
    EXPECT_TRUE(fifo_push(&DsTwrItem.InputFifo, DS_TWR_INPUT_RX_POLL));
    EXPECT_TRUE(wait_in_loop_ms(PROC_TIME_MS));

    EXPECT_TRUE(ds_twr_proc_rx_time(&DsTwrItem, RESPONDER_RX_TIME1)); // Rx
    EXPECT_TRUE(wait_in_loop_ms(PROC_TIME_MS));

    EXPECT_EQ_U64(RESPONDER_RX_TIME1, DsTwrItem.responder.rx_stamp);
    EXPECT_EQ(DS_TWR_RESPONDER_DELAY, DsTwrItem.state);

    EXPECT_TRUE(ds_twr_proc_tx_time(&DsTwrItem, RESPONDER_TX_TIME1)); // Tx
    EXPECT_TRUE(wait_in_loop_ms(PROC_TIME_MS));

    EXPECT_EQ_U64(RESPONDER_TX_TIME1, DsTwrItem.responder.tx_stamp);
    EXPECT_EQ_U64(RESPONDER_T_DELAY_TIME, DsTwrItem.responder.t_delay);

    EXPECT_EQ(DS_TWR_RESPONDER_LOOP, DsTwrItem.state);

    DsTwrItem.start_ms = time_get_ms32();
    LOG_DEBUG(TBFP, "SignalRxResp in State %s", DsTwrState2Str(DsTwrItem.state));
    // uint64_t initiator_t_loop = INITIATOR_T_LOOP_TIME;
    // EXPECT_TRUE(ds_twr_parse_pesponse(&DsTwrItem, (uint8_t*)&initiator_t_loop, 8));
    DsTwrItem.initiator.t_loop = INITIATOR_T_LOOP_TIME;
    EXPECT_TRUE(fifo_push(&DsTwrItem.InputFifo, DS_TWR_INPUT_RX_RESPONSE));

    EXPECT_TRUE(wait_in_loop_ms(PROC_TIME_MS));

    EXPECT_TRUE(ds_twr_proc_rx_time(&DsTwrItem, RESPONDER_RX_TIME2)); // Rx
    EXPECT_TRUE(wait_in_loop_ms(PROC_TIME_MS));
    EXPECT_EQ_U64(RESPONDER_T_LOOP_TIME, DsTwrItem.responder.t_loop);

    EXPECT_TRUE(ds_twr_proc_tx_time(&DsTwrItem, RESPONDER_TX_TIME2)); // Tx
    EXPECT_TRUE(wait_in_loop_ms(PROC_TIME_MS));

    EXPECT_EQ(DS_TWR_IDLE, DsTwrItem.state);

    set_log_level(DS_TWR, LOG_LEVEL_INFO);
    set_log_level(TBFP, LOG_LEVEL_INFO);
    DsTwrItem.interface = orig_interface;
    return res;
}

bool test_ds_twr_responder_poll(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(DS_TWR, LOG_LEVEL_PARANOID);
    set_log_level(TBFP, LOG_LEVEL_PARANOID);

    Interfaces_t orig_interface = DsTwrItem.interface;
    DsTwrItem.interface = IF_BLACK_HOLE;

    ASSERT_TRUE(ds_twr_reset(&DsTwrItem));

    DsTwrItem.start_ms = time_get_ms32();
    LOG_DEBUG(TBFP, "SignalRxPoll in State %s", DsTwrState2Str(DsTwrItem.state));
    ASSERT_TRUE(fifo_push(&DsTwrItem.InputFifo, DS_TWR_INPUT_RX_POLL));
    ASSERT_TRUE(wait_in_loop_ms(PROC_TIME_MS));
    ASSERT_EQ(DS_TWR_IDLE, DsTwrItem.state);

    ASSERT_TRUE(ds_twr_proc_rx_time(&DsTwrItem, RESPONDER_RX_TIME1)); // Rx
    ASSERT_TRUE(wait_in_loop_ms(PROC_TIME_MS));
    ASSERT_EQ_U64(RESPONDER_RX_TIME1, DsTwrItem.responder.rx_stamp);
    ASSERT_EQ(DS_TWR_RESPONDER_DELAY, DsTwrItem.state);

    set_log_level(DS_TWR, LOG_LEVEL_INFO);
    set_log_level(TBFP, LOG_LEVEL_INFO);
    ASSERT_TRUE(ds_twr_reset(&DsTwrItem));

    DsTwrItem.interface = orig_interface;
    return res;
}
