#include "device_id.h"

#include <inttypes.h>
#include <stdint.h>
#ifdef HAS_CORE
#include "core_driver.h"
#endif
#include "read_mem.h"
#include "str_utils.h"
#include "version.h"

uint64_t get_device_serial(void) {
    uint32_t value = 0;
#ifdef CC26XX
    value = read_addr_32bit(CPU_SCS_CPUID);
#endif
    return (uint64_t)value;
}
