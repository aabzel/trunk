#include "spi_mcal.h"

#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "array_diag.h"
#include "bit_utils.h"
#include "clock_mcal.h"
#include "data_utils.h"
#include "debug_info.h"
#include "gpio_mcal.h"
#include "hal_diag.h"
#include "hal_mcal.h"
#include "interrupt_mcal.h"
#include "log.h"
#include "spi_custom_diag.h"
#include "stm32fx_hal.h"
#include "sys_config.h"
#include "time_mcal.h"
#include "utils_math.h"
#include "spi_dma.h"

static const SpiClockTimingInfo_t SpiClockTimingInfo[] = {
    {
        .polarity = SPI_POLARITY_LATCH_RISING,
        .phase = SPI_CLK_IDLE_LEVEL_1,
        .clk_polarity = SPI_POLARITY_HIGH,
        .clk_phase = SPI_PHASE_2EDGE,
        .valid = true,
    },
    {
        .polarity = SPI_POLARITY_LATCH_FALING,
        .phase = SPI_CLK_IDLE_LEVEL_0,
        .clk_polarity = SPI_POLARITY_LOW,
        .clk_phase = SPI_PHASE_2EDGE,
        .valid = true,
    },
    {
        .polarity = SPI_POLARITY_LATCH_FALING,
        .phase = SPI_CLK_IDLE_LEVEL_1,
        .clk_polarity = SPI_POLARITY_HIGH,
        .clk_phase = SPI_PHASE_1EDGE,
        .valid = true,
    },
    {
        .polarity = SPI_POLARITY_LATCH_RISING,
        .phase = SPI_CLK_IDLE_LEVEL_0,
        .clk_polarity = SPI_POLARITY_LOW,
        .clk_phase = SPI_PHASE_1EDGE,
        .valid = true,
    },
};

static uint32_t SpiDirectionToStmDirection(const SpiDirection_t direction) {
    uint32_t direction_code = 0;
    switch(direction) {
    case SPI_DIRECTION_1WIRE:
        direction_code = SPI_DIRECTION_1LINE;
        break;
    case SPI_DIRECTION_2WIRES:
        direction_code = SPI_DIRECTION_2LINES;
        break;
    case SPI_DIRECTION_1WIRE_RX_ONLY:
        direction_code = SPI_DIRECTION_2LINES_RXONLY;
        break;
    default:
        direction_code = 0;
        break;
    }
    return direction_code;
}

static uint32_t SpiToDataSizeStmDataSize(const uint8_t frame_size) {
    /*!< Specifies the SPI data size.
     This parameter can be a value of @ref SPI_Data_Size */
    uint32_t DataSize = 0;
    switch(frame_size) {
    case 8:
        DataSize = SPI_DATASIZE_8BIT;
        break;
    case 16:
        DataSize = SPI_DATASIZE_16BIT;
        break;
    default:
        DataSize = 0;
        break;
    }
    return DataSize;
}

static const SpiInfo_t SpiInfo[] = {
#ifdef SPI1
    {
        .num = 1,
        .irq_n = SPI1_IRQn,
        .SPIx = SPI1,
        .clock_bus = CLOCK_BUS_APB2,
        .valid = true,
    },
#endif

#ifdef SPI2
    {
        .num = 2,
        .irq_n = SPI2_IRQn,
        .SPIx = SPI2,
        .clock_bus = CLOCK_BUS_APB1,
        .valid = true,
    },
#endif

#ifdef SPI3
    {
        .num = 3,
        .irq_n = SPI3_IRQn,
        .SPIx = SPI3,
        .clock_bus = CLOCK_BUS_APB1,
        .valid = true,
    },
#endif

#ifdef SPI4
    {
        .num = 4,
        .irq_n = SPI4_IRQn,
        .SPIx = SPI4,
        .clock_bus = CLOCK_BUS_APB1,
        .valid = true,
    },
#endif

#ifdef SPI5
    {
        .num = 5,
        .irq_n = SPI5_IRQn,
        .SPIx = SPI5,
        .clock_bus = CLOCK_BUS_APB1,
        .valid = true,
    },
#endif
};

