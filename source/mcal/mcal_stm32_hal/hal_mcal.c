#include "hal_mcal.h"

#include <string.h>

#include "clock_diag.h"
#include "microcontroller_types.h"
#include "std_includes.h"
//#include "stm32fx_hal_def.h"

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_ARRAY_DIAG
#include "array_diag.h"
#endif

bool HAL_retToRes(const HAL_StatusTypeDef ret) {
    bool res = false;
    switch(ret) {
    case HAL_OK:
        res = true;
        break;
    case HAL_ERROR:
        res = false;
        break;
    case HAL_BUSY:
        res = false;
        break;
    case HAL_TIMEOUT:
        res = false;
        break;
    default:
        res = false;
        break;
    }
    return res;
}

bool stm32_unique_device_id_get(Stm32UniqueDeviceID_t* const Node) {
    bool res = false;
    if(Node) {
        memcpy((void*)Node, (void*)UID_BASE, 12);
        res = true;
    }
    return res;
}

bool isFromInterrupt(void) {
    bool res = false;
    /*TODO: Explore register SCB->ICSR */
    // res = ((SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) != 0);
    return res;
}

bool hal_init(void) {
    bool res = false;
    HAL_StatusTypeDef ret = HAL_Init();
    res = HAL_retToRes(ret);
    return res;
}

void Error_Handler(void) {
#ifdef HAS_LOG
    LOG_ERROR(SYS, "Error");
#endif
    __disable_irq();
    while(1) {
    }
}

bool microcontroller_custom_init(void) {
    bool res = false;
    Stm32UniqueDeviceID_t UniqueDeviceID = {0};
    res = stm32_unique_device_id_get(&UniqueDeviceID);
#ifdef HAS_ARRAY_DIAG
    LOG_WARNING(MICROCONTROLLER, "MCU:UniqueDeviceID:%s", ArrayToStr(UniqueDeviceID.buff, 12));
#endif

#ifdef HAS_CLOCK_DIAG
    Stm32RccCsr_t RccCsr;
    RccCsr.dword = RCC->CSR;
    LOG_INFO(MICROCONTROLLER, "%s", Stm32RccCsrToStr(&RccCsr));
#endif
    return res;
}
