#ifndef MIK32_ISR_PROTOTYPES_H
#define MIK32_ISR_PROTOTYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

extern uint32_t int_cnt;

void trap_handler(void);

#ifdef __cplusplus
}
#endif

#endif /* MIK32_ISR_PROTOTYPES_H */
