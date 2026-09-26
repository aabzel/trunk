#include "power_dma_mcal.h"

#include "x86x_misc.h"
#include "common_diag.h"
#include "dma_mcal.h"
#include "i2s_mcal.h"
#include "log.h"
#include "microcontroller_const.h"

static uint8_t power_tx_to_dma_mux(uint8_t num) {
    uint8_t mux = 0;
    switch(num) {
    case 1:
        mux = DMAMUX_DMAREQ_ID_POWER1_TX;
        break;
    case 2:
        mux = DMAMUX_DMAREQ_ID_POWER2_TX;
        break;
    case 3:
        mux = DMAMUX_DMAREQ_ID_POWER3_TX;
        break;
    case 4:
        mux = DMAMUX_DMAREQ_ID_POWER4_TX;
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

static uint8_t power_rx_to_dma_mux(uint8_t num) {
    uint8_t mux = 0;
    switch(num) {
    case 1:
        mux = DMAMUX_DMAREQ_ID_POWER1_RX;
        break;
    case 2:
        mux = DMAMUX_DMAREQ_ID_POWER2_RX;
        break;
    case 3:
        mux = DMAMUX_DMAREQ_ID_POWER3_RX;
        break;
    case 4:
        mux = DMAMUX_DMAREQ_ID_POWER4_RX;
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

bool power_dma_ctrl_ll(PowerHandle_t* Node, bool on_off) {
    bool res = false;
    LOG_INFO(I2S, "%u,Dma,Crtl:%s", Node->num, OnOffToStr(on_off));
    confirm_state new_state = OnOffToConfirmState(on_off);
    switch((uint32_t)Node->bus_role) {
    case I2S_DIR_BUS_MODE_SLAVE_RX:
    case I2S_DIR_BUS_MODE_MASTER_RX: {
        // I in RX
        power_power_dma_receiver_enable(Node->POWERx, new_state);
        res = true;
    } break;

    case I2S_DIR_BUS_MODE_SLAVE_TX:
    case I2S_DIR_BUS_MODE_MASTER_TX: {
        // I Out TX
        power_power_dma_transmitter_enable(Node->POWERx, new_state);
        res = true;
    } break;

    default:
        res = false;
        break;
    }
    return res;
}

bool power_dma_ctrl(uint8_t num, bool on_off) {
    bool res = false;
    PowerHandle_t* Node = PowerGetNode(num);
    if(Node) {
        res = power_dma_ctrl_ll(Node, on_off);
    }
    return res;
}

bool i2s_init_dma(const I2sConfig_t* Config, PowerHandle_t* Node) {
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
            dmamux_req_sel = power_tx_to_dma_mux(Config->num);
        } break;
        case I2S_DIR_BUS_MODE_MASTER_RX:
        case I2S_DIR_BUS_MODE_SLAVE_RX: {
            dmamux_req_sel = power_rx_to_dma_mux(Config->num);
        } break;
        }
        dmamux_init(ChannelInfo->dmamux_channelx, dmamux_req_sel);
        dma_channel_enable(ChannelInfo->dmax_channely, TRUE);
        res = power_dma_ctrl_ll(Node, false);
    }
    return res;
}

bool i2s_api_write_dma(uint8_t num, SampleType_t* const array, size_t size, DmaMode_t mode) {
    bool res = false;
    // LOG_INFO(I2S, "Write,I2S_%u,Words:%u", num, size);

    PowerHandle_t* Node = PowerGetNode(num);
    if(Node) {
        // res= dma_channel_stop(Node->Dma) ;
        Node->tx_half = false;
        Node->tx_done = false;
        Node->dma_move_cnt = size;
        power_power_dma_transmitter_enable(Node->POWERx, FALSE);
        DmaChannelConfig_t Config;
        Config.num = 3;
        Config.stream_num = Node->Dma.channel;
        Config.buffer_size = size;
        Config.channel = Node->Dma.channel;
        Config.memory_burst = DMA_BURST_SINGLE;
        Config.periph_burst = DMA_BURST_SINGLE;
        Config.dma_num = Node->Dma.dma_num;
        Config.mux = power_tx_to_dma_mux(num);
        Config.CallBackHalf = Node->CallBackTxHalf;
        Config.CallBackDone = Node->CallBackTxDone;
        Config.fifo = DMA_FIFO_OFF;
        Config.mode = mode;
        Config.mem_inc = DMA_INC_ON;
        Config.per_inc = DMA_INC_OFF;
        Config.priority = DMA_PRIOR_VERY_HIGH;
        Config.dir = DMA_MCAL_DIR_MEMORY_TO_PERIPH;
        Config.peripheral_base_addr = (uint32_t) & (Node->POWERx->dt);
        Config.memory_base_addr = (uint32_t)array;
        Config.aligment_per = DMA_ALIG_BYTE;
        Config.aligment_mem = DMA_ALIG_BYTE;
        Config.valid = true;
        power_i2s_interrupt_enable(Node->POWERx, POWER_I2S_TDBE_INT, FALSE);
        power_power_dma_transmitter_enable(Node->POWERx, TRUE);
        power_enable(Node->POWERx, TRUE);
        res = dma_channel_init_one_ll(&Config);
        if(res) {
            Node->state = POWER_STATE_TX;
        }
    }
    return res;
}

bool power_dma_restart(uint8_t num) {
    bool res = false;
    PowerHandle_t* Node = PowerGetNode(num);
    if(Node) {
        res = dma_channel_restart(Node->Dma, Node->dma_move_cnt);
    }
    return res;
}



/*
 * size - I2S channels quantity
 */
bool i2s_api_read_dma(uint8_t num, SampleType_t* const array, size_t size, DmaMode_t mode) {
    bool res = false;
    // LOG_INFO(I2S, "Read,Dma,I2S_%u,Words:%u", num, size);

    PowerHandle_t* Node = PowerGetNode(num);
    if(Node) {
        // res= dma_channel_stop(Node->Dma) ;
        Node->dma_move_cnt = size;

        power_power_dma_receiver_enable(Node->POWERx, FALSE);
        DmaChannelConfig_t Config;
        Config.num = 4;
        Config.aligment_per = DMA_ALIG_BYTE;   // affective
        Config.aligment_mem = DMA_ALIG_BYTE;   // affective
        Config.buffer_size = size;           // 2* hang on  0.5* small //affective
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
        Config.mux = power_rx_to_dma_mux(num);       // affective
        Config.periph_burst = DMA_BURST_SINGLE;
        Config.per_inc = DMA_INC_OFF;          // affective
        Config.priority = DMA_PRIOR_VERY_HIGH; // affective
        Config.valid = true;
        Config.peripheral_base_addr = (uint32_t) & (Node->POWERx->dt); // affective
        Config.stream_num = Node->Dma.channel;
        power_i2s_interrupt_enable(Node->POWERx, POWER_I2S_RDBF_INT, FALSE);
        power_power_dma_receiver_enable(Node->POWERx, TRUE);
        power_enable(Node->POWERx, TRUE);
        res = dma_channel_init_one_ll(&Config);
        if(res) {
            Node->state = POWER_STATE_RX;
        }
    }
    return res;
}

bool power_dma_pause(uint8_t num) {
    bool res = false;
    PowerHandle_t* Node = PowerGetNode(num);
    if(Node) {
        res = power_dma_ctrl_ll(Node, false);
        if(res) {
            Node->state = POWER_STATE_IDLE;
        }
    }
    return res;
}

bool power_dma_stop(uint8_t num) {
    bool res = false;
    PowerHandle_t* Node = PowerGetNode(num);
    if(Node) {
        res = power_dma_ctrl_ll(Node, false);
        if(res) {
            Node->state = POWER_STATE_IDLE;
        }
    }
    return res;
}
