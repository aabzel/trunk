#ifndef GM67_DIAG_H
#define GM67_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "gm67_types.h"

#ifndef HAS_GM67
#error "+HAS_GM67"
#endif /**/

#ifndef HAS_GM67_DIAG
#error "+HAS_GM67_DIAG"
#endif /**/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /**/

const char* Gm67ConfigToStr(const Gm67Config_t* const Config);
bool Gm67DiagConfig(const Gm67Config_t* const Config);
bool gm67_diag(void);

#endif /* GM67_DIAG_H  */
