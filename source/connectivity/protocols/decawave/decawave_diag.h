#ifndef DECAWAVE_DIAG_H
#define DECAWAVE_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "decawave_types.h"
#include "log.h"

const char* DecaMes2Str(DwcaMess_t code);
const char* DecaWaveHeader2Str( const DecaWaveHeader_t* const Node);
const char* DecaWaveVarId2Str(UwbVatiable_t var_id);
bool decawave_diag_distanse(uint8_t num);
bool decawave_diag_flow(uint8_t num);
bool decawave_protocol_diag(uint8_t num);
bool DecaWaveHeaderDiag(log_level_t level, const char* const prefix, const DecaWaveHeader_t* const Header);

#ifdef HAS_DECAWAVE_SNIFFER
bool decawave_log_sd(const DecaWaveHeader_t* const Header);
#endif

#ifdef __cplusplus
}
#endif

#endif /* DECAWAVE_DIAG_H */
