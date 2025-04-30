#include "clock_config.h"

#include "hal_diag.h"
#ifdef HAS_LOG
#include "log.h"
#endif
#include "stm32f4xx_hal.h"
#include "sys_config.h"
#include "clocks.h"
#include "clock_stm32.h"

#if 0
bool clock_init(void) {
    bool res = true;
#ifdef HAS_LOG
    LOG_INFO(SYS, "ClockInit. XTAL:%u Hz",XTALL_FREQ_HZ);
#endif
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
    //sw_pause_ms(100);
    RCC_OscInitStruct.OscillatorType =  RCC_OSCILLATORTYPE_LSI| RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.LSIState = RCC_LSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 15;
    RCC_OscInitStruct.PLL.PLLN = 144;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 5;
    HAL_StatusTypeDef ret;
    ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
    if(ret != HAL_OK) {
#ifdef HAS_HAL_DIAG
        LOG_ERROR(SYS, "Err %s", HalStatus2Str(ret));
#endif
        res = false;
    }
    //sw_pause_ms(200);
    if(res) {
        RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
        		| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
        RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
        RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
        RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
        RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
        //ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);
        //ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
        ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);
        //ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4);
        //ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
        if(ret != HAL_OK) {
#ifdef HAS_HAL_DIAG
            LOG_ERROR(SYS, "Err %s", HalStatus2Str(ret));
#endif
            res = false;
        }
        //sw_pause_ms(200);
    }
    return res;
}
#endif

#if 1
bool clock_init(void) {
    bool res = true;
#ifdef HAS_LOG
    LOG_INFO(SYS, "ClockInit. XTAL:%u Hz",XTALL_FREQ_HZ);
#endif
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
    //sw_pause_ms(100);
    RCC_OscInitStruct.OscillatorType =  RCC_OSCILLATORTYPE_LSI| RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.LSIState = RCC_LSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = XTALL_FREQ_HZ/1000000;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    HAL_StatusTypeDef ret;
    ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
    if(ret != HAL_OK) {
#ifdef HAS_HAL_DIAG
        LOG_ERROR(SYS, "Err %s", HalStatus2Str(ret));
#endif
        res = false;
    }
    //sw_pause_ms(200);
    if(res) {
        RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
        		| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
        RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
        RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
        RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
        RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
        //ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);
        //ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
        ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
        //ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4);
        //ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
        if(ret != HAL_OK) {
#ifdef HAS_HAL_DIAG
            LOG_ERROR(SYS, "Err %s", HalStatus2Str(ret));
#endif
            res = false;
        }
        //sw_pause_ms(200);
    }
    return res;
}
#endif
