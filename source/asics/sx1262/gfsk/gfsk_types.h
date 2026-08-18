#ifndef GFSK_CONST_H
#define GFSK_CONST_H

#include <stdbool.h>
#include <stdint.h>

typedef struct xGfskPacketParam_t {
    uint16_t preamble_length;         /* packetparam1 & packetparam2*/
    uint8_t preamble_detector_length; /* packetparam3*/
    uint8_t syncword_length;          /* packetparam4*/
    uint8_t addr_comp;                /* packetparam5*/
    uint8_t packet_type;              /* packetparam6*/
    uint8_t payload_length;           /* packetparam7*/
    uint8_t crc_type;                 /* packetparam8*/
    uint8_t whitening;                /* packetParam9*/
} GfskPacketParam_t;

typedef struct xGfskModulationParams_t {
    uint32_t bit_rate;
    uint32_t frequency_deviation;
    uint8_t pulse_shape;
    uint8_t bandwidth;
} GfskModulationParams_t;

typedef union uGfskRxStatus_t{
    uint8_t byte;
    struct{
        uint8_t pkt_sent:1;    /*bit 0*/
        uint8_t pkt_received:1;/*bit 1*/
        uint8_t abort_err:1;   /*bit 2*/
        uint8_t length_err:1;  /*bit 3*/
        uint8_t crc_err:1;     /*bit 4*/
        uint8_t adrs_err:1;    /*bit 5*/
        uint8_t sync_err:1;    /*bit 6*/
        uint8_t preamble_err:1;/*bit 7*/
    };
}GfskRxStatus_t;

typedef struct xGfskPacketStatus_t{
    GfskRxStatus_t RxStatus;
    int8_t rssi_sync;
    int8_t rssi_avg;
} GfskPacketStatus_t ;

#endif /* GFSK_CONST_H  */
