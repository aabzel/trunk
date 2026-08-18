#ifndef RS2058_DRV_H
#define RS2058_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "rs2058_config.h"
#include "rs2058_dep.h"
#include "rs2058_types.h"

const Rs2058Config_t* Rs2058GetConfig(uint8_t num);
Rs2058Item_t* Rs2058GetNode(uint8_t num);
bool rs2058_ctrl(uint8_t chip_num, uint8_t mux_num, uint8_t state);
bool rs2058_init(void);
bool rs2058_proc(void);
bool rs2058_set(const Rs2058Sw_t* const Node);
Rs2058State_t Rs20582LogLev2State(GpioLogicLevel_t logic_lev);

#endif /* RS2058_DRV_H */
