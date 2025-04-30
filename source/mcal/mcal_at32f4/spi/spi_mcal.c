#include "spi_mcal.h"

#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "bit_utils.h"
#include "clock.h"
#include "code_generator.h"
#include "data_utils.h"
#include "debug_info.h"
#include "gpio_mcal.h"
#include "hal_diag.h"
#include "log.h"
#include "microcontroller_const.h"
#include "spi_custom_drv.h"
#include "time_mcal.h"
#include "utils_math.h"

static const SpiDivider_t SpiDivider[] = {
    {
        .valid = true,
        .code = SPI_MCLK_DIV_2,
        .divider = 2,
    },
    {
        .valid = true,
        .code = SPI_MCLK_DIV_3,
        .divider = 3,
    },
    {
        .valid = true,
        .code = SPI_MCLK_DIV_4,
        .divider = 4,
    },
    {
        .valid = true,
        .code = SPI_MCLK_DIV_8,
        .divider = 8,
    },
    {
        .valid = true,
        .code = SPI_MCLK_DIV_16,
        .divider = 16,
    },
    {
        .valid = true,
        .code = SPI_MCLK_DIV_32,
        .divider = 32,
    },
    {
        .valid = true,
        .code = SPI_MCLK_DIV_64,
        .divider = 64,
    },
    {
        .valid = true,
        .code = SPI_MCLK_DIV_128,
        .divider = 128,
    },
    {
        .valid = true,
        .code = SPI_MCLK_DIV_256,
        .divider = 256,
    },
    {
        .valid = true,
        .code = SPI_MCLK_DIV_512,
        .divider = 512,
    },
    {
        .valid = true,
        .code = SPI_MCLK_DIV_1024,
        .divider = 1024,
    },
};

static const SpiInfo_t SpiInfo[] = {
#ifdef HAS_SPI1
    {
        .num = 1,
        .SPIx = SPI1,
        .clock_bus = CLOCK_BUS_APB2,
        .clock_type = CRM_SPI1_PERIPH_CLOCK,
        .irq_n = SPI1_IRQn,
        .valid = true,
    },
#endif

#ifdef HAS_SPI2
    {
        .num = 2,
        .SPIx = SPI2,
        .clock_bus = CLOCK_BUS_APB1,
        .clock_type = CRM_SPI2_PERIPH_CLOCK,
        .irq_n = SPI2_I2S2EXT_IRQn,
        .valid = true,
    },
#endif

#ifdef HAS_SPI3
    {
        .num = 3,
        .SPIx = SPI3,
        .clock_bus = CLOCK_BUS_APB1,
        .clock_type = CRM_SPI3_PERIPH_CLOCK,
        .irq_n = SPI3_I2S3EXT_IRQn,
        .valid = true,
    },
#endif

#ifdef HAS_SPI4
    {
        .num = 4,
        .SPIx = SPI4,
        .clock_bus = CLOCK_BUS_APB2,
        .clock_type = CRM_SPI4_PERIPH_CLOCK,
        .irq_n = SPI4_IRQn,
        .valid = true,
    },
#endif
};

COMPONENT_GET_INFO(Spi)
#if 0
const SpiInfo_t* SpiGetInfo(uint8_t num) {
    SpiInfo_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(SpiInfo);
    for(i = 0; i < cnt; i++) {
        if(num == SpiInfo[i].num) {
            if(SpiInfo[i].valid) {
                Node = &SpiInfo[i];
                break;
            }
        }
    }
    return Node;
}
#endif

static spi_first_bit_type SpiBitOrgerToArteryBo(BitOrder_t bit_order) {
    spi_first_bit_type first_bit = SPI_MODE_MASTER;

    switch((uint32_t)bit_order) {
    case SPI_MOST_SIGNIFICANT_BIT_FIRST: {
        /* the frame format is msb first */
        first_bit = SPI_FIRST_BIT_MSB;
    } break;

    case SPI_LEAST_SIGNIFICANT_BIT_FIRST: {
        /* the frame format is lsb first */
        first_bit = SPI_FIRST_BIT_LSB;
    } break;
    }

    return first_bit;
}

