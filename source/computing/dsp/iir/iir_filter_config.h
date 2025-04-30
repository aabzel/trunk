#ifndef IIR_FILT_CONFIG_H
#define IIR_FILT_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "iir_types.h"

#define IIF_FILT_ECHO_NUM 1
#define IIF_FILT_ECHO_FIFO_SIZE 9000

extern const IirConfig_t IirFiltConfig[];
extern IirHandle_t IirFiltItem[];

uint32_t iir_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* IIR_FILT_CONFIG_H */
