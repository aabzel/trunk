#ifndef SWD_DRV_H
#define SWD_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "swd_stm_types.h"
#include "stm32f4xx_hal.h"

#ifndef HAS_CONNECTIVITY
#error "+HAS_CONNECTIVITY"
#endif

#ifndef HAS_SWD
#error "+HAS_SWD"
#endif

#ifndef HAS_STREAM
#error "+HAS_STREAM"
#endif

bool swd_proc(void);
bool swd_init(void);
bool swd_write(uint8_t* array, uint16_t array_len);
bool swd_read(uint8_t* rx_array, uint16_t array_len);

#ifdef __cplusplus
}
#endif

#endif /* SWD_DRV_H  */
