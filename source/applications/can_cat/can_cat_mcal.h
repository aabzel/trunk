#ifndef CAN_CAT_MCAL_H
#define CAN_CAT_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "can_mcal.h"
#include "can_cat_config.h"
#include "can_cat_types.h"
#ifdef HAS_CAN_CAT_DIAG
#include "can_cat_diag.h"
#endif

/* API */
const CanCatConfig_t* CanCatGetConfig(uint8_t num);
CanCatHandle_t* CanCatGetNode(uint8_t num);
bool CanCatIsValidConfig(const CanCatConfig_t* const Config);

#ifdef HAS_CAN_CAT_CUSTOM
const CanCatInfo_t* CanCatGetInfo(uint8_t num);
#endif

bool can_cat_mcal_init(void);
bool can_cat_init_custom(void);
bool can_cat_init_one(uint8_t num);
bool can_cat_init_common(const CanCatConfig_t* const Config,
                              CanCatHandle_t* const Node);

bool can_cat_proc_one(uint8_t num);
bool can_cat_proc(void);

/* setters */
bool can_cat_config(uint8_t com_num,
                    uint32_t can_bit_rate,
                    uint32_t my_addr,
                    uint32_t subscribe_addr);

/*getters*/
bool can_cat_raw_reg_diag(uint8_t i) ;

#ifdef __cplusplus
}
#endif

#endif /* CAN_CAT_MCAL_H */
