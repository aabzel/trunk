#ifndef SPI_DRV_H
#define SPI_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "spi_types.h"

#ifndef HAS_SPI
#error "+HAS_SPI"
#endif /*HAS_SPI*/

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif /*HAS_MICROCONTROLLER*/

bool spi_common_init(uint8_t num);
bool spi_is_init(uint8_t num);
bool spi_is_allowed(uint8_t num);
bool spi_read_safe(uint8_t num, uint8_t* rx_array, uint32_t size);
bool spi_wait_rxtx_ll(SpiHandle_t* Node);
bool spi_wait_tx_ll(SpiHandle_t* Node);
bool spi_wait_txrx_ll(SpiHandle_t* Node);
bool spi_wait_rx_ll(SpiHandle_t* Node);
const SpiConfig_t* SpiGetConfig(uint8_t num);
SpiHandle_t* SpiGetNode(uint8_t num);
bool spi_write_byte(uint8_t num, const uint8_t byte);
bool spi_api_write(uint8_t num, const uint8_t* const tx_array, uint32_t tx_array_len);
bool spi_write_word(uint8_t num, const uint16_t word);
bool spi_api_read(uint8_t num, uint8_t* const rx_array, uint32_t array_len);
bool spi_api_read_word(uint8_t num, uint16_t* word);
bool spi_api_write_read(uint8_t num, const uint8_t* const tx_array, uint8_t* rx_array, uint32_t size);
bool spi_init(void);
bool spi_init_one(uint8_t num);
uint32_t spi_get_rate_conf(uint8_t num);
bool spi_set_clock(uint8_t num, uint32_t bit_rate_hz);
bool spi_wait_tx_done(uint8_t num);
SpiPhase_t spi_get_phase(uint8_t num);
SpiPolarity_t spi_get_polarity(uint8_t num);
uint8_t spi_read_byte(uint8_t num);
uint16_t spi_read_word(uint8_t num);
uint32_t spi_read_dword(uint8_t num);
uint64_t spi_read_qword(uint8_t num);
uint8_t spi_get_data_size(uint8_t num);
uint32_t spi_get_clock(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* SPI_DRV_H  */
