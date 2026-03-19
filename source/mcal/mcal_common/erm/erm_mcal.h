#ifndef ERM_MCAL_H
#define ERM_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "erm_config.h"
#include "erm_isr.h"
#include "erm_types.h"
#ifdef HAS_ERM_CUSTOM
#include "erm_custom.h"
#endif

#ifdef HAS_ERM_DIAG
#include "erm_diag.h"
#endif

/*API*/
const ErmConfig_t* ErmGetConfig(uint8_t num);
ErmHandle_t* ErmGetNode(uint8_t num);
#ifdef HAS_ERM_CUSTOM
const ErmInfo_t* ErmGetInfo(uint8_t num);
#endif

bool erm_mcal_init(void);
bool erm_init_one(uint8_t num);
bool erm_init_custom(void);
bool erm_init_common(const ErmConfig_t* const Config, ErmHandle_t* const Node) ;

bool erm_proc_one(uint8_t num);
bool erm_proc(void);

/*getters*/
bool ErmIsValidConfig(const ErmConfig_t* const Config);

/*setters*/

#ifdef __cplusplus
}
#endif

#endif /* ERM_MCAL_H  */
