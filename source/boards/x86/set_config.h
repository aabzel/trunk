#ifndef SET_CONFIG_H
#define SET_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "set_types.h"

#ifndef HAS_SET
#error "+HAS_SET"
#endif /*HAS_SET*/

extern const SetConfig_t SetConfig[];
extern SetItem_t SetItem[];

uint32_t set_get_instance_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /*SET_CONFIG_H*/
