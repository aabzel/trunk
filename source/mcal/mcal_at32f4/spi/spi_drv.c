#include "spi_drv.h"

#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "bit_utils.h"
#include "clock.h"
#include "data_utils.h"
#include "debug_info.h"
#include "gpio_drv.h"
#include "hal_diag.h"
#include "log.h"
#include "spi_config.h"
#include "at32f435_437.h"
#include "sys_config.h"
#include "time_mcal.h"
#include "utils_math.h"

static const SpiBusClock_t SpiBusClock[] = {
#ifdef HAS_SPI1
    {.num = 1, .bus_clock = 84000000},
#endif

#ifdef HAS_SPI2
    {.num = 2, .bus_clock = 42000000},
#endif

#ifdef HAS_SPI3
    {.num = 3, .bus_clock = 42000000},
#endif

#ifdef HAS_SPI4
    {.num = 4, .bus_clock = 84000000}
#endif
};

uint32_t spi_num_2_bus_clock(uint8_t num) {
    uint32_t bus_clock = 84000000;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(SpiBusClock);
    for(i = 0; i < cnt; i++) {
        if(num == SpiBusClock[i].num) {
            bus_clock = SpiBusClock[i].bus_clock;
            break;
        }
    }
    return bus_clock;
}

uint8_t spi_base_2_num(SPI_TypeDef* Instance) {
    uint8_t num = (uint8_t)0;
#ifdef HAS_SPI1
    if(SPI1 == Instance) {
        num = (uint8_t)1;
    }
#endif

#ifdef HAS_SPI2
    if(SPI2 == Instance) {
        num = (uint8_t)2;
    }
#endif

#ifdef HAS_SPI3
    if(SPI3 == Instance) {
        num = (uint8_t)3;
    }
#endif

#ifdef HAS_SPI4
    if(SPI4 == Instance) {
        num = (uint8_t)4;
    }
#endif

#ifdef HAS_SPI5
    if(SPI5 == Instance) {
        num = (uint8_t)5;
    }
#endif
    return num;
}

static SPI_TypeDef* SpiNum2Base(uint8_t num) {
    SPI_TypeDef* Instance = NULL;
    switch(num) {
#ifdef HAS_SPI1
    case 1:
        Instance = SPI1;
        break;
#endif

#ifdef HAS_SPI2
    case 2:
        Instance = SPI2;
        break;
#endif

#ifdef HAS_SPI3
    case 3:
        Instance = SPI3;
        break;
#endif

#ifdef HAS_SPI4
    case 4:
        Instance = SPI4;
        break;
#endif
#ifdef HAS_SPI5
    case 5:
        Instance = SPI5;
        break;
#endif
    default:
        Instance = NULL;
        break;
    }
    if(NULL == Instance) {
        LOG_ERROR(SPI, "%u NoInstance", num);
    }
    return Instance;
}

uint32_t Index2prescaler(uint8_t prescaler_index) {
    uint32_t prescaler = SPI_BAUDRATEPRESCALER_256;
    switch(prescaler_index) {
    case 1:
        prescaler = SPI_BAUDRATEPRESCALER_2;
        break;
    case 2:
        prescaler = SPI_BAUDRATEPRESCALER_4;
        break;
    case 3:
        prescaler = SPI_BAUDRATEPRESCALER_8;
        break;
    case 4:
        prescaler = SPI_BAUDRATEPRESCALER_16;
        break;
    case 5:
        prescaler = SPI_BAUDRATEPRESCALER_32;
        break;
    case 6:
        prescaler = SPI_BAUDRATEPRESCALER_64;
        break;
    case 7:
        prescaler = SPI_BAUDRATEPRESCALER_128;
        break;
    case 8:
        prescaler = SPI_BAUDRATEPRESCALER_256;
        break;
    default:
        prescaler = SPI_BAUDRATEPRESCALER_256;
        break;
    }
    return prescaler;
}

static uint32_t BitRate2Prescaler(int32_t bit_rate, int32_t bus_freq) {
    uint32_t prescaler = 0;
    LOG_INFO(SPI, "Des BitRate:%u bit/s", bit_rate);
    uint8_t final_prescaler_index = 8;
    int32_t cur_bit_rate = 0;
    int32_t cur_bit_rate_error = INT_MAX;
    int32_t min_abs_bit_rate_error = INT_MAX;
    uint32_t i = 0;
    for(i = 1; i <= 8; i++) {
        cur_bit_rate = bus_freq / int_pow(2, i);
        cur_bit_rate_error = abs(cur_bit_rate - bit_rate);
        if(cur_bit_rate_error < min_abs_bit_rate_error) {
            min_abs_bit_rate_error = cur_bit_rate_error;
            final_prescaler_index = i;
        }
    }
    cur_bit_rate = bus_freq / int_pow(2, final_prescaler_index);
    LOG_INFO(SPI, "Prescaler:%u", int_pow(2, final_prescaler_index));
    LOG_INFO(SPI, "RealClock:%u Hz", cur_bit_rate);
    LOG_INFO(SPI, "ClockErr:%d Hz", abs(bit_rate - cur_bit_rate));
    prescaler = Index2prescaler(final_prescaler_index);
    return prescaler;
}

