#ifndef TEST_SDIO_H
#define TEST_SDIO_H

#include <stdbool.h>
#include <stdint.h>

#include "test_hw_dep_check.h"

bool test_sdio_read_write(void);
bool test_sdio_read(void);
bool test_sdio_const(void);
bool test_sdio_link(void);

#ifdef HAS_SDIO_INTERRUPT
bool test_sdio_read_it(void);
bool test_sdio_write_it(void);

#define TEST_SUIT_SDIO_IT {"SdioReadIt", test_sdio_read_it}, {"SdioWriteIt", test_sdio_write_it},
#else
#define TEST_SUIT_SDIO_IT
#endif

#ifdef HAS_SDIO_DMA
bool test_sdio_read_dma(void);
bool test_sdio_write_dma(void);
#define TEST_SUIT_SDIO_DMA {"SdioReadDma", test_sdio_read_dma}, {"SdioWriteDma", test_sdio_write_dma},
#else
#define TEST_SUIT_SDIO_DMA
#endif

#define TEST_SUIT_SDIO                     \
    {"sdio_const", test_sdio_const},       \
    {"sdio_read", test_sdio_read},                     \
    {"sdio_read_write", test_sdio_read_write},     \
    TEST_SUIT_SDIO_DMA      \
	TEST_SUIT_SDIO_IT

#endif /* TEST_SDIO_H */
