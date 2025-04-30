#ifndef DS_TWR_DIAG_H
#define DS_TWR_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_DS_TWR
#error "+ HAS_DS_TWR"
#endif

#ifndef HAS_DS_TWR_DIAG
#error "+HAS_DS_TWR_DIAG"
#endif

#include "ds_twr_types.h"


bool DsTwdDiagConfig(const DsTwrConfig_t* const Config);
const char* DsTwrDiagNode2Str( DsTwr_t* const Node);
char* DsTwrInput2Str(DsTwrInput_t input);
char* DsTwrState2Str(DsTwrState_t state);
bool DsTwrDiagNode(const DsTwr_t* const Node);
#ifdef HAS_UWB
bool DsTwrDiagDistances(UwbIdInfo_t* Node, uint16_t size);
#endif /*HAS_UWB*/

#endif /* DS_TWR_DIAG_H  */
