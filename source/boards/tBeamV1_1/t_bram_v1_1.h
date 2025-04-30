#ifndef T_BEAM_V1_1_H
#define T_BEAM_V1_1_H

#include "esp32.h"

#define BOARD_NAME "TBeamV1.1"

#define UART_COUNT 2

#define I2C_COUNT 2
#define SPI_COUNT 4
#define SX1262_SPI_NUM 3
#define LED_COUNT 1
#define LED_INDEX_RED 0

/*GPIO name utils*/
#define DIO_GNSS_RXD 34 /*TXD1*/
#define DIO_GNSS_TXD 12 /*RXD1*/
#define DIO_LED_RED 4 /*Active low*/
#define DIO_BUTTON 38  /*Active low*/
#define DIO_SPI0_MISO 19
#define DIO_SPI0_MOSI 27

#define DIO_I2C_SDA 21
#define DIO_I2C_SCK 22

#define DIO_SPI0_SCLK 5
#define DIO_SX1262_BUSY 32  /*LoRa_BUSY TODO explore*/
#define DIO_SX1262_INT 33  /*LoRa_INT*/
#define DIO_SX1262_RST 23 /*LoRa_NRESET*/
#define DIO_SX1262_SS 18  /*SS0_LoRa*/
#define DIO_UART_CLI_RX	3
#define DIO_UART_CLI_TX	1

#define AXP192_I2C_ADDR 0x34

#endif /* T_BEAM_V1_1_H  */
