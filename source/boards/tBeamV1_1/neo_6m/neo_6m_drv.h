#ifndef NEO_6M_DRV_H
#define NEO_6M_DRV_H

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include "gnss_utils.h"
#include "system.h"

#define NEO_6M_PERIOD_US S_2_US(1.5)

#ifndef HAS_NEO_6M
#include "HAS_NEO_6M component must be included"
#endif


bool neo_6m_init(void);
bool neo_6m_proc(void);

#endif /* NEO_6M_DRV_H  */
