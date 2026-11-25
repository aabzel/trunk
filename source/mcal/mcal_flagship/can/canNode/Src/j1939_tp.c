/*
 * j1939_tp.c
 *
 *  Created on: 28 мар. 2023 г.
 *      Author: d.petrov
 *  Modified on: Oct 6, 2025
 *      Author: karbovskiy
 */


/* ---------------------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

#include "main.h"
#include "j1939_def.h"
#include "j1939_tp.h"
#include "can_packets.h"
#include <string.h>



/* ---------------------------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

extern canTxPackets_t canTxPackets;



/* ---------------------------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

#define J1939TP_BUFFER_FORCE_CLEAR_IS_ENABLED		true
#define J1939TP_INTERVAL_MS							( 50 )	// The required time interval between packets of a Multipacket Broadcast message is 50 to 200 ms.
#define J1939TP_TIMEOUT_MS							( 750 )	// All devices expecting a response must wait at least 1.25s (T3) before giving up or retrying.



/* ---------------------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

J1939tp_t J1939tp0 =
{
#if ( CAN0_J1939TP_IS_USED > 0 )
	.pTPCM = &canTxPackets.CAN0_J1939_TPCM,
	.pTPDT = &canTxPackets.CAN0_J1939_TPDT,
	.pACK = &canTxPackets.CAN0_J1939_ACK,
#else
	.pTPCM = NULL,
	.pTPDT = NULL,
	.pACK = NULL,
#endif
};

J1939tp_t J1939tp1 =
{
#if ( CAN1_J1939TP_IS_USED > 0 )
	.pTPCM = &canTxPackets.CAN1_J1939_TPCM,
	.pTPDT = &canTxPackets.CAN1_J1939_TPDT,
	.pACK = &canTxPackets.CAN1_J1939_ACK,
#else
	.pTPCM = NULL,
	.pTPDT = NULL,
	.pACK = NULL,
#endif
};

J1939tp_t J1939tp2 =
{
#if ( CAN2_J1939TP_IS_USED > 0 )
	.pTPCM = &canTxPackets.CAN2_J1939_TPCM,
	.pTPDT = &canTxPackets.CAN2_J1939_TPDT,
	.pACK = &canTxPackets.CAN2_J1939_ACK,
#else
	.pTPCM = NULL,
	.pTPDT = NULL,
	.pACK = NULL,
#endif
};

J1939tp_t J1939tp3 =
{
#if ( CAN3_J1939TP_IS_USED > 0 )
	.pTPCM = &canTxPackets.CAN3_J1939_TPCM,
	.pTPDT = &canTxPackets.CAN3_J1939_TPDT,
	.pACK = &canTxPackets.CAN3_J1939_ACK,
#else
	.pTPCM = NULL,
	.pTPDT = NULL,
	.pACK = NULL,
#endif
};

J1939tp_t J1939tp4 =
{
#if ( CAN4_J1939TP_IS_USED > 0 )
	.pTPCM = &canTxPackets.CAN4_J1939_TPCM,
	.pTPDT = &canTxPackets.CAN4_J1939_TPDT,
	.pACK = &canTxPackets.CAN4_J1939_ACK,
#else
	.pTPCM = NULL,
	.pTPDT = NULL,
	.pACK = NULL,
#endif
};

J1939tp_t J1939tp5 =
{
#if ( CAN5_J1939TP_IS_USED > 0 )
	.pTPCM = &canTxPackets.CAN5_J1939_TPCM,
	.pTPDT = &canTxPackets.CAN5_J1939_TPDT,
	.pACK = &canTxPackets.CAN5_J1939_ACK,
#else
	.pTPCM = NULL,
	.pTPDT = NULL,
	.pACK = NULL,
#endif
};

J1939tp_t J1939tp6 =
{
#if ( CAN6_J1939TP_IS_USED > 0 )
	.pTPCM = &canTxPackets.CAN6_J1939_TPCM,
	.pTPDT = &canTxPackets.CAN6_J1939_TPDT,
	.pACK = &canTxPackets.CAN6_J1939_ACK,
#else
	.pTPCM = NULL,
	.pTPDT = NULL,
	.pACK = NULL,
#endif
};

J1939tp_t J1939tp7 =
{
#if ( CAN7_J1939TP_IS_USED > 0 )
	.pTPCM = &canTxPackets.CAN7_J1939_TPCM,
	.pTPDT = &canTxPackets.CAN7_J1939_TPDT,
	.pACK = &canTxPackets.CAN7_J1939_ACK,
#else
	.pTPCM = NULL,
	.pTPDT = NULL,
	.pACK = NULL,
#endif
};

J1939tp_t J1939tp8 =
{
#if ( CAN8_J1939TP_IS_USED > 0 )
	.pTPCM = &canTxPackets.CAN8_J1939_TPCM,
	.pTPDT = &canTxPackets.CAN8_J1939_TPDT,
	.pACK = &canTxPackets.CAN8_J1939_ACK,
#else
	.pTPCM = NULL,
	.pTPDT = NULL,
	.pACK = NULL,
#endif
};

J1939tp_t J1939tp9 =
{
#if ( CAN9_J1939TP_IS_USED > 0 )
	.pTPCM = &canTxPackets.CAN9_J1939_TPCM,
	.pTPDT = &canTxPackets.CAN9_J1939_TPDT,
	.pACK = &canTxPackets.CAN9_J1939_ACK,
#else
	.pTPCM = NULL,
	.pTPDT = NULL,
	.pACK = NULL,
#endif
};



/* ---------------------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* ---------------------------------------------------------------------------*/

