#ifndef AUTO_VERSION_DIAG_H
#define AUTO_VERSION_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "auto_version_types.h"

bool auto_version_diag(void);
bool AutoVersionDiag(const  AutoVersionHandle_t* const Node);
const char* AutoVersionDiag2Str(const AutoVersionHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* AUTO_VERSION_DIAG_H */
