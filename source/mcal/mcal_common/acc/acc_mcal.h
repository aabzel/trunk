#ifndef ACC_MCAL_H
#define ACC_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "acc_config.h"
#include "acc_types.h"
#ifdef HAS_ACC_DIAG
#include "acc_diag.h"
#endif

/* API */
const AccConfig_t* AccGetConfig(uint8_t num);
AccHandle_t* AccGetNode(uint8_t num);
bool AccIsValidConfig(const AccConfig_t* const Config);

#ifdef HAS_ACC_CUSTOM
const AccInfo_t* AccGetInfo(uint8_t num);
#endif

bool acc_mcal_init(void);
bool acc_init_custom(void);
bool acc_init_one(uint8_t num);
bool acc_init_common(const AccConfig_t* const Config,
                              AccHandle_t* const Node);


/*setters*/

/*getters*/

#ifdef __cplusplus
}
#endif

#endif /* ACC_MCAL_H */
