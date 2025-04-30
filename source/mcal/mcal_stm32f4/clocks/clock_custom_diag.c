#include "clock_custom_diag.h"

#include <stdio.h>
#include <string.h>

#include "clock_types.h"
#include "common_diag.h"
#include "log.h"
#include "log_utils.h"
#include "stm32f4xx_hal.h"

#ifdef HAS_STRING
#include "str_utils.h"
#endif

static bool print_conditional(char* key_word1, char* key_word2, char* bus, char* module, bool on_off) {
    bool res = false;
    static char temp_str[80] = "";
    strcpy(temp_str, "");
    snprintf(temp_str, sizeof(temp_str), "%4s %8s %3s", bus, module, OnOff2Str(on_off));
    if(is_contain(temp_str, key_word1, key_word2)) {
        if(on_off) {
            LOG_WARNING(CLK, "%s", temp_str);
        } else {
            LOG_NOTICE(CLK, "%s", temp_str);
        }
        res = true;
    }
    return res;
}

bool periph_clock_diag(char* key_word1, char* key_word2) {
    bool res = false;
    RccAhb1PeriphClkEnReg_t RegAhb1;
    RegAhb1.reg_val = RCC->AHB1ENR;
    set_log_level(CLK, LOG_LEVEL_NOTICE);
    print_conditional(key_word1, key_word2, "AHB1", "CRC", RegAhb1.crc);
    print_conditional(key_word1, key_word2, "AHB1", "DMA1", RegAhb1.dma1);
    print_conditional(key_word1, key_word2, "AHB1", "DMA2", RegAhb1.dma2);
    print_conditional(key_word1, key_word2, "AHB1", "GPIOA", RegAhb1.gpioa);
    print_conditional(key_word1, key_word2, "AHB1", "GPIOB", RegAhb1.gpiob);
    print_conditional(key_word1, key_word2, "AHB1", "GPIOC", RegAhb1.gpioc);
    print_conditional(key_word1, key_word2, "AHB1", "GPIOD", RegAhb1.gpiod);
    print_conditional(key_word1, key_word2, "AHB1", "GPIOE", RegAhb1.gpioe);
    print_conditional(key_word1, key_word2, "AHB1", "GPIOF", RegAhb1.gpiof);
    print_conditional(key_word1, key_word2, "AHB1", "GPIOG", RegAhb1.gpiog);
    print_conditional(key_word1, key_word2, "AHB1", "GPIOH", RegAhb1.gpioh);

    RccAhb2PeriphClkEnReg_t RegAhb2;
    RegAhb2.reg_val = RCC->AHB2ENR;
    print_conditional(key_word1, key_word2, "AHB2", " RNG", RegAhb2.rng);
    print_conditional(key_word1, key_word2, "AHB2", " OTGFS", RegAhb2.otgfs);

    RccAhb3PeriphClkEnReg_t RegAhb3;
    RegAhb3.reg_val = RCC->AHB3ENR;
    print_conditional(key_word1, key_word2, "AHB3", "FSMC", RegAhb3.fsmc);
    print_conditional(key_word1, key_word2, "AHB3", "QSPI", RegAhb3.qspi);

    RccApb1PeriphClkEnReg_t RccApb1;
    RccApb1.reg_val = RCC->APB1ENR;
    print_conditional(key_word1, key_word2, "APB1", "CAN1", RccApb1.can1);
    print_conditional(key_word1, key_word2, "APB1", "CAN2", RccApb1.can2);
    print_conditional(key_word1, key_word2, "APB1", "CAN3", RccApb1.can3);
    print_conditional(key_word1, key_word2, "APB1", "DAC", RccApb1.dac);
    print_conditional(key_word1, key_word2, "APB1", "I2C1", RccApb1.i2c1);
    print_conditional(key_word1, key_word2, "APB1", "I2C2", RccApb1.i2c2);
    print_conditional(key_word1, key_word2, "APB1", "I2C3", RccApb1.i2c3);
    print_conditional(key_word1, key_word2, "APB1", "I2CFMP1", RccApb1.i2cfmp1);
    print_conditional(key_word1, key_word2, "APB1", "LPTIMER1", RccApb1.lptimer1);
    print_conditional(key_word1, key_word2, "APB1", "PWR", RccApb1.pwr);
    print_conditional(key_word1, key_word2, "APB1", "RTCAPB", RccApb1.rtcapb);
    print_conditional(key_word1, key_word2, "APB1", "SPI2", RccApb1.spi2);
    print_conditional(key_word1, key_word2, "APB1", "SPI3", RccApb1.spi3);
    print_conditional(key_word1, key_word2, "APB1", "TIM12", RccApb1.tim12);
    print_conditional(key_word1, key_word2, "APB1", "TIM13", RccApb1.tim13);
    print_conditional(key_word1, key_word2, "APB1", "TIM14", RccApb1.tim14);
    print_conditional(key_word1, key_word2, "APB1", "TIM2", RccApb1.tim2);
    print_conditional(key_word1, key_word2, "APB1", "TIM3", RccApb1.tim3);
    print_conditional(key_word1, key_word2, "APB1", "TIM4", RccApb1.tim4);
    print_conditional(key_word1, key_word2, "APB1", "TIM5", RccApb1.tim5);
    print_conditional(key_word1, key_word2, "APB1", "TIM6", RccApb1.tim6);
    print_conditional(key_word1, key_word2, "APB1", "TIM7", RccApb1.tim7);
    print_conditional(key_word1, key_word2, "APB1", "UART4", RccApb1.uart4);
    print_conditional(key_word1, key_word2, "APB1", "UART5", RccApb1.uart5);
    print_conditional(key_word1, key_word2, "APB1", "UART7", RccApb1.uart7);
    print_conditional(key_word1, key_word2, "APB1", "UART8", RccApb1.uart8);
    print_conditional(key_word1, key_word2, "APB1", "USART2", RccApb1.usart2);
    print_conditional(key_word1, key_word2, "APB1", "USART3", RccApb1.usart3);
    print_conditional(key_word1, key_word2, "APB1", "WWDG", RccApb1.wwdg);

    RccApb2PeriphClkEnReg_t RccApb2;
    RccApb2.reg_val = RCC->APB2ENR;
    print_conditional(key_word1, key_word2, "APB2", "ADC1", RccApb2.adc1);
    print_conditional(key_word1, key_word2, "APB2", "DFSDM1", RccApb2.dfsdm1);
    print_conditional(key_word1, key_word2, "APB2", "DFSDM2", RccApb2.dfsdm2);
    print_conditional(key_word1, key_word2, "APB2", "EXTIT", RccApb2.extit);
    print_conditional(key_word1, key_word2, "APB2", "SAI1", RccApb2.sai1);
    print_conditional(key_word1, key_word2, "APB2", "SDIO", RccApb2.sdio);
    print_conditional(key_word1, key_word2, "APB2", "SPI1", RccApb2.spi1);
    print_conditional(key_word1, key_word2, "APB2", "SPI4", RccApb2.spi4);
    print_conditional(key_word1, key_word2, "APB2", "SPI5", RccApb2.spi5);
    print_conditional(key_word1, key_word2, "APB2", "SYSCF", RccApb2.syscfg);
    print_conditional(key_word1, key_word2, "APB2", "TIM1", RccApb2.tim1);
    print_conditional(key_word1, key_word2, "APB2", "TIM10", RccApb2.tim10);
    print_conditional(key_word1, key_word2, "APB2", "TIM11", RccApb2.tim11);
    print_conditional(key_word1, key_word2, "APB2", "TIM8", RccApb2.tim8);
    print_conditional(key_word1, key_word2, "APB2", "TIM9", RccApb2.tim9);
    print_conditional(key_word1, key_word2, "APB2", "UART10", RccApb2.uart10);
    print_conditional(key_word1, key_word2, "APB2", "UART9", RccApb2.uart9);
    print_conditional(key_word1, key_word2, "APB2", "USART1", RccApb2.usart1);
    print_conditional(key_word1, key_word2, "APB2", "USART6", RccApb2.usart6);

    return res;
}

const char* Bus2Str(ClockBus_t bus_code) {
    char* name = "?";
    switch((uint8_t)bus_code) {
    case CLOCK_BUS_AHB1:
        name = "AHB1";
        break;
    case CLOCK_BUS_AHB2:
        name = "AHB2";
        break;
    case CLOCK_BUS_AHB3:
        name = "AHB3";
        break;
    case CLOCK_BUS_APB1:
        name = "APB1";
        break;
    case CLOCK_BUS_APB2:
        name = "APB2";
        break;
    }
    return name;
}
