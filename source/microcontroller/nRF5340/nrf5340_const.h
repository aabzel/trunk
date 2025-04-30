#ifndef NRF5340_CONST_H
#define NRF5340_CONST_H

#ifdef HAS_FLASH_CUSTOM
#include "flash_custom_const.h"
#endif

#ifdef HAS_GPIO
#include "gpio_nrf5340_const.h"
#endif

#ifdef HAS_CORE_APP
#include "nrf5340_application.h"
#include "nrf5340_app_const.h"
#endif /*HAS_CORE_APP*/


#ifdef HAS_CORE_NET
#include "nrf5340_net_const.h"
#endif /*HAS_CORE_NET*/

#define FLASH_START_NET_CORE 0x01000000
#define FLASH_SIZE_NET_CORE (256 * K_BYTES)
#define ON_CHIP_NOR_FLASH_NET_PAGE_SIZE (2*K_BYTES)


#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif /*HAS_MICROCONTROLLER*/

#define MIN_IRQ_NUM (-14)
#define MAX_IRQ_NUM 60
#define GPIO_PIN_MAX 31
#define GPIO_PORT_MAX 1

#define DEFAULT_CPU_CLOCK_HZ 64000000

#define RAM_END (RAM_START + RAM_SIZE)
#define ROM_END (ROM_START + ROM_SIZE)

#define UART_MAX_NUM (UART_COUNT-1)

#define MCU_NAME "nRF5340"


#endif /* NRF5340_CONST_H */
