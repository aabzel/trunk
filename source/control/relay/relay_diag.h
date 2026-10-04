#ifndef RELAY_DIAG_H
#define RELAY_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "relay_types.h"

bool relay_diag(char* key_word1, char* key_word2);
const char* RelayModeToStr(RelayMode_t mode);
const char* RelayConfigToStr(const RelayConfig_t* const Config);
const char* RelayNumToStr(uint32_t num);

#ifdef __cplusplus
}
#endif

#endif /* RELAY_DIAG_H  */
