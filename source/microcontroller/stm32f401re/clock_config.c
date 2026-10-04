#include "clock_config.h"

#include "stm32f4xx_hal.h"
#include "clock_const.h"
#include "hal_mcal.h"
#include "clock_types.h"
#include "data_utils.h"

ClockConfig_t ClockConfig = {
        .irq_priority = 7,
        .hf_source = CLK_HI_FREQ_8MHZ,  //  CLOCK_HF_EXTERNAL,
        .lf_source = CLK_LOW_FREQ_32KHZ, // CLOCK_LF_EXTERNAL,
        .valid = true,
};

ClockHandle_t ClockInstance = { .valid = true, };

static bool clock_init_8_84_mhz(void) {
    bool res = true;
    RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
    RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

    /** Configure the main internal regulator output voltage
     */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */


    RCC_OscInitStruct.OscillatorType =  RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_LSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.LSEState = RCC_LSE_ON;
   // RCC_OscInitStruct.LSIState = RCC_LSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    HAL_StatusTypeDef ret = HAL_RCC_OscConfig(&RCC_OscInitStruct) ;
    res = HAL_retToRes(ret);

    if (res) {
        /** Initializes the CPU, AHB and APB buses clocks
         */
        RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1
                | RCC_CLOCKTYPE_PCLK2;
        RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
        RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
        RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
        RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
        ret=HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
        res = HAL_retToRes(ret);
    }
    return res;
}

bool clock_init_48mhz(void) {
    bool res = true;
    res = clock_init_8_84_mhz();
    return res;
}

bool clock_mcal_init(void) {
    bool res = true;

    res = clock_init_8_84_mhz();
#ifdef HAS_MCO
    HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSE, RCC_MCODIV_4);
    HAL_RCC_MCOConfig(RCC_MCO2, RCC_MCO2SOURCE_SYSCLK, RCC_MCODIV_5);
#endif
    return res;
}
