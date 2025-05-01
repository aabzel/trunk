#include "rv32imc_driver.h"

#include "microcontroller.h"

#ifdef HAS_INTERRUPT
#include "interrupt_mcal.h"
#endif

#include "csr.h"

#ifdef HAS_LED
#include "led_drv.h"
#endif

#ifdef HAS_MISCELLANEOUS
#include "data_types.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_FLASH
#include "flash_config.h"
#endif

#ifdef HAS_WATCHDOG
#include "watchdog_mcal.h"
#endif

#ifdef HAS_RV32IMC_EXT
bool rv32imc_is_interrupt(void) {
    bool res = false;
    return res;
}
#endif

bool rv32imc_reboot(void) {
    bool res = true;
#ifdef HAS_LOG
    LOG_WARNING(SYS, "rv32imc-Reboot..");
#endif

#ifdef HAS_INTERRUPT
    interrupt_disable();
#endif
    // Debug Control and Status
    // set_csr(dcsr, DCSR_FULLRESET);
#ifdef HAS_WATCHDOG
    res = watchdog_timeout_set(0);
#endif

    return res;
}

#ifdef HAS_CORE_EXT
bool rv32imc_boot_spifi(void) {
    bool res = true;
    __asm__ volatile("la ra, 0x80000000\n\t"
                     "jalr ra");
    return res;
}

bool rv32imc_boot_eeprom(void) {
    bool res = true;
    __asm__ volatile("la ra, 0x01000000\n\t"
                     "jalr ra");
    return res;
}

bool rv32imc_boot_sram(void) {
    bool res = true;
    __asm__ volatile("la ra, 0x02000000\n\t"
                     "jalr ra");
    return res;
}
#endif

bool rv32imc_boot_addr_asm(const uint32_t app_start_address) {
    bool res = true;
    /* JR (jump register) performs an unconditional control transfer to the address in
     *  register rs1. C.JR expands to jalr x0, rs1, 0.*/
    __asm__ volatile("jr %0" : : "r"(app_start_address) :);
    return res;
}

bool rv32imc_boot_addr(uint32_t app_start_address) {
    bool res = false;
    interrupt_disable();
    res = rv32imc_boot_addr_asm(app_start_address);
    return res;
}

#ifdef HAS_RV32IMC_EXT
uint64_t rv32imc_up_time_counter_get(void) {
    uint64_t val = 0;
    Counter64bit_t Un64 = {0};
    Un64.u32[0] = read_csr(cycle);
    Un64.u32[1] = read_csr(cycleh);
    val = Un64.u64;
    return val;
}
#endif

#ifdef HAS_RV32IMC_EXT
uint32_t rv32imc_up_time_get_ms32(void) {
    uint64_t counter = rv32imc_up_time_counter_get();
    uint32_t up_time_ms = (1000UL * counter) / (SYS_FREQ);
    return up_time_ms;
}
#endif

#ifdef HAS_RV32IMC_EXT
uint64_t rv32imc_up_time_get_us(void) {
    uint64_t counter = rv32imc_up_time_counter_get();
    uint64_t up_time_us = (1000000UL * counter) / (SYS_FREQ);
    return up_time_us;
}
#endif

#ifdef HAS_CORE_EXT
float rv32imc_up_time_get(void) {
    float up_time_s = 0.0;
    uint64_t counter = rv32imc_up_time_counter_get();
    up_time_s = ((float)counter) / ((float)SYS_FREQ);
    return up_time_s;
}
#endif

#ifdef HAS_RV32IMC_EXT
uint64_t rv32imc_up_time_get_ms(void) {
    uint64_t counter = rv32imc_up_time_counter_get();
    uint64_t up_time_us = (1000UL * counter) / (SYS_FREQ);
    return up_time_us;
}
#endif
