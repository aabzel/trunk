#include "test_i2s.h"

#include <string.h>

#include "array.h"
#include "log.h"
#include "debug_info.h"
#include "i2s_drv.h"
#include "none_blocking_pause.h"
#ifdef HAS_SW_DAC
#include "sw_dac_drv.h"
#include "sw_dac_diag.h"
#endif /*HAS_SW_DAC*/
#include "sys_config.h"
#include "data_utils.h"
#include "unit_test_check.h"

static uint8_t array_rx[I2S_TEST_BLOCK_SIZE];
static uint8_t array_tx[I2S_TEST_BLOCK_SIZE];
static uint16_t array_u16_tx[I2S_TEST_BLOCK_SIZE];

/*
 That test requires some I2S slave on the other end of I2S bus*/
bool test_i2s_read_one(uint8_t num) {
    LOG_INFO(I2S, "%s()", __FUNCTION__);
    bool res = true;
    memset(array_rx, 0, sizeof(array_rx));
    memset(array_tx, 0x55, sizeof(array_tx));

    uint32_t sum = arr_sum(array_rx, sizeof(array_rx));
    ASSERT_EQ(0, sum);

    I2sHandle_t* I2sNode = I2sGetNode(num);
    ASSERT_NE(NULL, I2sNode);
	I2sNode->cur_rx_track=0;
	I2sNode->cur_tx_track=0;
	I2sNode->it_cnt=0;
    uint8_t i = 0;
    for(i=0; i<2; i++) {
#ifdef HAS_NRFX_I2S
        I2sNode->i2s_buffers[i].p_rx_buffer = (uint32_t* ) array_rx;
        I2sNode->i2s_buffers[i].p_tx_buffer = (uint32_t* ) array_tx;
#endif
    }

    ASSERT_TRUE(i2s_api_start(num, I2S_TEST_BLOCK_SIZE / 4));
    ASSERT_TRUE(wait_in_loop_ms(1000));

    LOG_INFO(I2S, "RxArray: ");
    print_hex_buf(array_rx, sizeof(array_rx));

    sum = arr_sum(array_rx, sizeof(array_rx));
    EXPECT_GR(0, sum);

    ASSERT_TRUE(i2s_dma_stop(num));
    EXPECT_GR(0, I2sNode->it_cnt);

    return res;
}

bool test_i2s_types(void) {
    LOG_INFO(I2S, "%s()", __FUNCTION__);
    ASSERT_EQ(2, sizeof(I2s8BitSample_t));
    ASSERT_EQ(4, sizeof(I2sSample_t));
    ASSERT_EQ(4, sizeof(I2s16BitSample_t));
    ASSERT_EQ(8, sizeof(I2s32BitSample_t));
    ASSERT_EQ(8, sizeof(I2sRlSample_t));
    return true;
}

static bool test_i2s_write_single(uint8_t num) {
    LOG_INFO(I2S, "%s() I2sNum %u", __FUNCTION__, num);
    uint32_t s = 0;
    bool res = true;
    ASSERT_TRUE(i2s_dma_stop(num));

    ASSERT_TRUE(wait_in_loop_ms(100));
    for(s = 0; s < (I2S_TEST_BLOCK_SIZE); s += 4) {
        array_tx[s] = 0x87;
        array_tx[s + 1] = 0x65;
        array_tx[s + 2] = 0x43;
        array_tx[s + 3] = 0x21;
    }
    print_hex_buf(array_tx, I2S_TEST_BLOCK_SIZE);
    I2sHandle_t* I2sNode = I2sGetNode(0);
    ASSERT_NE(NULL, I2sNode);
    I2sNode->stop_needed = true;
    I2sNode->total_stop_cnt = 0;
    I2sNode->status_stop_cnt = 0;
    ASSERT_TRUE(wait_in_loop_ms(100));
    LOG_INFO(I2S, "Sample[0] 0x%08x", *((uint32_t*)&array_tx[0]));
    uint32_t frames = I2S_BYTES_TO_FRAMES(I2S_TEST_BLOCK_SIZE, I2S_SAMPLE_SIZE);
    LOG_INFO(I2S, "TxFrames %u", frames);
    ASSERT_TRUE(i2s_api_write(num,  ( SampleType_t* )array_tx, frames));
    ASSERT_TRUE(wait_in_loop_ms(100));

    EXPECT_GR(3, I2sNode->total_stop_cnt); /*Still uncertainly why 3*/
    EXPECT_GR(1, I2sNode->status_stop_cnt);

    ASSERT_TRUE(i2s_dma_stop(num));
    return res;
}

