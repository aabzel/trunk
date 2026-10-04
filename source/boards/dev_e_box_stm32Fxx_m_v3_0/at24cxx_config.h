#ifndef AT24CXX_CONFIG_H
#define AT24CXX_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "at24cxx_types.h"

extern const At24cxxConfig_t At24cxxConfig[];
extern At24cxxHandle_t At24cxxInstance[];

uint32_t at24cxx_get_cnt(void);

#endif /* AT24CXX_CONFIG_H */
