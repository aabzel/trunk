#ifndef DISPLAY_DIAG_H
#define DISPLAY_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "display_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /*HAS_LOG*/

#ifndef HAS_DISPLAY
#error "+HAS_DISPLAY"
#endif /*HAS_DISPLAY*/

#ifndef HAS_DISPLAY_DIAG
#error "+HAS_DISPLAY_DIAG"
#endif /*HAS_DIAG_DISPLAY*/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /*HAS_DIAG*/

bool display_render_ll(DisplayHandle_t* Node , uint8_t* FrameBuffer, uint32_t size);


#endif /* DISPLAY_DIAG_H  */
