#ifndef TPA2013D1_DIAG_H
#define TPA2013D1_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "tpa2013d1_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /*HAS_LOG*/

#ifndef HAS_TPA2013D1
#error "+HAS_TPA2013D1"
#endif /*HAS_TPA2013D1*/

#ifndef HAS_TPA2013D1_DIAG
#error "+HAS_TPA2013D1_DIAG"
#endif /*HAS_DIAG_TPA2013D1*/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /*HAS_DIAG*/

bool tpa2013d1_diag(void);

#endif /* TPA2013D1_DIAG_H  */
