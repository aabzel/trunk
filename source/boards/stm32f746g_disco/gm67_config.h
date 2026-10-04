#ifndef GM67_CONFIG_H
#define GM67_CONFIG_H

#include "gm67_types.h"
#include "sys_config.h"

extern const Gm67Config_t Gm67Config[];
extern Gm67Handle_t Gm67Instance[];

uint32_t gm67_get_cnt(void);

#endif /* GM67_CONFIG_H  */