static bool test_i2s_write_toggle(uint8_t num) {
    LOG_INFO(I2S, "%s()", __FUNCTION__);
    static uint32_t array1[4] = {0x55555555, 0x55555555, 0x55555555, 0x55555555};
    static uint32_t array2[4] = {0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA};

    I2sHandle_t* I2sNode = I2sGetNode(0);
    ASSERT_NE(NULL, I2sNode);
    I2sNode->stop_needed = false;
    I2sNode->toggle_cnt = 0;

    ASSERT_TRUE(i2s_set_join_write(num, array1, array2));
    ASSERT_TRUE(i2s_api_write(num,( SampleType_t* ) array1, 4));
    /*See Data change on the logic analyzer*/
    ASSERT_TRUE(wait_in_loop_ms(1000));
    ASSERT_TRUE(i2s_dma_stop(num));
    ASSERT_GR(0, I2sNode->toggle_cnt);

    return true;
}

bool test_i2s_loopback_single(uint8_t num) {
    LOG_INFO(I2S, "%s()", __FUNCTION__);
    bool res = true;
    static uint32_t RxBuff[32];
    static uint32_t TxBuff[32];
    memset(RxBuff, 0, sizeof(RxBuff));
#if 0
    nrfx_i2s_uninit();
    ASSERT_TRUE( i2s_init_ll(num));
    nrfx_i2s_stop();
#endif

    ASSERT_TRUE(array_incr_u32(TxBuff, ARRAY_SIZE(TxBuff)));

    I2sHandle_t* I2sNode = I2sGetNode(num);
    ASSERT_NE(NULL, I2sNode);
    I2sNode->stop_needed = true;
    I2sNode->switch_needed = false;
    I2sNode->it_cnt = 0;
    I2sNode->total_stop_cnt = 0;
#ifdef HAS_NRFX_I2S
    I2sNode->i2s_buffers[0].p_rx_buffer = RxBuff;
    I2sNode->i2s_buffers[0].p_tx_buffer = TxBuff;
    I2sNode->i2s_buffers[1].p_rx_buffer = RxBuff;
    I2sNode->i2s_buffers[1].p_tx_buffer = TxBuff;
#endif

    ASSERT_TRUE(i2s_api_start(num, 16));

    ASSERT_TRUE(wait_in_loop_ms(1000));
    ASSERT_GR(0, I2sNode->it_cnt);
    EXPECT_GR(1, I2sNode->total_stop_cnt);

    ASSERT_EQ_MEM(RxBuff, TxBuff, 16 * sizeof(uint32_t));
    return res;
}

bool test_i2s_loopback_continuous(uint8_t num) {
    LOG_INFO(I2S, "%s()", __FUNCTION__);
    bool res = true;
    static uint32_t RxBuff[32];
    static uint32_t TxBuff[32];
    memset(RxBuff, 0, sizeof(RxBuff));
#if 0
    nrfx_i2s_uninit();
    ASSERT_TRUE( i2s_init_ll(num));
    nrfx_i2s_stop();
#endif
    ASSERT_TRUE(array_incr_u32(TxBuff, ARRAY_SIZE(TxBuff)));

    I2sHandle_t* I2sNode = I2sGetNode(num);
    ASSERT_NE(NULL, I2sNode);
    I2sNode->stop_needed = false;
    I2sNode->switch_needed = true;
    I2sNode->it_cnt = 0;
    I2sNode->total_stop_cnt = 0;
#ifdef HAS_NRFX_I2S
    I2sNode->i2s_buffers[0].p_rx_buffer = RxBuff;

    I2sNode->i2s_buffers[0].p_tx_buffer = TxBuff;
    I2sNode->i2s_buffers[1].p_tx_buffer = TxBuff;
    I2sNode->i2s_buffers[1].p_rx_buffer = RxBuff;

    nrfx_err_t ret = nrfx_i2s_next_buffers_set((nrfx_i2s_buffers_t const *) &(I2sNode->i2s_buffers[1]));
    EXPECT_EQ(NRFX_SUCCESS,ret);
#endif
    ASSERT_TRUE(i2s_api_start(num, 16));
    ASSERT_TRUE(wait_in_loop_ms(500));
#ifdef HAS_NRFX_I2S
    nrfx_i2s_stop();
#endif
    ASSERT_GR(0, I2sNode->it_cnt);

    ASSERT_EQ_MEM(RxBuff, TxBuff, 16 * sizeof(uint32_t));
    return res;
}

