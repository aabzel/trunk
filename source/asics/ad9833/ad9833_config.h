
#ifndef AD9833_CONFIG_H
#define AD9833_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "ad9833_types.h"

extern const Ad9833Config_t Ad9833Config[];
extern Ad9833Handle_t Ad9833Instance[];

uint32_t ad9833_get_cnt(void);

#endif /* AD9833_CONFIG_H */