static i2s_operation_mode_type SpiTxModeToArteryOperation(SpiOperationMode_t op_mode) {
    i2s_operation_mode_type operation_mode = I2S_MODE_MASTER_TX;
    switch((uint32_t)op_mode) {
    case SPI_OP_MODE_SLAVE_TX: {
        operation_mode = I2S_MODE_SLAVE_TX;
    } break;

    case SPI_OP_MODE_SLAVE_RX: {
        operation_mode = I2S_MODE_SLAVE_RX;
    } break;

    case SPI_OP_MODE_MASTER_TX: {
        operation_mode = I2S_MODE_MASTER_TX;
    } break;

    case SPI_OP_MODE_MASTER_RX: {
        operation_mode = I2S_MODE_MASTER_RX;
    } break;
    }

    return operation_mode;
}

static spi_transmission_mode_type SpiTxModeToArteryTm(SpiTxMode_t tx_mode) {
    spi_transmission_mode_type transmission_mode = SPI_TX_FULL_DUPLEX;
    switch((uint32_t)tx_mode) {
    case SPI_TX_FULL_DUPLEX: {
        /* dual line unidirectional full-duplex mode(slben = 0 and ora = 0) */
        transmission_mode = SPI_TRANSMIT_FULL_DUPLEX;
    } break;
    case SPI_TX_SIMPLEX_RX: {
        /* dual line unidirectional simplex receive-only mode(slben = 0 and ora = 1) */
        transmission_mode = SPI_TRANSMIT_SIMPLEX_RX;
    } break;
    case SPI_TX_HALF_DUPLEX_RX: {
        /* single line bidirectional half duplex mode-receiving(slben = 1 and slbtd = 0) */
        transmission_mode = SPI_TRANSMIT_HALF_DUPLEX_RX;
    } break;
    case SPI_TX_HALF_DUPLEX_TX: {
        /* single line bidirectional half duplex mode-transmitting(slben = 1 and slbtd = 1) */
        transmission_mode = SPI_TRANSMIT_HALF_DUPLEX_TX;
    } break;
    }

    return transmission_mode;
}

// SpiAtChipSelCtrl_t
static spi_cs_mode_type SpiChipSelectToArterySc(ChipSelect_t chip_select) {
    spi_cs_mode_type cs_mode = SPI_CS_SOFTWARE_MODE;
    switch((uint32_t)chip_select) {
    case SPI_CHIP_SEL_HW:
        cs_mode = SPI_CS_HARDWARE_MODE;
        break;
    case SPI_CHIP_SEL_SW:
        cs_mode = SPI_CS_SOFTWARE_MODE;
        break;
    }
    return cs_mode;
}

static spi_clock_phase_type SpiClockPhaseToArteryCf(SpiPhase_t phase) {
    spi_clock_phase_type clock_phase = SPI_CS_SOFTWARE_MODE;
    switch((uint32_t)phase) {
    case SPI_PHASE_0: {
        /* data capture start from the first clock edge */
        clock_phase = SPI_CLOCK_PHASE_1EDGE;
    } break;
    case SPI_PHASE_1: {
        /* data capture start from the second clock edge */
        clock_phase = SPI_CLOCK_PHASE_2EDGE;
    } break;
    }
    return clock_phase;
}

static spi_master_slave_mode_type SpiBusRoleToArteryBr(IfBusRole_t bus_role) {
    spi_master_slave_mode_type master_slave_mode = SPI_MODE_MASTER;

    switch((uint32_t)bus_role) {
    case IF_BUS_ROLE_MASTER: {
        master_slave_mode = SPI_MODE_MASTER;
    } break;
    case IF_BUS_ROLE_SLAVE: {
        master_slave_mode = SPI_MODE_SLAVE;
    } break;
    }

    return master_slave_mode;
}

static spi_frame_bit_num_type SpiFrameSizeToArteryFs(uint8_t frame_size) {
    spi_frame_bit_num_type frame_bit_num = SPI_FRAME_8BIT;
    switch((uint32_t)frame_size) {
    case 8: {
        frame_bit_num = SPI_FRAME_8BIT;
    } break;
    case 16: {
        frame_bit_num = SPI_FRAME_16BIT;
    } break;
    }
    return frame_bit_num;
}

