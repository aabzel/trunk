#ifndef W25Q32JV_DIAG_H
#define W25Q32JV_DIAG_H

#include "std_includes.h"
#include "w25q32jv_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /*HAS_LOG*/

#ifndef HAS_W25Q32JV
#error "+HAS_W25Q32JV"
#endif /*HAS_W25Q32JV*/

#ifndef HAS_W25Q32JV_DIAG
#error "+HAS_W25Q32JV_DIAG"
#endif /*HAS_DIAG_W25Q32JV*/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /*HAS_DIAG*/

bool W25q32jvDiagRegStatus1( const W25q32jvRegStatus_t* const Reg);
bool W25q32jvDiagRegStatus2( const W25q32jvRegStatus2_t* const Reg);
bool W25q32jvDiagRegStatus3( const W25q32jvRegStatus3_t* const Reg);

bool W25q32jvDiagReg( const W25q32jvRegUniversal_t* Node, uint8_t reg_num);

#endif /* W25Q32JV_DIAG_H  */
