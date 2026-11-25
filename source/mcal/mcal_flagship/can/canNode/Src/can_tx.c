/*
 * can_tx.c
 *
 *  Created on: Feb 02, 2024
 *      Author: karbovskiy
 *  Modified on: Oct 6, 2025
 *      Author: karbovskiy
 */



/* ---------------------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

#include "main.h"
#include "can.h"
#include "j1939_def.h"
#include "can_packets.h"
#include "can_tx.h"



/* ---------------------------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

extern canTxPackets_t canTxPackets;



/* ---------------------------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

typedef struct canPacket_t canPacket_t;



/* ---------------------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* ---------------------------------------------------------------------------*/

extern uint32_t HAL_GetTick( void );

static void canTxSchedulerStep( canNode_t* pNode );
static void canProcessPackets( canNode_t* pNode );
static void canProcessSlots( canNode_t* pNode );



/* ---------------------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

canTxSlots_t canTxSlots0 =
{
	.slot[0] = { .mailbox = 0, },
	.slot[1] = { .mailbox = 1, },
	.slot[2] = { .mailbox = 2, },
};
canTxSlots_t canTxSlots1 =
{
	.slot[0] = { .mailbox = 0, },
	.slot[1] = { .mailbox = 1, },
	.slot[2] = { .mailbox = 2, },
};
canTxSlots_t canTxSlots2 =
{
	.slot[0] = { .mailbox = 0, },
	.slot[1] = { .mailbox = 1, },
	.slot[2] = { .mailbox = 2, },
};
canTxSlots_t canTxSlots3 =
{
	.slot[0] = { .mailbox = 0, },
	.slot[1] = { .mailbox = 1, },
	.slot[2] = { .mailbox = 2, },
};
canTxSlots_t canTxSlots4 =
{
	.slot[0] = { .mailbox = 0, },
	.slot[1] = { .mailbox = 1, },
	.slot[2] = { .mailbox = 2, },
};
canTxSlots_t canTxSlots5 =
{
	.slot[0] = { .mailbox = 0, },
	.slot[1] = { .mailbox = 1, },
	.slot[2] = { .mailbox = 2, },
};
canTxSlots_t canTxSlots6 =
{
	.slot[0] = { .mailbox = 0, },
	.slot[1] = { .mailbox = 1, },
	.slot[2] = { .mailbox = 2, },
};
canTxSlots_t canTxSlots7 =
{
	.slot[0] = { .mailbox = 0, },
	.slot[1] = { .mailbox = 1, },
	.slot[2] = { .mailbox = 2, },
};
canTxSlots_t canTxSlots8 =
{
	.slot[0] = { .mailbox = 0, },
	.slot[1] = { .mailbox = 1, },
	.slot[2] = { .mailbox = 2, },
};
canTxSlots_t canTxSlots9 =
{
	.slot[0] = { .mailbox = 0, },
	.slot[1] = { .mailbox = 1, },
	.slot[2] = { .mailbox = 2, },
};



/* ---------------------------------------------------------------------------*/
/* Public Functions ----------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

void canTxHandler( canNode_t* pNode )
{
	/* warning: do not change the call sequence */
	canTxSchedulerStep( pNode );
	canProcessPackets( pNode );
	canProcessSlots( pNode );
}


