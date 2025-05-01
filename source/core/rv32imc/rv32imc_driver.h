#ifndef RV32IMC_DRV_H
#define RV32IMC_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "rv32imc_types.h"

#ifdef HAS_RV32IMC_DIAG
#include "rv32imc_diag.h"
#endif

float rv32imc_up_time_get(void);
bool rv32imc_reboot(void);
bool rv32imc_is_interrupt(void);

bool rv32imc_boot_sram(void);
bool rv32imc_boot_spifi(void);
bool rv32imc_boot_eeprom(void);
bool rv32imc_boot_addr(uint32_t app_start_address);
bool rv32imc_boot_addr_asm(const uint32_t app_start_address);

uint64_t rv32imc_up_time_counter_get(void);
uint64_t rv32imc_up_time_get_us(void) ;
uint64_t rv32imc_up_time_get_ms(void) ;
uint32_t rv32imc_up_time_get_ms32(void) ;

#ifdef __cplusplus
}
#endif

#endif /* RV32IMC_DRV_H */
