#ifndef SPIFI_MIK_TYPES_H
#define SPIFI_MIK_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "spifi_custom_const.h"
#include "spifi_register_types.h"
#include "mik32_hal_spifi.h"
#include "microcontroller_const.h"
#include "spifi.h"

#define SPIFI_CUSTOM_VARIABLES     \
    SPIFI_HandleTypeDef Handle;    \
    SPIFI_CONFIG_TypeDef* SPIFIx;

typedef struct {
    bool valid;
    uint8_t num;
    SPIFI_CONFIG_TypeDef* SPIFIx;
    uint32_t clock_hz;
    //uint32_t interrupt_mask;
    IRQn_Type irq_n;
}SpiFiInfo_t;


#ifdef __cplusplus
}
#endif

#endif /* SPIFI_MIK_TYPES_H  */
