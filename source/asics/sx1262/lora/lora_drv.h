#ifndef LORA__DRV_H
#define LORA__DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "sx1262_types.h"

bool is_valid_spreading_factor(SpreadingFactor_t Spreading_factor);

bool is_valid_coding_rate(LoRaCodingRate_t coding_rate);
bool is_valid_bandwidth(BandWidth_t bandwidth) ;
bool sx1262_set_modulation_quality_workaround(BandWidth_t band_width);
bool sx1262_set_lora_modulation_params(LoRaModulationParams_t* modParams);
bool sx1262_load_params(Sx1262_t* sx1262Instance);
uint32_t bandwidth2num(BandWidth_t bandwidth) ;

double lora_calc_data_rate(uint8_t sf_code, uint8_t bw_code, uint8_t cr_code) ;

bool sx1262_load_params_lora(Sx1262_t* sx1262Instance);

/*
 * de - Low Data Rate Optimize can
 *           be enabled  (Value of DE = 1) or
 *           disabled (Value of DE = 0)
 * header  -    implicit or explicit, i.e. H of value
 *                   0 indicates it is enabled and it is explicit mode where as H of value
 *                   1 indicates it is disabled and it is implicit mode.
 * n_preamble -  Number of symbols in preamble
 * */
double lora_calc_max_frame_tx_time(uint8_t sf_code, uint8_t bw_code, uint8_t cr_code, uint16_t n_preamble,
                                   uint8_t header, uint8_t low_data_rate_opt, double* out_t_sym,
                                   double* out_t_preamble) ;
#endif /*LORA__DRV_H*/