const SpiInfo_t* SpiGetInfo(const uint8_t num) {
    SpiInfo_t* Info = NULL;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(SpiInfo);
    for(i = 0; i < cnt; i++) {
        if(num == SpiInfo[i].num) {
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
        bus_clock = clock_freq_get(Info->clock_bus);
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
    SPI_TypeDef* SPIx = NULL;
    const SpiInfo_t* Info = SpiGetInfo(num);
    if(Info) {
        SPIx = Info->SPIx;
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
    default:
        break;
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
    default:
        break;
    }
    return ss_mode;
}

bool spi_mcal_write_it(uint8_t num, const uint8_t* const tx_array, const uint32_t size) {
    bool res = false;
    LOG_DEBUG(SPI, "SPI%u,Write,Size:%u,Data:[%s]", num, size, ArrayToStr(tx_array, size));
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node && tx_array) {
        Node->tx_done = false;
        HAL_StatusTypeDef ret = HAL_ERROR;
        ret = HAL_SPI_Transmit_IT(&Node->handle, (uint8_t*) tx_array, size);
        res = HAL_retToRes(ret);
        if(res) {
            LOG_PARN(SPI, "TxOk");
            res = spi_wait_tx_ll(Node);
            if(res) {
                Node->tx_cnt += size;
            }
        } else {
            LOG_ERROR(SPI, "SPI%u,TxErr:%u=%s", num, ret, HalStatusToStr(ret));
        }
    }
    return res;
}

#if 0
bool spi_mcal_write(uint8_t num, const uint8_t* const tx_array, uint32_t size) {
    bool res = false;
    res = spi_mcal_write_it(num, tx_array, size);
    return res;
}
#endif

#if 0
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
                Node->rx_cnt += size;
                Node->tx_cnt += size;
            }
        } else {
            LOG_ERROR(SPI, "TxRxErr %u %s", ret, HalStatusToStr(ret));
        }
    }
    return res;
}
#endif

bool spi_mcal_read_one_it_ll(SpiHandle_t* Node, uint8_t* rx_array) {
    bool res = false;
    Node->rx_done = false;
    HAL_StatusTypeDef ret = HAL_ERROR;
    // ret = HAL_SPI_Abort_IT(&Node->handle);
    ret = HAL_SPI_Receive_IT(&Node->handle, rx_array, 1);
    if (HAL_OK == ret) {
        LOG_PARN(SPI, "%u RxOk", Node->num);
        res = spi_wait_rx_ll(Node);
        if (res) {
            Node->rx_cnt += 1;
        }
    } else {
        LOG_ERROR(SPI, "RxErr %u %s", ret, HalStatusToStr(ret));
    }

    return res;
}

bool spi_mcal_read_it(uint8_t num, uint8_t* rx_array, uint32_t size) {
    bool res = false;
    SpiHandle_t* Node = SpiGetNode(num);
    if (Node) {
        uint32_t i = 0;
        for (i = 0; i < size; i++) {
            res = spi_mcal_read_one_it_ll(Node, &rx_array[i]);
        }
    }
    return res;
}

#if 0
bool spi_mcal_read(uint8_t num, uint8_t* rx_array, uint32_t size) {
    bool res = false;
    res = spi_read_safe(num, rx_array, size);
    //res = spi_mcal_read_it(num, rx_array, size) ;
    return res;
}
#endif

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
       // HAL_NVIC_SetPriority(SPI1_IRQn, 7, 0);
       // HAL_NVIC_EnableIRQ(SPI1_IRQn);
    }
#endif /**/

#ifdef HAS_SPI2
    if(SPI2 == spiHandle->Instance) {
        __HAL_RCC_SPI2_CLK_ENABLE();
        //HAL_NVIC_SetPriority(SPI2_IRQn, 7, 0);
        //HAL_NVIC_EnableIRQ(SPI2_IRQn);
    }
#endif /**/

#ifdef HAS_SPI3
    if(SPI3 == spiHandle->Instance) {
        __HAL_RCC_SPI3_CLK_ENABLE();
        //HAL_NVIC_SetPriority(SPI3_IRQn, 7, 0);
        //HAL_NVIC_EnableIRQ(SPI3_IRQn);
    }
#endif /**/

#ifdef HAS_SPI4
    if(SPI4 == spiHandle->Instance) {
        __HAL_RCC_SPI4_CLK_ENABLE();
       // HAL_NVIC_SetPriority(SPI4_IRQn, 7, 0);
       // HAL_NVIC_EnableIRQ(SPI4_IRQn);
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
    for(i = 0; i < 4; i++) {
        if(Config->phase == SpiClockTimingInfo[i].phase) {
            if(Config->polarity == SpiClockTimingInfo[i].polarity) {
                TimingInfo = &SpiClockTimingInfo[i];
                break;
            }
        }
    }

    return TimingInfo;
}

static uint32_t SpiPhaseToStm32Phase(const SpiConfig_t* const Config) {
    uint32_t clk_phase = SPI_PHASE_1EDGE;
    SpiClockTimingInfo_t* TimingInfo = SpiConfigToClockTimingInfo(Config);
    if(TimingInfo) {
        clk_phase = TimingInfo->clk_phase;
    }
    return clk_phase;
}

/*see Figure 194. Data clock timing diagram*/
uint32_t SpiPolarityToStm32Polarity(const SpiConfig_t* const Config) {
    uint32_t clk_polarity = SPI_POLARITY_LOW;
    SpiClockTimingInfo_t* TimingInfo = SpiConfigToClockTimingInfo(Config);
    if(TimingInfo) {
        clk_polarity = TimingInfo->clk_polarity;
    }
    return clk_polarity;
}

