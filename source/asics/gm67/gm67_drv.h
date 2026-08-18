#ifndef GM67_DRV_H
#define GM67_DRV_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "gm67_config.h"
#include "gm67_types.h"
#ifdef HAS_GM67_DIAG
#include "gm67_diag.h"
#endif

const Gm67Config_t* Gm67GetConfig(uint8_t num);
Gm67Handle_t* Gm67GetNode(uint8_t num);
Gm67Handle_t* Gm67GetNodeByUart(uint8_t uart_num);

bool gm67_is_connected(uint8_t num);
bool gm67_mcal_init(void);
bool gm67_init_one(uint8_t num);

bool gm67_proc_byte_isr(uint8_t uart_num, uint8_t rx_byte);
bool gm67_proc_one(uint8_t num);
bool gm67_proc(void);

#endif /* GM67_DRV_H */
