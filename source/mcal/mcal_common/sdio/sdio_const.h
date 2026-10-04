#ifndef SDIO_GENERAL_CONST_H
#define SDIO_GENERAL_CONST_H

#include "sdio_dep.h"

#define SDIO_READ_TRY_CNT 8
#define SDIO_WRITE_TRY_CNT 8
#define SDIO_NAME_SIZE_BYTE 30
#define SDIO_BLOCK_SIZE 512U

#define  SDIO_POLL_PERIOD_US 10000000

#ifndef HAS_SDIO
#error "+HAS_SDIO"
#endif

typedef enum {
    SDIO_BUS_RESOLUTION_UNDEF = 0,
    SDIO_BUS_RESOLUTION_1BIT = 1,
    SDIO_BUS_RESOLUTION_4BIT = 4,
}SdioBusResolution_t;

#endif /* SDIO_GENERAL_CONST_H */
