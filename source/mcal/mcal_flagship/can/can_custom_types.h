#ifndef CAN_FLAGSHIP_TYPES_H
#define CAN_FLAGSHIP_TYPES_H

#include "std_inc.h"
#include "interfaces_types.h"
#include "can_node.h"
#include "storage_file_ids.h"
#include "can_custom_const.h"
#include "can_register_types.h"
#include "can_const.h"

typedef void (*Call_Back_Error_t)(struct _FLEXCAN_HandleType *pHandle, FLEXCAN_ErrorInfoType *pErrorInfo);
typedef void (*Call_Back_Fifo_Issue_t)(struct _FLEXCAN_HandleType *pHandle, FLEXCAN_FifoIssueType *pFifoIssue);
typedef void (*Call_Back_Tx_t)  (struct _FLEXCAN_HandleType *pHandle, uint8_t u8TxHandle);
typedef void (*Call_Back_Rx_t)  (struct _FLEXCAN_HandleType *pHandle, FLEXCAN_RxMsgType *pRxMsg);
typedef void (*Call_Back_Wake_t)(struct _FLEXCAN_HandleType *pHandle, FLEXCAN_WakeupMsgType *pWakeMsg);

#define CAN_CUSTOM_TX_VARIABLES

#define CAN_CUSTOM_RX_VARIABLES                         \
    FLEXCAN_FifoFilterType  EnhancedFifoFilterList[12]; \
    FLEXCAN_RxMsgType RxMsg;

#define CAN_CUSTOM_VARIABLES          \
    FLEXCAN_MbSettingType aMbList[32];                  \
    canNode_t* pCanNode;              \
    volatile FLEXCAN_Type* CANx;      \
    CAN_CUSTOM_RX_VARIABLES           \
    CAN_CUSTOM_TX_VARIABLES           \
    CanRegESR1_t ESR1;                \
    CanRegESR2_t ESR2;

// FLEXCAN_HandleType* pHandle;

typedef struct {
    StorageId_t nvram_id;
    volatile FLEXCAN_Type* const CANx;
    FLEXCAN_HandleType* const pHandle;
    canNode_t* pCanNode;
    PCC_ClkSrcType e_clock_name;
    FLEXCAN_InstanceType e_instance;
    bool valid;
    IRQn_Type irq_n;
    //canTxSlots_t* pTxSlots;
    uint8_t num;
    Call_Back_Error_t Call_Back_Error;
    Call_Back_Fifo_Issue_t Call_Back_Fifo_Issue;
    Call_Back_Tx_t Call_Back_Tx ;
    Call_Back_Rx_t Call_Back_Rx;
    Call_Back_Wake_t Call_Back_Wake;
}CanInfo_t;

/* Baud-rate clock and divider */
typedef struct {
    CAN_BaudClkType      eClkHz;      /**< Clock Hz for baudrate             */
    CAN_BaudType         eBaudrate;   /**< Normal bit baudrate               */
    uint32_t             u32Presdiv;  /**< Presdiv for can                   */
    uint32_t             u32Propseg;  /**< Propseg for can                   */
    uint32_t             u32Pseg1;    /**< Pseg1 for can                     */
    uint32_t             u32Pseg2;    /**< Pseg2 for can                     */
    uint32_t             u32Rjw;      /**< RJW for can                       */
} CAN_BaudRegType;



typedef struct {
    CanIdentifier_t id_type ;
    uint32_t IDE;
    FLEXCAN_IdType IdType;
} CanIdTypeInfo_t;


#endif /* CAN_FLAGSHIP_TYPES_H */
