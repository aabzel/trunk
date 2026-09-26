#ifndef JUMPER_CODE_CONFIG_H
#define JUMPER_CODE_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "jumper_code_types.h"
#include "jumper_code_dep.h"

extern const JumperCodeConfig_t JumperCodeConfig[];
extern JumperCodeHandle_t JumperCodeInstance[];

uint32_t jumper_code_get_cnt(void);



#ifdef __cplusplus
}
#endif

#endif /* JUMPER_CODE_CONFIG_H */
