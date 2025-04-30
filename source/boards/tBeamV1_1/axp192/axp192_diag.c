#include "axp192_diag.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "axp192_types.h"

bool axp192_parse_reg33(uint8_t byte){
    bool res = true;
    ChargeControl_t Reg;
    Reg.byte=byte;
    printf("\n\r internal_path_charge_current_setting %u",Reg.internal_path_charge_current_setting);
    printf("\n\r Endofcharge_current_setting %u",Reg.Endofcharge_current_setting);
    printf("\n\r target_voltage_setting %u",Reg.target_voltage_setting);
    printf("\n\r enable %u",Reg.enable);
    return res;
}