int32_t spi_bus_clock_get(uint8_t num) {
    int32_t clock_hz = -1;
    SpiInfo_t* Info = SpiGetInfo(num);
    if(Info) {
        crm_clocks_freq_type clocks_struct = {0};
        crm_clocks_freq_get(&clocks_struct);
        switch((ClockBus_t)Info->clock_bus) {
        case CLOCK_BUS_APB1:
            clock_hz = (int32_t)(clocks_struct.apb1_freq);
            break;
        case CLOCK_BUS_APB2:
            clock_hz = (int32_t)(clocks_struct.apb2_freq);
            break; /* apb2 bus clock frequency */
        default:
            break;
        }
    }
    LOG_PARN(SPI, "SPI%u BusClck:%u Hz", num, clock_hz);
    return clock_hz;
}

static int32_t SpiArteryDeividerToDeivider(SpiAtMasterClkFreqDiv_t artery_mdiv) {
    int32_t real_divider = 0;
    switch((uint32_t)artery_mdiv) {
    case SPI_AT32_MASTER_CLK_DIVIDER_2:
        real_divider = 2;
        break; // Divided by 2
    case SPI_AT32_MASTER_CLK_DIVIDER_4:
        real_divider = 4;
        break; // Divided by 4
    case SPI_AT32_MASTER_CLK_DIVIDER_8:
        real_divider = 8;
        break; // Divided by 8
    case SPI_AT32_MASTER_CLK_DIVIDER_16:
        real_divider = 16;
        break; // Divided by 16
    case SPI_AT32_MASTER_CLK_DIVIDER_32:
        real_divider = 32;
        break; // Divided by 32
    case SPI_AT32_MASTER_CLK_DIVIDER_64:
        real_divider = 64;
        break; // Divided by 64
    case SPI_AT32_MASTER_CLK_DIVIDER_128:
        real_divider = 128;
        break; // Divided by 128
    case SPI_AT32_MASTER_CLK_DIVIDER_256:
        real_divider = 256;
        break; // Divided by 256
    case SPI_AT32_MASTER_CLK_DIVIDER_512:
        real_divider = 512;
        break; // Divided by 512
    case SPI_AT32_MASTER_CLK_DIVIDER_1024:
        real_divider = 1024;
        break; // Divided by 1024
    }
    return real_divider;
}

static uint8_t SpiArteryFrameSizeToLogicFrameSize(SpiAtFrameSize_t artery_fbn) {
    uint8_t frame_size = 0;
    switch((uint32_t)artery_fbn) {
    case SPI_AT32_FRAME_SIZE_8_BIT:
        frame_size = 8;
        break;
    case SPI_AT32_FRAME_SIZE_16_BIT:
        frame_size = 16;
        break;
    }
    return frame_size;
}

static SpiPhase_t SpiArteryPhaseToPhase(SpiAtClockPhase_t artery_clkpha) {
    SpiPhase_t real_phase = 0;
    switch((uint32_t)artery_clkpha) {
    case SPI_AT32_CLOCK_PHASE_1ST:
        real_phase = SPI_PHASE_0;
        break;
    case SPI_AT32_CLOCK_PHASE_2ND:
        real_phase = SPI_PHASE_1;
        break;
    }
    return real_phase;
}

static SpiPolarity_t SpiArteryPolarityToPolarity(SpiAtClockPolarity_t artery_pol) {
    SpiPolarity_t real_polarity = 0;
    switch((uint32_t)artery_pol) {
    case SPI_AT32_CLOCK_POLARITY_LOW:
        real_polarity = SPI_POLARITY_LATCH_FALING;
        break;
    case SPI_AT32_CLOCK_POLARITY_HIGH:
        real_polarity = SPI_POLARITY_LATCH_RISING;
        break;
    }
    return real_polarity;
}

SpiPhase_t spi_get_phase(uint8_t num) {
    SpiPhase_t phase = SPI_PHASE_UNDEF;
    SpiInfo_t* Info = SpiGetInfo(num);
    if(Info) {
        phase = SpiArteryPhaseToPhase(Info->SPIx->ctrl1_bit.clkpha);
    }
    return phase;
}

SpiPolarity_t spi_get_polarity(uint8_t num) {
    SpiPolarity_t polarity = SPI_POLARITY_UNDEF;
    SpiInfo_t* Info = SpiGetInfo(num);
    if(Info) {
        polarity = SpiArteryPolarityToPolarity(Info->SPIx->ctrl1_bit.clkpol);
    }
    return polarity;
}

