#ifndef SX1262_GFSK_PARAMS_H
#define SX1262_GFSK_PARAMS_H

#include "param_ids.h"
#include "param_types.h"
#include "log.h"

#define PARAMS_SX1262_GFSK                                              \
    {GFSK, PAR_ID_ADDR_COMP, 1, TYPE_UINT8, "AddrComp"},                \
    {GFSK, PAR_ID_BROADCAST_ADDR, 1, TYPE_UINT8, "BrdCastAddr"},        \
    {GFSK, PAR_ID_GFSK_BANDWIDTH, 1, TYPE_UINT8, "Bandwidth"},          \
    {GFSK, PAR_ID_GFSK_BITRATE,4,TYPE_UINT32, "BitRate"},               \
    {GFSK, PAR_ID_GFSK_CRC_TYPE, 1, TYPE_UINT8, "CrcGfsk"},             \
    {GFSK, PAR_ID_GFSK_FREQ_DEV, 4, TYPE_UINT32, "FreqDev"},            \
    {GFSK, PAR_ID_GFSK_PACKET_TYPE,1,TYPE_UINT8,"PktType"},             \
    {GFSK, PAR_ID_GFSK_PAYLOAD_LEN, 1 ,TYPE_UINT8,"PayLen"},            \
    {GFSK, PAR_ID_GFSK_PRE_LEN, 2 , TYPE_UINT16, "PreLen"},             \
    {GFSK, PAR_ID_GFSK_PULSE_SHAPE, 1, TYPE_UINT8, "PulseShape"},       \
    {GFSK, PAR_ID_CRC_INIT, 2, TYPE_UINT16, "CrcInit"},            \
    {GFSK, PAR_ID_CRC_POLY, 2, TYPE_UINT16, "CrcPoly"},            \
    {GFSK, PAR_ID_SYNC_WORD_LEN, 1 , TYPE_UINT8, "SyncWordLen"},        \
    {GFSK, PAR_ID_NODE_ADDR, 1, TYPE_UINT8, "NodeAddr"},                \
    {GFSK, PAR_ID_PRE_DET_LEN, 1, TYPE_UINT8, "PreDetLen"},             \
    {GFSK, PAR_ID_SYNC_WORD, 8, TYPE_UINT64, "SyncWord"},               \
    {GFSK, PAR_ID_WHITENING, 1, TYPE_UINT8, "Whitening"},               \
    {GFSK, PAR_ID_WHITENING_INIT_VALUE, 2, TYPE_UINT16, "WhitenInit"},


#endif /* SX1262_GFSK_PARAMS_H  */
