#ifndef AXP192_TYPES_H
#define AXP192_TYPES_H

#include <stdint.h>

typedef union uChargeControl_t{
      uint8_t byte;
      struct {
          uint8_t internal_path_charge_current_setting:4; /*bits 0-3*/
          uint8_t Endofcharge_current_setting:1; /*bit 4*/
          uint8_t target_voltage_setting:2;      /*bits 5-6*/
          uint8_t enable :1;                     /*bit 8*/
      };
} ChargeControl_t;


#endif /* AXP192_TYPES_H  */
