#ifndef BOARD_HARVESTER_V1_H
#define BOARD_HARVESTER_V1_H

#define BOARD_NAME "h407"
#define MCU_NAME "STM32F407ZGT6"
#define UART_COUNT 6
#define SPI_COUNT 3

#define SYS_FREQ 120000000U
#define APB2_CLOCK_HZ 60000000
#define APB1_CLOCK_HZ 30000000

#define DIO_SX1262_SS (gpio_port_pin2pad(PORT_B,7))
#define DIO_SX1262_BUSY (gpio_port_pin2pad(PORT_G,2))
#define DIO_SX1262_RST (gpio_port_pin2pad(PORT_G,1))
#define DIO_SX1262_INT (gpio_port_pin2pad(PORT_D,0))

#define LED_COUNT 1
#define DIO_LED_GREEN (gpio_port_pin2pad(PORT_C, 13))

#define RAM_SIZE (192 * K_BYTES)
#define ROM_SIZE ( 1024 * K_BYTES)

#endif /* BOARD_HARVESTER_V1_H  */