#ifdef HAS_J1939
__WEAK int32_t canJ1939RequestHandler( canNode_t *pNode, FLEXCAN_RxMsgType *pRxMsg )
{
	if ( CAN_ID_EXT != pRxMsg->eFrameType ) return -1; // filter mismatch

	const J1939_ID_t id = { .Extended = pRxMsg->u32CanId };
	if ( 0xEA != id.PF ) return -1; // filter mismatch
	if ( J1939_ECU_ADDR != id.PS ) return -1; // filter mismatch

	if ( pRxMsg->u32DataLen != 3 ) return 1; // seems, packet is broken -> ignore it

	uint32_t rqst_pgn = ( (uint32_t)pRxMsg->aData[0] << 0 ) + ( (uint32_t)pRxMsg->aData[1] << 8 ) + ( (uint32_t)pRxMsg->aData[2] << 16 );

	// set pointer to the first CAN packet in the array
	canPacket_t* pPacket = (canPacket_t*)&canTxPackets;

	// a cycle for each CAN packet in the <canTxPackets> structure
	for ( ; (uintptr_t)pPacket < ( (uintptr_t)&canTxPackets + sizeof(canTxPackets_t) ); pPacket++ )
	{
		if ( NULL == pPacket )
		{
			continue; // program error detected...
		} //if

		if ( pNode != pPacket->pNode )
		{
			continue; // this packet is for another CAN node -> skip it
		} //if

		if ( false == pPacket->isJ1939 )
		{
			continue; // no actions required...
		} //if

		const J1939_ID_t id = { .Extended = pPacket->Id };
		if ( rqst_pgn != id.pgn.PGN )
		{
			continue; // no actions required...
		} //if

		pPacket->sendOnce |= true; // requested packet found
	} //for

	return 0; // filter matches
}
#endif



