#ifndef BOARD_NUCLEO_MB1136_H 
#define BOARD_NUCLEO_MB1136_H 

#include "stm32f401re.h"

#define BOARD_NAME "NucleoMB1136"
#define UART_COUNT 1
#define SPI_COUNT 1

#define SYS_FREQ 84000000U
#define APB2_CLOCK_HZ 84000000
#define APB1_CLOCK_HZ 42000000

#define TIMER_COUNT 1
#define LED_COUNT 1
#define DIO_LED_GREEN (gpio_port_pin2pad(PORT_A, 5))


#endif /* BOARD_NUCLEO_MB1136_H   */