bool test_i2s_write_one_qword(uint8_t num) {
    LOG_INFO(I2S, "%s() I2sNum %u", __FUNCTION__, num);
    uint32_t s = 0;
    for(s = 0; s < ARRAY_SIZE(array_tx); s += 4) {
        array_tx[s] = 0x87;
        array_tx[s + 1] = 0x65;
        array_tx[s + 2] = 0x43;
        array_tx[s + 3] = 0x21;
    }
    print_hex_buf(array_tx, I2S_TEST_BLOCK_SIZE);
    LOG_INFO(I2S, "Sample[0] 0x%08x", *((uint32_t*)&array_tx[0]));
    ASSERT_TRUE(i2s_api_write(num,( SampleType_t* ) array_tx, I2S_TEST_BLOCK_SIZE / 4));
    ASSERT_TRUE(i2s_send(num, true));
    /*See Data change on the logic analyzer*/
    return true;
}

bool test_i2s_write_one_word(uint8_t num) {
    LOG_INFO(I2S, "%s() I2sNum %u", __FUNCTION__, num);
    uint32_t s = 0;
    for(s = 0; s < ARRAY_SIZE(array_u16_tx); s++) {
    	array_u16_tx[s ] = 0x4321;
    }
    LOG_INFO(I2S, "In Memory");
    print_hex_buf( (uint8_t*) array_u16_tx, 2);
    LOG_INFO(I2S, "Sample[0] 0x%04x",array_u16_tx[0]);
    ASSERT_TRUE(i2s_api_write(num, ( SampleType_t* )array_u16_tx, ARRAY_SIZE(array_u16_tx)));
    ASSERT_TRUE(i2s_send(num, true));
    /*See Data change on the logic analyzer*/
    return true;
}

#define TEST_AMPLITUDE 30000 /*30000 fits in 16bit*/
#define TEST_DAC_NUM 1

bool test_i2s_play_freq_com(uint8_t num, double freq, SampleType_t amp) {
    LOG_WARNING(I2S, CRLF CRLF "I2S%u PlayCon: Freq %f Hz Amp %u Num",num ,freq, amp);
    bool res = true;
    uint32_t fps = 0;
    ASSERT_GR(0.0, freq);
    ASSERT_GR(0, amp);
    fps = i2s_get_sample_rate(num);
    ASSERT_GR(0, fps);
    LOG_INFO(I2S, "SampleRate: %u Hz", fps);
    I2sHandle_t* I2sNode = I2sGetNode(num);
    ASSERT_NE(NULL, I2sNode);
    I2sNode->switch_needed = false;
#ifdef HAS_SW_DAC
    ASSERT_TRUE(sw_dac_set_sin(TEST_DAC_NUM, freq, amp, 0, (SampleType_t)0));
    ASSERT_TRUE(sw_dac_set_array(TEST_DAC_NUM, 1, 0));
    log_level_t ll = log_level_get(SW_DAC);
    if(LOG_LEVEL_DEBUG==ll){
        sw_dac_diag();
        ASSERT_TRUE(sw_dac_print_track(TEST_DAC_NUM));
    }
#else
    res = false;
#endif /*HAS_SW_DAC*/

    ASSERT_TRUE(i2s_play_tx(num, TEST_DAC_NUM, true));
    return res;
}

bool test_i2s_play_freq(uint8_t num, double freq, SampleType_t amp, uint32_t pause_ms) {
    LOG_INFO(I2S, "%s() I2S%u Freq: %f Hz Amp%u Dur:%u ms", __FUNCTION__,num,freq, amp,pause_ms);
    I2sHandle_t* I2sNode = I2sGetNode(0);
    ASSERT_NE(NULL, I2sNode);
    uint32_t orig_it_cnt = I2sNode->it_cnt;

    ASSERT_TRUE(test_i2s_play_freq_com(num, freq, amp));

    ASSERT_TRUE(wait_in_loop_ms(pause_ms));
    ASSERT_TRUE(i2s_dma_stop(num));

    LOG_INFO(I2S, "ItCnt: %d", I2sNode->it_cnt - orig_it_cnt);
    ASSERT_GR(orig_it_cnt, I2sNode->it_cnt);
    return true;
}

#ifdef HAS_I2S0
bool test_i2s0_loopback(void) {
    LOG_INFO(I2S, "%s()", __FUNCTION__);
    ASSERT_TRUE(test_i2s_loopback_single(0));
    return true;
}

bool test_i2s0_loopback_continuous(void) {
    LOG_INFO(I2S, "%s()", __FUNCTION__);
    ASSERT_TRUE(test_i2s_loopback_continuous(0));
    return true;
}

