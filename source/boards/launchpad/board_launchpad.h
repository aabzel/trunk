#ifndef BOARD_LAUNCHPAD_H
#define BOARD_LAUNCHPAD_H

#include "cc2652r1f.h"

#define BOARD_NAME "LaunchPad"

#define CLOCK_FOR_US (SYS_FREQ / 1000000U)
#define DIO_LED_GREEN 7
#define DIO_LED_RED 6
#define DIO_UART_CLI_RX 2U
#define DIO_UART_CLI_TX 3U
#define DIO_BUTTON1 13
#define DIO_BUTTON2 14 
#define DIO_FLASH_CS 20
#define DIO_SPI0_MOSI 9
#define DIO_SPI0_MISO 8
#define DIO_SPI0_SCLK 10

//#define UART_COUNT 1
#define LED_COUNT 2


#endif /* BOARD_LAUNCHPAD_H  */
