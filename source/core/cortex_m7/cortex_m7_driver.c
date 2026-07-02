#include "cortex_m7_driver.h"

#include "sys_config.h"

#ifdef USE_HAL_DRIVER
#include "stm32fx_hal.h"
#endif

#ifdef HAS_CMSIS
#include "core_cm7.h"
#endif

#ifdef HAS_INTERRUPT
#include "interrupt_mcal.h"
#endif

//#include "interrupt_drv.h"

bool cortex_m7_is_interrupt(void) {
    bool res = false;
#ifdef HAS_CMSIS
    // if(SCB_ICSR_ISRPENDING_Msk==(SCB->ICSR&SCB_ICSR_ISRPENDING_Msk)){ that code does not work
    //	res = true;
    //}
#endif /*HAS_CMSIS*/
    return res;
}

bool cortex_m7_exceptions(bool status) {
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

bool cortex_m7_exceptions_nmi(bool status) {
    bool res = false;
#ifdef HAS_CMSIS
    if(status) {
        __set_FAULTMASK(0);
    } else {
        __set_FAULTMASK(1);
    }
#endif /*HAS_CMSIS*/
    return res;
}

bool cortex_m7_set_sp(StackPointerSel_t sp) {
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

bool cortex_m7_reboot(void) {
#ifdef HAS_INTERRUPT
    interrupt_disable();
#endif

#ifdef HAS_STM32
    HAL_SuspendTick();
#endif

#ifdef HAS_CMSIS
    __disable_irq();
    NVIC_SystemReset();
#endif /*HAS_CMSIS*/

#ifdef HAS_WDT
    res = watchdog_set(10, 0);
#endif
    return true;
}

bool cortex_m7_set_vector_table(uint32_t start_address) {
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
bool cortex_m7_init_isr_vector(void) {
    bool res = false;
#ifdef HAS_CORTEX_M7

#ifdef HAS_MBR
    res = cortex_m7_set_vector_table(MBR_START_ADDRESS);
#endif /*HAS_MBR*/

#ifdef HAS_GENERIC
    res = cortex_m7_set_vector_table(APP_START_ADDRESS);
#endif /*HAS_GENERIC*/

#ifdef HAS_BOOTLOADER
    res = cortex_m7_set_vector_table(BOOT_START_ADDRESS);
#endif /*HAS_BOOTLOADER*/

#endif /*HAS_CORTEX_M7*/
    return res;
}
