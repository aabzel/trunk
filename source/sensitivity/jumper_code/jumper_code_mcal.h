#ifndef JUMPER_CODE_MCAL_H
#define JUMPER_CODE_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "jumper_code_config.h"
#include "jumper_code_types.h"

#ifdef HAS_JUMPER_CODE_DIAG
#include "jumper_code_diag.h"
#endif

/* API */
JumperCodeHandle_t* JumperCodeGetNode(uint8_t num);
const JumperCodeConfig_t* JumperCodeGetConfig(uint8_t num);
bool JumperCodeIsValidConfig(const JumperCodeConfig_t* const Config);

#ifdef HAS_JUMPER_CODE_CUSTOM
const JumperCodeInfo_t* JumperCodeGetInfo(uint8_t num);
#endif

bool jumper_code_mcal_init(void);
bool jumper_code_init_custom(void);
bool jumper_code_init_common(const JumperCodeConfig_t* const Config, JumperCodeHandle_t* const Node);
bool jumper_code_init_node(JumperCodeHandle_t* const Node);
bool jumper_code_init_one(uint8_t num);

bool jumper_code_proc_one(uint8_t num);
bool jumper_code_proc(void);

/*setters*/

/*getters*/
uint32_t jumper_code_get(const uint8_t num);
bool jumper_code_is_valid(uint8_t num);
bool jumper_code_is_valid_num(const uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* JUMPER_CODE_MCAL_H */
