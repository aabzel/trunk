#include "test_dma.h"

#include <string.h>

#include "array.h"
//#include "clock.h"
#include "dma_mcal.h"
#include "time_mcal.h"
#include "unit_test_check.h"
#include "dma_channel_mcal.h"

#ifdef HAS_DMA_CHANNEL
#include "dma_channel_mcal.h"
#endif

bool test_dma_types(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
#if 0
    ASSERT_EQ(4, sizeof(DmaLowIntStatusReg_t));
    ASSERT_EQ(4, sizeof(DmaHighIntStatusReg_t));
    ASSERT_EQ(4, sizeof(DmaLowIntFlagClearReg_t));
    ASSERT_EQ(4, sizeof(DmaHighIntFlagClearReg_t));
    
    ASSERT_EQ(1, sizeof(DmaStreamClearIntReg_t));
    ASSERT_EQ(1, sizeof(DmaStreamIntStatusReg_t));
#endif

    return true;
}

static bool test_dma_memcpy_custom(uint8_t dma_num, uint8_t stream ,uint8_t channel) {
    LOG_INFO(TEST, "%s(): DMA%u_Steam_%u_CH%u", __FUNCTION__, dma_num, stream ,channel);
    // log_level_get_set(ARRAY, LOG_LEVEL_DEBUG);
#ifdef HAS_DMA_CHANNEL
    volatile uint8_t destination[TEST_DMA_SIZE] = {0};
    volatile uint8_t source[TEST_DMA_SIZE] = {0};
    memset(destination, 0xFF, sizeof(destination));

    ASSERT_TRUE(array_incr(source, sizeof(source), 0));

    ASSERT_TRUE(dma_memcpy_custom_ll(destination, source, sizeof(source), dma_num, stream, channel));

    ASSERT_TRUE(wait_in_loop_ms(1));

    ASSERT_TRUE(array_is_equal(source, destination, sizeof(source)));

#endif
    return true;
}


bool test_dma_memcpy_base(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
#ifdef HAS_DMA_CHANNEL
    volatile uint8_t destination[TEST_DMA_SIZE] = {0};
    volatile uint8_t source[TEST_DMA_SIZE] = {0};
    memset(source, 0x44, sizeof(source));
    memset(destination, 0xFF, sizeof(destination));

    ASSERT_TRUE(array_incr(source, sizeof(source), 0));

    ASSERT_TRUE(dma_memcpy(destination, source, sizeof(source) ) );

    ASSERT_TRUE(wait_in_loop_ms(1));

    ASSERT_TRUE(array_is_equal(source, destination, sizeof(source)));

#endif
    return true;
}


static bool test_dma_memcpy(uint8_t dma_num, uint8_t stream, uint8_t channel) {
    LOG_INFO(TEST, "%s():DMA%u_Stream_%u_Channel_%u", __FUNCTION__, dma_num,stream, channel);
#ifdef HAS_DMA_CHANNEL
    volatile uint8_t destination[TEST_DMA_SIZE] = {0};
    volatile uint8_t source[TEST_DMA_SIZE / 2] = {0};
    memset(destination, 0, sizeof(destination));

    ASSERT_TRUE(array_incr(source, sizeof(source), 0));

    ASSERT_TRUE(dma_memcpy_ll(destination, source, sizeof(source), dma_num, stream, channel));

    ASSERT_TRUE(wait_in_loop_ms(1));

    ASSERT_TRUE(array_is_equal(source, destination, sizeof(source)));
    log_level_get_set(ARRAY, LOG_LEVEL_INFO);
#endif

    return true;
}

bool test_dma_memcpy_all(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;

    uint32_t cnt = dma_channel_spare_get_cnt();
    uint8_t i = 0;
    for (i = 0; i < cnt; i++) {
        EXPECT_TRUE(
                test_dma_memcpy(DmaSpareChannels[i].dma_num,
                                DmaSpareChannels[i].stream,
                                DmaSpareChannels[i].channel));
    }
    return res;
}
// tr dma_memcpy_custom_all
bool test_dma_memcpy_custom_all(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    uint32_t cnt = dma_channel_spare_get_cnt();
    uint8_t i = 0;
    for (i = 0; i < cnt; i++) {
        EXPECT_TRUE(
                test_dma_memcpy_custom(DmaSpareChannels[i].dma_num,
                                       DmaSpareChannels[i].stream,
                                       DmaSpareChannels[i].channel));
    }
    return res;
}
