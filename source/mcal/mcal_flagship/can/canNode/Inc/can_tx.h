/*
 * can_tx.h
 *
 *  Created on: Feb 02, 2024
 *      Author: karbovskiy
 *  Modified on: Sep 10, 2025
 *      Author: karbovskiy
 */

#ifndef INC_CAN_TX_H_
#define INC_CAN_TX_H_


/* ---------------------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

#include "main.h"
//#include "can_node.h"



/* ---------------------------------------------------------------------------*/
/* Defines -------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

typedef struct canPacket_t canPacket_t;
typedef struct canNode_t canNode_t;
typedef uint8_t (*BYTE_CAN_PACK_FUNC_t)( canPacket_t* pPacket, uint8_t* pAddr );



typedef enum
{
	P_IDLE,
	P_WAIT,
	P_RETRY,
	P_BOXED,
	P_ABORT,
} canPktState_t;



typedef enum
{
	CAN_SLOT_EMPTY,			/* Tx mailbox is empty, no packet assigned */
	CAN_SLOT_PENDING,		/* Tx mailbox is empty, someone packet assigned */
	CAN_SLOT_BUSY,			/* Tx mailbox is occupied by any packet */
	CAN_SLOT_SENT,			/* Tx mailbox is empty, packet sent */
	CAN_SLOT_FAILED,		/* Tx mailbox is empty, transfer failed */
} canSlotStatus_t;



typedef struct
{
	uint8_t*						pData;
	uint16_t						DataBytes;
	bool							InProgress;
} canTpConfig_t;



typedef struct
{
	uint8_t const					mailbox;
	canSlotStatus_t					status;
	canPacket_t* 					pPacket;
#ifdef DEBUG
	uint32_t						txCntr;
	uint32_t						fakeTxCntr;
	uint32_t						busyErrCntr;
	uint32_t						packetErrCnt;
	uint32_t						statusErrCnt;
	uint32_t						txErrCnt;
	uint32_t						otherErrCnt;
#endif
} canTxSlot_t;



struct canTxSlots_t
{
	canTxSlot_t						slot[3];
};



struct canPacket_t
{
	// user configurable parameters
	canNode_t*						pNode;
	uint32_t						Id;
	uint32_t						IDE;
	BYTE_CAN_PACK_FUNC_t			pFuncPack;
	uint32_t						period;
	canTpConfig_t* const			pTP;
	bool							isJ1939;
	bool							isEnabled;
	bool							sendOnce;

	// internal parameters
	bool							isSent;
	canTxSlot_t*					pSlot;
	uint32_t						waitTime;
	uint32_t						lastTxTime;
	canPktState_t					state;
	uint32_t						txCntr;
	uint32_t						txErrCntr;
	uint32_t						sentCntr;

	// debug only
	uint32_t						slotErrCntr;
	uint32_t						caseErrCntr;
};



/* ---------------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/


/* ---------------------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
/* ---------------------------------------------------------------------------*/

void canTxHandler( canNode_t* pNode );
#ifdef HAS_J1939
int32_t canJ1939RequestHandler( canNode_t *pNode, FLEXCAN_RxMsgType *pRxMsg );
#endif
void CAN_TxCallback( FLEXCAN_HandleType *pHandle, uint8_t u8TxHandle );



/* ---------------------------------------------------------------------------*/
/* Asserts -------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

#endif /* INC_CAN_TX_H_ */
