#ifndef JUMPER_CODE_DIAG_H
#define JUMPER_CODE_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "jumper_code_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_JUMPER_CODE
#error "+HAS_JUMPER_CODE"
#endif

#ifndef HAS_JUMPER_CODE_DIAG
#error "+HAS_JUMPER_CODE_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

bool jumper_code_diag(void);
bool jumper_code_diag_one(uint8_t num);
bool jumper_code_raw_reg_diag(uint8_t num);
const char* JumperCodeVariable1ToStr(const JumperCodeVariable1_t variable1);
const char* JumperCodeConfigToStr(const JumperCodeConfig_t* const Config);
const char* JumperCodeNodeToStr(const JumperCodeHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* JUMPER_CODE_DIAG_H  */