static int32_t spi_at_divider_get(uint8_t num) {
    int32_t real_divider = 0;
    SpiInfo_t* Info = SpiGetInfo(num);
    if(Info) {
        real_divider = SpiArteryDeividerToDeivider(Info->SPIx->ctrl1_bit.mdiv_l);
    }
    return real_divider;
}

// SCK
uint32_t spi_get_sck_frequency(uint8_t num) {
    uint32_t clock_frequency_hz = 0;
    int32_t bus_clock_hz = spi_bus_clock_get(num);
    int32_t divider = spi_at_divider_get(num);
    clock_frequency_hz = bus_clock_hz / divider;
    return clock_frequency_hz;
}

// data_size=frame size
uint8_t spi_get_data_size(uint8_t num) {
    uint8_t data_size_bits = 0;
    SpiInfo_t* Info = SpiGetInfo(num);
    if(Info) {
        data_size_bits = SpiArteryFrameSizeToLogicFrameSize(Info->SPIx->ctrl1_bit.fbn);
    }
    return data_size_bits;
}

spi_type* SpiNumToBase(uint8_t num) {
    spi_type* SPIx = NULL;
    const SpiInfo_t* Info = SpiGetInfo(num);
    if(Info) {
        SPIx = Info->SPIx;
    }
    return SPIx;
}

bool spi_operation_set(uint8_t num, SpiOperationMode_t spi_operation) {
    bool res = false;
    SpiInfo_t* Info = SpiGetInfo(num);
    if(Info) {
        Info->SPIx->i2sctrl_bit.opersel = SpiTxModeToArteryOperation(spi_operation);
        res = true;
    }
    return res;
}
/*Half-duplex communication – master transmit
  Figure 13-8 Master half-duplex transmit
 */
bool spi_write_interrupt(uint8_t num, const uint8_t* const data, size_t size) {
    bool res = false;
    LOG_DEBUG(SPI, "SPI%u,Write,Int,Size:%u", num, size);
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node) {
        if(data) {
            if(size) {
                Node->state = SPI_STATE_TX;
                // spi_enable(Node->SPIx, false);
                Node->tx_done = false;
                // res = spi_operation_set(num, SPI_OP_MODE_MASTER_TX);
                // Half-duplex communication – master transmit
                Node->SPIx->ctrl1_bit.msten = SPI_AT32_BUS_ROLE_MASTER;        // MSTEN=1: Master enable
                Node->SPIx->ctrl1_bit.slben = SPI_AT32_SINGLE_LINE_BI_DIR_OFF; // SLBEN=1: Single line bidirectional
                                                                               // mode
                // Node->SPIx->ctrl1_bit.slben = SPI_AT32_SINGLE_LINE_BI_DIR_ON;//error
                Node->SPIx->ctrl1_bit.fbn = SPI_AT32_FRAME_SIZE_8_BIT; // FBN=0: 8-bit frame
#if 0
                //error
                Node->SPIx->ctrl1_bit.slben = SPI_AT32_SINGLE_LINE_BI_DIR_ON;
                Node->SPIx->ctrl1_bit.slbtd = SPI_AT32_HALF_DUPLEX_TX_ONLY;
                Node->SPIx->ctrl1_bit.ora = SPI_AT32_MOVE_MODE_TX_AND_RX;
#endif

                Node->Tx.cnt = 0;
                Node->Tx.data = data;
                Node->Tx.size = size;

                spi_i2s_interrupt_enable(Node->SPIx, SPI_I2S_TDBE_INT, TRUE);
                // spi_i2s_data_transmit(Node->SPIx, (uint16_t)data[0]);
                spi_enable(Node->SPIx, TRUE);

                res = spi_wait_tx_ll(Node);

                spi_enable(Node->SPIx, false);
            }
        }
    }
    return res;
}

/*
 * Full-duplex communication – master mode
 * see Figure 13-6 Master full-duplex communications*/
