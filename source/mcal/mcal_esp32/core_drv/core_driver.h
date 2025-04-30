#ifndef CORE_DRIVER_H
#define CORE_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#define EXPECT_STACK_SIZE (4096 * 10)


uint32_t cpu_get_id(void);
bool reboot(void);
uint64_t get_ble_mac(void);

#ifdef __cplusplus
}
#endif

#endif /* CORE_DRIVER_H */
