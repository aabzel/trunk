#ifndef DAC_CUSTOM_CONST_H
#define DAC_CUSTOM_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define DAC_TIMEOUT 0xFFFFFFFF
#define DAC_CHECK_TIMEOUT 0x7FFF


#define DAC_ALL_INT (DAC_TD_INT|DAC_RD_INT|DAC_ADDR_INT|DAC_ACKFIAL_INT|DAC_STOP_INT|DAC_TDC_INT|DAC_ERR_INT)


typedef enum {
    DAC_MODE_DAC=0,
    DAC_MODE_SMBUS=1,
}DacMode_t;

typedef enum {
    DAC_BUS_ROLE_SLAVE=0,
    DAC_BUS_ROLE_MASTER=1,
}DacBusRole_t;

typedef enum {
    DAC_BUS_STATE_SPARE = 0,
    DAC_BUS_STATE_BUSY = 1,
}DacBusState_t;

typedef enum {
    DAC_DIR_RX = 0,
    DAC_DIR_TX = 1,
}DacDir_t;

#ifdef __cplusplus
}
#endif

#endif /* DAC_CUSTOM_CONST_H */
