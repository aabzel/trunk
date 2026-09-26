#ifndef SEGGER_RTT_CONFIG_H
#define SEGGER_RTT_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "segger_rtt_types.h"
#include "segger_rtt_dep.h"

extern const SeggerRttConfig_t SeggerRttConfig[];
extern SeggerRttHandle_t SeggerRttInstance[];

uint32_t segger_rtt_get_cnt(void);



#ifdef __cplusplus
}
#endif

#endif /* SEGGER_RTT_CONFIG_H */
