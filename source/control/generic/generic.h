#ifndef GENERIC_H
#define GENERIC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "generic_types.h"

bool generic_jump_to_bootloader(void);
bool generic_proc(void);

#ifdef __cplusplus
}
#endif

#endif /* GENERIC_H */
