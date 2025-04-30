#ifndef DTMF_DIAG
#define DTMF_DIAG

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "dtmf_types.h"

bool dtmf_diag(void);
bool DtmfConfigDiag(const DtmfConfig_t * const Config);
bool DtmfNimbleDiag(const DtmfKeyPadFreq_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* DTMF_DIAG  */
