#ifndef TEST_DMA_H
#define TEST_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "test_hw_dep_check.h"

bool test_dma_types(void);

#define TEST_SUIT_DMA                     \
    {"dmaType", test_dma_types},      
 
#ifdef __cplusplus
}
#endif

#endif /* TEST_DMA_H */
