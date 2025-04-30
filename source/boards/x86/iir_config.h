#ifndef IIR_CONFIG_H
#define IIR_CONFIG_H

#include "std_includes.h"
#include "iir_types.h"

extern const IirConfig_t IirConfig[];
extern IirHandle_t IirInstance[];

uint32_t iir_get_cnt(void);

#endif /* IIR_CONFIG_H */
