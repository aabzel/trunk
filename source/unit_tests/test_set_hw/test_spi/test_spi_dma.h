#ifndef TEST_SPI_DMA_H
#define TEST_SPI_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "test_hw_dep_check.h"
#include "std_includes.h"

#ifndef HAS_SPI_DMA
#error "+HAS_SPI_DMA"
#endif

bool test_spi_dma_write(uint8_t num) ;
bool test_spi_dma_read(uint8_t num);
bool test_spi_dma_write_read(uint8_t num);
bool test_spi_dma_loopback_num(uint8_t num);

#ifdef HAS_SPI1
bool test_spi1_write_dma(void);
bool test_spi1_read_dma(void);
bool test_spi1_write_read_dma(void);

#define TEST_SUIT_SPI1_DMA                                           \
           {"spi1_write_dma", test_spi1_write_dma},                  \
           {"spi1_read_dma", test_spi1_read_dma},                    \
           {"spi1_write_read_dma", test_spi1_write_read_dma},

#else
#define TEST_SUIT_SPI1_DMA
#endif


#ifdef HAS_SPI2
bool test_spi2_write_dma(void);
bool test_spi2_read_dma(void);
bool test_spi2_write_read_dma(void);
bool test_spi2_dma_loopback(void);

#define TEST_SUIT_SPI2_DMA                                           \
           {"spi2_dma_write", test_spi2_write_dma},                  \
           {.name = "spi2_dma_loopback", .utest_func = test_spi2_dma_loopback, .integration = true},            \
           {"spi2_dma_read", test_spi2_read_dma},                    \
           {"spi2_dma_write_read", test_spi2_write_read_dma},

#else
#define TEST_SUIT_SPI2_DMA
#endif

#ifdef HAS_SPI3

bool test_spi3_write_dma(void);
bool test_spi3_read_dma(void);
bool test_spi3_write_read_dma(void);

#define TEST_SUIT_SPI3_DMA                                           \
           {"spi3_write_dma", test_spi3_write_dma},                  \
           {"spi3_read_dma", test_spi3_read_dma},                    \
           {"spi3_write_read_dma", test_spi3_write_read_dma},

#else
#define TEST_SUIT_SPI3_DMA
#endif

#ifdef HAS_SPI4
bool test_spi4_write_dma(void);
bool test_spi4_read_dma(void);
bool test_spi4_write_read_dma(void);

#define TEST_SUIT_SPI4_DMA                                           \
           {"spi4_write_dma", test_spi4_write_dma},                  \
           {"spi4_read_dma", test_spi4_read_dma},                    \
           {"spi4_write_read_dma", test_spi4_write_read_dma},

#else
#define TEST_SUIT_SPI4_DMA
#endif

#ifdef HAS_SPI5
bool test_spi5_write_dma(void);
bool test_spi5_read_dma(void);
bool test_spi5_write_read_dma(void);

#define TEST_SUIT_SPI5_DMA                                           \
           {"spi5_write_dma", test_spi5_write_dma},                  \
           {"spi5_read_dma", test_spi5_read_dma},                    \
           {"spi5_write_read_dma", test_spi5_write_read_dma},

#else
#define TEST_SUIT_SPI5_DMA
#endif

#define TEST_SUIT_SPI_DMA    \
        TEST_SUIT_SPI1_DMA   \
        TEST_SUIT_SPI2_DMA   \
        TEST_SUIT_SPI3_DMA   \
        TEST_SUIT_SPI4_DMA   \
        TEST_SUIT_SPI5_DMA

#ifdef __cplusplus
}
#endif

#endif /* TEST_SPI_DMA_H */
