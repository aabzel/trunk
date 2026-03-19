#ifndef EIM_GENERAL_DRIVER_H
#define EIM_GENERAL_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "eim_config.h"
#ifdef HAS_EIM_DIAG
#include "eim_diag.h"
#endif


EimHandle_t* EimGetNode(uint8_t num);
const EimConfig_t* EimGetConfig(uint8_t num);
const EimInfo_t* EimGetInfo(uint8_t num);

bool eim_mcal_init(void);
bool eim_init_one(uint8_t num);
bool EimIsValidConfig(const EimConfig_t* const Config );
bool eim_init_common(const EimConfig_t* const Config, EimHandle_t* const Node);
bool eim_proc_one(uint8_t num);
bool eim_proc(void);
bool eim_init_custom(void);


#ifdef __cplusplus
}
#endif

#endif /* EIM_GENERAL_DRIVER_H */