/* ---------------------------------------------------------------------------*/
/* Private Functions ---------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

static void canTxSchedulerStep( canNode_t* pNode )
{
	// set pointer to the first CAN packet in the array
	canPacket_t* pPacket = (canPacket_t*)&canTxPackets;

	// a cycle for each CAN packet in the <canTxPackets> structure
	for ( ; (uintptr_t)pPacket < ( (uintptr_t)&canTxPackets + sizeof(canTxPackets_t) ); pPacket++ )
	{
		if ( NULL == pPacket )
		{
			continue; // program error detected...
		} //if

		if ( pNode != pPacket->pNode )
		{
			continue; // this packet is for another CAN node -> skip it
		} //if

		if ( false == pPacket->isEnabled )
		{
			if ( NULL != pPacket->pSlot )
			{
				// release the related slot
				if ( CAN_SLOT_BUSY != pPacket->pSlot->status )
				{
					pPacket->state = P_IDLE; // reset the state of the packet
					pPacket->pSlot->status = CAN_SLOT_EMPTY; // release the slot
					pPacket->pSlot = NULL;
				} //if
			} //if

			continue; // no actions required for this packet -> skip it
		} //if

		switch ( pPacket->state )
		{

		case P_IDLE :
		{
			// check for the single transfer request
			if ( true == pPacket->sendOnce )
			{
				pPacket->sendOnce = false;
				pPacket->isSent = false; // reset the previous transfer flag
				pPacket->state = P_WAIT;
				continue; // this packet is handled -> go to the next one
			} //if

			// check for the cyclic transfer request
			if (	( pPacket->period != 0 )
				 &&	( HAL_GetTick() >= ( pPacket->lastTxTime + pPacket->period ) ) )
			{
				pPacket->lastTxTime = HAL_GetTick(); // update the last transmit time, even without actually sending a package
				pPacket->isSent = false; // reset the previous transfer flag
				pPacket->state = P_WAIT;
			} //if
			break;
		} //case

		case P_WAIT :
		case P_RETRY :
		{
			continue; // this packet has already been processed -> go to the next one
			break;
		} //case
		case P_BOXED :
		{
			if ( NULL == pPacket->pSlot )
			{
#ifdef DEBUG
				pPacket->slotErrCntr++; // program error detected...
#endif
				continue;
			} //if
#ifdef DEBUG
			if ( pPacket->pSlot->pPacket != pPacket )
			{
				pPacket->pSlot->packetErrCnt++;
			} //if
#endif
			switch ( pPacket->pSlot->status )
			{

			case CAN_SLOT_BUSY :
			{
				continue; // this packet has already been processed -> go to the next one
				break;
			} //case

			case CAN_SLOT_SENT :
			{
				pPacket->isSent = true;
				pPacket->waitTime = 0;
				pPacket->state = P_IDLE;
				pPacket->pSlot->status = CAN_SLOT_EMPTY; // release the slot
				break;
			} //case

			case CAN_SLOT_FAILED :
			{
				pPacket->state = P_RETRY;
				pPacket->pSlot->status = CAN_SLOT_EMPTY; // release the slot
				break;
			} //case

			case CAN_SLOT_EMPTY :
			case CAN_SLOT_PENDING :
			default :
			{
#ifdef DEBUG
				pPacket->pSlot->statusErrCnt++; // program error detected...
#endif
				break;
			} //default

			} //switch
			break;
		} //case

		case P_ABORT :
		{
			if ( NULL == pPacket->pSlot )
			{
#ifdef DEBUG
				pPacket->slotErrCntr++; // program error detected...
#endif
				continue;
			} //if
#ifdef DEBUG
			if ( pPacket->pSlot->pPacket != pPacket )
			{
				pPacket->pSlot->packetErrCnt++;
			} //if
#endif
			switch ( pPacket->pSlot->status )
			{

			case CAN_SLOT_BUSY :
			{
				continue; // this packet has already been processed -> go to the next one
				break;
			} //case

			case CAN_SLOT_EMPTY :
			case CAN_SLOT_PENDING :
			case CAN_SLOT_SENT :
			case CAN_SLOT_FAILED :
			{
				pPacket->isSent = true;
				pPacket->waitTime = 0;
				pPacket->state = P_IDLE;
				pPacket->pSlot->status = CAN_SLOT_EMPTY; // release the slot
				break;
			} //case

			default :
			{
#ifdef DEBUG
				pPacket->pSlot->statusErrCnt++; // program error detected...
#endif
				break;
			} //default

			} //switch
			break;
		} //case

		default :
		{
#ifdef DEBUG
			pPacket->caseErrCntr++; // program error detected...
#endif
			break;
		} //default

		} //switch

	} //for

} //canTxSchedulerStep()



static void canProcessPackets( canNode_t* pNode )
{
	// reset pointer to the first CAN packet in the array
	canPacket_t* pPacket = (canPacket_t*)&canTxPackets;

	// a cycle for each CAN packet in the <canTxPackets> structure
	for ( ; (uintptr_t)pPacket < ( (uintptr_t)&canTxPackets + sizeof(canTxPackets_t) ); pPacket++ )
	{
		if ( NULL == pPacket )
		{
			continue; // program error detected...
		} //if

		if ( pNode != pPacket->pNode )
		{
			continue; // this packet is not for this CAN node -> skip it
		} //if

		if ( ( P_WAIT == pPacket->state ) || ( P_RETRY == pPacket->state ) )
		{
			pPacket->waitTime++;

			if ( NULL == pPacket->pTP ) // non TP message -> try to put it into the slot
			{
				// set pointer to the first Tx slot in the structure
				canTxSlot_t* pSlot = (canTxSlot_t*)pNode->pTxSlots;

				// a cycle for each Tx slot in the <TxSlots> structure
				for ( ; (uintptr_t)pSlot < ( (uintptr_t)pNode->pTxSlots + sizeof(canTxSlots_t) ); pSlot++ )
				{
					if (	( CAN_SLOT_BUSY == pSlot->status )
						 ||	( CAN_SLOT_SENT == pSlot->status )
						 ||	( CAN_SLOT_FAILED == pSlot->status ) )
					{
						continue; // this slot was occupied in the previous CAN handler cycle -> skip it
					} //if

					if ( CAN_SLOT_EMPTY == pSlot->status )
					{
						pSlot->pPacket = pPacket;
						pPacket->pSlot = pSlot; // add a cross-reference for future status check
						pSlot->status = CAN_SLOT_PENDING;
						break; // cycle interrupt
					} //if
					else // CAN_SLOT_PENDING
					{
						if ( pPacket->waitTime > pSlot->pPacket->waitTime )
						{
							pSlot->pPacket = pPacket; // override previous packet in this slot
							pPacket->pSlot = pSlot; // add a cross-reference for future status check
							break; // cycle interrupt
						} //if
						else
						{
							; // no actions required...
						} //else
					} //else
				} //for
			} //if
			else // TP message -> use the independent handler
			{
				if ( false == pPacket->pTP->InProgress )
				{
#ifdef HAS_J1939
					// message is not sent yet
					if ( TP_OK == j1939tpPollStatus( pPacket->pNode ) )
					{
						// when TP Tx handler ready
						pPacket->pTP->InProgress = j1939tpStartTx( pPacket->pNode, pPacket );
					} //if
#endif
				} //if
				else
				{
#ifdef HAS_J1939
					// message was sent
					switch ( j1939tpPollSuccess( pPacket->pNode->pJ1939tp ) )
					{

					case TP_OK : // sending done
					{
						pPacket->pTP->InProgress = false;
						pPacket->isSent = true;
						pPacket->waitTime = 0;
						pPacket->state = P_IDLE;
						break;
					} //case

					case TP_ERROR : // sending failed, try in the next cycle
					{
						pPacket->pTP->InProgress = false;
						pPacket->state = P_IDLE;
						break;
					} //case

					case TP_BUSY :
					{
						break; // no actions required...
					} //case

					default :
					{
#ifdef DEBUG
						pPacket->caseErrCntr++; // program error detected...
#endif
						break;
					} //default

					} //switch
#endif
				} //else
			} //else
		} //if
	} //for
} //canProcessPackets()



static void canProcessSlots( canNode_t* pNode )
{
	// set pointer to the first Tx slot in the structure
	canTxSlot_t* pSlot = (canTxSlot_t*)pNode->pTxSlots;

	// a cycle for each Tx slot in the <TxSlots> structure
	for ( ; (uintptr_t)pSlot < ( (uintptr_t)pNode->pTxSlots + sizeof(canTxSlots_t) ); pSlot++ )
	{
		if ( CAN_SLOT_PENDING != pSlot->status )
		{
			continue; // no actions required -> skip this slot
		} //if

		canPacket_t* pPacket = pSlot->pPacket;
		if ( NULL == pPacket)
		{
#ifdef DEBUG
			pSlot->packetErrCnt++; // program error detected...
#endif
			continue;
		} //if

		// prepare the CAN message
		FLEXCAN_TxMsgType txMsg = {
			.u8TxHandle = pSlot->mailbox,
			.eDataType = FLEXCAN_FRAME_DATA,
			.eFrameType = pPacket->IDE,
			.u32CanId = pPacket->Id,
			.aData = { [0 ... 7 ] = 0xFF }, // default values (in accordance with SAE J1939)
		};

		// pack the actual data
		txMsg.u32DataLen = pPacket->pFuncPack( pPacket, txMsg.aData );

		FLEXCAN_ErrorType tRetval = FLEXCAN_TransmitData( pPacket->pNode->hcan, &txMsg );
		if ( FLEXCAN_E_OK == tRetval )
		{
			pPacket->state = P_BOXED;
			pSlot->status = CAN_SLOT_BUSY; // corresponding mailbox is occupied
		} //if
		else
		{
			; // no action required -> skip a transmission
		} //else
#ifdef DEBUG
		pPacket->txCntr += ( FLEXCAN_E_OK == tRetval ) ? 1 : 0;
		pPacket->txErrCntr += ( FLEXCAN_E_OK == tRetval ) ? 0 : 1;
		pSlot->txErrCnt += ( FLEXCAN_E_OK == tRetval ) ? 0 : 1;
#endif
	} //for
} //canProcessSlots()



inline
void CAN_TxCallback( FLEXCAN_HandleType *pHandle, uint8_t u8TxHandle )
{
	canNode_t* pNode = Get_CAN_Node( pHandle );

#ifdef DEBUG
	pNode->pTxSlots->slot[u8TxHandle].txCntr += ( CAN_SLOT_BUSY == pNode->pTxSlots->slot[u8TxHandle].status ) ? 1 : 0;
	pNode->pTxSlots->slot[u8TxHandle].fakeTxCntr += ( CAN_SLOT_BUSY == pNode->pTxSlots->slot[u8TxHandle].status ) ? 0 : 1;
	pNode->pTxSlots->slot[u8TxHandle].pPacket->sentCntr++;
#endif

	if ( CAN_SLOT_BUSY == pNode->pTxSlots->slot[u8TxHandle].status )
	{
		pNode->pTxSlots->slot[u8TxHandle].status = CAN_SLOT_SENT;
	} //if
	else
	{
		; // maybe message abort has been requested -> skip the callback
	} //else

	pNode->tx_done = true; /* Need for unit tests */
}
