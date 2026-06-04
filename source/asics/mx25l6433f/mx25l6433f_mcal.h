#ifndef MX25L6433F_MCAL_H
#define MX25L6433F_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "mx25l6433f_config.h"
#include "mx25l6433f_types.h"

#ifdef HAS_MX25L6433F_DIAG
#include "mx25l6433f_diag.h"
#endif

/* API */
Mx25l6433fHandle_t* Mx25l6433fGetNode(uint8_t num);
const Mx25l6433fConfig_t* Mx25l6433fGetConfig(uint8_t num);
bool Mx25l6433fIsValidConfig(const Mx25l6433fConfig_t* const Config);

#ifdef HAS_MX25L6433F_CUSTOM
const Mx25l6433fInfo_t* Mx25l6433fGetInfo(uint8_t num);
#endif

bool mx25l6433f_mcal_init(void);
bool mx25l6433f_init_custom(void);
bool mx25l6433f_init_common(const Mx25l6433fConfig_t* const Config, Mx25l6433fHandle_t* const Node);
bool mx25l6433f_init_node(Mx25l6433fHandle_t* const Node);
bool mx25l6433f_init_one(uint8_t num);

bool mx25l6433f_proc_one(uint8_t num);
bool mx25l6433f_proc(void);

bool mx25l6433f_wait_write_done(uint8_t num, uint32_t time_out);

/*setters*/
bool mx25l6433f_erase_chip(uint8_t num);
bool mx25l6433f_erase_block(uint8_t num, uint32_t address, Mx25BlockSize_t block_size);
bool mx25l6433f_erase_sector(uint8_t num, uint32_t address);
bool mx25l6433f_erase_mem(uint8_t num, uint32_t address, uint32_t size);
bool mx25l6433f_page_program(uint8_t num, uint32_t address, const uint8_t* const data, uint32_t size);
bool mx25l6433f_reset_hw(uint8_t num);
bool mx25l6433f_reset(uint8_t num);
bool mx25l6433f_reg_set(uint8_t num, uint8_t reg_addr, uint8_t reg_val);
bool mx25l6433f_write(uint8_t num, uint32_t address, const uint8_t* const data, uint32_t size);
bool mx25l6433f_write_status_register(uint8_t num, const uint16_t data);
bool mx25l6433f_write_enable(uint8_t num, bool on_off);
bool mx25l6433f_write_reg_by_bitmask(uint8_t num, uint8_t reg_addr, char* bit_mask);
bool mx25l6433f_zero(uint8_t num, uint32_t address, uint32_t size);

/* getters */
bool mx25l6433f_raw_reg_diag(uint8_t i) ;
bool mx25l6433f_reg_get(uint8_t num, uint8_t reg_addr, uint8_t* reg_val);
bool mx25l6433f_is_valid_addr(uint8_t num, uint32_t address);
bool mx25l6433f_is_connected(uint8_t num);
bool mx25l6433f_reg_read_all(uint8_t num);
bool mx25l6433f_scan(uint8_t num, uint32_t address, uint32_t size, double* usage_pec, uint32_t* spare, uint32_t* busy);
bool mx25l6433f_verify(uint8_t num, uint32_t address, const uint8_t* const data, uint32_t size);
bool mx25l6433f_is_write_in_progress(uint8_t num);
bool mx25l6433f_read(uint8_t num, uint32_t address, uint8_t* data, uint32_t size);
bool mx25l6433f_read_sfdp(uint8_t num, uint32_t address, uint16_t* word);
bool mx25l6433f_read_status_reg(uint8_t num);
bool mx25l6433f_read_identification(uint8_t num);
bool mx25l6433f_read_configuration_reg(uint8_t num);
bool mx25l6433f_read_electronic_signature(uint8_t num );

bool mx25l6433f_deep_power_down(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* MX25L6433F_MCAL_H */
