#ifndef CAN_MCAL_DIAG_H
#define CAN_MCAL_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "can_types.h"

#ifdef HAS_CAN_CUSTOM_DIAG
#include "can_custom_diag.h"
#endif

const char* CanPriorityToStr(const CanPriority_t priority);
const char* CanMessageBufferConfigToStr(const CanMessageBufferConfig_t * const MbConfig );
const char* CanModeToStr( CanMode_t mode);
const char* CanConfigToStr(const CanConfig_t* const Config);
const char* CanClkStrToStr(const CanClockSource_t clock_source) ;
const char* CanIdTypeToStr(const CanIdentifier_t id_type);
const char* CanFrameTypeToStr(const CanTxFrame_t frame_type);
const char* CanMacModeToStr(const CanMacMode_t mac_mode);
const char* CansToStr(const Cans_t  Obj) ;
const char* CanMessageToStr(const CanMessage_t* const Message);
const char* CanSegmentInfoToStr(const CanSegmentInfo_t* const Info );
bool CanDiagNode(const CanHandle_t* const Node);
bool can_diag(void);
bool can_diag_interrupt(void);
bool can_fd_diag(void);
bool can_show_my_id(const uint8_t num);
uint32_t can_filter_id_mask_diag(const uint32_t filter_id, const uint32_t filter_mask) ;

#ifdef __cplusplus
}
#endif

#endif /* CAN_MCAL_DIAG_H */
