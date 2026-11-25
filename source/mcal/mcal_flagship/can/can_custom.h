#ifndef CAN_CUSTOM_H
#define CAN_CUSTOM_H

#include "std_inc.h"
#include "can_types.h"
#include "module_driver_flexcan.h"
#include "_driver_header.h"
#include "can_custom_types.h"
#include "can_core.h"

extern const CAN_BaudRegType s_aFlexCan_DataBaudDividerTable[];
extern const CAN_BaudRegType s_aFlexCan_NormalBaudDividerTable[];

#ifdef HAS_CAN0
extern FLEXCAN_HandleType hCan0;
#endif

#ifdef HAS_CAN1
extern FLEXCAN_HandleType hCan1;
#endif

#ifdef HAS_CAN2
extern FLEXCAN_HandleType hCan2;
#endif

#ifdef HAS_CAN3
extern FLEXCAN_HandleType hCan3;
#endif

#ifdef HAS_CAN4
extern FLEXCAN_HandleType hCan4;
#endif

#ifdef HAS_CAN5
extern FLEXCAN_HandleType hCan5;
#endif

#ifdef HAS_CAN6
extern FLEXCAN_HandleType hCan6;
#endif

#ifdef HAS_CAN7
extern FLEXCAN_HandleType hCan7;
#endif

#ifdef HAS_CAN8
extern FLEXCAN_HandleType hCan8;
#endif

#ifdef HAS_CAN9
extern FLEXCAN_HandleType hCan9;
#endif


/*setters*/
bool can_mcal_transmit_message_sdk(uint8_t num, const CanMessage_t* const Message);
bool can_freeze_ctrl(uint8_t num, bool on_off);
bool can_module_ctrl(uint8_t num, bool on_off);
uint8_t BSP_CAN_LL_ProcessBaud(const FLEXCAN_InstanceType eInstance, FLEXCAN_InitType *const pInitCfg,
                               const uint32_t baudrate);
bool CanMsgToMessage(uint32_t can_num, const FLEXCAN_RxMsgType* const Msg, CanMessage_t* const Message);

/*getters*/
bool CanBitRateToSegment(uint32_t clk_freq_hz, uint32_t bit_rate, FLEXCAN_BaudRegType* const TimeSeg);
bool CanFsRetToRes(const FLEXCAN_ErrorType ret);
canNode_t* Get_CAN_Node( FLEXCAN_HandleType *hcan);
CanMacMode_t can_get_mac_mode(const uint8_t num);
uint32_t BSP_CAN_LL_GetBaudrate( FLEXCAN_InitType *const pInitCfg );
uint32_t CanTimeSegToBitrate(const uint32_t clk_freq_hz, const FLEXCAN_BaudRegType* const TimeSeg);
uint32_t CanBitrateToPreScaler(const FLEXCAN_BaudRegType* const TimeSeg);
uint8_t CanResToRet(const bool res);




#endif /* CAN_CUSTOM_H */

