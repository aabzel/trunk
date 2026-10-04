#ifndef MX25L6433F_CONFIG_H
#define MX25L6433F_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "mx25l6433f_types.h"

extern const Mx25l6433fConfig_t Mx25l6433fConfig[];
extern Mx25l6433fHandle_t Mx25l6433fInstance[];

uint32_t mx25l6433f_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* MX25L6433F_CONFIG_H */
