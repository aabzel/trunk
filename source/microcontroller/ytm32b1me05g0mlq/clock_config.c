#include "clock_config.h"

#include <stddef.h>

#include "board_const.h"
#include "compiler_const.h"
#include "clock.h"
#include "data_utils.h"
#include "log.h"

#ifdef HAS_YTM32B1ME0_1_3_1
#include "yuntu_misc.h"
#include "clock_YTM32B1Mx.h"
#endif

ClockConfig_t ClockConfig = {
    .irq_priority = 7,
    .core_clock_mhz = 120000000,
    .hf_source = XTALL_FREQ_HZ,      // CLOCK_HF_EXTERNAL,
    .lf_source = CLK_LOW_FREQ_32KHZ, // CLOCK_LF_EXTERNAL,
    .valid = true,
};

ClockHandle_t ClockInstance = {
    .valid = true,
};


#ifdef HAS_YTM32B1ME0_1_3_1
// check by cldf
const scu_config_t clock_config0ScuConfig = {
    .fircEnable = true,
    .fircDeepSleepEnable = false,
    .sircDeepSleepEnable = true,
    .sircStandbyEnable = true,
    .sircPowerDownEnable = true,
    .sysClkSrc = SCU_SYSTEM_CLOCK_SRC_PLL,
    .fxoscConfig =
        {
            .enable = true,
            .bypassMode = false,
            .gainSelection = 5,
            .frequency = XTALL_FREQ_HZ,
        },
    .sxoscConfig =
        {
            .enable = true,
            .gainSelection = 0,
            .bypassMode = true,
            .deepsleepEnable = true,
            .standbyEnable = true,
            .powerdownEnable = true,
            .frequency = CLK_LOW_FREQ_32KHZ,
        },
    .pllConfig =
        {
            .enable = true,
            .pllRefClock = SCU_PLL_REF_FXOSC_CLK,
            .pllFeedBackDiv = 10,
            .pllRefClkDiv = 1,
        },
    .sysDiv = SCU_SYS_CLK_DIV_BY_2,
    .fastBusDiv = SCU_SYS_CLK_DIV_BY_1,
    .slowBusDiv = SCU_SYS_CLK_DIV_BY_2,
    .flashDiv = SCU_SYS_CLK_DIV_BY_3,
    .clockOutConfig =
        {
            .enable = true,
            .source = SCU_CLKOUT_SEL_PLL_CLK,
            .divider = 254,
        },
};

/*! @brief peripheral clock PeripheralClockConfig
 * Table 13.1: IP Clock Control Table
 * */

peripheral_clock_config_t clock_config0PeripheralClockConfig[] = {
    {
        .clkName = FlexCAN0_CLK,
        .clkGate = true,
        .divider = DIV_BY_1,
        .clkSrc = CLK_SRC_DISABLED,
    },
#ifdef HAS_CAN0
#endif

    {
        .clkName = FlexCAN1_CLK,
        .clkGate = true,
        .divider = DIV_BY_1,
        .clkSrc = CLK_SRC_DISABLED,
    },
#ifdef HAS_CAN1
#endif

    {
        .clkName = FlexCAN2_CLK,
        .clkGate = true,
        .divider = DIV_BY_1,
        .clkSrc = CLK_SRC_DISABLED,
    },
#ifdef HAS_CAN2
#endif

    {
        .clkName = FlexCAN3_CLK,
        .clkGate = true,
        .divider = DIV_BY_1,
        .clkSrc = CLK_SRC_DISABLED,
    },
#ifdef HAS_CAN3
#endif

    {
        .clkName = FlexCAN4_CLK,
        .clkGate = true,
        .divider = DIV_BY_1,
        .clkSrc = CLK_SRC_DISABLED,
    },
#ifdef HAS_CAN4
#endif

    {
        .clkName = FlexCAN5_CLK,
        .clkGate = true,
        .divider = DIV_BY_1,
        .clkSrc = CLK_SRC_DISABLED,
    },
#ifdef HAS_CAN5
#endif

#ifdef HAS_GPIO
    {
        .clkName = GPIO_CLK,
        .clkGate = true,
        .divider = DIV_BY_3,
        .clkSrc = CLK_SRC_FIRC,
    },
#endif

    //   { .clkName = LINFlexD0_CLK, .clkGate = true, .divider = DIV_BY_1, .clkSrc = CLK_SRC_DISABLED,    },
    //   { .clkName = LINFlexD1_CLK, .clkGate = true, .divider = DIV_BY_1, .clkSrc = CLK_SRC_DISABLED,    },
    {
        .clkName = LINFlexD2_CLK,
        .clkGate = true,
        .divider = DIV_BY_1,
        .clkSrc = CLK_SRC_DISABLED,
    },
    //    { .clkName = LINFlexD3_CLK, .clkGate = true, .divider = DIV_BY_1, .clkSrc = CLK_SRC_DISABLED,    },
    //   { .clkName = eTMR0_CLK, .clkGate = true, .divider = DIV_BY_1, .clkSrc = CLK_SRC_DISABLED,    },
    //   { .clkName = eTMR1_CLK, .clkGate = true, .divider = DIV_BY_1, .clkSrc = CLK_SRC_DISABLED,    },
};

/*! @brief User Configuration structure clock_config0ClockManager */
clock_manager_user_config_t clock_config0ClockManager = {
    .scuConfigPtr = &clock_config0ScuConfig,
    .cmuConfigPtr = NULL,
    .ipcConfig =
        {
            .peripheralClocks = clock_config0PeripheralClockConfig,
            .count = ARRAY_SIZE(clock_config0PeripheralClockConfig),
        },
};

/*! @brief Array of pointers to User configuration structures */
clock_manager_user_config_t const* g_clockManConfigsArr[] = {
    &clock_config0ClockManager,
};

/*! @brief Array of pointers to User defined Callbacks configuration structures */
/* The tool do not support generate Callbacks configuration. It's always empty. */
clock_manager_callback_user_config_t* g_clockManCallbacksArr[] = {(void*)0};
#endif

bool clock_init(void) {
    bool res = false;
#ifdef HAS_YTM32B1ME0_1_3_1
    status_t ret = STATUS_ERROR;
    (void)ret;
    ret = CLOCK_SYS_Init(g_clockManConfigsArr, CLOCK_MANAGER_CONFIG_CNT, g_clockManCallbacksArr,
                         CLOCK_MANAGER_CALLBACK_CNT);
    res = YunTuSdkStatusToRes(ret);
    ret = CLOCK_SYS_UpdateConfiguration(CLOCK_MANAGER_ACTIVE_INDEX, CLOCK_MANAGER_POLICY_FORCIBLE);

    res = YunTuSdkStatusToRes(ret) && res;
#endif
    return res;
}

_WEAK_FUN_ bool system_clock_config(void) { return false; }
