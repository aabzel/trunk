#include "cortex_m7_diag.h"

#include "cortex_m7_types.h"
#include "log.h"

static char* FloatingPointToStr(uint8_t code) {
    char* name = "?";
    switch(code) {
    case FPU_MODE_OFF:
        name = "off";
        break;
    case FPU_MODE_ON:
        name = "on";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

static char* FaulmaskToStr(uint8_t code) {
    char* name = "?";
    switch(code) {
    case PREVENT_EXEPTRION_OFF:
        name = "AllowExept";
        break;
    case PREVENT_EXEPTRION_ON:
        name = "PrenentExpt";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

static char* TreadModeToStr(uint8_t code) {
    char* name = "?";
    switch(code) {
    case TM_PRIV:
        name = "Privileged";
        break;
    case TM_UNPRIV:
        name = "Unprivileged";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

static char* StackPointerSelToStr(uint8_t code) {
    char* name = "?";
    switch(code) {
    case CUR_MSP:
        name = "MSP";
        break;
    case CUR_PSP:
        name = "PSP";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

bool parse_control_reg(uint32_t reg_val) {
    bool res = true;
    RegCtrl_t RegCtrl;
    RegCtrl.val = reg_val;
    cli_printf("TrMode:%u=%s" CRLF, RegCtrl.npriv, TreadModeToStr(RegCtrl.npriv));
    cli_printf("SP:%u=%s" CRLF, RegCtrl.spsel, StackPointerSelToStr(RegCtrl.spsel));
    cli_printf("FPU:%u=%s" CRLF, RegCtrl.fpca, FloatingPointToStr(RegCtrl.fpca));

    return res;
}

bool print_vector_table(uint32_t vectors_table_base) {
    uint32_t* addres = 0;
    LOG_WARNING(SYS, "VectorsTableBase: 0x%08x", vectors_table_base);
    uint32_t offset = 0, num = 0;
    for(offset = 0, num = 0; offset <= 4 * 53; offset += 4, num++) {
        addres = (uint32_t*)(vectors_table_base + offset);
        cli_printf("number %2u Addr: 0x%08p Handler: 0x%08x" CRLF, num, addres, *(addres));
    }
    return true;
}

bool parse_faultmask_reg(uint32_t reg_val) {
    bool res = true;
    RegFaultmask_t RegCtrl;
    RegCtrl.val = reg_val;
    cli_printf("faultmask:%u=%s" CRLF, RegCtrl.faultmask, FaulmaskToStr(RegCtrl.faultmask));

    return res;
}

bool parse_basepri_reg(uint32_t reg_val) {
    bool res = true;
    RegBasePri_t Reg;
    Reg.val = reg_val;
    cli_printf("Priority:%u" CRLF, Reg.basepri);
    return res;
}

bool CortexM7_SCB_Diag(const SCB_Type* const SCBx) {
    bool res = true;
    LOG_WARNING(SYS, "CPUID:0x%08x", SCBx->CPUID); /*!< Offset: 0x000 (R/ )  CPUID Base Register */
    LOG_WARNING(SYS, "VTOR:0x%08x", SCBx->VTOR);   /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
    LOG_WARNING(SYS, "ICSR:0x%08x", SCBx->ICSR);   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
    LOG_WARNING(SYS, "AIRCR:0x%08x",
                SCBx->AIRCR); /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
    LOG_WARNING(SYS, "SCR:0x%08x", SCBx->SCR);       /*!< Offset: 0x010 (R/W)  System Control Register */
    LOG_WARNING(SYS, "CCR:0x%08x", SCBx->CCR);       /*!< Offset: 0x014 (R/W)  Configuration Control Register */
    LOG_WARNING(SYS, "CPACR:0x%08x", SCBx->CPACR);   /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
    LOG_WARNING(SYS, "HFSR:0x%08x", SCBx->HFSR);     /*!< Offset: 0x02C (R/W)  HardFault Status Register */
    LOG_WARNING(SYS, "ID_DFR:0x%08x", SCBx->ID_DFR); /*!< Offset: 0x048 (R/ )  Debug Feature Register */

    LOG_DEBUG(SYS, "ABFSR:0x%08x", SCBx->ABFSR);
    LOG_DEBUG(SYS, "SHCSR:0x%08x", SCBx->SHCSR); /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
    LOG_DEBUG(SYS, "CFSR:0x%08x", SCBx->CFSR);   /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
    LOG_DEBUG(SYS, "DFSR:0x%08x", SCBx->DFSR);   /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
    LOG_DEBUG(SYS, "MMFAR:0x%08x", SCBx->MMFAR); /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
    LOG_DEBUG(SYS, "BFAR:0x%08x", SCBx->BFAR);   /*!< Offset: 0x038 (R/W)  BusFault Address Register */
    LOG_DEBUG(SYS, "AFSR:0x%08x", SCBx->AFSR);   /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
    LOG_DEBUG(SYS, "ID_AFR:0x%08x", SCBx->ID_AFR);   /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
    LOG_DEBUG(SYS, "CLIDR:0x%08x", SCBx->CLIDR);     /*!< Offset: 0x078 (R/ )  Cache Level ID register */
    LOG_DEBUG(SYS, "CTR:0x%08x", SCBx->CTR);         /*!< Offset: 0x07C (R/ )  Cache Type register */
    LOG_DEBUG(SYS, "CCSIDR:0x%08x", SCBx->CCSIDR);   /*!< Offset: 0x080 (R/ )  Cache Size ID Register */
    LOG_DEBUG(SYS, "CSSELR:0x%08x", SCBx->CSSELR);   /*!< Offset: 0x084 (R/W)  Cache Size Selection Register */
    LOG_DEBUG(SYS, "STIR:0x%08x", SCBx->STIR);       /*!< Offset: 0x200 ( /W)  Software Triggered Interrupt Register */
    LOG_DEBUG(SYS, "MVFR0:0x%08x", SCBx->MVFR0);     /*!< Offset: 0x240 (R/ )  Media and VFP Feature Register 0 */
    LOG_DEBUG(SYS, "MVFR1:0x%08x", SCBx->MVFR1);     /*!< Offset: 0x244 (R/ )  Media and VFP Feature Register 1 */
    LOG_DEBUG(SYS, "MVFR2:0x%08x", SCBx->MVFR2);     /*!< Offset: 0x248 (R/ )  Media and VFP Feature Register 1 */
    LOG_DEBUG(SYS, "ICIALLU:0x%08x", SCBx->ICIALLU); /*!< Offset: 0x250 ( /W)  I-Cache Invalidate All to PoU */
    LOG_DEBUG(SYS, "DCIMVAC:0x%08x", SCBx->DCIMVAC); /*!< Offset: 0x25C ( /W)  D-Cache Invalidate by MVA to PoC */
    LOG_DEBUG(SYS, "ICIMVAU:0x%08x", SCBx->ICIMVAU); /*!< Offset: 0x258 ( /W)  I-Cache Invalidate by MVA to PoU */
    LOG_DEBUG(SYS, "DCISW:0x%08x", SCBx->DCISW);     /*!< Offset: 0x260 ( /W)  D-Cache Invalidate by Set-way */
    LOG_DEBUG(SYS, "DCCMVAU:0x%08x", SCBx->DCCMVAU); /*!< Offset: 0x264 ( /W)  D-Cache Clean by MVA to PoU */
    LOG_DEBUG(SYS, "DCCMVAC:0x%08x", SCBx->DCCMVAC); /*!< Offset: 0x268 ( /W)  D-Cache Clean by MVA to PoC */
    LOG_DEBUG(SYS, "DCCSW:0x%08x", SCBx->DCCSW);     /*!< Offset: 0x26C ( /W)  D-Cache Clean by Set-way */
    LOG_DEBUG(SYS, "DCCIMVAC:0x%08x",
              SCBx->DCCIMVAC); /*!< Offset: 0x270 ( /W)  D-Cache Clean and Invalidate by MVA to PoC */
    LOG_DEBUG(SYS, "DCCISW:0x%08x", SCBx->DCCISW); /*!< Offset: 0x274 ( /W)  D-Cache Clean and Invalidate by Set-way */
    LOG_DEBUG(SYS, "ITCMCR:0x%08x",
              SCBx->ITCMCR); /*!< Offset: 0x290 (R/W)  Instruction Tightly-Coupled Memory Control Register */
    LOG_DEBUG(SYS, "DTCMCR:0x%08x",
              SCBx->DTCMCR); /*!< Offset: 0x294 (R/W)  Data Tightly-Coupled Memory Control Registers */
    LOG_DEBUG(SYS, "AHBPCR:0x%08x", SCBx->AHBPCR); /*!< Offset: 0x298 (R/W)  AHBP Control Register */
    LOG_DEBUG(SYS, "CACR:0x%08x", SCBx->CACR);     /*!< Offset: 0x29C (R/W)  L1 Cache Control Register */
    LOG_DEBUG(SYS, "AHBSCR:0x%08x", SCBx->AHBSCR); /*!< Offset: 0x2A0 (R/W)  AHB Slave Control Register */
    LOG_DEBUG(SYS, "ABFSR:0x%08x", SCBx->ABFSR);   /*!< Offset: 0x2A8 (R/W)  Auxiliary Bus Fault Status Register */
    return res;
}