bool test_i2s0_write_single(void) {
    LOG_INFO(I2S, "%s()", __FUNCTION__);
    ASSERT_TRUE(test_i2s_write_single(0));
    return true;
}

bool test_i2s0_write_toggle(void) {
    LOG_INFO(I2S, "%s()", __FUNCTION__);
    ASSERT_TRUE(test_i2s_write_toggle(0));
    return true;
}

bool test_i2s0_play(void) {
    LOG_INFO(I2S, "%s():", __FUNCTION__);
    ASSERT_TRUE(test_i2s_play_freq(0, 500.0,TEST_AMPLITUDE, PLAY_DURATION));
    ASSERT_TRUE(test_i2s_play_freq(0, 1000.0,TEST_AMPLITUDE,PLAY_DURATION));
    ASSERT_TRUE(test_i2s_play_freq(0, 2000.0,TEST_AMPLITUDE,PLAY_DURATION));
    ASSERT_TRUE(test_i2s_play_freq(0, 4000.0,TEST_AMPLITUDE,PLAY_DURATION));
    ASSERT_TRUE(test_i2s_play_freq(0, 8000.0,TEST_AMPLITUDE,PLAY_DURATION));
    return true;
}

#define TEST_FREQ 500.0
bool test_i2s0_amplitude_play(void) {
    LOG_INFO(I2S, "%s():", __FUNCTION__);
    ASSERT_TRUE(test_i2s_play_freq(0, TEST_FREQ,50, PLAY_DURATION));
    ASSERT_TRUE(test_i2s_play_freq(0, TEST_FREQ,100, PLAY_DURATION));
    ASSERT_TRUE(test_i2s_play_freq(0, TEST_FREQ,5000, PLAY_DURATION));
    ASSERT_TRUE(test_i2s_play_freq(0, TEST_FREQ,10000,PLAY_DURATION));
    ASSERT_TRUE(test_i2s_play_freq(0, TEST_FREQ,20000,PLAY_DURATION));
    ASSERT_TRUE(test_i2s_play_freq(0, TEST_FREQ,30000,PLAY_DURATION));
    return true;
}

bool test_i2s0_write(void) {
    LOG_INFO(I2S, "%s()", __FUNCTION__);
    ASSERT_TRUE(test_i2s_write_one_qword(0))
    return true;
}

bool test_i2s0_write_word(void){
    LOG_INFO(I2S, "%s()", __FUNCTION__);
    ASSERT_TRUE(test_i2s_write_one_word(0))
    return true;
}


bool test_i2s0_read(void) {
    LOG_INFO(I2S, "%s()", __FUNCTION__);
    ASSERT_TRUE(test_i2s_read_one(0));
    return true;
}
#endif /*HAS_I2S0*/

#ifdef HAS_I2S1
bool test_i2s1_write(void) {
    LOG_INFO(I2S, "%s()", __FUNCTION__);
    ASSERT_TRUE(test_i2s_write_one(1));
    return true;
}
bool test_i2s1_read(void) {
    LOG_INFO(I2S, "%s()", __FUNCTION__);
    ASSERT_FALSE(i2s_api_read(1, array_rx, I2S_TEST_BLOCK_SIZE));
    return true;
}
#endif /*HAS_I2S1*/

#ifdef HAS_I2S2
bool test_i2s2_write(void) {
    LOG_INFO(I2S, "%s()", __FUNCTION__);
    ASSERT_TRUE(test_i2s_write_one_qword(2));
    return true;
}

bool test_i2s2_write_word(void) {
    LOG_INFO(I2S, "%s()", __FUNCTION__);
    ASSERT_TRUE(test_i2s_write_one_word(2));
    return true;
}

bool test_i2s2_read(void) {
    LOG_INFO(I2S, "%s()", __FUNCTION__);
    ASSERT_FALSE(i2s_api_read(2, array_rx, I2S_TEST_BLOCK_SIZE));
    return true;
}
#endif /*HAS_I2S2*/

#ifdef HAS_I2S3
bool test_i2s3_write(void) {
    LOG_INFO(I2S, "%s()", __FUNCTION__);
    ASSERT_TRUE(test_i2s_write_one(3));
    return true;
}
bool test_i2s3_read(void) {
    LOG_INFO(I2S, "%s()", __FUNCTION__);
    ASSERT_FALSE(i2s_api_read(3, array_rx, I2S_TEST_BLOCK_SIZE));
    return true;
}
#endif /*HAS_I2S3*/
