#ifndef IQUEUE_DIAG_H
#define IQUEUE_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "iqueue_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /**/

#ifndef HAS_IQUEUE
#error "+HAS_IQUEUE"
#endif /**/

#ifndef HAS_IQUEUE_DIAG
#error "+HAS_IQUEUE_DIAG"
#endif /**/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /**/

const char* iQueueConfigToStr(const iQueueConfig_t* const Config);
const char* iQueueNodeToStr(const iQueueHandle_t* const Node);
const char* iQueueHandleToStr(const iqueue_t* const pHandle);
const char* iQueueStatusToStr(const i_status ret);

bool iqueue_diag(void);
#ifdef __cplusplus
}
#endif

#endif /* IQUEUE_DIAG_H  */
