#ifndef MX25L6433F_DIAG_H
#define MX25L6433F_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "mx25l6433f_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_MX25L6433F_DIAG
#error "+HAS_MX25L6433F_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

const char* Mx25l6433fConfigToStr(const Mx25l6433fConfig_t* const Config);
const char* Mx25l6433fNodeToStr(const Mx25l6433fHandle_t* const Node);

bool mx25_diag_configuration(uint8_t num,Mx25l6433fRegConfiguration_t* configuration);
bool mx25_diag_id(Mx25l6433fRegIdentification_t* reg);
bool mx25l6433f_diag(void);
bool mx25l6433f_diag_one(uint8_t num);
bool mx25l6433f_diag_high_level(uint8_t num);
bool mx25l6433f_usage(uint8_t num,uint32_t piece_size);

#ifdef __cplusplus
}
#endif

#endif /* MX25L6433F_DIAG_H  */
