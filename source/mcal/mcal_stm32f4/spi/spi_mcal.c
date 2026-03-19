#include "spi_mcal.h"

#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "array_diag.h"
#include "bit_utils.h"
#include "clock.h"
#include "data_utils.h"
#include "debug_info.h"
#include "gpio_mcal.h"
#include "hal_diag.h"
#include "log.h"
#include "stm32f4xx_hal.h"
#include "sys_config.h"
#include "time_mcal.h"
#include "utils_math.h"


static const SpiClockTimingInfo_t SpiClockTimingInfo[] = {
   { .polarity=SPI_POLARITY_LATCH_RISING,  .phase = SPI_CLK_IDLE_LEVEL_1,  .clk_polarity=SPI_POLARITY_HIGH,  .clk_phase=SPI_PHASE_2EDGE, .valid=true, },
   { .polarity=SPI_POLARITY_LATCH_FALING,  .phase = SPI_CLK_IDLE_LEVEL_0,  .clk_polarity=SPI_POLARITY_LOW,  .clk_phase=SPI_PHASE_2EDGE, .valid=true, },
   { .polarity=SPI_POLARITY_LATCH_FALING,  .phase = SPI_CLK_IDLE_LEVEL_1,  .clk_polarity=SPI_POLARITY_HIGH,  .clk_phase=SPI_PHASE_1EDGE, .valid=true,   },
   { .polarity=SPI_POLARITY_LATCH_RISING,  .phase = SPI_CLK_IDLE_LEVEL_0,  .clk_polarity=SPI_POLARITY_LOW, .clk_phase=SPI_PHASE_1EDGE,    .valid=true,    },
};


static uint32_t SpiDirectionToStmDirection(const SpiDirection_t direction){
    uint32_t direction_code = 0;
    switch(direction) {
        case SPI_DIRECTION_1WIRE:  direction_code=SPI_DIRECTION_1LINE; break;
        case SPI_DIRECTION_2WIRES: direction_code=SPI_DIRECTION_2LINES; break;
        case SPI_DIRECTION_1WIRE_RX_ONLY: direction_code=SPI_DIRECTION_2LINES_RXONLY; break;
        default : direction_code = 0; break;
    }
    return direction_code;
}

static const SpiInfo_t SpiInfo[]={
#ifdef SPI1
        {.num = 1,
         .irq_n = SPI1_IRQn,
         .SPIx = SPI1,
         .clock_bus = CLOCK_BUS_APB2,
         .valid = true, },
#endif

#ifdef SPI2
        {.num = 2,
         .irq_n = SPI2_IRQn,
         .SPIx = SPI2,
         .clock_bus = CLOCK_BUS_APB1,
         .valid = true, },
#endif

#ifdef SPI3
        {.num = 3,
         .irq_n = SPI3_IRQn,
         .SPIx = SPI3,
         .clock_bus = CLOCK_BUS_APB1,
         .valid = true, },
#endif
};

const SpiInfo_t* SpiGetInfo(const uint8_t num) {
    SpiInfo_t* Info = NULL;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(SpiInfo);
    for(i=0;i<cnt;i++) {
        if(num==SpiInfo[i].num) {
            Info = &SpiInfo[i];
            break;
        }
    }
    return Info;
}

uint32_t spi_num_to_bus_clock(const uint8_t num) {
    uint32_t bus_clock = 84000000;
    const SpiInfo_t* Info = SpiGetInfo(num);
    if(Info) {
        bus_clock= clock_freq_get(Info->clock_bus);
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


SPI_TypeDef* SpiNum2Base(const uint8_t num) {
    SPI_TypeDef* SPIx=NULL;
    const SpiInfo_t* Info=SpiGetInfo( num);
    if(Info){
        SPIx=Info->SPIx;
    }
    return SPIx;
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

static uint32_t SpiFirstBitToStmFirstBit(const IfBitOrder_t bit_order) {
    uint32_t mode = SPI_FIRSTBIT_MSB;
    switch(bit_order) {
    case BIT_ORDER_MSB:
        mode = SPI_FIRSTBIT_MSB;
        break;
    case BIT_ORDER_LSB:
        mode = SPI_FIRSTBIT_LSB;
        break;
    default: break;
    }
    return mode;
}

static uint32_t SpiChipSelectToStmChipSelect(ChipSelect_t chip_select) {
    uint32_t ss_mode = SPI_NSS_SOFT;
    switch(chip_select) {
    case SPI_CHIP_SEL_HW:
        LOG_INFO(SPI, "HwChipSel");
        ss_mode = SPI_NSS_HARD_OUTPUT;
        break;
    case SPI_CHIP_SEL_SW:
        LOG_INFO(SPI, "SwChipSel");
        ss_mode = SPI_NSS_SOFT;
        break;
    default: break;
    }
    return ss_mode;
}

bool spi_mcal_write(uint8_t num, const uint8_t* const tx_array, uint32_t tx_array_len) {
    bool res = false;
    LOG_DEBUG(SPI, "Write:%s", ArrayToStr(tx_array,tx_array_len));
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node && tx_array) {
        Node->tx_done = false;
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
            LOG_ERROR(SPI, "TxErr %u %s", ret, HalStatusToStr(ret));
        }
    }
    return res;
}

bool spi_mcal_write_read(uint8_t num, const uint8_t* const tx_array, uint8_t* rx_array, uint32_t size) {
    bool res = false;
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node) {
        Node->txrx_done = false;
        Node->it_done = false;
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
            LOG_ERROR(SPI, "TxRxErr %u %s", ret, HalStatusToStr(ret));
        }
    }
    return res;
}

