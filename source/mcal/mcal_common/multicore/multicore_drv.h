#ifndef MULTICORE_DRV_H
#define MULTICORE_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "multicore_types.h"

#ifndef HAS_MULTICORE
#error "+HAS_MULTICORE"
#endif /*HAS_MULTICORE*/

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif /*HAS_MICROCONTROLLER*/

bool multicore_init_one(uint8_t num);
bool multicore_mcal_init(void);
const MultiCoreConfig_t* MultiCoreGetConfig(uint8_t num);
MultiCoreHandle_t* MultiCoreGetNode(uint8_t num);


#ifdef __cplusplus
}
#endif

#endif /* MULTICORE_DRV_H  */
