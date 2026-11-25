/*
 * j1939_tp.h
 *
 *  Created on: Apr 24, 2023
 *      Author: d.petrov
 *  Modified on: Sep 10, 2025
 *      Author: karbovskiy
 */

#ifndef INC_J1939_TP_H_
#define INC_J1939_TP_H_


/* ---------------------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

#include "can_node.h"
#include "can_tx.h"



/* ---------------------------------------------------------------------------*/
/* Defines -------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

#define J1939_TP_MAX_LENGTH	( 1785U )				// [bytes] J1939 standard provides 1785 bytes maximum per one TP packet
#define J1939_TPCM_PNG		( 0xECFF )
#define J1939_TPDT_PNG		( 0xEBFF )
#define J1939_ACK_PNG		( 0xE800 )

#define J1939_TPCM_ID		( ( J1939_TP_PRIO << 26 ) + ( J1939_TPCM_PNG << 8 ) + J1939_ECU_ADDR )
#define J1939_TPDT_ID		( ( J1939_TP_PRIO << 26 ) + ( J1939_TPDT_PNG << 8 ) + J1939_ECU_ADDR )
#define J1939_ACK_ID		( ( J1939_TP_PRIO << 26 ) + ( J1939_ACK_PNG << 8 ) + J1939_ECU_ADDR )



/* ---------------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

typedef struct canPacket_t canPacket_t;
typedef struct canNode_t canNode_t;
typedef struct J1939tp_t J1939tp_t;



enum
{
	TPCM_FORMAT_RTS = 16,
	TPCM_FORMAT_CTS = 17,
	TPCM_FORMAT_EOA = 19,
	TPCM_FORMAT_BAM = 32,
	TPCM_FORMAT_ABORT = 255,
};


typedef enum
{
	TP_RX_IDLE,				// when ready to Rx
	TP_RX_HEADER_RX,		// receiving TPCM
	TP_RX_HEADER_OK,		// TP_CM received and it's OK
	TP_RX_DATA_RX,			// receiving data
	TP_RX_DATA_OK,			// data OK
	TP_RX_DATA_CORRUPTED,	// data NG
	TP_RX_DATA_TIMEOUT,		// data rx took tool long
	TP_RX_DATA_READY,		// data can be extracted from rx buffer

} tpRxState_t;



typedef enum
{
	TP_TX_IDLE,				// when ready to Tx
	TP_TX_HEADER_TX,		// transmitting header
	TP_TX_HEADER_TX_WAIT,	// wait for Tx to go be done
	TP_TX_HEADER_TX_TIMEOUT,// timeout after Tx OK (as specified by SAE)
	TP_TX_DATA_TX,			// transmitting data
	TP_TX_DATA_TX_WAIT,		// waiting for Tx OK
	TP_TX_DATA_TX_DELAY,	// wait after packet
	TP_TX_INTERRUPTED_BY_BUS,// interrupted by someone else

} tpTxState_t;



typedef enum
{
	TP_OK,
	TP_BUSY,
	TP_ERROR
} j1939tpResult_t;



/**
  * @brief  J1939 TP.CM_RTS Structure Definition
  * @Note	Connection Mode Request to Send (TP.CM_RTS): Destination Specific
  */
typedef union
{
	struct
	{
		uint32_t		Control			: 8;	/*!< Control byte = 16, Destination Specific Request_To_Send (RTS) */
		uint32_t		MsgSize			: 16;	/*!< Total message size, number of bytes */
		uint32_t		NumOfPackets	: 8;	/*!< Total number of packets */
		uint32_t		MaxNumOfPackets	: 8;	/*!< Maximum number of packets that can be sent in response to one CTS. FF indicates that no limit exists for the originator. */
		uint32_t		PGN				: 24;	/*!< Parameter Group Number of the packeted message */
	};

	uint8_t				Bytes[8];				/*!< Byte array access provided by union */

} tpcmRTS_t;



/**
  * @brief  J1939 TP.CM_BAM Structure Definition
  * @Note	Broadcast Announce Message (TP.CM_BAM): Global Destination
  */
typedef union
{
	struct
	{
		uint32_t		Control			: 8;	/*!< Control byte = 32, Broadcast Announce Message */
		uint32_t		MsgSize			: 16;	/*!< Total message size, number of bytes */
		uint32_t		NumOfPackets	: 8;	/*!< Total number of packets */
		uint32_t						: 8;	/*!< Reserved for assignment by SAE, this byte should be filled with FF */
		uint32_t		PGN				: 24;	/*!< Parameter Group Number of the packeted message */
	};

	uint8_t				Bytes[8];				/*!< Byte array access provided by union */

} tpcmBAM_t;



typedef struct
{
	tpRxState_t				State;
	bool					IsNewPacketAvailable;
	FLEXCAN_RxMsgType 		Msg;
	uint32_t				HeaderPGN;

	// TP.CM
	struct
	{
		tpcmBAM_t			BAM;
		uint16_t			RemainingMsgSize;
	} tpcm;

	// TP.DT
	struct
	{
		uint16_t			MsgByteIndex;
		uint8_t				SeqIndex;
		uint8_t				SeqIndexPrev;
	} tpdt;

} tpRx_t;



typedef struct
{
	tpTxState_t				State;
	bool					IsPending;
	uint8_t					Data[8];

	// TP.CM
	struct
	{
		tpcmBAM_t			BAM;
		uint32_t			MsgSizeLeft;
	} tpcm;

	// TP.DT
	struct
	{
		uint16_t			MsgByteIndex;
		uint8_t				SeqIndex;
	} tpdt;

	uint8_t*				pData;

} tpTx_t;



struct J1939tp_t
{
	tpRx_t					Rx;

	tpTx_t					Tx;

	canPacket_t*			pTPCM;

	canPacket_t*			pTPDT;

	canPacket_t*			pACK;

	uint8_t					DataBuffer[J1939_TP_MAX_LENGTH];

	uint8_t					AckData[8];

	uint32_t				RxDataTimer;

	uint32_t				TxHeaderTimer;

	uint32_t				TxDataTxTimer;

	bool					IsInited;

	bool					IsInterruptHandled;

	uint32_t				TxOkCntr;			// debug only

	uint32_t				RxOkCntr;			// debug only

	uint32_t				RxCorruptedCntr;	// debug only

	uint32_t				RxTimeoutCntr;		// debug only

	uint32_t				RxWhenNotReadyCntr;	// debug only

	uint32_t				StateErrorCntr;		// debug only
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

void j1939tpHandler( canNode_t* pNode );

int32_t j1939tpGetRxPacket( J1939tp_t* pJ1939tp, FLEXCAN_RxMsgType *pRxMsg );
bool j1939tpStartTx( canNode_t* pNode, canPacket_t* pPacket );

j1939tpResult_t j1939tpPollSuccess( J1939tp_t* pJ1939tp );
j1939tpResult_t j1939tpPollStatus( canNode_t* pNode );

uint8_t j1939tpPackData( canPacket_t* pPacket, uint8_t* pAddr );



/* ---------------------------------------------------------------------------*/
/* Asserts -------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

#if ( J1939_TP_MAX_LENGTH > 1785 )
#error J1939 TP BUFFER SIZE IS REDUNDANT
#endif
#if ( J1939_TP_MAX_LENGTH < 64 )
#warning J1939 TP BUFFER SIZE IS INSUFFICIENT
#endif



#endif /* INC_J1939_TP_H_ */