bool spi_mcal_read(uint8_t num, uint8_t* rx_array, uint32_t rx_array_len) {
    bool res = false;
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node) {
        Node->rx_done = false;
        HAL_StatusTypeDef ret = HAL_ERROR;
        ret = HAL_SPI_Receive_IT(&Node->handle, rx_array, rx_array_len);
        if(HAL_OK == ret) {
            LOG_PARN(SPI, "%u RxOk", num);
            res = spi_wait_rx_ll(Node);
            if(res) {
                Node->rx_byte_cnt += rx_array_len;
            }
        } else {
            LOG_ERROR(SPI, "RxErr %u %s", ret, HalStatusToStr(ret));
        }
    }
    return res;
}

uint32_t spi_get_clock(uint8_t num) {
    uint32_t spi_bit_rate = 0;
    /*TODO*/
    return spi_bit_rate;
}

SpiClkIdleLevel_t spi_get_phase(uint8_t num) {
    SpiClkIdleLevel_t phase = SPI_CLK_IDLE_LEVEL_UNDEF;
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


static SpiClockTimingInfo_t* SpiConfigToClockTimingInfo(const SpiConfig_t* const Config) {
    SpiClockTimingInfo_t* TimingInfo = NULL;
    uint32_t i = 0;
    for(i=0;i<4;i++) {
        if(Config->phase==SpiClockTimingInfo[i].phase) {
            if(Config->polarity==SpiClockTimingInfo[i].polarity) {
                TimingInfo = &SpiClockTimingInfo[i];
                break;
            }
        }
    }

    return TimingInfo;
}

static uint32_t SpiPhaseToStm32Phase(const SpiConfig_t* const Config) {
    uint32_t clk_phase = SPI_PHASE_1EDGE;
    SpiClockTimingInfo_t* TimingInfo = SpiConfigToClockTimingInfo(Config) ;
    if(TimingInfo){
        clk_phase = TimingInfo->clk_phase;
    }
    return clk_phase;
}

/*see Figure 194. Data clock timing diagram*/
uint32_t SpiPolarityToStm32Polarity(const SpiConfig_t* const Config) {
    uint32_t clk_polarity = SPI_POLARITY_LOW;
    SpiClockTimingInfo_t* TimingInfo = SpiConfigToClockTimingInfo(Config) ;
    if(TimingInfo){
        clk_polarity = TimingInfo->clk_polarity;
    }
    return clk_polarity;
}


bool spi_init_one(uint8_t num) {
    bool res = false;
    const SpiConfig_t* Config = SpiGetConfig(num);
    if(Config) {
        LOG_WARNING(SPI, "%s", SpiConfigToStr(Config));
        uint32_t bus_clock = spi_num_to_bus_clock(num);
        LOG_INFO(SPI, "SPI%u BusClock: %u Hz", num, bus_clock);
        uint32_t stm_prescaler = BitRate2Prescaler(Config->bit_rate_hz, bus_clock);
        SpiHandle_t* Node = SpiGetNode(num);
        if(Node) {
            SpiInfo_t* Info = SpiGetInfo(num);
            if(Info) {
                Node->SPIx = Info->SPIx;
                Node->handle.Instance = Info->SPIx;
                Node->handle.Init.Mode = SPI_MODE_MASTER;
                Node->handle.Init.CLKPolarity = SpiPolarityToStm32Polarity(Config);
                Node->handle.Init.CLKPhase = SpiPhaseToStm32Phase(Config);

                Node->handle.Init.BaudRatePrescaler = stm_prescaler;
                Node->handle.Init.DataSize = SPI_DATASIZE_8BIT;
                Node->handle.Init.Direction =  SpiDirectionToStmDirection(Config->direction);
                Node->handle.Init.NSS = SpiChipSelectToStmChipSelect(Config->chip_select);
                Node->handle.Init.FirstBit = SpiFirstBitToStmFirstBit(Config->bit_order);
                Node->handle.Init.TIMode = SPI_TIMODE_DISABLE;
                Node->handle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
                Node->handle.Init.CRCPolynomial = 10;
                HAL_StatusTypeDef ret = HAL_SPI_Init(&Node->handle);
                if(HAL_OK == ret) {
                    res = true;
                    Node->init = true;
                    LOG_INFO(SPI, "SPI%u,Init,Ok", num);
                } else {
                    LOG_ERROR(SPI, "SPI%u InitErr %s", num, HalStatusToStr(ret));
                    res = false;
                }
            }else {
                LOG_ERROR(SPI, "SPI%u Info,Err", num);
            }
        } else {
            LOG_ERROR(SPI, "SPI%u NodeErr", num);
        }
    } else {
        LOG_DEBUG(SPI, "SPI%u ConfErr", num);
    }
    return res;
}
