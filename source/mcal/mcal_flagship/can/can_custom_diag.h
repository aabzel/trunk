#ifndef CAN_CUSTOM_DIAG_H
#define CAN_CUSTOM_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "can_custom_types.h"
#include "can_registers_diag.h"
#include "module_driver_flexcan.h"

bool can_diag_custom(void);
bool can_diag_handle(const  FLEXCAN_HandleType* const pHandle);
bool can_diag_low_level(uint8_t num, char* const keyword);

const char* CanBRSToStr(const CanBRSCode_t bit_rate_sw);
const char* CanClockStrToStr(const Can_CTRL1_CLKSRC_t clk_src) ;
const char* CanEDLToStr(CanEDLCode_t extended_data_length);
const char* CanESItoStr(const CanESICode_t error_ind);
const char* CanErrorToStr(const FLEXCAN_ErrorType error);
const char* CanFlexErrorToStr(const FLEXCAN_ErrorType error);
const char* CanFrameRTRToStr(const CanFrameRTR_t rtr);
const char* CanIDEToStr(const CanIDECode_t id_ext_bit);
const char* CanInfoToStr(const CanInfo_t* const Info );
const char* CanRTRToStr(const CanRTRCode_t  remote_tx_req);
const char* CanSRRToStr(const CanSRRCode_t srr);
const char* CanTxMessageToStr(const FLEXCAN_TxMsgType* const TxMsg);
const char* FlexCanBaudRegToStr(const FLEXCAN_BaudRegType* const TimeSeg) ;


#ifdef __cplusplus
}
#endif

#endif /* CAN_CUSTOM_DIAG_H */





