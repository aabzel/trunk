#ifndef CAN_DIFF_MCAL_H
#define CAN_DIFF_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "can_diff_config.h"
#include "can_diff_types.h"
#ifdef HAS_CAN_DIFF_DIAG
#include "can_diff_diag.h"
#endif

/* API */
CanDiffHandle_t* CanDiffGetNode(uint8_t num);
const CanDiffConfig_t* CanDiffGetConfig(uint8_t num);
bool CanDiffIsValidConfig(const CanDiffConfig_t* const Config);

#ifdef HAS_CAN_DIFF_CUSTOM
const CanDiffInfo_t* CanDiffGetInfo(uint8_t num);
#endif

bool can_diff_mcal_init(void);
bool can_diff_init_custom(void);
bool can_diff_init_common(const CanDiffConfig_t* const Config, CanDiffHandle_t* const Node);
bool can_diff_init_node(CanDiffHandle_t* const Node);
bool can_diff_init_one(uint8_t num);

bool can_diff_proc_one(uint8_t num);
bool can_diff_proc(void);

/*setters*/
bool can_diff_watch(const uint8_t num,const uint8_t can_num,  const uint32_t can_id, const CanIdentifier_t id_type);
bool can_diff_proc_frame(const CanMessage_t* const pRxMesg);

/*getters*/

#ifdef __cplusplus
}
#endif

#endif /* CAN_DIFF_MCAL_H */
