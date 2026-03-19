#ifndef MAM_PROXY_MCAL_H
#define MAM_PROXY_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "mam_config.h"
#include "mam_types.h"
#include "mam_custom.h"
#ifdef HAS_MAM_DIAG
#include "mam_diag.h"
#endif

/* API */
const MamConfig_t* MamGetConfig(uint8_t num);
MamHandle_t* MamGetNode(uint8_t num);
bool MamIsValidConfig(const MamConfig_t* const Config);

#ifdef HAS_MAM_CUSTOM
const MamInfo_t* MamGetInfo(uint8_t num);
#endif

bool mam_mcal_init(void);
bool mam_init_custom(void);
bool mam_init_one(uint8_t num);
bool mam_init_common(const MamConfig_t* const Config,
                     MamHandle_t* const Node);

bool mam_proc_one(uint8_t num);
bool mam_proc(void);

/*setters*/

/*getters*/


#ifdef __cplusplus
}
#endif

#endif /* MAM_PROXY_MCAL_H */
