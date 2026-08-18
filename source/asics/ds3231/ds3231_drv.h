#ifndef DS3231_DRV_H
#define DS3231_DRV_H

#include <time.h>

#include "std_includes.h"
#include "ds3231_config.h"
#include "ds3231_types.h"

extern const Ds3231Reg_t Ds3231RegMapStatic[];


/*API*/
Ds3231Handle_t* Ds3231GetNode(uint8_t num);
bool ds3231_init_one(uint8_t num);
bool ds3231_mcal_init(void);
bool ds3231_proc(void);
bool ds3231_proc_one(uint8_t num);


/*setter*/
bool ds3231_temperature_convert(uint8_t num);
bool ds3231_set_reg(uint8_t num, uint8_t reg_addr, uint8_t reg_val);
bool ds3231_set_time_date(uint8_t num, const struct tm* const time_date_set);
bool ds3231_tune(uint8_t num, int8_t offset);
bool ds3231_set_time(uint8_t num, const struct tm* const time_date);
bool ds3231_run(uint8_t num, bool on_off);
bool ds3231_set_date(uint8_t num, const struct tm* const time_date);

/*getter*/
bool ds3231_is_connected_ll(const Ds3231Config_t* const Node);
bool ds3231_get_reg(uint8_t num, uint8_t reg_addr, uint8_t* reg_val);
uint8_t ds3231_get_reg_cnt(void);
bool ds3231_get_time_date(uint8_t num, struct tm* const time_date_get);
bool ds3231_reg_map_get(uint8_t num);
bool ds3231_temperature_get(uint8_t num, double* const temp);
bool ds3231_is_connected(uint8_t num);
bool ds3231_temperature(uint8_t num, double* const temp);
HourMode_t ds3231_hour_mode_get(uint8_t num);


#endif /* DS3231_DRV_H */
