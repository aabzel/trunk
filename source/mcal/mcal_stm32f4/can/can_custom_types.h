#ifndef CAN_STM32_CUSTOM_TYPE_H
#define CAN_STM32_CUSTOM_TYPE_H

#include "clock_const.h"
#include "microcontroller.h"
#include "mcal_types.h"
#include "can_custom_const.h"
#include "can_register_types.h"



/*
CAN TX mailbox identifier register (CAN_TIxR) (x=0..2)
Address offsets: 0x180, 0x190, 0x1A0
Reset value: 0xXXXX XXXX (except bit 0, TXRQ = 0)
*/
typedef union {
    uint32_t dword;
    struct {
        uint32_t EXID_17_0 :18; /* EXID[17:0]: Extended identifier */
        uint32_t EXTID_28_18 :11; /* EXID[28:18]: Standard identifier or extended identifier */
        uint32_t RES1 :3; /* */
    };
    struct {
        uint32_t EXTID :29; /*  */
        uint32_t RES2 :3; /* */
    };
} CanExtId_t;


#define CAN_CUSTOM_TX_VARIABLES       \
    CAN_TxHeaderTypeDef TxHeader;

#define CAN_CUSTOM_RX_VARIABLES

#ifdef HAS_CAN_STM32
#define CAN_STM_HAL_VARIABLES CAN_HandleTypeDef Handle;
#else
#define CAN_STM_HAL_VARIABLES
#endif


#define CAN_CUSTOM_VARIABLES      \
    CAN_CUSTOM_TX_VARIABLES       \
    CAN_STM_HAL_VARIABLES         \
    CAN_TypeDef* CANx;

typedef struct {
    StorageId_t nvram_id;
    CAN_TypeDef* CANx;
    bool valid;
    IRQn_Type irq_n_tx;
    IRQn_Type irq_n_rx0;
    IRQn_Type irq_n_rx1;
    IRQn_Type irq_n_sce;
    ClockBus_t clock_bus;
    uint8_t num;
}CanInfo_t;

typedef struct {
    int32_t error;
    CanReg_BTR_t CAN_BTR ;
}CanBestBtr_t;


#endif /* CAN_STM32_CUSTOM_TYPE_H  */
