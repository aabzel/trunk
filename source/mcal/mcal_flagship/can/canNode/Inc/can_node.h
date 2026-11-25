/*
 * CAN_node.h
 *
 *  Created on: Sep 11, 2023
 *      Author: karbovskiy
 *  Modified on: Oct 6, 2025
 *      Author: karbovskiy
 */

#ifndef CAN_NODE_H_
#define CAN_NODE_H_


/* ---------------------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

#include "main.h"
#include "config.h"
#ifdef HAS_J1939
#include "j1939_def.h"
#include "j1939_tp.h"
#endif
#include "can_tx.h"



/* ---------------------------------------------------------------------------*/
/* Defines -------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

#define CAN_ID_STD					FLEXCAN_ID_STD
#define CAN_ID_EXT					FLEXCAN_ID_EXT



/* ---------------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

typedef struct J1939tp_t J1939tp_t;
typedef struct canTxSlots_t canTxSlots_t;



struct canNode_t
{
	FLEXCAN_HandleType* 			hcan;

	J1939tp_t*						pJ1939tp;

	canTxSlots_t*					pTxSlots;

	volatile FLEXCAN_RxMsgType		rxMsg;

	volatile bool tx_done;

	volatile bool rx_done;
};



typedef struct __canNodes_t
{
#if ( CAN_NODE0_IS_USED > 0 )
	canNode_t 						n0;
#endif
#if ( CAN_NODE1_IS_USED > 0 )
	canNode_t 						n1;
#endif
#if ( CAN_NODE2_IS_USED > 0 )
	canNode_t 						n2;
#endif
#if ( CAN_NODE3_IS_USED > 0 )
	canNode_t 						n3;
#endif
#if ( CAN_NODE4_IS_USED > 0 )
	canNode_t 						n4;
#endif
#if ( CAN_NODE5_IS_USED > 0 )
	canNode_t 						n5;
#endif
#if ( CAN_NODE6_IS_USED > 0 )
	canNode_t 						n6;
#endif
#if ( CAN_NODE7_IS_USED > 0 )
	canNode_t 						n7;
#endif
#if ( CAN_NODE8_IS_USED > 0 )
	canNode_t 						n8;
#endif
#if ( CAN_NODE9_IS_USED > 0 )
	canNode_t 						n9;
#endif
} canNodes_t;



/* ---------------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

extern canNodes_t canNodes;



/* ---------------------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
/* ---------------------------------------------------------------------------*/

FLEXCAN_ErrorType CAN_NodeInit( canNode_t* pNode, uint32_t baudrate );
void CAN_Step( void );
canNode_t* Get_CAN_Node( FLEXCAN_HandleType *hcan );
FLEXCAN_FifoFilterType ExtID_RxFilterSet( uint32_t const id, uint32_t const mask );
FLEXCAN_FifoFilterType StdID_RxFilterSet( uint16_t const id, uint16_t const mask );
#ifdef HAS_J1939
FLEXCAN_FifoFilterType J1939ID_RxFilterSet( J1939_ID_t const id, J1939_ID_t const mask );
#endif
int32_t canCustomRxHandler( canNode_t* const pNode, FLEXCAN_RxMsgType const * const pRxMsg );
int32_t canJ1939RxHandler( FLEXCAN_RxMsgType *pRxMsg );



/* ---------------------------------------------------------------------------*/
/* Asserts -------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

#endif /* CAN_NODE_H_ */
