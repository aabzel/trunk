#ifndef SCHMITT_TRIGGER_CONFIG_H
#define SCHMITT_TRIGGER_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "schmitt_trigger_types.h"

#ifndef HAS_SCHMITT_TRIGGER
#error "Add HAS_SCHMITT_TRIGGER"
#endif /*HAS_SCHMITT_TRIGGER*/

extern const SchmittTriggerConfig_t SchmittTriggerConfig[ ];
extern SchmittTrigger_t SchmittTriggerItem[ ];

uint32_t schmitt_trigger_get_cnt(void);

#endif /* SCHMITT_TRIGGER_CONFIG_H  */
