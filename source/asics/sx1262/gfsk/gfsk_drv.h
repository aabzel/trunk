
#ifndef GFSK_DRV_H
#define GFSK_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "sx1262_types.h"
#include "gfsk_types.h"

uint8_t GfskCrcType2Len(uint8_t code);
uint8_t SyncWordLenCode2Len(uint8_t code);
bool gfsk_proc_rx_status(GfskRxStatus_t RxStatus);

double gfsk_calc_max_frame_tx_time(uint32_t bitrate,
                                   uint16_t n_preamble,
                                   uint8_t sync_word_len,
                                   uint8_t crc_len
                                   ) ;

bool sx1262_set_gfsk_modulation_params(GfskModulationParams_t* modParams);
bool sx1262_load_params_gfsk(Sx1262_t* sx1262Instance);
bool sx1262_set_gfsk_packet_params(GfskPacketParam_t *gfsk);
bool gfsk_proc_rx_status(GfskRxStatus_t RxStatus);

#endif /* GFSK_DRV_H  */
