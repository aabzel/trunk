#ifndef IIR_SWC_H
#define IIR_SWC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#include "iir_config.h"
#ifdef HAS_IIR_DIAG
#include "iir_diag.h"
#endif
#include "iir_types.h"
#include "iir_isr.h"

// API
const IirConfig_t* IirGetConfig(uint8_t num);
IirHandle_t* IirGetNode(uint8_t num);
bool iir_mcal_init(void);
bool iir_init_one(uint8_t num);
bool iir_lowpas_1st_order_v2(uint8_t num, double x);
bool iir_lowpas_1st_order(uint8_t num, double k);
bool iir_synthesize(uint8_t num, uint32_t M, double cutoff_frequency_hz, double sampling_frequency_hz);
#ifdef __cplusplus
}
#endif

#endif /* IIR_SWC_H */
