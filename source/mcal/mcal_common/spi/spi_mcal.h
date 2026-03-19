#ifndef SPI_MCAL_H
#define SPI_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "spi_config.h"
#include "spi_types.h"

#ifdef HAS_SPI_INTERRUPT
#include "spi_isr.h"
#endif

#ifdef HAS_SPI_CUSTOM
#include "spi_custom.h"
#endif

#ifdef HAS_SPI_DIAG
#include "spi_diag.h"
#endif

/* API */
SpiHandle_t* SpiGetNode(const uint8_t num);
const SpiConfig_t* SpiGetConfig(const uint8_t num);
#ifdef HAS_SPI_CUSTOM
const SpiInfo_t* SpiGetInfo(const uint8_t num);
#endif

bool SpiIsValidConfig(const SpiConfig_t* const Config);
bool spi_is_init(uint8_t num);
bool spi_init_common(const SpiConfig_t* const Config, SpiHandle_t* const Node);
bool spi_init_one(uint8_t num);
bool spi_init_custom(void);
bool spi_mcal_init(void);

bool spi_proc_one(uint8_t num);
bool spi_proc(void);

/*wait*/
bool spi_wait_tx_done(uint8_t num);
bool spi_wait_rxtx_ll(SpiHandle_t * const Node);
bool spi_wait_tx_ll(SpiHandle_t * const Node);
bool spi_wait_txrx_ll(SpiHandle_t * const Node);
bool spi_wait_rx_ll(SpiHandle_t * const Node);

/*getters*/
bool spi_read_safe(uint8_t num, uint8_t* rx_array, uint32_t size);
bool spi_mcal_read(uint8_t num, uint8_t* const rx_array, uint32_t array_len);
bool spi_mcal_read_word(uint8_t num, uint16_t* word);
bool spi_read_byte_v2(uint8_t num, uint8_t* const rx_byte);
SpiClkIdleLevel_t spi_get_phase(uint8_t num);
SpiPolarity_t spi_get_polarity(uint8_t num);
uint8_t spi_get_data_size(uint8_t num);
uint8_t spi_read_byte(uint8_t num);
uint16_t spi_read_word(uint8_t num);
uint32_t spi_get_rate_conf(uint8_t num);
uint32_t spi_read_dword(uint8_t num);
uint32_t spi_get_clock(uint8_t num);
uint64_t spi_read_qword(uint8_t num);
bool spi_move_mode_get(const uint8_t num, MoveMode_t* const move_mode);
bool spi_read_until_pattern(const uint8_t num, const uint8_t exp_rx, const uint32_t try);

/*setters*/
bool spi_move_mode_set(const uint8_t num, const MoveMode_t move_mode);
bool spi_write_byte(uint8_t num, const uint8_t byte);
bool spi_write_word(uint8_t num, const uint16_t word);
bool spi_write_dword(uint8_t num, const uint32_t word);
bool spi_mcal_write(uint8_t num, const uint8_t* const tx_array, uint32_t tx_array_len);
bool spi_mcal_write_read(uint8_t num, const uint8_t* const tx_array, uint8_t* rx_array, uint32_t size);
bool spi_set_clock(uint8_t num, uint32_t bit_rate_hz);

#ifdef __cplusplus
}
#endif

#endif /* SPI_MCAL_H  */
