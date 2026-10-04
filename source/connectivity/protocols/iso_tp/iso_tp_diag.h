#ifndef ISO_TP_DIAG_H
#define ISO_TP_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "iso_tp_types.h"

const char* IsoTpProtocolFormatToStr(const IsoTpProtocolFormat_t protocol_format);
const char* IsoTpAddressingToStr(const IsoTpAddressing_t addressing) ;
const char* IsoToConsecutiveToStr(const IsoTpHandle_t* const Node);
const char* IsoTpIdToStr(const IsoTpNormalFixedAddress_t* const can_id);
const char* IsoTpFrameIdToStr(const IsoTpFrameCode_t frame_id);
const char* IsoTpConfigToStr(const IsoTpConfig_t* const Config) ;
const char* IsoTpStateToStr(const IsoTpState_t state);
const char* IsoTpRoleToStr(const IsoTpRole_t role);
const char* IsoTpFrameToStr(const IsoTpFrame_t* const Frame);
const char* IsoTpFlowToStr(const IsoTpHandle_t* const Node);
const char* IsoTpNodeToStr(const IsoTpHandle_t* const Node);
bool iso_tp_buff_print(uint8_t num, uint32_t size, IsoTpBuff_t buff);
bool iso_tp_buff_print_ll(IsoTpHandle_t* Node, uint32_t size, IsoTpBuff_t buff);
bool iso_tp_diag(void);
bool IsoTpDiagNode(const IsoTpHandle_t* const Node);
bool IsoTpDiagFlowControlHeader(IsoTpFlowControlHeader_t* Header);

#ifdef __cplusplus
}
#endif

#endif /* ISO_TP_DIAG_H */
