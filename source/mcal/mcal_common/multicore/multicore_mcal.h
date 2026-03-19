#ifndef MULTICORE_MCAL_H
#define MULTICORE_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif


#include "std_includes.h"
#include "multicore_isr.h"
#include "multicore_types.h"
#include "multicore_config.h"
#include "writer_types.h"

#ifdef HAS_MULTICORE_DIAG
#include "multicore_diag.h"
#endif

/*API*/
const MultiCoreConfig_t* MultiCoreGetConfig(uint8_t num);
MultiCoreHandle_t* MultiCoreGetNode(uint8_t num);
bool multicore_init_one(uint8_t num);
bool multicore_proc_one(uint8_t num);
bool multicore_control(uint8_t num, bool on_off);
bool multicore_proc(void);
bool multicore_init_custom(void);
bool multicore_mcal_init(void);
bool multicore1_init(void);
bool multicore2_init(void);
bool multicore3_init(void);

/*getters*/
int8_t multicore_get_core_num(void);

/*setters*/
bool multicore_reset(uint8_t core_num);
bool multicore_release(uint8_t core_num);

#ifdef __cplusplus
}
#endif

#endif /* MULTICORE_MCAL_H  */
