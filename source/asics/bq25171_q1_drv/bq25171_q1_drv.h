#ifndef BQ25171_Q1_H
#define BQ25171_Q1_H

#include <stdbool.h>
#include <stdint.h>

typedef enum eChargingStatus_t {
	CHRG_STAT_NON_RECOV_FAULT = 0,
	CHRG_STAT_INPROC = 1,
	CHRG_STAT_RECOV_FAULT = 2,
	CHRG_STAT_COMPLETED = 3,
	
	CHRG_STAT_UNDEF = 4
}ChargingStatus_t;

bool bq25171_q1_init(void);
ChargingStatus_t bq25171_q1_get_status(void);
bool bq25171_q1_charge_enable(bool state);

#endif /* BQ25171_Q1_H */
