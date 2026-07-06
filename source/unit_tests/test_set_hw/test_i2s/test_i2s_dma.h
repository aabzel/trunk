#ifndef TEST_I2S_DMA_H
#define TEST_I2S_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "test_hw_dep_check.h"

bool test_i2s_dma_done_read(uint8_t num);
bool test_i2s_dma_half_read(uint8_t num);
bool test_i2s_dma_half_write(uint8_t num);
bool test_i2s_dma_done_write(uint8_t num);


#ifdef HAS_I2S2
bool test_i2s2_dma_half_write(void);
bool test_i2s2_dma_done_write(void);

bool test_i2s2_dma_half_read(void);
bool test_i2s2_dma_done_read(void);

#define TEST_SUIT_I2S2_DMA_READ                             \
    {"i2s2_dma_half_read", test_i2s2_dma_half_read},        \
    {"i2s2_dma_done_read", test_i2s2_dma_done_read},

#define TEST_SUIT_I2S2_DMA_WRITE                            \
    {"i2s2_dma_half_write", test_i2s2_dma_half_write},      \
    {"i2s2_dma_done_write", test_i2s2_dma_done_write},

#define TEST_SUIT_I2S2_DMA           \
        TEST_SUIT_I2S2_DMA_READ      \
        TEST_SUIT_I2S2_DMA_WRITE

#else
#define TEST_SUIT_I2S2_DMA
#endif

#define TEST_SUIT_I2S_DMA    \
        TEST_SUIT_I2S2_DMA
 

 

#ifdef __cplusplus
}
#endif

#endif /* TEST_I2S_DMA_H */
