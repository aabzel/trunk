#ifndef PROTOCOL_DIAG_H
#define PROTOCOL_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include "std_includes.h"
#include "protocol_types.h"
#include "interfaces_types.h"
#include "sys_constants.h"

bool flow_ctrl_print_lost(facility_t facility, FlowCrtl_t* Node, uint16_t s_num, InterfaceType_t interface);
bool flow_ctrl_diag(facility_t facility, FlowCrtl_t* Node, InterfaceType_t interface);
char* ProtocolRxStateToStr(RxState_t rx_state);
char* Mask32ToStr(const Addr32Mask_t* const Mask);
const char* FlowCtrlToStr(const FlowCrtl_t* const Node);
const char* ProtocolFrameToStr(const uint8_t* const data, size_t size, Protocol_t protocol);

#ifdef __cplusplus
}
#endif

#endif /* PROTOCOL_DIAG_H */
