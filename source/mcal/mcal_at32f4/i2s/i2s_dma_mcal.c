#include "i2s_dma_mcal.h"

#include "at32_misc.h"
#include "common_diag.h"
#include "dma_mcal.h"
#include "i2s_mcal.h"
#include "log.h"
#include "microcontroller_const.h"

static uint8_t i2s_tx_to_dma_mux(uint8_t num) {
    uint8_t mux = 0;
    switch(num) {
    case 1:
        mux = DMAMUX_DMAREQ_ID_SPI1_TX;
        break;
    case 2:
        mux = DMAMUX_DMAREQ_ID_SPI2_TX;
        break;
    case 3:
        mux = DMAMUX_DMAREQ_ID_SPI3_TX;
        break;
    case 4:
        mux = DMAMUX_DMAREQ_ID_SPI4_TX;
        break;
    case 5:
        mux = DMAMUX_DMAREQ_ID_I2S2_EXT_TX;
        break;
    case 6:
        mux = DMAMUX_DMAREQ_ID_I2S3_EXT_TX;
        break;
    }
    return mux;
}

static uint8_t i2s_rx_to_dma_mux(uint8_t num) {
    uint8_t mux = 0;
    switch(num) {
    case 1:
        mux = DMAMUX_DMAREQ_ID_SPI1_RX;
        break;
    case 2:
        mux = DMAMUX_DMAREQ_ID_SPI2_RX;
        break;
    case 3:
        mux = DMAMUX_DMAREQ_ID_SPI3_RX;
        break;
    case 4:
        mux = DMAMUX_DMAREQ_ID_SPI4_RX;
        break;
    case 5:
        mux = DMAMUX_DMAREQ_ID_I2S2_EXT_RX;
        break;
    case 6:
        mux = DMAMUX_DMAREQ_ID_I2S3_EXT_RX;
        break;
    }
    return mux;
}

bool i2s_dma_ctrl_ll(I2sHandle_t* Node, bool on_off) {
    bool res = false;
    LOG_INFO(I2S, "%u,Dma,Crtl:%s", Node->num, OnOffToStr(on_off));
    confirm_state new_state = OnOffToConfirmState(on_off);
    switch((uint32_t)Node->bus_role) {
    case I2S_DIR_BUS_MODE_SLAVE_RX:
    case I2S_DIR_BUS_MODE_MASTER_RX: {
        // I in RX
        spi_i2s_dma_receiver_enable(Node->I2Sx, new_state);
        res = true;
    } break;

    case I2S_DIR_BUS_MODE_SLAVE_TX:
    case I2S_DIR_BUS_MODE_MASTER_TX: {
        // I Out TX
        spi_i2s_dma_transmitter_enable(Node->I2Sx, new_state);
        res = true;
    } break;

    default:
        res = false;
        break;
    }
    return res;
}

bool i2s_dma_ctrl(uint8_t num, bool on_off) {
    bool res = false;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        res = i2s_dma_ctrl_ll(Node, on_off);
    }
    return res;
}

bool i2s_init_dma(const I2sConfig_t* Config, I2sHandle_t* Node) {
    bool res = false;
    LOG_WARNING(I2S, "Init,DMA");
    const DmaChannelInfo_t* ChannelInfo = DmaChannelGetInfo(Config->Dma.dma_num, Config->Dma.channel);
    if(ChannelInfo) {
        dma_reset(ChannelInfo->dmax_channely);
        const DmaInfo_t* Info = DmaGetInfo(Config->Dma.dma_num);
        if(Info) {
            dmamux_enable(Info->DMAx, TRUE);
        }
        dmamux_requst_id_sel_type dmamux_req_sel = 0;
        switch((uint32_t)Node->bus_role) {
        case I2S_DIR_BUS_MODE_MASTER_TX:
        case I2S_DIR_BUS_MODE_SLAVE_TX: {
            dmamux_req_sel = i2s_tx_to_dma_mux(Config->num);
        } break;
        case I2S_DIR_BUS_MODE_MASTER_RX:
        case I2S_DIR_BUS_MODE_SLAVE_RX: {
            dmamux_req_sel = i2s_rx_to_dma_mux(Config->num);
        } break;
        }
        dmamux_init(ChannelInfo->dmamux_channelx, dmamux_req_sel);
        dma_channel_enable(ChannelInfo->dmax_channely, TRUE);
        res = i2s_dma_ctrl_ll(Node, false);
    }
    return res;
}

