#ifndef LTR390_CONFIG_H
#define LTR390_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "ltr390_types.h"
#include "ltr390_dep.h"

extern const Ltr390Config_t Ltr390Config[];
extern Ltr390Handle_t Ltr390Instance[];
extern const Ltr390Register_t Ltr390Register[];

uint32_t ltr390_reg_get_cnt(void);
uint32_t ltr390_get_cnt(void);

#endif /* LTR390_CONFIG_H */
