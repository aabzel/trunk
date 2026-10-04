#ifndef DRV8870_MCAL_H
#define DRV8870_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "drv8870_config.h"
#include "drv8870_types.h"
#ifdef HAS_DRV8870_DIAG
#include "drv8870_diag.h"
#endif

/* API */
Drv8870Handle_t* Drv8870GetNode(uint8_t num);
const Drv8870Config_t* Drv8870GetConfig(uint8_t num);
bool Drv8870IsValidConfig(const Drv8870Config_t* const Config);


bool drv8870_mcal_init(void);
bool drv8870_init_custom(void);
bool drv8870_init_one(uint8_t num);


bool drv8870_proc_one(uint8_t num);
bool drv8870_proc(void);

/*setters*/
bool drv8870_set(uint8_t num, Drv8870Mode_t mode, float pwm_duty);
bool drv8870_freq_set(  uint8_t num, float freq_hz);
bool drv8870_deploy(uint8_t num);

/*getters*/


#ifdef __cplusplus
}
#endif

#endif /* DRV8870_MCAL_H */
