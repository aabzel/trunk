#ifndef LORA_TYPES_H
#define LORA_TYPES_H

#include <stdint.h>

//#include "sx1262_constants.h"

typedef struct xLoRaModulationParams_t {
    BandWidth_t band_width;
    SpreadingFactor_t spreading_factor;
    LoRaCodingRate_t coding_rate;
    LowDataRateOpt_t low_data_rate_optimization; //(LDRO)
} LoRaModulationParams_t;

/*Table 13-79: GetPacketStatus SPI Transaction*/
typedef struct xLoRaPacketStatus_t {
    int8_t rssi_pkt;
    uint8_t snr_pkt;
    int8_t signal_rssi_pkt;
} LoRaPacketStatus_t;

typedef struct xLoRaPacketParam_t {
    uint16_t preamble_length;/*PacketParam1 PacketParam2 */
    uint8_t header_type; /*PacketParam3*/
    uint8_t payload_length;/*PacketParam4*/
    uint8_t crc_type;/*PacketParam5*/
    uint8_t invert_iq; /*PacketParam6*/
} LoRaPacketParam_t;

typedef union uModeInfoId_t {
    uint16_t id;
    struct {
        uint8_t spreading_factor : 4; /**/
        uint8_t band_width : 4;       /**/
        uint8_t coding_rate : 4;      /**/
        uint8_t type : 4;             /**/
    };
} ModeInfoId_t;

#endif /* LORA_TYPES_H  */