bool i2s_api_write_dma(uint8_t num, SampleType_t* const array, size_t channel_cnt, DmaMode_t mode) {
    bool res = false;
    // LOG_INFO(I2S, "Write,I2S_%u,Words:%u", num, size);

    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        // res= dma_channel_stop(Node->Dma) ;
        Node->tx_half = false;
        Node->tx_done = false;
        Node->dma_move_cnt = channel_cnt;
        spi_i2s_dma_transmitter_enable(Node->I2Sx, FALSE);
        DmaChannelConfig_t Config;
        Config.num = 1;
        // Config.stream_num = Node->Dma.channel;
        Config.buffer_size = channel_cnt;
        Config.channel = Node->Dma.channel;
        Config.memory_burst = DMA_BURST_SINGLE;
        Config.periph_burst = DMA_BURST_SINGLE;
        Config.dma_num = Node->Dma.dma_num;
        Config.mux = i2s_tx_to_dma_mux(num);
        Config.CallBackHalf = Node->CallBackTxHalf;
        Config.CallBackDone = Node->CallBackTxDone;
        Config.fifo = DMA_FIFO_OFF;
        Config.mode = mode;
        Config.mem_inc = DMA_INC_ON;
        Config.per_inc = DMA_INC_OFF;
        Config.priority = DMA_PRIOR_VERY_HIGH;
        Config.dir = DMA_MCAL_DIR_MEMORY_TO_PERIPH;
        Config.peripheral_base_addr = (uint32_t) & (Node->I2Sx->dt);
        Config.memory_base_addr = (uint32_t)array;
        Config.aligment_per = DMA_ALIG_HALF_WORD;
        Config.aligment_mem = DMA_ALIG_HALF_WORD;
        Config.valid = true;
        spi_i2s_interrupt_enable(Node->I2Sx, SPI_I2S_TDBE_INT, FALSE);
        spi_i2s_dma_transmitter_enable(Node->I2Sx, TRUE);
        i2s_enable(Node->I2Sx, TRUE);
        res = dma_channel_init_one_ll(&Config);
        if(res) {
            Node->state = I2S_STATE_PLAY;
        }
    }
    return res;
}

bool i2s_dma_restart(uint8_t num) {
    bool res = false;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        res = dma_channel_restart(Node->Dma, Node->dma_move_cnt);
    }
    return res;
}

/*
 * channel_cnt - I2S channels quantity
 */
bool i2s_api_read_dma(uint8_t num, SampleType_t* const array, size_t channel_cnt, DmaMode_t mode) {
    bool res = false;
    // LOG_INFO(I2S, "Read,Dma,I2S_%u,Words:%u", num, size);

    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        // res= dma_channel_stop(Node->Dma) ;
        Node->dma_move_cnt = channel_cnt;

        spi_i2s_dma_receiver_enable(Node->I2Sx, FALSE);
        DmaChannelConfig_t Config;
        Config.num = 2;
        Config.aligment_per = DMA_ALIG_HALF_WORD;   // affective
        Config.aligment_mem = DMA_ALIG_HALF_WORD;   // affective
        Config.buffer_size = channel_cnt;           // 2* hang on  0.5* small //affective
        Config.CallBackDone = Node->CallBackRxHalf; // affective
        Config.CallBackHalf = Node->CallBackRxDone; // affective
        Config.channel = Node->Dma.channel;         // affective
        Config.dir = DMA_MCAL_DIR_PERIPH_TO_MEMORY; // affective
        Config.dma_num = Node->Dma.dma_num;         // affective
        Config.fifo = DMA_FIFO_OFF;
        Config.mode = mode; // affective
        Config.memory_burst = DMA_BURST_SINGLE;
        Config.memory_base_addr = (uint32_t)array; // affective
        Config.mem_inc = DMA_INC_ON;               // affective
        Config.mux = i2s_rx_to_dma_mux(num);       // affective
        Config.periph_burst = DMA_BURST_SINGLE;
        Config.per_inc = DMA_INC_OFF;          // affective
        Config.priority = DMA_PRIOR_VERY_HIGH; // affective
        Config.valid = true;
        Config.peripheral_base_addr = (uint32_t) & (Node->I2Sx->dt); // affective
                                                                     // Config.stream_num = Node->Dma.channel;
        spi_i2s_interrupt_enable(Node->I2Sx, SPI_I2S_RDBF_INT, FALSE);
        spi_i2s_dma_receiver_enable(Node->I2Sx, TRUE);
        i2s_enable(Node->I2Sx, TRUE);
        res = dma_channel_init_one_ll(&Config);
        if(res) {
            Node->state = I2S_STATE_REC;
        }
    }
    return res;
}

bool i2s_dma_pause(uint8_t num) {
    bool res = false;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        res = i2s_dma_ctrl_ll(Node, false);
        if(res) {
            Node->state = I2S_STATE_IDLE;
        }
    }
    return res;
}

bool i2s_dma_stop(uint8_t num) {
    bool res = false;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        res = i2s_dma_ctrl_ll(Node, false);
        if(res) {
            Node->state = I2S_STATE_IDLE;
        }
    }
    return res;
}
