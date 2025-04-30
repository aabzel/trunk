#ifndef UDS_CONSTANTS_H
#define UDS_CONSTANTS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "uds_dep.h"

#define DID_PERIOD_US 500000
#define UDS_PERIOD_US 5000
#define UDS_RX_TIME_OUT_MS 5000

#define UDS_OK_SHIFT 0x40
#define NR_SI 0x7F /* Negative response service identifier*/

#define SID_SIZE 1
#define DID_SIZE 2


/*Table 23 — Services allowed during default and non-default diagnostic session*/
typedef enum {
    UDS_SID_DIAGNOSTIC_SESSION_CONTROL=0x10, /*DiagnosticSessionControl*/
    UDS_SID_ECU_RESET=0x11,/*ECUReset*/
    UDS_SID_CLEAR_DIAGNOSTIC_INFORMATION=0x14,/*ClearDiagnosticInformation*/
    UDS_SID_READ_DTC_INFORMATION=0x19,/**/
    UDS_SID_READ_DIAGNOSTIC_INFORMATION=0x19,/*ReadDTCInformation*/
    UDS_SID_READ_DATA_BY_ID = 0x22, /* ReadDataByIdentifier*/
    UDS_SID_READ_DATA_BY_PERIODIC_IDENTIFIER=0x2A,/*ReadDataByPeriodicIdentifier*/
    UDS_SID_READ_MEMORY_BY_ADDRESS=0x23,/*ReadMemoryByAddress*/
    UDS_SID_READ_SCALING_DATA_BY_IDENTIFIER=0x24,/*ReadScalingDataByIdentifier*/
    UDS_SID_SECURITY_ACCESS=0x27,/*SecurityAccess*/
    UDS_SID_COMMUNICATION_CONTROL=0x28,/*CommunicationControl*/
    UDS_SID_DYNAMICALLY_DEFINE_DATA_IDENTIFIER=0x2C,/*DynamicallyDefineDataIdentifier*/
    UDS_SID_WRITE_DATA_BY_IDENTIFIER=0x2E,/*WriteDataByIdentifier*/
    UDS_SID_INPUT_OUTPUT_CONTROL_BYIDENTIFIER=0x2F,/*InputOutputControlByIdentifier*/
    UDS_SID_ROUTINE_CONTROL=0x31, /*13.2 RoutineControl (0x31) service RoutineControl*/
    UDS_SID_REQUEST_DOWNLOAD=0x34,/*RequestDownload*/
    UDS_SID_REQUEST_UP_LOAD=0x35,/*RequestUpload*/
    UDS_SID_TRANSFER_DATA=0x36,/*TransferData*/
    UDS_SID_REQUEST_TRANSFER_EXIT=0x37,/*RequestTransferExit*/
    UDS_SID_REQUEST_FILE_TRANSFER=0x38,/*RequestFileTransfer*/
    UDS_SID_WRITEMEMORY_BYADDRESS=0x3D,/*WriteMemoryByAddress*/
    UDS_SID_TESTER_PRESENT=0x3E,/*TesterPresent*/
    UDS_SID_ACCESS_TIMING_PARAMETER=0x83,/*AccessTimingParameter*/
    UDS_SID_SECURED_DATA_TRANSMISSION=0x84,/*SecuredDataTransmission*/
    UDS_SID_CONTROL_DTC_SETTING=0x85,/*ControlDTCSetting*/
    UDS_SID_RESPONSE_ON_EVENT=0x86,/*ResponseOnEvent*/
    UDS_SID_LINK_CONTROL=0x87,/*LinkControl*/

    UDS_SID_UNDEF = 0,
}UdsSID_t;

// see https://canhacker.ru/protocol-uds/
typedef enum{
    UDS_DID_INPUT_STATES= 0x0001, /**/
    UDS_DID_OUTPUT_STATES= 0x0002, /**/
    UDS_DID_BOARD_VOLTAGE= 0x0003, /**/
    UDS_DID_SYSTEM_STATE= 0x0006, /**/
    UDS_DID_TIME_STAMP= 0x000B, /**/
    UDS_DID_SOS1_BUTTON_HOLD_TIME= 0x0101, /**/
    UDS_DID_SOS2_BUTTON_HOLD_TIME= 0x0102, /**/
    UDS_DID_SERVICE_BUTTON_HOLD_TIME= 0x0103, /**/

    UDS_DID_FULE_LEVEL= 0x2206, /**/
    UDS_DID_UNDEF = 0xFFFF,
}UdsDid_t;

// Table 379 — Request message sub-function definition
typedef enum{
    UDS_RC_START_ROUTINE= 0x01 ,/*startRoutine*/
    UDS_RC_STOP_ROUTINE = 0x02,/*stopRoutine*/
    UDS_RC_REQUEST_ROUTINE_RESULTS=0x03,/*requestRoutineResults*/

    UDS_RC_UNDEF= 0
}UdsRcSubFunc_t;


typedef enum{
    UDS_STATE_IDLE = 1,
    UDS_STATE_WAIT_RESPONCE = 2,

    UDS_STATE_UNDEF = 0,
}UdsState_t;

/*
 * see https://confluence.itelma.su:8443/pages/viewpage.action?pageId=482378387
 * */
typedef enum {
    UDS_ROUTINE_ID_KL30_ON =   0x0101,
    UDS_ROUTINE_ID_KL15_ON = 0x0102  ,
    UDS_ROUTINE_ID_KL30_OFF =   0x0103,
    UDS_ROUTINE_ID_KL15_OFF =   0x0104,
    UDS_ROUTINE_ID_SOS1_ON =   0x5101,
    UDS_ROUTINE_ID_SOS2_ON =   0x5102,
    UDS_ROUTINE_ID_SERVICE_ON =   0x5103,

    UDS_ROUTINE_ID_ENS_10HZ = 0x3101, //Enable emergency alert system(ENS) with 10Hz. 0x3101
    UDS_ROUTINE_ID_ENS_250HZ = 0x3102, //Enable emergency alert system(ENS) with 250Hz.  0x3102
    UDS_ROUTINE_ID_ENS_500HZ = 0x3103, //Enable emergency alert system (ENS) with 500Hz. 0x3103
    UDS_ROUTINE_ID_ENS_250HZ_500HZ = 0x3104, //Enable emergency alert system (ENS) with 250 - 500Hz. 0x3104
    UDS_ROUTINE_ID_ENS_OFF = 0x3105, //

    UDS_ROUTINE_ID_UNDEF = 0  ,
}UdsRoutineIdentifier_t;


#ifdef __cplusplus
}
#endif

#endif /* UDS_CONSTANTS_H */
