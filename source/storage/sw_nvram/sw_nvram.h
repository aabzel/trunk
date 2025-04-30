#ifndef SW_NVRAM_DRIVER_H
#define SW_NVRAM_DRIVER_H

#include <stdbool.h>
#include <stdint.h>

#include "sw_nvram_types.h"
#include "sw_nvram_config.h"

#ifndef HAS_ALLOCATOR
#error "+HAS_ALLOCATOR"
#endif /*HAS_ALLOCATOR*/

#ifndef HAS_SW_NVRAM
#error "+HAS_SW_NVRAM"
#endif /*HAS_SW_NVRAM*/

#ifndef HAS_MATH
#error "+HAS_MATH"
#endif /*HAS_MATH*/

uint32_t nvram_entry_cnt(uint8_t num);
uint32_t sw_nvram_get_end( NvRamItem_t* Node, uint32_t offset);
NvRamItem_t* NvRamGetNode(uint8_t num);
const NvRamConfig_t* NvRamGetConfig(uint8_t num);
bool sw_nvram_write(uint8_t num, uint32_t address,const  uint8_t* const data, uint32_t size);
bool sw_nvram_traversal_level_order( NvRamItem_t* Node, uint32_t base, EntryActionFoo_t* EntryActionFoo );
bool sw_nvram_traversal_in_order( NvRamItem_t* Node, uint32_t base, EntryActionFoo_t* EntryActionFoo );
bool sw_nvram_write_opposite_page(NvRamItem_t* const Node, NvRamHeader_t const* const HeaderToMove, uint32_t from_addr );
bool sw_nvram_read(uint8_t num, uint32_t address, uint8_t*const  data, uint32_t *const  size);
bool sw_nvram_is_address_exist(uint8_t num, uint32_t address);
bool sw_nvram_delete(uint8_t num, uint32_t address);
bool sw_nvram_init(void);
bool sw_nvram_init_one(uint8_t num);
bool sw_nvram_format(NvRamItem_t* Node, NvRamPage_t active_page );
bool sw_nvram_toggle_page(NvRamItem_t* Node);
bool sw_nvram_is_node_exist(NvRamItem_t* Node, NvRamPage_t active_page, NvRamHeader_t* Header);

#endif /*SW_NVRAM_DRIVER_H*/