static bool spi_init_hal_one(const SpiConfig_t* const Config, SPI_InitTypeDef* const pInit) {
    bool res = false;
    if(Config) {
        if(pInit) {
            uint32_t bus_clock = spi_num_to_bus_clock(Config->num);
            LOG_INFO(SPI, "SPI%u,BusClock:%u Hz", Config->num, bus_clock);
            uint32_t stm_prescaler = BitRate2Prescaler(Config->bit_rate_hz, bus_clock);
            pInit->BaudRatePrescaler = stm_prescaler;
            pInit->CLKPolarity = SpiPolarityToStm32Polarity(Config);
            pInit->CLKPhase = SpiPhaseToStm32Phase(Config);
            pInit->DataSize = SpiToDataSizeStmDataSize(Config->frame_size);
            pInit->Direction = SpiDirectionToStmDirection(Config->direction);
            pInit->FirstBit = SpiFirstBitToStmFirstBit(Config->bit_order);
            pInit->Mode = SPI_MODE_MASTER;
            pInit->NSS = SpiChipSelectToStmChipSelect(Config->chip_select);
            pInit->TIMode = SPI_TIMODE_DISABLE;
            pInit->CRCCalculation = SPI_CRCCALCULATION_DISABLE;
            pInit->CRCPolynomial = 10;
            res = true;
        }
    }
    return res;
}

bool spi_interrupt_ctrl(uint8_t num, bool enable) {
    bool res = false;
    const SpiInfo_t* Info = SpiGetInfo(num);
    if(Info){
        res = interrupt_control(Info->irq_n, enable);
    }
    return res;
}

bool spi_interrupt_priority_set(uint8_t num, uint8_t irq_priority) {
    bool res = false;
    const SpiInfo_t *Info = SpiGetInfo(num);
    if (Info) {
        res = interrupt_set_priority(Info->irq_n, irq_priority);
    }
    return res;
}

bool spi_proc_status(SpiHandle_t* const Node, const  SpiStm32RegStatus_t * const Status){
    bool res = true;
    if(Status->FRE) {
        LOG_ERROR(SPI,"SPI%u,Err,FrameEormat",Node->num);
        Node->error_cnt++;
    }

    if(Status->OVR) {
        LOG_ERROR(SPI,"SPI%u,Err,Overrun",Node->num);
        Node->error_cnt++;
    }

    if(Status->CRCERR) {
        LOG_ERROR(SPI,"SPI%u,Err,CRC",Node->num);
        Node->error_cnt++;
    }

    if(Status->UDR) {
        LOG_ERROR(SPI,"SPI%u,Err,Underrun",Node->num);
        Node->error_cnt++;
    }

    return res;
}


bool spi_proc_one(uint8_t i) {
    bool res = false;
    LOG_PARN(SPI, "Proc %u", i);
    SpiHandle_t* Node = SpiGetNode(i);
    if(Node) {
        uint32_t error = HAL_SPI_GetError(&Node->handle);
        if(error){
            LOG_ERROR(SPI, "SPI%u,Err 0x%x=%s", i, error,SpiErrToStr(error));
        }
        SpiStm32RegStatus_t Status;
        Status.dword=Node->SPIx->SR;//SPI status register
        res = spi_proc_status(Node,&Status);

        Node->spin++;
    }
    return res;
}

static bool spi_interrupt_init(const SpiConfig_t* Config){
    bool res = false;
    res = spi_interrupt_ctrl(Config->num, Config->interrupt_on);
    log_info_res(SPI, res, "IntInit");

    res = spi_interrupt_priority_set(Config->num, Config->irq_priority);
    log_info_res(SPI, res, "IntPrio");
    return res;
}

bool spi_init_one(uint8_t num) {
    bool res = false;
    const SpiConfig_t* Config = SpiGetConfig(num);
    res = SpiIsValidConfig(Config);
    if(res) {
        LOG_WARNING(SPI, "%s", SpiConfigToStr(Config));
        SpiHandle_t* Node = SpiGetNode(num);
        if(Node) {
            res = spi_init_common(Config, Node);
            SpiInfo_t* Info = SpiGetInfo(num);
            if(Info) {
                Node->SPIx = Info->SPIx;
                Node->handle.Instance = Info->SPIx;
                res = spi_init_hal_one(Config, &Node->handle.Init);
                HAL_StatusTypeDef ret = HAL_SPI_Init(&Node->handle);
                if(HAL_OK == ret) {
#ifdef HAS_SPI_DMA
                    res = spi_dma_init(num);
                    log_info_res(SPI, res, "DmaInit");
#endif
                    SET_BIT(Node->handle.Instance->CR2, SPI_CR2_ERRIE);
                    res = spi_interrupt_init(Config);
                    log_info_res(SPI, res, "IntInit");

                    Node->init = true;
                    LOG_INFO(SPI, "SPI%u,Init,Ok", num);
                    res = true;
                    __HAL_SPI_ENABLE(&Node->handle);
                } else {
                    LOG_ERROR(SPI, "SPI%u,InitErr %s", num, HalStatusToStr(ret));
                    res = false;
                }
            } else {
                LOG_ERROR(SPI, "SPI%u,Info,Err", num);
            }
        } else {
            LOG_ERROR(SPI, "SPI%u,NodeErr", num);
        }
    } else {
        LOG_DEBUG(SPI, "SPI%u,ConfErr", num);
    }
    return res;
}
