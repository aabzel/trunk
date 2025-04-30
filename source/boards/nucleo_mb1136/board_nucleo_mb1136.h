#ifndef BOARD_NUCLEO_MB1136_H 
#define BOARD_NUCLEO_MB1136_H 

#include "stm32f401re.h"

#define BOARD_NAME "NucleoMB1136"
#define UART_COUNT 1
#define SPI_COUNT 1

#define SYS_FREQ 84000000U
#define APB2_CLOCK_HZ 84000000
#define APB1_CLOCK_HZ 42000000

#define DIO_SX1262_SS (gpio_port_pin2pad(PORT_A,8))
#define DIO_SX1262_BUSY (gpio_port_pin2pad(PORT_B,3))
#define DIO_SX1262_RST (gpio_port_pin2pad(PORT_A,0))
#define DIO_SX1262_INT (gpio_port_pin2pad(PORT_B,4))

#define LED_COUNT 1
#define DIO_LED_GREEN (gpio_port_pin2pad(PORT_A, 5))
#define SX1262_SPI_NUM 1 /*TODO find out real number */


#endif /* BOARD_NUCLEO_MB1136_H   */
