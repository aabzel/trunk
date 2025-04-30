#ifndef ISO_TP_DIAG_H
#define ISO_TP_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "iso_tp.h"

const char* IsoTpState2Str(IsoTpState_t state);
const char* IsoTpRole2Str(IsoTpRole_t role);
const char* Frame2Str(const IsoTpFrame_t* const Frame);
const char* IsoTpNodeToStr(const IsoTpHandle_t* const Node);
char* IsoTpNode2Str(const IsoTpHandle_t* const Node);
bool iso_tp_buff_print(uint8_t num, uint32_t size, IsoTpBuff_t buff);
bool iso_tp_buff_print_ll(IsoTpHandle_t* Node, uint32_t size, IsoTpBuff_t buff);
bool iso_tp_diag(void);
bool IsoTpDiagNode(const IsoTpHandle_t* const Node);
bool IsoTpDiagFlowControlHeader(IsoTpFlowControlHeader_t* Header);

#ifdef __cplusplus
}
#endif

#endif /* ISO_TP_DIAG_H */
