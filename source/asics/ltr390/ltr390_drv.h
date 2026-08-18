#ifndef LTR390_DRV_H
#define LTR390_DRV_H

#include "std_includes.h"
#include "ltr390_types.h"
#include "ltr390_config.h"
#ifdef HAS_LTR390_DIAG
#include "ltr390_diag.h"
#endif

/*Hash functions*/
ResolutionVal_t ResolutionCodeToResolution(uint8_t code);
double ResolutionToIntergationTime(ResolutionVal_t resolution);

/*Physics*/
bool ltr390_uvs_code_to_uvi(Ltr390Handle_t* Node);
bool ltr390_als_code_to_lx(Ltr390Handle_t* Node);

/*System API*/
Ltr390Handle_t* Ltr390GetNode(uint8_t num);
const Ltr390RegisterInfo_t* Ltr390RegisterInfoGet(uint8_t address);
const Ltr390Config_t* Ltr390GetConfig(uint8_t num);
bool ltr390_reset(uint8_t num);
bool ltr390_proc_one(uint8_t num);
bool ltr390_init_one(uint8_t num);
bool ltr390_mcal_init(void);
bool ltr390_is_connected(uint8_t num);
bool ltr390_proc(void);

/*Low Level API*/
bool ltr390_is_valid_reg_addr(uint8_t reg_addr);
bool ltr390_register_read(uint8_t num, uint8_t reg_addr, uint8_t* const val);
bool ltr390_register_write(uint8_t num, uint8_t reg_addr, uint8_t val);

/*Hi level API*/
bool ltr390_start_measurement(uint8_t num, DataSource_t source);

/*getters*/
bool ltr390_gain_get(uint8_t num, Ltr390GainVal_t* const gain_val);
bool ltr390_thresh_low_get(uint8_t num, uint32_t* int_thresh_low);
bool ltr390_thresh_up_get(uint8_t num, uint32_t* int_thresh_up);
bool ltr390_rate_get(uint8_t num, Ltr390Rate_t* rate);
bool ltr390_integration_time_get(uint8_t num, double* const intergation_time);
bool ltr390_resolution_get(uint8_t num, ResolutionVal_t* const resolution);
bool ltr390_mode_get_source(uint8_t num, DataSource_t* source);

/*setters*/
bool ltr390_thresh_low_set(uint8_t num, uint32_t int_thresh_low);
bool ltr390_thresh_up_set(uint8_t num, uint32_t int_thresh_up);
bool ltr390_mode_set_source(uint8_t num, DataSource_t source);
bool ltr390_resolution_set(uint8_t num, ResolutionVal_t resolution);
bool ltr390_rate_set(uint8_t num, Ltr390Rate_t rate);
bool ltr390_gain_set(uint8_t num, Ltr390GainVal_t gain_range);

double ltr390_read_lx_short(uint8_t num);
double ltr390_read_uv_short(uint8_t num);

#endif /* LTR390_DRV_H */