static void j1939tpAbortTx( canPacket_t* const pPacket );



/* ---------------------------------------------------------------------------*/
/* Public Functions ----------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

int32_t j1939tpGetRxPacket( J1939tp_t* pJ1939tp, FLEXCAN_RxMsgType *pRxMsg )
{
	if ( NULL == pJ1939tp ) return -1; // filter mismatch

	if ( CAN_ID_EXT != pRxMsg->eFrameType ) return -1; // filter mismatch

	const J1939_ID_t id = { .Extended = pRxMsg->u32CanId };
	if ( J1939_TPCM_PNG != id.pgn.PGN && J1939_TPDT_PNG != id.pgn.PGN ) return -1; // filter mismatch
	
	// store new packet to use with Rx handler
	if ( !pJ1939tp->Rx.IsNewPacketAvailable )
	{
		pJ1939tp->Rx.Msg = *pRxMsg; // copy the header and data
		pJ1939tp->Rx.HeaderPGN = id.pgn.PGN;
		pJ1939tp->Rx.IsNewPacketAvailable = true;
	} //if
	else
	{
		pJ1939tp->RxWhenNotReadyCntr++;
	} //else

	return 0; // filter matches
}



bool j1939tpStartTx( canNode_t* pNode, canPacket_t* pPacket )
{
	if ( NULL == pPacket->pTP->pData )
	{
		return false;
	} //if

	if ( 0 == pPacket->pTP->DataBytes )
	{
		return false;
	} //if

	J1939tp_t* pJ1939tp = pNode->pJ1939tp;

	// register request to start transmission
	if ( TP_RX_IDLE != pJ1939tp->Rx.State )
	{
		return false;
	} //if

	if ( TP_TX_IDLE != pJ1939tp->Tx.State )
	{
		return false;
	} //if

	else // CAN bus is free for new TP
	{
		if ( pPacket->pTP->DataBytes > J1939_TP_MAX_LENGTH )
		{
			return false;
		} //if

		pJ1939tp->Tx.tpdt.MsgByteIndex = 0;
		pJ1939tp->Tx.tpdt.SeqIndex = 0;

		uint16_t msgSize = pPacket->pTP->DataBytes;
		pJ1939tp->Tx.pData = pPacket->pTP->pData;
		pJ1939tp->Tx.tpcm.BAM.Control = TPCM_FORMAT_BAM;
		pJ1939tp->Tx.tpcm.BAM.MsgSize = msgSize;
		pJ1939tp->Tx.tpcm.MsgSizeLeft = msgSize;
		pJ1939tp->Tx.tpcm.BAM.NumOfPackets = (uint8_t)( msgSize / 7U );
		if ( 0 != ( msgSize % 7U ) )
		{
			pJ1939tp->Tx.tpcm.BAM.NumOfPackets++;
		} //if

		const J1939_ID_t id = { .Extended = pPacket->Id };
		pJ1939tp->Tx.tpcm.BAM.PGN = id.pgn.PGN;
		pJ1939tp->Tx.IsPending = true;
		return true;
	}

	return false;
}



j1939tpResult_t j1939tpPollStatus( canNode_t* pNode )
{
	bool isPacketsReady = 	( pNode->pJ1939tp->pTPCM->state == P_IDLE )
						 && ( pNode->pJ1939tp->pTPDT->state == P_IDLE );

	if ( false == isPacketsReady )
	{
		return TP_BUSY;
	} //if

	switch ( pNode->pJ1939tp->Tx.State )
	{

	case TP_TX_IDLE :
	{
		return TP_OK;
		break;
	} //case

	case TP_TX_HEADER_TX :
	case TP_TX_HEADER_TX_WAIT :
	case TP_TX_HEADER_TX_TIMEOUT :
	case TP_TX_DATA_TX :
	case TP_TX_DATA_TX_WAIT :
	case TP_TX_DATA_TX_DELAY :
	case TP_TX_INTERRUPTED_BY_BUS :
	default :
	{
		return TP_BUSY;
		break;
	} //default

	} //switch
}



j1939tpResult_t j1939tpPollSuccess( J1939tp_t* pJ1939tp )
{
	switch ( pJ1939tp->Tx.State )
	{

	case TP_TX_IDLE :
	{
		return ( true == pJ1939tp->Tx.IsPending ) ? TP_BUSY : TP_OK;
		break;
	} //case

	case TP_TX_INTERRUPTED_BY_BUS :
	{
		// interrupt gonna be handled -> release the state
		pJ1939tp->IsInterruptHandled = true;
		return TP_ERROR;
		break;
	} //case

	case TP_TX_HEADER_TX :
	case TP_TX_HEADER_TX_WAIT :
	case TP_TX_HEADER_TX_TIMEOUT :
	case TP_TX_DATA_TX :
	case TP_TX_DATA_TX_WAIT :
	case TP_TX_DATA_TX_DELAY :
	default :
	{
		return TP_BUSY;
		break;
	} //default

	} //switch
}



void j1939tpHandler( canNode_t* pNode )
{
	J1939tp_t* pJ1939tp = pNode->pJ1939tp;

	if ( false == pJ1939tp->IsInited )
	{
		if ( FLEXCAN_SEQUENCE_STARTED == pNode->hcan->tStatus.eStatusSeq )
		{
#if J1939TP_BUFFER_FORCE_CLEAR_IS_ENABLED
			for ( size_t i = 0; i < J1939_TP_MAX_LENGTH; i++ )
			{
				pJ1939tp->DataBuffer[i] = 0;
			} //for
#endif
			pJ1939tp->Rx.tpdt.MsgByteIndex = 0;
			pJ1939tp->Rx.tpdt.SeqIndex = 0;
			pJ1939tp->Rx.tpdt.SeqIndexPrev = 0;
			pJ1939tp->Rx.tpcm.RemainingMsgSize = 0;
			pJ1939tp->Rx.tpcm.BAM.PGN = J1939_PGN_MASK;
			pJ1939tp->Rx.State = TP_RX_IDLE;

			pJ1939tp->Tx.tpdt.MsgByteIndex = 0;
			pJ1939tp->Tx.tpdt.SeqIndex = 0;
			pJ1939tp->Tx.tpcm.MsgSizeLeft = 0;
			pJ1939tp->Tx.tpcm.BAM.PGN = J1939_PGN_MASK;
			pJ1939tp->Tx.State = TP_TX_IDLE;

			pJ1939tp->IsInited = true;
		} //if
		else
		{
			return; // CAN node is not ready
		} //else
	} //if
	else
	{
		; //no actions required...
	} //else

	// state machine validation
	if ( ( TP_RX_IDLE != pJ1939tp->Rx.State ) && ( TP_TX_IDLE != pJ1939tp->Tx.State ) )
	{
		pJ1939tp->StateErrorCntr++;
		pJ1939tp->Tx.State = TP_TX_IDLE;
	} //if

	switch ( pJ1939tp->Rx.State )
	{

	case TP_RX_IDLE :
	{
		// check for the received TP packets
		if ( true == pJ1939tp->Rx.IsNewPacketAvailable )
		{
			if ( TP_TX_IDLE == pJ1939tp->Tx.State )
			{
				; // TP is free -> no actions required...
			} //if
			else
			{
				if ( TP_TX_INTERRUPTED_BY_BUS != pJ1939tp->Tx.State )
				{
					j1939tpAbortTx( pNode->pJ1939tp->pTPCM );
					j1939tpAbortTx( pNode->pJ1939tp->pTPDT );
					pJ1939tp->Tx.State = TP_TX_INTERRUPTED_BY_BUS;
				} //if
				else
				{
					; // no actions required...
				} //else
				break; // wait for the transfer interrupt to complete
			} //else

			if ( pJ1939tp->Rx.HeaderPGN == J1939_TPCM_PNG )
			{
				// start receiving a new message
				pJ1939tp->Rx.State = TP_RX_HEADER_RX;
				break;
			} //if
			else if ( pJ1939tp->Rx.HeaderPGN == J1939_TPDT_PNG )
			{
				// data received, but not header, means we've missed BAM message
				// omit all following data until BAM header rx
				pJ1939tp->Rx.IsNewPacketAvailable = false;
				break;
			} //elif
			else
			{
				; // program error detected...
			} //else
		} //if
		else
		{
			; // no actions required...
		} //else

		break;
	} // case

	case TP_RX_HEADER_RX :
	{
		if ( pJ1939tp->Rx.Msg.aData[0] == TPCM_FORMAT_BAM )
		{
			pJ1939tp->Rx.tpdt.MsgByteIndex = 0;
			pJ1939tp->Rx.tpdt.SeqIndex = 0;
			pJ1939tp->Rx.tpdt.SeqIndexPrev = 0;
			pJ1939tp->Rx.tpcm.BAM.PGN = J1939_PGN_MASK;

			memcpy( pJ1939tp->Rx.tpcm.BAM.Bytes, pJ1939tp->Rx.Msg.aData, sizeof( pJ1939tp->Rx.tpcm.BAM.Bytes ) );
			pJ1939tp->Rx.tpcm.RemainingMsgSize = pJ1939tp->Rx.tpcm.BAM.MsgSize;
			pJ1939tp->Rx.State = TP_RX_HEADER_OK;
		} //if
		else
		{
			// corrupted header, omit this TP message chain
			pJ1939tp->Rx.State = TP_RX_IDLE;
		} //else

		pJ1939tp->Rx.IsNewPacketAvailable = false;
		break;
	} //case

	case TP_RX_HEADER_OK :
	{
		// wait for data rx
		if ( true == pJ1939tp->Rx.IsNewPacketAvailable )
		{
			// wait for new packet
			if ( pJ1939tp->Rx.HeaderPGN == J1939_TPCM_PNG )
			{
				// TP.CM BAM rx -> no data after previous BAM
				pJ1939tp->Rx.State = TP_RX_HEADER_RX;
			} //if
			else if ( pJ1939tp->Rx.HeaderPGN == J1939_TPDT_PNG )
			{
				// data received
				pJ1939tp->Rx.State = TP_RX_DATA_RX;
			} //elif
			else
			{
				; // program error detected...
			} //else
		} //if
		break;
	} //case

	case TP_RX_DATA_RX :
	{
		pJ1939tp->RxDataTimer++;

		if ( true == pJ1939tp->Rx.IsNewPacketAvailable )
		{
			// wait for the new packet (or process packet from prev switch state)
			if ( pJ1939tp->Rx.HeaderPGN == J1939_TPCM_PNG )
			{
				// TP.CM BAM rx -> receiving BAM too early -> prev data is corrupted
				pJ1939tp->Rx.State = TP_RX_HEADER_RX;
			} //if
			else if ( pJ1939tp->Rx.HeaderPGN == J1939_TPDT_PNG )
			{
				// data received
				pJ1939tp->Rx.tpdt.SeqIndex = pJ1939tp->Rx.Msg.aData[0];
				if ( pJ1939tp->Rx.tpdt.SeqIndex != ( pJ1939tp->Rx.tpdt.SeqIndexPrev + 1 ) )
				{
					// part of sequence is skipped
					pJ1939tp->Rx.State = TP_RX_DATA_CORRUPTED;
					break;
				} //if

				// try to receive 7 bytes or less
				uint8_t bytesToRx = pJ1939tp->Rx.tpcm.RemainingMsgSize > 7 ? 7 : pJ1939tp->Rx.tpcm.RemainingMsgSize;

				for ( size_t i = 0; i < bytesToRx; i++ )
				{
					pJ1939tp->DataBuffer[pJ1939tp->Rx.tpdt.MsgByteIndex] = pJ1939tp->Rx.Msg.aData[i+1];
					pJ1939tp->Rx.tpdt.MsgByteIndex++;
				} //for

				pJ1939tp->Rx.tpcm.RemainingMsgSize -= bytesToRx;
				pJ1939tp->Rx.tpdt.SeqIndexPrev = pJ1939tp->Rx.tpdt.SeqIndex;
			} //elif
			else
			{
				; // program error detected...
			} //else

			pJ1939tp->Rx.IsNewPacketAvailable = false;
			pJ1939tp->RxDataTimer = 0;
		} //if

		if ( 0 == pJ1939tp->Rx.tpcm.RemainingMsgSize )
		{
			pJ1939tp->Rx.State = TP_RX_DATA_OK;
		} //if

		if ( pJ1939tp->RxDataTimer >= J1939TP_TIMEOUT_MS )
		{
			pJ1939tp->RxDataTimer = 0;
			pJ1939tp->Rx.State = TP_RX_DATA_TIMEOUT;
		} //if

		break;
	} //case

	case TP_RX_DATA_OK :
	{
		const J1939_ID_t id =
		{
			.pgn =
			{
				.SourceAddress = pJ1939tp->Rx.Msg.u32CanId & 0xFF,
				.PGN = pJ1939tp->Rx.tpcm.BAM.PGN,
				.Priority = 0, // not used
			},
		};

		FLEXCAN_RxMsgType msg =
		{
			.u8CanIndex = pNode->hcan->eInstance,
			.u8RxHandle = 0,
			.u32CanId = id.Extended,
			.eFrameType = CAN_ID_EXT,
			.eDataType = FLEXCAN_FRAME_DATA,
			.u32DataLen = pJ1939tp->Rx.tpcm.BAM.MsgSize,
		};
		memcpy( msg.aData, pJ1939tp->DataBuffer, sizeof(msg.aData) ); // copy the data
		canJ1939RxHandler( &msg );

		pJ1939tp->Rx.State = TP_RX_DATA_READY;
		break;
	} //case

	case TP_RX_DATA_CORRUPTED :
	{
		pJ1939tp->RxCorruptedCntr++;
		pJ1939tp->Rx.State = TP_RX_IDLE;
		break;
	} //case

	case TP_RX_DATA_TIMEOUT :
	{
		pJ1939tp->RxTimeoutCntr++;
		pJ1939tp->Rx.State = TP_RX_IDLE;
		break;
	} //case

	case TP_RX_DATA_READY :
	{
		pJ1939tp->RxOkCntr++;
		pJ1939tp->Rx.State = TP_RX_IDLE;
		break;
	} //case

	default :
	{
		break;
	} //default

	} //switch

	switch ( pJ1939tp->Tx.State )
	{

	case TP_TX_IDLE :
	{
		// check the TP receiver state
		if ( TP_RX_IDLE == pJ1939tp->Rx.State )
		{
			if ( pJ1939tp->Tx.IsPending )
			{
				// tx is requested and bus is ready: prepare the data
				pJ1939tp->Tx.State = TP_TX_HEADER_TX;
				pJ1939tp->Tx.IsPending = false;
			} //if
		} //if
		break;
	} //case

	case TP_TX_HEADER_TX :
	{
		// form the TPCM packet
		memcpy( pJ1939tp->Tx.Data, pJ1939tp->Tx.tpcm.BAM.Bytes, sizeof( pJ1939tp->Tx.Data ) ); // copy the data

		// transmit the TPCM BAM
		if ( ( false == pNode->pJ1939tp->pTPCM->sendOnce ) && ( false == pNode->pJ1939tp->pTPDT->sendOnce ) )
		{
			pNode->pJ1939tp->pTPCM->sendOnce = true;
			pJ1939tp->Tx.State = TP_TX_HEADER_TX_WAIT;
		} //if
		break;
	} //case

	case TP_TX_HEADER_TX_WAIT :
	{
		// wait for sendOnce flag to go FALSE -> packet sent OK
		if ( true == pNode->pJ1939tp->pTPCM->isSent )
		{
			// TPCM sent OK
			pJ1939tp->Tx.State = TP_TX_HEADER_TX_TIMEOUT;
		} //if
		break;
	} //case

	case TP_TX_HEADER_TX_TIMEOUT :
	{
		// after frame sent, wait a bit (up to 200 ms)
		pJ1939tp->TxHeaderTimer++;
		if ( pJ1939tp->TxHeaderTimer >= J1939TP_INTERVAL_MS )
		{
			pJ1939tp->TxHeaderTimer = 0;
			pJ1939tp->Tx.State = TP_TX_DATA_TX;
		} //if
		break;
	} //case

	case TP_TX_DATA_TX :
	{
		// create Tx packet according to current Tx index
		pJ1939tp->Tx.Data[0] = pJ1939tp->Tx.tpdt.SeqIndex + 1U;

		uint8_t bytesToTx = pJ1939tp->Tx.tpcm.MsgSizeLeft > 7 ? 7 : pJ1939tp->Tx.tpcm.MsgSizeLeft;

		for ( size_t i = 0; i < bytesToTx; i++ )
		{
			pJ1939tp->Tx.Data[i+1] = pJ1939tp->Tx.pData[pJ1939tp->Tx.tpdt.MsgByteIndex];
			pJ1939tp->Tx.tpdt.MsgByteIndex++;
		} //for

		if (false == pNode->pJ1939tp->pTPDT->sendOnce && false == pNode->pJ1939tp->pTPCM->sendOnce)
		{
			// send this TPDT
			pJ1939tp->Tx.tpcm.MsgSizeLeft -= bytesToTx;
			pJ1939tp->Tx.tpdt.SeqIndex++;

			pNode->pJ1939tp->pTPDT->sendOnce = true;
			pJ1939tp->Tx.State = TP_TX_DATA_TX_WAIT;
		} //if

		break;
	} //case

	case TP_TX_DATA_TX_WAIT :
	{
		// wait for sendOnce flag to go FALSE -> packet sent OK
		if ( true == pNode->pJ1939tp->pTPDT->isSent )
		{
			// TPDT sent OK
			if ( pJ1939tp->Tx.tpdt.SeqIndex < pJ1939tp->Tx.tpcm.BAM.NumOfPackets )
			{
				// send packets until done
				pJ1939tp->Tx.State = TP_TX_DATA_TX_DELAY;
			} //if
			else
			{
				pJ1939tp->TxOkCntr++;
				pJ1939tp->Tx.State = TP_TX_IDLE;
			} //else
		} //if
		break;
	} //case

	case TP_TX_DATA_TX_DELAY :
	{
		// after frame sent, wait a bit (up to 200 ms)
		if ( ++pJ1939tp->TxDataTxTimer >= J1939TP_INTERVAL_MS )
		{
			pJ1939tp->TxDataTxTimer = 0;
			pJ1939tp->Tx.State = TP_TX_DATA_TX;
		} //if
		break;
	} //case

	case TP_TX_INTERRUPTED_BY_BUS :
	{
		// someone else on the bus messed up our TP Tx
		if ( true == pJ1939tp->IsInterruptHandled )
		{
			pJ1939tp->Tx.State = TP_TX_IDLE;
			pJ1939tp->IsInterruptHandled = false;
		} //if
		else
		{
			; // no actions required -> wait for corresponding packet to be released
		} //else
		break;
	} //case

	default :
	{
		break; // program error detected... // ToDo add error counter
	} //case

	} //switch
}



uint8_t j1939tpPackData( canPacket_t* pPacket, uint8_t* pAddr )
{
	const size_t length = 8;
	memcpy( pAddr, pPacket->pNode->pJ1939tp->Tx.Data, length ); // copy the data
	return (uint8_t)length;
}



/* ---------------------------------------------------------------------------*/
/* Private Functions ---------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

static void j1939tpAbortTx( canPacket_t* const pPacket )
{
	pPacket->state = P_ABORT;
	pPacket->waitTime = 0;
	pPacket->sendOnce = false;

	if ( NULL != pPacket->pSlot )
	{
		if ( CAN_SLOT_PENDING == pPacket->pSlot->status )
		{
			pPacket->pSlot->status = CAN_SLOT_EMPTY;
		} //if
		else
		{
			; // slot is already being processed -> no actions required...
		} //else
	} //if
	else
	{
		; // no actions required...
	} //else
}
