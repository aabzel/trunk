#ifndef MX25R6435F_DIAG_H
#define MX25R6435F_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "mx25r6435f_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /*HAS_LOG*/

#ifndef HAS_MX25R6435F
#error "+HAS_MX25R6435F"
#endif /*HAS_MX25R6435F*/

#ifndef HAS_MX25R6435F_DIAG
#error "+HAS_MX25R6435F_DIAG"
#endif /*HAS_DIAG_MX25R6435F*/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /*HAS_DIAG*/

bool mx25_diag_id(RegIdentification_t* reg);
bool mx25r6435f_diag(void);
bool mx25r6435f_diag_high_level(void);
bool mx25r6435f_usage(uint32_t piece_size);

#endif /* MX25R6435F_DIAG_H  */
