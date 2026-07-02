#ifndef TEST_DMA_H
#define TEST_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "test_hw_dep_check.h"

#define TEST_DMA_SIZE 80

bool test_dma_types(void);
bool test_dma_memcpy_base(void);
bool test_dma_memcpy_all(void);
bool test_dma_memcpy_custom_all(void);

#define TEST_SUIT_DMA                               \
    {"dma_types", test_dma_types},                  \
    {"dma_memcpy_base", test_dma_memcpy_base},      \
    {"dma_memcpy_all", test_dma_memcpy_all},        \
    {"dma_memcpy_custom_all", test_dma_memcpy_custom_all},
 
#ifdef __cplusplus
}
#endif

#endif /* TEST_DMA_H */
