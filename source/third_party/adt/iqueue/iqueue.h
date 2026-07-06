#ifndef IQUEUE_MCAL_H
#define IQUEUE_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "iqueue_config.h"
#include "iqueue_types.h"
#include "lib_iqueue.h"

#ifdef HAS_IQUEUE_DIAG
#include "iqueue_diag.h"
#endif

/* API */
iQueueHandle_t* iQueueInterfaceToNode(const InterfaceType_t Interface);
iQueueHandle_t* iQueueGetNode(uint8_t num);
const iQueueConfig_t* iQueueGetConfig(uint8_t num);
bool iQueueIsValidConfig(const iQueueConfig_t* const Config);

#ifdef HAS_IQUEUE_CUSTOM
const iQueueInfo_t* iQueueGetInfo(uint8_t num);
#endif

bool iqueue_mcal_init(void);
bool iqueue_init_custom(void);
bool iqueue_init_one(uint8_t num);
bool iqueue_init_common(const iQueueConfig_t* const Config,
                              iQueueHandle_t* const Node);

bool iqueue_proc_one(uint8_t num);
bool iqueue_proc(void);

/*setters*/
i_status iqueue_empty(iqueue_t* _queue, uint32_t* const cnt);

/*getters*/
bool iqueue_ret_res(const i_status ret);

#ifdef __cplusplus
}
#endif

#endif /* IQUEUE_MCAL_H */
