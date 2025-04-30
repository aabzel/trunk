#ifndef SDIO_GENERAL_CONST_H
#define SDIO_GENERAL_CONST_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "sdio_dep.h"

#define SDIO_READ_TRY_CNT 8
#define SDIO_WRITE_TRY_CNT 8
#define SDIO_NAME_SIZE_BYTE 30
#define SDIO_BLOCK_SIZE 512U

#ifndef HAS_SDIO
#error "+HAS_SDIO"
#endif

#ifdef __cplusplus
}
#endif

#endif /* SDIO_GENERAL_CONST_H */
