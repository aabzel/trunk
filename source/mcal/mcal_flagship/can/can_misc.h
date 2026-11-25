#ifndef CAN_MISC_H
#define CAN_MISC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "module_driver_flexcan.h"
#include "can_const.h"
#include "connectivity_const.h"
#include "can_custom_const.h"

#ifdef HAS_CAN_FD
uint8_t CanFdBitRateSwitchToBrs(const CanFdBitRateSwitch_t bit_rate_switch);
CanFdBitRateSwitch_t CanEnBrsToFdBitRateSwitch(const uint8_t en_brs);
#endif

bool CanRetToRes(const FLEXCAN_ErrorType ret);
CanIdentifier_t CanIdTypeToIdentifier(const FLEXCAN_IdType frame_type) ;
CanTxFrame_t CanDataTypeToFrameType(const FLEXCAN_DataType data_type) ;
FLEXCAN_FifoType CanMacModeToFifoType(const CanMacMode_t mac_mode);
FLEXCAN_ClockSrcType CanClockSourceToClockSrcType(CanClockSource_t clock_source) ;
FLEXCAN_IdType CanMessageBuffetIdTypeToFrameType(const CanIdentifier_t id_type) ;
FLEXCAN_IdType CanMessageIdTyoeToFrameType(const CanIdentifier_t id_type) ;
FLEXCAN_DataType CanFrameTypeToDataType(const CanTxFrame_t frame_type) ;
uint8_t CanMessageBuffDirToIsTx(const ConnectivitDir_t direction) ;
uint8_t CanMacModeToEnableFifo(const CanMacMode_t mac_mode);

#ifdef __cplusplus
}
#endif

#endif /* CAN_MISC_H  */



