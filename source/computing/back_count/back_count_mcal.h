#ifndef BACK_COUNT_MCAL_H
#define BACK_COUNT_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "back_count_config.h"
#include "back_count_types.h"

#ifdef HAS_BACK_COUNT_DIAG
#include "back_count_diag.h"
#endif

/* API */
BackCountHandle_t* BackCountGetNode(uint8_t num);
const BackCountConfig_t* BackCountGetConfig(uint8_t num);
bool BackCountIsValidConfig(const BackCountConfig_t* const Config);

#ifdef HAS_BACK_COUNT_CUSTOM
const BackCountInfo_t* BackCountGetInfo(uint8_t num);
#endif

bool back_count_mcal_init(void);
bool back_count_init_custom(void);
bool back_count_init_common(const BackCountConfig_t* const Config, BackCountHandle_t* const Node);
bool back_count_init_node(BackCountHandle_t* const Node);
bool back_count_init_one(uint8_t num);

bool back_count_proc_one(uint8_t num);
bool back_count_proc(void);

/*setters*/
bool back_count_add(uint8_t num, uint32_t val);

/*getters*/
uint8_t back_count_state_get(uint8_t num) ;
bool back_count_is_valid_num(const uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* BACK_COUNT_MCAL_H */
