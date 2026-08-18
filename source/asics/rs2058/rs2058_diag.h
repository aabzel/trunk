#ifndef RS2058_DIAG_H
#define RS2058_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "rs2058_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /*HAS_LOG*/

#ifndef HAS_RS2058
#error "+HAS_RS2058"
#endif /*HAS_RS2058*/

#ifndef HAS_RS2058_DIAG
#error "+HAS_RS2058_DIAG"
#endif /*HAS_DIAG_RS2058*/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /*HAS_DIAG*/

bool rs2058_diag(void);
const char* Rs2058SwStateToStr(Rs2058State_t state);

#endif /* RS2058_DIAG_H  */
