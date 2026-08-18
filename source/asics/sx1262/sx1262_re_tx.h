#ifndef SX1262_RETX_H
#define SX1262_RETX_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "sx1262_re_tx_types.h"

#ifdef HAS_LORA
#include "lora_constants.h"
#endif

bool is_sx1262_retx_idle(void);
bool sx1262_retx_init(void);
bool sx1262_start_retx(uint8_t* array, uint16_t len, uint8_t try_cnt);
bool sx1216_retx_proc(void);

#ifdef __cplusplus
}
#endif

#endif /* SX1262_RETX_H */
