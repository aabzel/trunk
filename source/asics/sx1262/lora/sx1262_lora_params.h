#ifndef SX1262_LORA_PARAMS_H
#define SX1262_LORA_PARAMS_H

#include "param_drv.h"
#include "param_types.h"

#define PARAMS_SX1262_LORA                                                       \
    {LORA,PAR_ID_LORA_SF, 1, TYPE_UINT8, "SF"},            /*Chips / Symbol*/              \
    {LORA,PAR_ID_LORA_CR, 1, TYPE_UINT8, "CR"},           /*in raw bits/total bits*/       \
    {LORA,PAR_ID_LORA_BW, 1, TYPE_UINT8, "BW"},            /*Hz*/                          \
    {LORA,PAR_ID_LOW_DATA_RATE, 1, TYPE_UINT8, "LowDataRate"},                             \
    {LORA,PAR_ID_PREAMBLE_LENGTH, 2, TYPE_UINT16, "PreLen"}, /*bytes*/                     \
    {LORA, PAR_ID_PAYLOAD_LENGTH, 1, TYPE_UINT8, "PayLen"},   /*bytes*/                    \
    {LORA,PAR_ID_LORA_HEADER_TYPE, 1, TYPE_UINT8, "LoRaHeadType"},                         \
    {LORA,PAR_ID_LORA_SYNC_WORD, 2, TYPE_UINT16, "LoRaSyncWord"},                          \
    {LORA,PAR_ID_CRC_TYPE, 1, TYPE_UINT8, "CRC_T"},

#endif /* SX1262_LORA_PARAMS_H  */