static uint32_t SpiFirstBit2NrfFirstBit(BitOrder_t bit_order) {
    uint32_t mode = SPI_FIRSTBIT_MSB;
    switch((uint8_t)bit_order) {
    case SPI_MOST_SIGNIFICANT_BIT_FIRST:
        mode = SPI_FIRSTBIT_MSB;
        break;
    case SPI_LEAST_SIGNIFICANT_BIT_FIRST:
        mode = SPI_FIRSTBIT_LSB;
        break;
    }
    return mode;
};

static uint32_t SpiChipSelect2NrfChipSelect(ChipSelect_t chip_select) {
    uint32_t ss_mode = SPI_NSS_SOFT;
    switch((uint8_t)chip_select) {
    case SPI_CHIP_SEL_HW:
        LOG_INFO(SPI, "HwChipSel");
        ss_mode = SPI_NSS_HARD_OUTPUT;
        break;
    case SPI_CHIP_SEL_SW:
        LOG_INFO(SPI, "SwChipSel");
        ss_mode = SPI_NSS_SOFT;
        break;
    }
    return ss_mode;
}

bool spi_api_write(uint8_t num, const uint8_t* const tx_array, uint32_t tx_array_len) {
    bool res = false;
    log_level_t ll = log_level_get(SPI);
    if(LOG_LEVEL_DEBUG == ll) {
        print_hex_buf(tx_array, tx_array_len);
    }
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node && tx_array) {
        Node->tx_int = false;
        HAL_StatusTypeDef ret = HAL_ERROR;
        (void)ret;
        ret = HAL_SPI_Transmit_IT(&Node->handle, (uint8_t*)tx_array, tx_array_len);
        if(HAL_OK == ret) {
            LOG_PARN(SPI, "TxOk");
            res = spi_wait_tx_ll(Node);
            if(res) {
                Node->tx_byte_cnt += tx_array_len;
            }
        } else {
            LOG_ERROR(SPI, "TxErr %u %s", ret, HalStatus2Str(ret));
        }
    }
    return res;
}

bool spi_api_write_read(uint8_t num, const uint8_t* const tx_array, uint8_t* rx_array, uint32_t size) {
    bool res = false;
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node) {
        Node->txrx_int = false;
        HAL_StatusTypeDef ret = HAL_ERROR;
        ret = HAL_SPI_TransmitReceive_IT(&Node->handle, (uint8_t*)tx_array, rx_array, size);
        if(HAL_OK == ret) {
            LOG_PARN(SPI, "%u TxRxOk", num);
            res = spi_wait_txrx_ll(Node);
            if(res) {
                Node->rx_byte_cnt += size;
                Node->tx_byte_cnt += size;
            }
        } else {
            LOG_ERROR(SPI, "TxRxErr %u %s", ret, HalStatus2Str(ret));
        }
    }
    return res;
}

bool spi_api_read(uint8_t num, uint8_t* rx_array, uint32_t rx_array_len) {
    bool res = false;
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node) {
        Node->rx_int = false;
        HAL_StatusTypeDef ret = HAL_ERROR;
        ret = HAL_SPI_Receive_IT(&Node->handle, rx_array, rx_array_len);
        if(HAL_OK == ret) {
            LOG_PARN(SPI, "%u RxOk", num);
            res = spi_wait_rx_ll(Node);
            if(res) {
                Node->rx_byte_cnt += rx_array_len;
            }
        } else {
            LOG_ERROR(SPI, "RxErr %u %s", ret, HalStatus2Str(ret));
        }
    }
    return res;
}

uint32_t spi_get_clock(uint8_t num) {
    uint32_t spi_bit_rate = 0;
    /*TODO*/
    return spi_bit_rate;
}

SpiPhase_t spi_get_phase(uint8_t num) {
    SpiPhase_t phase = SPI_PHASE_UNDEF;
    /*TODO*/
    return phase;
}

SpiPolarity_t spi_get_polarity(uint8_t num) {
    SpiPolarity_t polarity = SPI_POLARITY_UNDEF;
    /*TODO*/
    return polarity;
}

uint8_t spi_get_data_size(uint8_t num) {
    uint32_t data_size = 8;
    return data_size;
}

