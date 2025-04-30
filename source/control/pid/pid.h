#ifndef PID_SWC_H
#define PID_SWC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <std_includes.h>

#include "pid_config.h"
#include "pid_types.h"
#ifdef HAS_PID_DIAG
#include "pid_diag.h"
#endif

// API
const PidConfig_t* PidGetConfig(uint8_t num);
PidHandle_t* PidGetNode(uint8_t num);
bool pid_mcal_init(void);

// setters
bool pid_set_p(uint8_t num, double p);
bool pid_set_i(uint8_t num, double i);
bool pid_set_d(uint8_t num, double d);
bool pid_ctrl(uint8_t num, bool on_off);
bool pid_proc_value(uint8_t num, double error, double * const voltage_out);
bool pid_target_set(uint8_t num, double target);

// getters

#ifdef HAS_PID_PROC
bool pid_proc_one(uint8_t num);
bool pid_proc(void);
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*PID_SWC_H*/
