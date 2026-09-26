#include "bin_adc_config.h"

#include "data_utils.h"

static volatile uint16_t GpioPortAData[BIN_ADC_SAMPLE_CNT] = {0};

const BinAdcConfig_t BinAdcConfig[] = {
    {
        .num = 1,
        .inPad = {.port = PORT_A, .pin = 1,},
        .debugPad = {.port = PORT_F, .pin = 0,},
        .sample_freq_hz = 8*9600,
        .GpioPortDataArray = GpioPortAData,
        .data_array_size = ARRAY_SIZE(GpioPortAData),
        .DmaChPad = {
             .name = "GPIO_READ",
             .dma_num = 2,
             .stream = 1,
             .priority = 1,
             .channel = 7,
        },
        .timer_num = 8,
        .on_off = true,
        .valid = true,
        .name = "BIN_ADC1",
    },
};

BinAdcHandle_t BinAdcInstance[] = {
    {
        .num = 1,
        .valid = true,
    },

};

COMPONENT_GET_CNT(BinAdc, bin_adc)


