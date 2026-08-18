#ifndef AD9833_DIAG_H
#define AD9833_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "ad9833_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /*HAS_LOG*/

#ifndef HAS_AD9833
#error "+HAS_AD9833"
#endif /*HAS_AD9833*/

#ifndef HAS_AD9833_DIAG
#error "+HAS_AD9833_DIAG"
#endif /*HAS_DIAG_AD9833*/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /*HAS_DIAG*/

bool ad9833_diag(void);
const char* SignalFormToStr(SignalForm_t form);

#endif /* AD9833_DIAG_H  */
