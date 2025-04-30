#include "clock_config.h"

#include <stddef.h>

#include "board_start_mik32_v1.h"
#include "compiler_const.h"
#include "clock.h"
#include "mik32_hal_pcc.h"
#ifdef HAS_MISCELLANEOUS
#include "data_utils.h"
#endif

#ifdef HAS_SCR1_TIMER
#include "scr1_timer/scr1_timer.h"
#include "HAL/core/Include/mik32_hal_scr1_timer.h"
#endif


#ifdef HAS_LOG
#include "log.h"
#endif


ClockConfig_t ClockConfig = {
    .irq_priority = 7,
    .core_clock_mhz = 32000000,
    .hf_source = XTALL_FREQ_HZ,      // CLOCK_HF_EXTERNAL,
    .lf_source = CLK_LOW_FREQ_32KHZ, // CLOCK_LF_EXTERNAL,
    .valid = true,
};

ClockHandle_t ClockInstance = {
    .valid = true,
};




bool clock_init(void) {
    bool res = true;
    // ��������� ������������ ��������� �� ���� APB_P:  UART_0, GPIO_0, GPIO_1, GPIO_2
    PM->CLK_APB_P_SET |=
                PM_CLOCK_APB_P_UART_0_M
              | PM_CLOCK_APB_P_UART_1_M
              | PM_CLOCK_APB_P_GPIO_IRQ_M
              | PM_CLOCK_APB_P_GPIO_0_M
              | PM_CLOCK_APB_P_GPIO_1_M
              | PM_CLOCK_APB_P_GPIO_2_M
              | PM_CLOCK_APB_P_WDT_M;
    // ��������� ������������ ��������� �� ���� APB_M: PAD_CONFIG, WU, PM
    PM->CLK_APB_M_SET |= PM_CLOCK_APB_M_PAD_CONFIG_M
               | PM_CLOCK_APB_M_EPIC_M
               | PM_CLOCK_APB_M_WU_M
               | PM_CLOCK_APB_M_PM_M;



#if 0
    PM->CLK_AHB_SET.dword |= PM_CLOCK_AHB_SPIFI_M |
                     | PM_CLOCK_AHB_CPU_M
                     | PM_CLOCK_AHB_DMA_M
                     | PM_CLOCK_AHB_RAM_M
                       PM_CLOCK_AHB_EEPROM_M;
#endif

    PM->CLK_AHB_SET.cpu = 1;
    PM->CLK_AHB_SET.eeprom = 1;
    PM->CLK_AHB_SET.ram = 1;
    PM->CLK_AHB_SET.spifi = 1;
    PM->CLK_AHB_SET.dma = 1;
    PM->CLK_AHB_SET.tcb = 0;
    PM->CLK_AHB_SET.cryp = 0;
    PM->CLK_AHB_SET.crc32 = 0;

    PM->WDT_CLK_MUX = PM_WDT_CLK_MUX_LSI32K_M;

    HAL_PCC_OscEnable(PCC_OSCILLATORTYPE_OSC32M);

#ifdef HAS_SCR1_TIMER
    res = scr1_timer_init();
#endif
    return res;
}

_WEAK_FUN_ bool system_clock_config(void) { return false; }
