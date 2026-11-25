#include "clock_config.h"

#include <stddef.h>

#include "clock.h"
#include "data_utils.h"
#include "compiler_const.h"
#include "module_driver_scg.h"
#include "board_config.h"

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_BOARD_INFO
#include "board_const.h"
#endif

ClockConfig_t ClockConfig = {
    .irq_priority = 7,
    .core_clock_mhz = 100000000,
    .hf_source = XTALL_FREQ_HZ,      // CLOCK_HF_EXTERNAL,
    .lf_source = CLK_LOW_FREQ_32KHZ, // CLOCK_LF_EXTERNAL,
    .valid = true,
};

ClockHandle_t ClockInstance = {
    .valid = true,
};


static bool clock_scg_init(void) {
	bool res = true;
    /* Enable FOSC, frequency is 24M, DIVH=DIV1(24M), DIVM=DIV1(24M), DIVL=DIV2(12M)*/
    SCG_FoscType tFoscStruct =
    {
        .bLock = false,
        .bCm = false,
        .bCmre = false,
        .bSten = false,
        .bBypass = false,
        .eDivH = SCG_ASYNCCLOCKDIV_BY1,
        .eDivM = SCG_ASYNCCLOCKDIV_BY1,
        .eDivL = SCG_ASYNCCLOCKDIV_BY2,
        .u8Eocv = 50U
    };
    SCG_EnableFOSC(&tFoscStruct);

    /* Enable PLL0, frequency is 300M, Freq=FOSC/ePrediv*Mult/Pstdiv=24M/12*300/2
     * DIVH=DIV2(150M), DIVM=DIV2(150M), DIVL=DIV4(75M), ClockSrc=FOSC */
    SCG_PllType tPll0Struct =
    {
        .bLock = false,
        .bCm = false,
        .bCmre = false,
        .bSten = false,
        .eSrc = SCG_PLLSOURCE_FOSC,
        .eDivH = SCG_ASYNCCLOCKDIV_BY2,
        .eDivM = SCG_ASYNCCLOCKDIV_BY2,
        .eDivL = SCG_ASYNCCLOCKDIV_BY4,
        .ePrediv = SCG_PLLPREDIV_BY12,
        .ePstDiv = SCG_PLLPSTDIV_BY2,
        .u16Mult = 299U
    };
    SCG_EnablePLL(SCG_PLL0, &tPll0Struct);

    /* Enable PLL1, frequency is 240M, Freq=FOSC/u8Prediv*Mult/Pstdiv=24M/12*240/2
     * DIVH=DIV2(120M), DIVM=DIV2(120M), DIVL=DIV4(60M), ClockSrc=FOSC */
    SCG_PllType tPll1Struct =
    {
        .bLock = false,
        .bCm = false,
        .bCmre = false,
        .bSten = false,
        .eSrc = SCG_PLLSOURCE_FOSC,
        .eDivH = SCG_ASYNCCLOCKDIV_BY2,
        .eDivM = SCG_ASYNCCLOCKDIV_BY2,
        .eDivL = SCG_ASYNCCLOCKDIV_BY4,
        .ePrediv = SCG_PLLPREDIV_BY12,
        .ePstDiv = SCG_PLLPSTDIV_BY2,
        .u16Mult = 239U
    };
    SCG_EnablePLL(SCG_PLL1, &tPll1Struct);

    /* Enable SIRC DIV, DIVH=DIV1(12M), DIVM=DIV1(12M), DIVL=DIV2(6M) */
    SCG_SircType tSircStruct =
    {
        .bLock = false,
        .bCm = false,
        .bTrEn = false,
        .bLpen = false,
        .bSten = false,
        .eDivH = SCG_ASYNCCLOCKDIV_BY1,
        .eDivM = SCG_ASYNCCLOCKDIV_BY1,
        .eDivL = SCG_ASYNCCLOCKDIV_BY2,
        .u8TrimSrc = 0U
    };
    SCG_SetSIRC(&tSircStruct);

    /* Set core clock source from PLL0, DIV_CORE=DIV1(300M), DIV_BUS=DIV2(150M), DIV_SLOW=DIV4(75M)*/
    SCG_ClockCtrlType tClockStruct =
    {
        .bSysClkMonitor = true,
        .eSrc = SCG_CLOCK_SRC_PLL0,
        .eDivSlow = SCG_CLOCK_DIV_BY2,
        .eDivBus = SCG_CLOCK_DIV_BY2,
        .eDivCore = SCG_CLOCK_DIV_BY1
    };
    SCG_SetClkCtrl(&tClockStruct);
    return res;
}



bool clock_init(void) {
    bool res = false;
    res = clock_scg_init();
    return res;
}

_WEAK_FUN_ bool system_clock_config(void) { return false; }
