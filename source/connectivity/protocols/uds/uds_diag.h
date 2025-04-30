#ifndef UDS_DIAG_H
#define UDS_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "uds.h"

const char* UdsRoutineIdentifierToStr(UdsRoutineIdentifier_t routine_identifier);
const char* UdsDidToStr(UdsDid_t did);
const char* DidConfigToStr(const DidConfig_t* const Config);

const char* UdsNode2Str(const UdsHandle_t* const Node);
bool uds_did_diag(uint8_t num);
bool uds_diag(void);

#ifdef __cplusplus
}
#endif

#endif /* UDS_DIAG_H */
