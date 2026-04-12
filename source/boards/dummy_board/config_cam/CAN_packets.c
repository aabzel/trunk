/*
 * can_packets.c
 */


/* ---------------------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

#include "main.h"
#include "can_node.h"
#include "j1939_tp.h"
#include "j1939_ack.h"
#ifdef HAS_XCP
#include "XCP_on_CAN.h"
#endif
#ifdef HAS_UDS
#include "UDS_on_CAN.h"
#endif
#include "can_packets.h"
#include <string.h>



/* ---------------------------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/  

/* ---------------------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

canTxPackets_t canTxPackets = {

#if ( XCP_ON_CAN > 0 )
	.CAN_XCP = {			.pNode = NULL,		.Id = XCP_TX_CAN_ID,	.IDE = CAN_ID_STD,	.pFuncPack = PackXCP_Data,		.period = 0,		.isJ1939 = false,	.isEnabled = true,	},
#endif

#ifdef HAS_J1939
	.CAN0_J1939_TPCM = {	.pNode = &canNode0,	.Id = J1939_TPCM_ID,	.IDE = CAN_ID_EXT,	.pFuncPack = &PackTP_Data,		.period = 0,		.isJ1939 = true,	.isEnabled = true,	},
	.CAN0_J1939_TPDT = {	.pNode = &canNode0,	.Id = J1939_TPDT_ID,	.IDE = CAN_ID_EXT,	.pFuncPack = &PackTP_Data,		.period = 0,		.isJ1939 = true,	.isEnabled = true,	},
	.CAN0_J1939_ACK = {		.pNode = &canNode0,	.Id = J1939_ACK_ID,		.IDE = CAN_ID_EXT,	.pFuncPack = &PackACK_Data,		.period = 0,		.isJ1939 = true,	.isEnabled = true,	},
	.CAN3_J1939_TPCM = {	.pNode = &canNode4,	.Id = J1939_TPCM_ID,	.IDE = CAN_ID_EXT,	.pFuncPack = &PackTP_Data,		.period = 0,		.isJ1939 = true,	.isEnabled = true,	},
	.CAN3_J1939_TPDT = {	.pNode = &canNode4,	.Id = J1939_TPDT_ID,	.IDE = CAN_ID_EXT,	.pFuncPack = &PackTP_Data,		.period = 0,		.isJ1939 = true,	.isEnabled = true,	},
	.CAN3_J1939_ACK = {		.pNode = &canNode4,	.Id = J1939_ACK_ID,		.IDE = CAN_ID_EXT,	.pFuncPack = &PackACK_Data,		.period = 0,		.isJ1939 = true,	.isEnabled = true,	},
#endif

	.CAN_TX_MSGS = { /* packets configuration provided via custom canTxMsgsInit() implementation */ },
};



/* ---------------------------------------------------------------------------*/
/* Public Functions ----------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

__WEAK
uint8_t PackCustomData( canPacket_t* pPacket, uint8_t* pAddr )
{
	/* debug packer only */
	const size_t length = 8;
	memcpy( pAddr, pPacket, length ); // copy the data
	return length;
#if 0
	/* template usage */
	if ( &canTxPackets.CUSTOM_PACKET_1 == pPacket )
	{
		; // copy the corresponding data
	} //if
	else if ( &canTxPackets.CUSTOM_PACKET_2 == pPacket )
	{
		; // copy the corresponding data
	} //elif
	else
	{
		; // program error detected...
	} //else
#endif

} //PackCustomData()



/* ---------------------------------------------------------------------------*/
/* Private Functions ---------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/
