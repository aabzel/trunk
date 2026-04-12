#ifndef DWT_DIAG_H
#define DWT_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dwt_types.h"
#include "mcal_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_DWT
#error "+HAS_DWT"
#endif

#ifndef HAS_DWT_DIAG
#error "+HAS_DWT_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

extern const Reg32_t DwtRegs[] ;

bool dwt_diag(void);
bool dwt_diag_one(uint8_t num);
bool dwt_raw_reg_diag(uint8_t num);
const char* DwtConfigToStr(const DwtConfig_t* const Config);
const char* DwtNodeToStr(const DwtHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* DWT_DIAG_H  */
