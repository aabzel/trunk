#ifndef SDIO_STM_TYPES_H
#define SDIO_STM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sdio_custom_const.h"

typedef union {
    uint8_t byte;
    struct {
        uint8_t m : 4; /**/
        uint8_t n : 4; /**/
    };
}ProdRev_t;

typedef union {
    uint16_t word;
    struct {
        uint8_t month : 4;/**/
        uint8_t year : 8; /**/
    };
}ManufDate_t;

#ifdef __cplusplus
}
#endif

#endif /* SDIO_STM_TYPES_H  */
