#ifndef RELAY_DIAG_H
#define RELAY_DIAG_H

#include "relay_types.h"

bool relay_diag(char* key_word1, char* key_word2);
const char* RelayModeToStr(RelayMode_t mode);
const char* RelayConfigToStr(const RelayConfig_t* const Config);

#endif /* RELAY_DIAG_H  */
