#ifndef BLACK_BOX_DRV_H
#define BLACK_BOX_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "black_box_config.h"
#include "black_box_types.h"

const BlackBoxConfig_t* BlackBoxGetConfNode(uint8_t num);
BlackBoxHandle_t* BlackBoxGetNode(uint8_t num);

bool black_box_proc(void);
bool black_box_init(void);

#ifdef __cplusplus
}
#endif

#endif /* BLACK_BOX_DRV_H */