void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle) {
#ifdef HAS_SPI1
    if(SPI1 == spiHandle->Instance) {
        __HAL_RCC_SPI1_CLK_ENABLE();
        HAL_NVIC_SetPriority(SPI1_IRQn, 7, 0);
        HAL_NVIC_EnableIRQ(SPI1_IRQn);
    }
#endif /**/

#ifdef HAS_SPI2
    if(SPI2 == spiHandle->Instance) {
        __HAL_RCC_SPI2_CLK_ENABLE();
        HAL_NVIC_SetPriority(SPI2_IRQn, 7, 0);
        HAL_NVIC_EnableIRQ(SPI2_IRQn);
    }
#endif /**/

#ifdef HAS_SPI3
    if(SPI3 == spiHandle->Instance) {
        __HAL_RCC_SPI3_CLK_ENABLE();
        HAL_NVIC_SetPriority(SPI3_IRQn, 7, 0);
        HAL_NVIC_EnableIRQ(SPI3_IRQn);
    }
#endif /**/

#ifdef HAS_SPI4
    if(SPI4 == spiHandle->Instance) {
        __HAL_RCC_SPI4_CLK_ENABLE();
        HAL_NVIC_SetPriority(SPI4_IRQn, 7, 0);
        HAL_NVIC_EnableIRQ(SPI4_IRQn);
    }
#endif /**/
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle) {
#ifdef HAS_SPI1
    if(SPI1 == spiHandle->Instance) {
        __HAL_RCC_SPI1_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(SPI1_IRQn);
    }
#endif

#ifdef HAS_SPI2
    if(SPI2 == spiHandle->Instance) {
        __HAL_RCC_SPI2_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(SPI2_IRQn);
    }
#endif

#ifdef HAS_SPI3
    if(SPI3 == spiHandle->Instance) {
        __HAL_RCC_SPI3_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(SPI3_IRQn);
    }
#endif

#ifdef HAS_SPI4
    if(SPI4 == spiHandle->Instance) {
        __HAL_RCC_SPI4_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(SPI4_IRQn);
    }
#endif
}

static uint32_t SpiPhase2Stm32Phase(SpiPhase_t phase) {
    uint32_t stm_phase = SPI_PHASE_1EDGE;
    switch((uint8_t)phase) {
    case SPI_PHASE_0:
        stm_phase = SPI_PHASE_1EDGE;
        break;
    case SPI_PHASE_1:
        stm_phase = SPI_PHASE_2EDGE;
        break;
    }
    return stm_phase;
}

uint32_t SpiPolarity2Stm32Polarity(SpiPolarity_t polarity) {
    uint32_t stm_polarity = SPI_POLARITY_LOW;
    switch((uint8_t)polarity) {
    case SPI_PHASE_0:
        stm_polarity = SPI_POLARITY_LOW;
        break;
    case SPI_PHASE_1:
        stm_polarity = SPI_POLARITY_HIGH;
        break;
    }
    return stm_polarity;
}

bool spi_init_one(uint8_t num) {
    bool res = false;
    const SpiConfig_t* Config = SpiGetConfig(num);
    if(Config) {
        uint32_t bus_clock = spi_num_2_bus_clock(num);
        LOG_WARNING(SPI, "%u BusClock: %u Hz", num, bus_clock);
        SpiHandle_t* Node = SpiGetNode(num);
        if(Node) {
            uint32_t stm_prescaler = BitRate2Prescaler(Config->bit_rate_hz, bus_clock);
            SPI_TypeDef* SpiInstance = SpiNum2Base(num);
            if(SpiInstance) {
                Node->handle.Instance = SpiInstance;
                Node->handle.Init.Mode = SPI_MODE_MASTER;
                Node->handle.Init.Direction = SPI_DIRECTION_2LINES;
                Node->handle.Init.DataSize = SPI_DATASIZE_8BIT;
                Node->handle.Init.CLKPolarity = SpiPolarity2Stm32Polarity(Config->polarity);
                Node->handle.Init.CLKPhase = SpiPhase2Stm32Phase(Config->phase);
                Node->handle.Init.NSS = SpiChipSelect2NrfChipSelect(Config->chip_select);
                Node->handle.Init.BaudRatePrescaler = stm_prescaler;
                Node->handle.Init.FirstBit = SpiFirstBit2NrfFirstBit(Config->bit_order);
                Node->handle.Init.TIMode = SPI_TIMODE_DISABLE;
                Node->handle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
                Node->handle.Init.CRCPolynomial = 10;
                HAL_StatusTypeDef ret = HAL_SPI_Init(&Node->handle);
                if(HAL_OK == ret) {
                    res = true;
                    Node->init_done = true;
                    LOG_INFO(SPI, "%u InitOk", num);
                } else {
                    res = false;
                    LOG_ERROR(SPI, "%u InitErr %s", num, HalStatus2Str(ret));
                }
            } else {
                LOG_ERROR(SPI, "%u InstErr", num);
            }
        } else {
            LOG_ERROR(SPI, "%u NodeErr", num);
        }
    } else {
        LOG_DEBUG(SPI, "%u ConfErr", num);
    }
    return res;
}
