#ifndef SCHMITT_TRIGGER_DRIVER_H
#define SCHMITT_TRIGGER_DRIVER_H

#include "std_includes.h"
#include "schmitt_trigger_config.h"
#include "schmitt_trigger_types.h"

#ifdef HAS_SCHMITT_TRIGGER_DIAG
#include "schmitt_trigger_diag.h"
#endif

/*API*/
SchmittTriggerHandle_t* SchmittTriggerGetNode(uint8_t num);
const SchmittTriggerConfig_t* SchmittTriggerGetConfig(uint8_t num);
bool schmitt_trigger_init_node(SchmittTriggerHandle_t* const Node) ;
bool schmitt_trigger_mcal_init(void);
bool schmitt_trigger_init_one(uint8_t num);
bool schmitt_trigger_init_custom(void);
/*getter*/
SchmittTriggerState_t schmitt_trigger_get_state(uint8_t num);

/*setter*/
bool schmitt_trigger_set_val(uint8_t num, float val);
bool schmitt_trigger_proc_val(uint8_t num, float val);
bool schmitt_trigger_proc_val_ll(SchmittTriggerHandle_t* const Node, float val);
bool schmitt_trigger_proc(void);


#endif /* SCHMITT_TRIGGER_DRIVER_H  */
