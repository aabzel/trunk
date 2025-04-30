#ifndef SET_H
#define SET_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

#include "set_config.h"
#include "set_types.h"

#ifndef HAS_SET
#error "+HAS_SET"
#endif

SetItem_t* SetGetNode(uint8_t num);
const SetConfig_t* SetGetConfig(uint8_t num);
bool set_delete(SetItem_t* const Node, const void* const data, size_t size);
bool set_push(uint8_t num, const void* const data, size_t size);
bool set_push_ll(SetItem_t* const Node, const void* const data, size_t size);
bool set_check(uint8_t num, const void* const data, size_t size);
bool set_check_ll(SetItem_t* const Node, const void* const data, size_t size);
bool set_get_cnt(SetItem_t* const Node, size_t* const size);
bool set_init(void);
bool set_init_one(uint8_t num);
uint32_t set_get_spare(SetItem_t* const Node);
uint32_t set_get_size(SetItem_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* SET_H */
