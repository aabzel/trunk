#ifndef SPI_DRV_H
#define SPI_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "spi_common.h"

#include "sys_config.h"

#define SPI0_BIT_RATE_HZ SPI_CLK_FREQUENCY_HZ /*sx1262*/
#define SPI1_BIT_RATE_HZ SPI_CLK_FREQUENCY_HZ
#define SPI2_BIT_RATE_HZ SPI_CLK_FREQUENCY_HZ
#define SPI3_BIT_RATE_HZ SPI_CLK_FREQUENCY_HZ

#define SPI0_BASE 0x3FF43000
#define SPI1_BASE 0x3FF42000
#define SPI2_BASE 0x3FF64000
#define SPI3_BASE 0x3FF65000

//#define SPI_DISCRET_WRITE
//#define SPI_DISCRET_READ

#define SPI_CON_WRITE
#define SPI_CON_READ

typedef enum eSpiName_t { SPI0_INX = 0, SPI1_INX = 1, SPI2_INX = 2, SPI3_INX = 3, SPI_CNT = 4 } SpiName_t;

bool spi_init(void);
bool spi_wait_write_wait(SpiName_t spi_num, const uint8_t* const tx_array, uint16_t tx_array_len);
bool spi_wait_write(SpiName_t spi_num, const uint8_t* const tx_array, uint16_t tx_array_len);
bool spi_write(SpiName_t spi_num, const uint8_t* const tx_array, uint16_t tx_array_len);
bool spi_read(SpiName_t spi_num, uint8_t* rx_array, uint16_t array_len);
uint32_t spi_get_clock(SpiName_t spi_num);
bool spi_wait_tx_done(SpiName_t spi_num);
uint8_t spi_get_phase(SpiName_t spi_num);
uint8_t spi_get_polarity(SpiName_t spi_num);
uint8_t spi_get_data_size(SpiName_t spi_num);
uint8_t spi_get_transmit_int(SpiName_t spi_num);
uint8_t spi_get_receive_int(SpiName_t spi_num);
uint8_t spi_get_receive_timeout_interrupt(SpiName_t spi_num);
uint8_t spi_get_receive_overrun_interrupt(SpiName_t spi_num);

#ifdef __cplusplus
}
#endif

#endif /* SPI_DRV_H  */
