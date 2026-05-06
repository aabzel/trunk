#ifndef DECIMATOR_DRIVER_H
#define DECIMATOR_DRIVER_H

#include "std_includes.h"
#include "decimator_config.h"
#include "decimator_types.h"

#ifdef HAS_DECIMATOR_DIAG
#include "decimator_diag.h"
#endif

const DecimatorConfig_t* DecimatorGetConfig(uint8_t num);
DecimatorHandle_t* DecimatorGetNode(uint8_t num);

bool decimator_mcal_init(void);
bool decimator_init_one(uint8_t num);

bool decimator_adjust(uint8_t num, uint32_t samples_per_bit);
bool decimator_proc_val(uint8_t num, int8_t sample_in, int8_t* const sample_out);

DecimatorState_t decimator_get_state(uint8_t num);

#endif /* DECIMATOR_DRIVER_H  */
