#ifndef SPI_MCAL_H
#define SPI_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif


#include "std_includes.h"
#include "spi_config.h"
#include "spi_isr.h"
#include "spi_types.h"
#include "spi_custom_drv.h"

#ifdef HAS_SPI_DIAG
#include "spi_diag.h"
#endif

/*API*/
const SpiConfig_t* SpiGetConfig(uint8_t num);
const SpiInfo_t* SpiGetInfo(uint8_t num);
SpiHandle_t* SpiGetNode(uint8_t num);
bool spi_common_init(uint8_t num);
bool spi_is_init(uint8_t num);
bool spi_is_allowed(uint8_t num);
bool spi_init_one(uint8_t num);
bool spi_proc_one(uint8_t num);
bool spi_proc(void);
bool spi_init_custom(void);
bool spi_mcal_init(void);

/*wait*/
bool spi_wait_tx_done(uint8_t num);
bool spi_wait_rxtx_ll(SpiHandle_t * const Node);
bool spi_wait_tx_ll(SpiHandle_t * const Node);
bool spi_wait_txrx_ll(SpiHandle_t * const Node);
bool spi_wait_rx_ll(SpiHandle_t * const Node);

/*getters*/
bool spi_read_safe(uint8_t num, uint8_t* rx_array, uint32_t size);
bool spi_api_read(uint8_t num, uint8_t* const rx_array, uint32_t array_len);
bool spi_api_read_word(uint8_t num, uint16_t* word);
uint32_t spi_get_rate_conf(uint8_t num);
SpiPhase_t spi_get_phase(uint8_t num);
SpiPolarity_t spi_get_polarity(uint8_t num);
uint8_t spi_get_data_size(uint8_t num);
uint8_t spi_read_byte(uint8_t num);
uint16_t spi_read_word(uint8_t num);
uint32_t spi_read_dword(uint8_t num);
uint64_t spi_read_qword(uint8_t num);
uint32_t spi_get_clock(uint8_t num);

/*setters*/
bool spi_write_byte(uint8_t num, const uint8_t byte);
bool spi_write_word(uint8_t num, const uint16_t word);
bool spi_api_write(uint8_t num, const uint8_t* const tx_array, uint32_t tx_array_len);
bool spi_api_write_read(uint8_t num, const uint8_t* const tx_array, uint8_t* rx_array, uint32_t size);
bool spi_set_clock(uint8_t num, uint32_t bit_rate_hz);

#ifdef __cplusplus
}
#endif

#endif /* SPI_MCAL_H  */
