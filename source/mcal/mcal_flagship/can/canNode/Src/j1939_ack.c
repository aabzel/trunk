/*
 * j1939_ack.c
 *
 *  Created on: 22 янв. 2024 г.
 *      Author: d.petrov
 *  Modified on: May 22, 2024
 *      Author: karbovskiy
 */

#include "main.h"
#include "can_node.h"
#include "j1939_ack.h"
#include <string.h>



void canAck( J1939tp_t* pJ1939tp, j1939_ack_t ack, uint8_t destAddr, uint32_t destPGN )
{
	if ( P_IDLE == pJ1939tp->pACK->state )
	{
		pJ1939tp->AckData[0] = ack;
		pJ1939tp->AckData[1] = 0xFF;
		pJ1939tp->AckData[2] = 0xFF;
		pJ1939tp->AckData[3] = 0xFF;
		pJ1939tp->AckData[4] = destAddr;
		pJ1939tp->AckData[5] = (destPGN >> 16) & 0xFF;
		pJ1939tp->AckData[6] = (destPGN >> 8) & 0xFF;
		pJ1939tp->AckData[7] = (destPGN >> 0) & 0xFF;
		pJ1939tp->pACK->sendOnce = true;
	} //if
};



uint8_t PackACK_Data( canPacket_t* pPacket, uint8_t* pAddr )
{
	const size_t length = 8;
	memcpy( pAddr, pPacket->pNode->pJ1939tp->AckData, length ); // copy the data
	return length;
}
