#ifndef DMA_MCAL_TYPES_H
#define DMA_MCAL_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dma_const.h"

#ifdef HAS_DMA_CUSTOM
#include "dma_custom_types.h"
#else
#define DMA_CUSTOM_TYPES
#endif





#define DMA_COMMON_VARIABLES     \
    uint8_t num;                 \
    uint8_t dma_num;             \
    char* name;                  \
    bool valid;


typedef struct {
    DMA_COMMON_VARIABLES
} DmaConfig_t;

typedef struct {
    DMA_COMMON_VARIABLES
    DMA_CUSTOM_TYPES
    bool init;
} DmaHandle_t;


 



#ifdef __cplusplus
}
#endif

#endif /* DMA_MCAL_TYPES_H  */
