#ifndef SDIO_CUSTOM_TYPES_H
#define SDIO_CUSTOM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "microcontroller.h"
#include "sdio_custom_const.h"

typedef union {
    uint8_t byte;
    struct {
        uint8_t m : 4; /**/
        uint8_t n : 4; /**/
    };
}ProdRev_t;

#define SDIO_CUSTOM_TYPES                        \
    SDIO_TypeDef* SDIOx;                         \
    SD_HandleTypeDef Handle;                     \
    HAL_SD_CardCSDTypeDef CSD;                   \
    HAL_SD_CardCIDTypeDef CID ;                  \
    HAL_SD_CardStatusTypeDef status;             \
    HAL_SD_CardStateTypeDef SD_CardState;        \
    HAL_SD_CardInfoTypeDef CardInfo;

typedef union {
    uint16_t word;
    struct {
        uint8_t month : 4;/**/
        uint8_t year : 8; /**/
    };
}ManufDate_t;

typedef struct  {
    uint8_t num;
    SDIO_TypeDef* SDIOx;
    bool valid;
    IRQn_Type irq_n;
}SdioInfo_t;

#ifdef __cplusplus
}
#endif

#endif /* SDIO_CUSTOM_TYPES_H  */
