#ifndef DWT_MCAL_H
#define DWT_MCAL_H

/* Data Watchpoint and Trace Unit */

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dwt_config.h"
#include "dwt_types.h"

#ifdef HAS_DWT_DIAG
#include "dwt_diag.h"
#endif

#ifdef HAS_LOG
#define DWT_NAME .name="Dwt",
#else
#define DWT_NAME
#endif

#define DWT_INIT { .init_function = dwt_mcal_init, DWT_NAME},



/* API */
DwtHandle_t* DwtGetNode(uint8_t num);
const DwtConfig_t* DwtGetConfig(uint8_t num);
bool DwtIsValidConfig(const DwtConfig_t* const Config);

#ifdef HAS_DWT_CUSTOM
const DwtInfo_t* DwtGetInfo(uint8_t num);
#endif

bool dwt_mcal_init(void);
bool dwt_init_custom(void);
bool dwt_init_common(const DwtConfig_t* const Config, DwtHandle_t* const Node);
bool dwt_init_node(DwtHandle_t* const Node);
bool dwt_init_one(uint8_t num);

bool dwt_proc_one(uint8_t num);
bool dwt_proc(void);

/*setters*/
void dwt_delay_ms(uint8_t num, uint32_t delay_ms);

/*getters*/
uint32_t dwt_get_time_ms32(uint8_t num);
uint64_t dwt_get_time_us64(uint8_t num);
uint32_t dwt_timer_get(uint8_t num);
uint64_t dwt_get_time_ms64(uint8_t num);
uint64_t dwt_get_run_time_counter_u64(uint8_t num) ;

#ifdef __cplusplus
}
#endif

#endif /* DWT_MCAL_H */
