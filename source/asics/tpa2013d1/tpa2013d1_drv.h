#ifndef TPA2013D1_DRV_H
#define TPA2013D1_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "tpa2013d1_dep.h"
#include "tpa2013d1_types.h"
#include "tpa2013d1_config.h"

bool tpa2013d1_init(void);
bool tpa2013d1_proc(void);

#endif /* TPA2013D1_DRV_H */
