#ifndef SX1262_PARAMS_H
#define SX1262_PARAMS_H

#include "param_drv.h"
#include "param_types.h"

#ifdef HAS_GFSK
#include "sx1262_gfsk_params.h"
#else
#define PARAMS_SX1262_GFSK
#endif

#ifdef HAS_LORA
#include "sx1262_lora_params.h"
#else
#define PARAMS_SX1262_LORA
#endif

#define PARAMS_SX1262       \
    PARAMS_SX1262_LORA      \
    PARAMS_SX1262_GFSK      \
    {SX1262, PAR_ID_FREQ, 4, TYPE_UINT32, "Freq"},   /*Hz*/                              \
    {SX1262, PAR_ID_WIRELESS_INTERFACE, 1, TYPE_UINT8, "Interface"},    /*LoRa or GFSK*/          \
    {SX1262, PAR_ID_TX_MUTE, 1, TYPE_UINT8, "TxMute"},                                        \
    {SX1262, PAR_ID_RX_GAIN, 1, TYPE_UINT8, "RxGain"},         \
    {SX1262, PAR_ID_RETX, 1, TYPE_UINT8, "ReTx"},              \
    {SX1262, PAR_ID_IQ_SETUP, 1, TYPE_UINT8, "IQSetUp"},                                         \
    {SX1262, PAR_ID_OUT_POWER, 1, TYPE_INT8, "OutPower"}, /*loRa output power*/          \
    {SX1262, PAR_ID_MAX_LINK_DIST, 8, TYPE_DOUBLE, "MaxLinkDist"}, /*Max Link Distance*/ \
    {SX1262, PAR_ID_MAX_BIT_RATE, 8, TYPE_DOUBLE, "MaxBitRate"}, /*Max bit/rate*/   \
    {SX1262, PAR_ID_RETX_CNT, 1, TYPE_UINT8, "ReTxCnt"},


#endif /* SX1262_PARAMS_H  */