bool spi_api_write_read(uint8_t num, const uint8_t* const tx_array, uint8_t* const rx_array, uint32_t size) {
    bool res = false;
    LOG_DEBUG(SPI, "SPI%u,TxAndRx,Size:%u", num, size);
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node) {
        Node->txrx_done = false;
        Node->tx_done = false;
        Node->rx_done = false;

        // Full-duplex communication – master mode
        Node->state = SPI_STATE_TX_RX;
        Node->SPIx->ctrl1_bit.msten = SPI_AT32_BUS_ROLE_MASTER;        // MSTEN=1: Master enable
        Node->SPIx->ctrl1_bit.slben = SPI_AT32_SINGLE_LINE_BI_DIR_OFF; // SLBEN=0: Full-duplex mode
        Node->SPIx->ctrl1_bit.fbn = SPI_AT32_FRAME_SIZE_8_BIT;         // FBN=0: 8-bit frame

        // Node->SPIx->ctrl1_bit.slbtd = SPI_AT32_HALF_DUPLEX_RX_ONLY ;
        // Node->SPIx->ctrl1_bit.ora = SPI_AT32_MOVE_MODE_RX_ONLY;

        Node->Tx.cnt = 0;
        Node->Tx.data = tx_array;
        Node->Tx.size = size;

        Node->Rx.cnt = 0;
        Node->Rx.data = rx_array;
        // Node->Rx.size = size+1;
        Node->Rx.size = size;
        uint16_t word = spi_i2s_data_receive(Node->SPIx);
        LOG_DEBUG(SPI, "SPI%u,PrevWord:0x%x", num, word);
        //  spi_i2s_data_transmit(Node->SPIx, (uint16_t)tx_array[0]);
        spi_i2s_interrupt_enable(Node->SPIx, SPI_I2S_RDBF_INT, TRUE);
        spi_i2s_interrupt_enable(Node->SPIx, SPI_I2S_TDBE_INT, TRUE);
        spi_enable(Node->SPIx, TRUE); // Signal exest on Wire if enable before int enable

        res = true;
        res = spi_wait_rx_ll(Node) && res;
        res = spi_wait_tx_ll(Node) && res;
        spi_enable(Node->SPIx, false);
    }
    return res;
}

/*
 */
bool spi_read_interrupt(uint8_t num, uint8_t* const data, size_t size) {
    bool res = false;
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node) {
        Node->rx_done = false;
        spi_i2s_interrupt_enable(Node->SPIx, SPI_I2S_RDBF_INT, false);
        LOG_DEBUG(SPI, "SPI%u,Rx,Size:%u", num, size);
        res = spi_operation_set(num, SPI_OP_MODE_MASTER_RX);

        // Half-duplex communication – master receive
        Node->SPIx->ctrl1_bit.msten = SPI_AT32_BUS_ROLE_MASTER;
        Node->SPIx->ctrl1_bit.fbn = SPI_AT32_FRAME_SIZE_8_BIT;
        Node->SPIx->ctrl1_bit.slbtd = SPI_AT32_HALF_DUPLEX_RX_ONLY;
        Node->SPIx->ctrl1_bit.ora = SPI_AT32_MOVE_MODE_RX_ONLY;
#if 0
        // min rx 16 bit
        Node->SPIx->ctrl1_bit.slben = SPI_AT32_SINGLE_LINE_BI_DIR_ON;
#endif
        Node->SPIx->ctrl1_bit.slben = SPI_AT32_SINGLE_LINE_BI_DIR_OFF;

        Node->Rx.cnt = 0;
        Node->Rx.data = data;
        Node->Rx.size = size;
        Node->state = SPI_STATE_RX;
        spi_enable(Node->SPIx, TRUE);
        spi_i2s_interrupt_enable(Node->SPIx, SPI_I2S_RDBF_INT, TRUE);
        // spi_i2s_data_receive(Node->SPIx);
        res = spi_wait_rx_ll(Node);
        spi_enable(Node->SPIx, false);
    }
    return res;
}

