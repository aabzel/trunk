#ifndef SDIO_STM_ISR_H
#define SDIO_STM_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_SDIO
#error "+HAS_SDIO"
#endif

#ifndef HAS_SDIO_ISR
#error "+HAS_SDIO_ISR"
#endif

#ifndef HAS_DMA
#warning "+HAS_DMA"
#endif

#include "stm32f4xx.h"


#ifdef __cplusplus
}
#endif

#endif /* SDIO_STM_ISR_H */
