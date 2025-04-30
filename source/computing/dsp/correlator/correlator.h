#ifndef CORRELATOR_DRV_H
#define CORRELATOR_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "correlator_diag.h"
#include "correlator_types.h"
#include "correlator_config.h"



CorrelatorHandle_t* CorrelatorGetNode(uint8_t num);
const CorrelatorConfig_t* CorrelatorGetConfig(uint8_t num);

bool correlator_calc_ll(CircularBufferWord_t* const SignalA,
                        CircularBufferWord_t* const SignalB,
                        uint32_t cnt,
						int32_t* const correlation_out);

bool correlator_s16_calc_diff_ll(int16_t* const arrayA,
		                         int16_t* const arrayB,
                                 uint32_t cnt,
						         int32_t* const correlation_out);

bool correlator_s16_calc_ll(int16_t* const SignalA,
                            int16_t* const SignalB,
                            uint32_t cnt,
						    int32_t* const correlation_out);


bool correlator_calc(uint8_t num, int32_t* const correlation_result);
bool correlator_init_one(uint8_t num);
bool correlator_mcal_init(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*CORRELATOR_DRV_H*/
