
#ifndef MCAL_DIAG_H
#define MCAL_DIAG_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "mcal_types.h"
#include "sys_constants.h"

const char* McalMoveModeToStr(MoveMode_t move_mode);
bool McalOkCntToRes(uint32_t okCnt, uint32_t dataQty);

#ifdef __cplusplus
}
#endif

#endif /* MCAL_DIAG_H */
