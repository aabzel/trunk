#include "neo_6m_drv.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#ifndef HAS_NEO_6M
#include "HAS_NEO_6M component must be included"
#endif

#ifdef HAS_LOG
#include "cli_manager.h"
#include "log.h"
#endif
#include "clocks.h"

#include "gnss_diag.h"
#ifdef HAS_NMEA
#include "nmea_protocol.h"
#endif
#include "none_blocking_pause.h"
#include "sys_config.h"
#include "system.h"
#include "task_config.h"
#include "task_info.h"
#include "time_diag.h"
#include "time_mcal.h"

#include "uart_common.h"
#ifdef HAS_UBLOX
#include "ublox_driver.h"
#include "ubx_protocol.h"
#include "ubx_types.h"
#endif

#ifdef HAS_CLI
#include "writer_config.h"
#endif
#include "neo_6m_diag.h"

bool neo_6m_init(void) {
    bool res = true;

    CfgMsg_t Msg; /*Ok*/
    //memset(&Msg,0,sizeof(CfgMsg_t));
    Msg.msgClass=UBX_CLA_NMEA;
    Msg.msgID=UBX_ID_CFG_NMEA_GLL;
    Msg.rate=1;
    res = ubx_send_message_ack(UBX_CLA_CFG, UBX_ID_CFG_MSG, (uint8_t*) &Msg, sizeof(CfgMsg_t));

    Msg.msgClass=UBX_CLA_NMEA;
    Msg.msgID=UBX_ID_CFG_NMEA_GGA;
    Msg.rate=1;
    res = ubx_send_message_ack(UBX_CLA_CFG, UBX_ID_CFG_MSG, (uint8_t*) &Msg, sizeof(CfgMsg_t));


    Msg.msgClass=UBX_CLA_NMEA;
    Msg.msgID=UBX_ID_CFG_NMEA_ZDA;
    Msg.rate=1;
    res = ubx_send_message_ack(UBX_CLA_CFG, UBX_ID_CFG_MSG, (uint8_t*) &Msg, sizeof(CfgMsg_t));

    //\/ ok
    CfgNmea_t data;
    //memset(&data,0,sizeof(CfgNmea_t));
    data.filter.byte=0;
    data.version=0x23;
    data.numSV=8;
    data.flags.byte=0;
    res = ubx_send_message_ack(UBX_CLA_CFG, UBX_ID_CFG_NMEA, (uint8_t*) &data, sizeof(CfgNmea_t));

    CfgPrt_t CfgPrt;
    //memset(&CfgPrt,0,sizeof(CfgPrt_t));
    CfgPrt.portID=1;
    //CfgPrt.UartMode.dword=;
     CfgPrt.UartMode.charLen=3;
     CfgPrt.UartMode.parity=5;
     CfgPrt.UartMode.nStopBits=0;

    CfgPrt.baudRate=9600;
    CfgPrt.inProtoMask = 0x0001;
    CfgPrt.outProtoMask = 0x0003;
    res = ubx_send_message_ack(UBX_CLA_CFG ,UBX_ID_CFG_PRT , (uint8_t*) &CfgPrt, 20); /*Error*/
#if 0
#endif
    return res;
}

bool neo_6m_proc(void){
    bool res = true;
    return res;
}