bool spi_read_byte_v2(uint8_t num, uint8_t* const rx_byte) {
    bool res = false;
    LOG_PARN(SPI, "SPI%u,Read,Byte", num);

    SpiHandle_t* Node = SpiGetNode(num);
    if(Node) {
        Node->rx_done = false;
        Node->SPIx->ctrl1_bit.msten = SPI_AT32_BUS_ROLE_MASTER;
        Node->SPIx->ctrl1_bit.slben = SPI_AT32_SINGLE_LINE_BI_DIR_OFF; // SPI_AT32_SINGLE_LINE_BI_DIR_ON;
        Node->SPIx->ctrl1_bit.slbtd = SPI_AT32_HALF_DUPLEX_RX_ONLY;    // SPI_AT32_HALF_DUPLEX_RX_ONLY
        Node->SPIx->ctrl1_bit.ora = SPI_AT32_MOVE_MODE_RX_ONLY;
        Node->SPIx->ctrl1_bit.fbn = SPI_AT32_FRAME_SIZE_8_BIT;
        // Node->SPIx->ctrl1_bit.spien = 1;
#if 0
        Node->SPIx->ctrl1_bit.ccen = 0;//
        Node->SPIx->ctrl1_bit.ntc = 0;//
        Node->SPIx->ctrl1_bit.swcsen = 0;//
        Node->SPIx->ctrl1_bit.swcsil = 1;//
#endif
        // Node->SPIx->ctrl1_bit.LTF = 0;//0: MSB

        Node->Rx.cnt = 0;
        Node->Rx.data = rx_byte;
        Node->Rx.size = 1;
        Node->state = SPI_STATE_RX;
        spi_i2s_interrupt_enable(Node->SPIx, SPI_I2S_RDBF_INT, TRUE);
        spi_enable(Node->SPIx, TRUE);
        res = spi_wait_rx_ll(Node);
        spi_enable(Node->SPIx, false);
    }

    return res;
}

uint8_t spi_read_byte(uint8_t num) {
    LOG_PARN(SPI, "SPI%u,Read,Byte", num);

    uint8_t rx_byte = 0x00;
    bool res = spi_read_byte_v2(num, &rx_byte);
    (void)res;

    return rx_byte;
}

bool spi_init_custom(void) {
    bool res = true;
    log_level_get_set(SPI, LOG_LEVEL_INFO);
    return res;
}

static spi_mclk_freq_div_type PrescalserToArteryDivider(uint32_t prescaler) {
    LOG_DEBUG(SPI, "PSC:%u", prescaler);
    uint32_t i = 0;
    int32_t prescaler_diff_abs = 0;
    SpiDividerItem_t BestDiv = {0};
    BestDiv.divider = 1024;
    BestDiv.code = SPI_MCLK_DIV_1024;
    BestDiv.prescaler_diff_abs = 99999;

    uint32_t cnt = ARRAY_SIZE(SpiDivider);
    LOG_DEBUG(SPI, "Cnt:%u", cnt);
    for(i = 0; i < cnt; i++) {
        prescaler_diff_abs = abs(((int32_t)prescaler) - ((int32_t)SpiDivider[i].divider));
        LOG_PARN(SPI, "i:%u,Diff:%d,BestDiff:%d", i, prescaler_diff_abs, BestDiv.prescaler_diff_abs);

        if(prescaler_diff_abs < BestDiv.prescaler_diff_abs) {
            LOG_PARN(SPI, "Upd:i:%u,Diff:%d", i, prescaler_diff_abs);
            BestDiv.code = SpiDivider[i].code;
            BestDiv.prescaler_diff_abs = prescaler_diff_abs;
            BestDiv.divider = SpiDivider[i].divider;
        }
    }
    LOG_DEBUG(SPI, "PSC:%u,Div:%u", prescaler, BestDiv.divider);
    return BestDiv.code;
}

static spi_clock_polarity_type SpiPolarityToArteryPo(SpiPolarity_t polarity) {
    spi_clock_polarity_type clock_polarity = SPI_CLOCK_POLARITY_LOW;
    switch((uint32_t)polarity) {
    case SPI_POLARITY_LATCH_RISING: {
        /* sck keeps low at idle state */
        clock_polarity = SPI_CLOCK_POLARITY_LOW;
    } break;
    case SPI_POLARITY_LATCH_FALING: {
        /* sck keeps high at idle state */
        clock_polarity = SPI_CLOCK_POLARITY_HIGH;
    } break;
    }

    return clock_polarity;
}

bool spi_proc_one(uint8_t num) {
    bool res = false;
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node) {
        if(SPI_STATE_IDLE == Node->state) {
            // spi_enable(Node->SPIx, false);
        }
    }
    return res;
}

