#include "clock_mcal.h"

#include "board_config.h"
#include "clock_config.h"
#include "clock_custom.h"
#include "hal_mcal.h"
#include "std_includes.h"
#include "stm32f4xx_hal.h"
#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_PLL_CALC
#include "pll_calc.h"
#endif

#ifdef HAS_SYSTICK
//#include "systick_general.h"
#endif /**/

#ifdef HAS_PLL_CALC
static uint32_t ClockPllPToRCC_PLLP_ClockDivider(const uint32_t pll_p) {
    uint32_t pllp = RCC_PLLP_DIV4;
    switch(pll_p) {
    case 2:
        pllp = RCC_PLLP_DIV2;
        break;
    case 4:
        pllp = RCC_PLLP_DIV4;
        break;
    case 6:
        pllp = RCC_PLLP_DIV6;
        break;
    case 8:
        pllp = RCC_PLLP_DIV8;
        break;
    default:
        break;
    }
    return pllp;
}
#endif /**/

/*calibrate*/
uint64_t pause_1ms(void) {
    uint64_t in = 0, cnt = 0;
    for(in = 0; in < 1397; in++) {
        cnt++;
    }
    return cnt;
}

uint64_t pause_1us(void) {
    uint64_t in = 0, cnt = 0;
    for(in = 0; in < 29700; in++) {
        cnt++;
    }
    return cnt;
}

uint64_t sw_pause_ms(uint32_t delay_in_ms) {
    uint64_t cnt = 0;
    // LOG_INFO(CLK, "SwPause %u ms", delay_in_ms); del
    uint32_t t = 0;
    for(t = 0; t < delay_in_ms; t++) {
        cnt += pause_1ms();
    }
    return cnt;
}

uint32_t clock_freq_get(const ClockBus_t clock_bus) {
    uint32_t clock_freq_hz = 0;
    switch(clock_bus) {
    case CLOCK_BUS_SYS: {
        clock_freq_hz = HAL_RCC_GetSysClockFreq();

    } break;
    case CLOCK_BUS_APB2: {
        clock_freq_hz = HAL_RCC_GetPCLK2Freq();

    } break;
    case CLOCK_BUS_APB1: {
        clock_freq_hz = HAL_RCC_GetPCLK1Freq();

    } break;
    case CLOCK_BUS_AHB: {
        clock_freq_hz = HAL_RCC_GetHCLKFreq();

    } break;
    default:
        clock_freq_hz = 0;
        break;
    }

    return clock_freq_hz;
}

bool clock_frequency_get(const ClockBus_t clock_name, uint32_t* const frequency_hz) {
    bool res = false;
    if(frequency_hz) {
        *frequency_hz = clock_freq_get(clock_name);
        res = false;
    }
    return res;
}

#ifdef HAS_PLL_CALC
static bool clock_init_rcc_osc_struct(const PllStm32Config_t* const Config, RCC_OscInitTypeDef* const pRccOscInit) {
    bool res = false;
    /* Initializes the RCC Oscillators according to the specified storageeters
       in the RCC_OscInitTypeDef structure.   */
    pRccOscInit->OscillatorType = RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_HSE;
    pRccOscInit->HSEState = RCC_HSE_ON;
    pRccOscInit->LSIState = RCC_LSI_ON;
    pRccOscInit->PLL.PLLState = RCC_PLL_ON;
    pRccOscInit->PLL.PLLSource = RCC_PLLSOURCE_HSE;
    pRccOscInit->PLL.PLLM = Config->M;
    pRccOscInit->PLL.PLLN = Config->N;
    pRccOscInit->PLL.PLLP = ClockPllPToRCC_PLLP_ClockDivider(Config->P);
    pRccOscInit->PLL.PLLQ = Config->Q;
    return res;
}
#endif

#ifdef HAS_PLL_CALC
static bool clock_init_rcc_clock(RCC_ClkInitTypeDef* const pRccClkInit) {
    /* Initializes the CPU, AHB and APB buses clocks */
    HAL_StatusTypeDef ret = HAL_ERROR;
    bool res = false;
    pRccClkInit->ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    pRccClkInit->SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    pRccClkInit->AHBCLKDivider = RCC_SYSCLK_DIV1;
    pRccClkInit->APB1CLKDivider = RCC_HCLK_DIV4;
    pRccClkInit->APB2CLKDivider = RCC_HCLK_DIV2;

    ret = HAL_RCC_ClockConfig(pRccClkInit, FLASH_LATENCY_3);
    res = HAL_retToRes(ret);
    HAL_SuspendTick();
    return res;
}
#endif

#ifdef HAS_PLL_CALC
static bool clock_runtime_init(const PllStm32Config_t* const Config) {
    bool res = false;
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};

    /* Configure the main internal regulator output voltage   */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    res = clock_init_rcc_osc_struct(Config, &RCC_OscInitStruct);

    HAL_StatusTypeDef ret;
    ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
    res = HAL_retToRes(ret);

    if(res) {
        RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
        res = clock_init_rcc_clock(&RCC_ClkInitStruct);
        ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
        res = HAL_retToRes(ret);
        HAL_SuspendTick();

        if(!res) {
            res = false;
#ifdef HAS_HAL_DIAG
            LOG_ERROR(CLK, "Err:%u=%s", ret, HalStatusToStr(ret));
#endif
        }
    } else {
#ifdef HAS_HAL_DIAG
        LOG_ERROR(CLK, "Err:%u=%s", ret, HalStatusToStr(ret));
#endif
    }
    return res;
}
#endif

uint32_t clock_core_freq_get(void) {
    uint32_t core_freq_hz = clock_freq_get(CLOCK_BUS_SYS);
    return core_freq_hz;
}

bool clock_core_freq_set(uint32_t core_freq_hz) {
    bool res = false;
#ifdef HAS_LOG
    LOG_INFO(CLK, "ClkSet:%u Hz", core_freq_hz);
#endif
#ifdef HAS_PLL_CALC
    PllStm32Config_t Config = {0};
    Config.xtall_freq_hz = XTAL_FREQ_HZ;
    Config.core_freq_hz = core_freq_hz;
    res = pll_calc_stm32_config(XTAL_FREQ_HZ, core_freq_hz, &Config);
    if(res) {
        LOG_INFO(CLK, "PLL:%s", PllStm32ConfigToStr(&Config));
    }
    res = clock_runtime_init(&Config);
#else
    res = clock_config_default();
#endif
    return res;
}
