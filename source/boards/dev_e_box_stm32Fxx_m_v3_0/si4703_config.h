#ifndef SI4703_CONFIG_H
#define SI4703_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "si4703_types.h"

extern const Si4703Config_t Si4703Config[];
extern Si4703Handle_t Si4703Instance[];

uint32_t si4703_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* SI4703_CONFIG_H */
