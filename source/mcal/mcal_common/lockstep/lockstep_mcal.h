#ifndef LOCKSTEP_MCAL_H
#define LOCKSTEP_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "lockstep_config.h"
#include "lockstep_isr.h"
#include "lockstep_types.h"
//#include "multicore_const.h"
#ifdef HAS_LOCKSTEP_CUSTOM
#include "lockstep_custom.h"
#endif

#ifdef HAS_LOCKSTEP_DIAG
#include "lockstep_diag.h"
#endif

/*API*/
const LockStepConfig_t* LockStepGetConfig(uint8_t num);
const LockStepInfo_t* LockStepGetInfo(uint8_t num);
LockStepHandle_t* LockStepGetNode(uint8_t num);

bool lockstep_mcal_init(void);
bool lockstep_proc(void);
bool lockstep_proc_one(uint8_t num);

bool lockstep_init_custom(void);
bool lockstep_init_common(const LockStepConfig_t* const Config, LockStepHandle_t* const Node);
bool lockstep_init_one(uint8_t num);
bool LockStepIsValidConfig(const LockStepConfig_t* const Config);

/*getters*/

/*setters*/
bool lockstep_error_injection_set(uint8_t core_num) ;
bool lockstep_error_injection_clear(uint8_t core_num);

#ifdef __cplusplus
}
#endif

#endif /* LOCKSTEP_MCAL_H  */
