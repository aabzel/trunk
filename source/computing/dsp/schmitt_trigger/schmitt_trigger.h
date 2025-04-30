#ifndef SCHMITT_TRIGGER_DRIVER_H
#define SCHMITT_TRIGGER_DRIVER_H

#include "std_includes.h"
#include "schmitt_trigger_config.h"
#include "schmitt_trigger_types.h"
#include "schmitt_trigger_diag.h"

SchmittTriggerState_t schmitt_trigger_get_state(uint8_t num);
bool schmitt_trigger_set_val(uint8_t num, double val);
bool schmitt_trigger_proc_val(uint8_t num, double val);
bool schmitt_trigger_proc_val_ll(SchmittTriggerHandle_t* const Node, double val);
bool schmitt_trigger_proc(void);
bool schmitt_trigger_mcal_init(void);
const SchmittTriggerConfig_t* SchmittTriggerGetConfig(uint8_t num);
SchmittTriggerHandle_t* SchmittTriggerGetNode(uint8_t num);

#endif /* SCHMITT_TRIGGER_DRIVER_H  */
