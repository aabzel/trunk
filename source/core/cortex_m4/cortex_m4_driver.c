#include "cortex_m4_driver.h"

#include "microcontroller.h"
#include "flash_config.h"
#include "log.h"
#include "interrupt_mcal.h"

#ifdef HAS_CMSIS
#include "cmsis_gcc.h"
#include "core_cm4.h"
#endif /*HAS_CMSIS*/

#ifdef HAS_EHAL
#include "core_ehal.h"
#endif

#ifdef HAS_WATCHDOG
#include "watchdog_mcal.h"
#endif


/*
  CPACR(Coprocessor Access Control Register) 0xE000ED88
  see ARM®v7-M Architecture Reference Manual

  access valid values
    COPROC_ACCESS_DENIED = 0,     Access denied – generates a NOCP UsageFault
    COPROC_ACCESS_PRIVILEGED = 1, Privileged access only. User access will generate a NOCP fault.
    COPROC_ACCESS_RESERVED = 2,   Reserved (UNPREDICTABLE).
    COPROC_ACCESS_FULL = 3,       Full access

 */
bool cortex_m4_coproc_access_set(uint8_t cp_num, CoProcAccess_t access) {
    bool res = false;
#ifndef HAS_EHAL
    if(access <= 3) {
#ifdef HAS_CORTEX_M4_DIAG
        LOG_INFO(SYS, "Set,CP:%u,Access:%u=%s", cp_num, access, CortecM4CoProcAccessToStr(access));
#endif
        CoProcessorAccessCtrlReg_t Reg = {0};
        Reg.qword = SCB->CPACR;
        switch(cp_num) {
        case 0: {
            Reg.CP0 = access;
            res = true;
        } break;
        case 1: {
            Reg.CP1 = access;
            res = true;
        } break;
        case 2: {
            Reg.CP2 = access;
            res = true;
        } break;
        case 3: {
            Reg.CP3 = access;
            res = true;
        } break;
        case 4: {
            Reg.CP4 = access;
            res = true;
        } break;
        case 5: {
            Reg.CP5 = access;
            res = true;
        } break;
        case 6: {
            Reg.CP6 = access;
            res = true;
        } break;
        case 7: {
            Reg.CP7 = access;
            res = true;
        } break;
        case 10: {
            Reg.CP10 = access;
            res = true;
        } break;
        case 11: {
            Reg.CP11 = access;
            res = true;
        } break;
        default:
            res = false;
            break;
        }

        if(res) {
            SCB->CPACR = Reg.qword;
        }
    }
#endif
    return res;
}

bool cortex_m4_coproc_access_get(uint8_t cp_num, CoProcAccess_t* const access) {
    bool res = false;
#ifndef HAS_EHAL
    if(access) {
        CoProcessorAccessCtrlReg_t Reg = {0};
        Reg.qword = SCB->CPACR;
        switch(cp_num) {
        case 0: {
            *access = Reg.CP0;
            res = true;
        } break;
        case 1: {
            *access = Reg.CP1;
            res = true;
        } break;
        case 2: {
            *access = Reg.CP2;
            res = true;
        } break;
        case 3: {
            *access = Reg.CP3;
            res = true;
        } break;
        case 4: {
            *access = Reg.CP4;
            res = true;
        } break;
        case 5: {
            *access = Reg.CP5;
            res = true;
        } break;
        case 6: {
            *access = Reg.CP6;
            res = true;
        } break;
        case 7: {
            *access = Reg.CP7;
            res = true;
        } break;
        case 10: {
            *access = Reg.CP10;
            res = true;
        } break;
        case 11: {
            *access = Reg.CP11;
            res = true;
        } break;
        default:
            res = false;
            break;
        }
    }
#endif
    return res;
}

bool cortex_m4_is_interrupt(void) {
    bool res = false;
#ifdef HAS_CMSIS
    // if(SCB_ICSR_ISRPENDING_Msk==(SCB->ICSR&SCB_ICSR_ISRPENDING_Msk)){ that code does not work
    //    res = true;
    //}
#endif /*HAS_CMSIS*/
    return res;
}

bool cortex_m4_exceptions(bool status) {
    bool res = false;
#ifdef HAS_CMSIS
    if(status) {
        __set_PRIMASK(0);
    } else {
        __set_PRIMASK(1);
    }
#endif /*HAS_CMSIS*/
    return res;
}

bool cortex_m4_exceptions_nmi(bool status) {
    bool res = false;
#ifdef HAS_CMSIS
    if(status) {
       // __set_FAULTMASK(0);
    } else {
       // __set_FAULTMASK(1);
    }
#endif /*HAS_CMSIS*/
    return res;
}

bool cortex_m4_set_sp(StackPointerSel_t sp) {
    bool res = false;
#ifdef HAS_CMSIS
    RegCtrl_t RegCtrl;
    RegCtrl.val = 0;
    RegCtrl.val = __get_CONTROL();
    RegCtrl.spsel = sp;
    __set_CONTROL(RegCtrl.val);
#endif /*HAS_CMSIS*/
    return res;
}

bool cortex_m4_reboot(void) {
    bool res = true;
    LOG_WARNING(SYS, "CM4-Reboot..");
    // HAL_SuspendTick();
    interrupt_disable();

#ifdef HAS_CMSIS
    __disable_irq();
    NVIC_SystemReset();
#endif

#ifdef HAS_WATCHDOG
    res = watchdog_timeout_set(0);
#endif

    return res;
}

bool cortex_m4_set_vector_table(uint32_t start_address) {
    bool res = false;
#ifdef HAS_CMSIS
    __disable_irq();
    __set_PRIMASK(1);
    SCB->VTOR = start_address;
    __set_PRIMASK(0);
    __enable_irq();
    if(start_address == SCB->VTOR) {
        res = true;
    } else {
        res = false;
    }
    //__enable_irq();
#endif /*HAS_CMSIS*/
    return res;
}

bool cortex_m4_init_isr_vector(void) {
    bool res = false;
#ifdef HAS_CORTEX_M4

#ifdef HAS_MBR
    res = cortex_m4_set_vector_table(MBR_START_ADDRESS);
#endif /*HAS_MBR*/

#ifdef HAS_GENERIC
    res = cortex_m4_set_vector_table(APP_START_ADDRESS);
#endif /*HAS_GENERIC*/

#ifdef HAS_BOOTLOADER
    res = cortex_m4_set_vector_table(BOOT_START_ADDRESS);
#endif /*HAS_BOOTLOADER*/

#endif /*HAS_CORTEX_M4*/
    return res;
}

bool cortex_m4_breakpoint_set(uint8_t num, uint32_t address) {
    bool res = false;
    LOG_INFO(SYS, "BreakPiont,Set,N:%u,Addr:0x%x", num, address);
    if(num < BREAKPOINTS_MAX_CNT) {
        FLASH_PATCH->FLASH_PATCH_COMPARATOR[num] = 0;
        res = true;
    }
    return res;
}

bool cortex_m4_breakpoints_reset(void) {
    bool res = true;
    LOG_WARNING(SYS, "ResetBreakPionts");
    uint32_t i = 0;
    for(i = 0; i < BREAKPOINTS_MAX_CNT; i++) {
        FLASH_PATCH->FLASH_PATCH_COMPARATOR[i] = 0;
    }
    return res;
}