bool spi_init_one(uint8_t num) {
    bool res = false;
    log_level_get_set(SPI, LOG_LEVEL_DEBUG);
    const SpiConfig_t* Config = SpiGetConfig(num);
    if(Config) {
        // TODO res = SpiIsValidConfig(Config);
        LOG_WARNING(SPI, "%s", SpiConfigToStr(Config));
        SpiHandle_t* Node = SpiGetNode(num);
        if(Node) {
            res = spi_init_common(Config, Node);

            SpiInfo_t* Info = SpiGetInfo(num);
            if(Info) {
                Node->SPIx = Info->SPIx;

                crm_periph_clock_enable(Info->clock_type, TRUE);

                spi_init_type SpiInitStruct = {0};
                spi_default_para_init(&SpiInitStruct);

                int32_t bus_freq = spi_bus_clock_get(num);

                uint32_t prescaler = calc_prescaler(bus_freq, Config->bit_rate_hz);
                LOG_DEBUG(SPI, "BusFreq:%d Hz,PSC:%u", bus_freq, prescaler);

                spi_mclk_freq_div_type divider = PrescalserToArteryDivider(prescaler);

                SpiInitStruct.cs_mode_selection = SpiChipSelectToArterySc(Config->chip_select);
                SpiInitStruct.clock_phase = SpiClockPhaseToArteryCf(Config->phase);
                SpiInitStruct.clock_polarity = SpiPolarityToArteryPo(Config->polarity);
                SpiInitStruct.frame_bit_num = SpiFrameSizeToArteryFs(Config->frame_size);
                SpiInitStruct.mclk_freq_division = divider;
                SpiInitStruct.master_slave_mode = SpiBusRoleToArteryBr(Config->bus_role);
                SpiInitStruct.first_bit_transmission = SpiBitOrgerToArteryBo(Config->bit_order);
                SpiInitStruct.transmission_mode = SpiTxModeToArteryTm(Config->tx_mode);

                spi_init(Node->SPIx, &SpiInitStruct);

                if(Config->interrupt_on) {
                    nvic_irq_enable(Info->irq_n, Config->irq_priority, Config->irq_priority);
                    spi_i2s_interrupt_enable(Node->SPIx, SPI_I2S_TDBE_INT, TRUE);
                    spi_i2s_interrupt_enable(Node->SPIx, SPI_I2S_RDBF_INT, TRUE);
                    spi_i2s_interrupt_enable(Node->SPIx, SPI_I2S_ERROR_INT, TRUE);
                }

                spi_enable(Node->SPIx, TRUE);
                res = true;

            } else {
                LOG_ERROR(SPI, "SPI%u InstErr", num);
            }
        } else {
            LOG_ERROR(SPI, "SPI%u NodeErr", num);
        }
    } else {
        LOG_DEBUG(SPI, "SPI%u ConfErr", num);
    }
    log_level_get_set(SPI, LOG_LEVEL_INFO);
    return res;
}

bool spi_api_write(uint8_t num, const uint8_t* const array, uint32_t size) {
    bool res = false;
    LOG_DEBUG(SPI, "SPI%u,Write,Size:%u byte", num, size);
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node) {
        Node->tx_done = false;
        const SpiConfig_t* Config = SpiGetConfig(num);
        if(Config) {
            switch(Node->move_mode) {
            case MOVE_MODE_INTERRUPT: {
                res = spi_write_interrupt(num, array, size);
            } break;
            case MOVE_MODE_DMA: {
                res = false;
#ifdef HAS_SPI_DMA
                res = spi_write_dma(num, array, size, DMA_MODE_CIRCULAR);
#endif
            } break;
            default:
                res = false;
                break;
            }
        }
    }
    return res;
}

/*
 */
bool spi_api_read(uint8_t num, uint8_t* const data, uint32_t size) {
    bool res = false;
    SpiHandle_t* Node = SpiGetNode(num);
    if(Node) {
        Node->rx_done = false;
        const SpiConfig_t* Config = SpiGetConfig(num);
        if(Config) {
            // res = spi_role_set(num, SPI_MODE_MASTER_RX);
            switch((uint32_t)Node->move_mode) {
            case MOVE_MODE_INTERRUPT: {
                res = spi_read_interrupt(num, data, size);
            } break;
            case MOVE_MODE_DMA: {
                res = false;
#ifdef HAS_SPI_DMA
                res = spi_read_dma(num, data, size, DMA_MODE_CIRCULAR);
#endif
            } break;
            default:
                res = false;
                break;
            }
        }
    }
    return res;
}
