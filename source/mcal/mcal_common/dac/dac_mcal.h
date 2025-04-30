#ifndef DAC_MCAL_H
#define DAC_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "dac_config.h"
#include "dac_isr.h"
#include "dac_types.h"

#ifdef HAS_DAC_DIAG
#include "dac_diag.h"
#endif

/*API*/
const DacConfig_t* DacGetConfig(uint8_t num);
DacHandle_t* DacGetNode(uint8_t num);


bool dac_is_init(uint8_t num);
bool dac_is_allowed(uint8_t num);
bool dac_init_one(uint8_t num);
bool dac_proc_one(uint8_t num);
bool dac_init_custom(void);
bool dac_mcal_init(void);


/*getters*/
bool dac_code_u16_get(uint8_t num, uint16_t* const code) ;

/*setters*/
bool dac_code_u16_set(uint8_t num, uint16_t code) ;
bool dac_voltage_set(uint8_t num, double voltage);

#ifdef __cplusplus
}
#endif

#endif /* DAC_MCAL_H  */
