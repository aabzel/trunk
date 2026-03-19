#include "dma_channel_config.h"

#include "data_utils.h"
#include "microcontroller_const.h"
#ifdef HAS_SPI
#include "spi_mcal.h"
#include "spi_isr.h"
#include "module_driver_fcspi.h"
#endif

#include "module_driver_fcspi.h"

static bool CallBackDoneSpi1Rx(void) {
    bool res = false;
#ifdef HAS_SPI
    SpiHandle_t* Spi = SpiGetNode(1);
    if(Spi) {
        FCSPIn_DmaDoneCallback_Rx(&Spi->Handle);
    }
#endif
    return res;
}

static bool CallBackDoneSpi1Tx(void){
    bool res = false;
#ifdef HAS_SPI
    SpiHandle_t* Spi = SpiGetNode(1);
    if(Spi){
        FCSPIn_DmaDoneCallback_Tx(&Spi->Handle);
    }
#endif
    return res;
}

static bool CallBackHalfSpi1Rx(void) {
    bool res = false;
#ifdef HAS_SPI
    res= SpiCallBackRxHalfCplt(1);
#endif
    return res;
}

static bool CallBackHalfSpi1Tx(void){
    bool res = false;
    #ifdef HAS_SPI
    res=  SpiCallBackTxHalfCplt(1);
#endif
    return res;
}

#if 0
static bool CallBackErrorSpi1Rx(void) {
    bool res = false;
#ifdef HAS_SPI
    res= SpiCallBackError(1);
#endif
    return res;
}

static bool CallBackErrorSpi1Tx(void) {
    bool res = false;
#ifdef HAS_SPI
    res= SpiCallBackError(1);
#endif
    return res;
}
#endif

#define DMA_MEMCPY_SIZE 50
static uint8_t toArray[DMA_MEMCPY_SIZE]={0};
static uint8_t fromArray[DMA_MEMCPY_SIZE]={0};

static bool CallBackHalfMemCpy(void){return true;}
//static bool CallBackErrorMemCpy(void){return true;}
static bool CallBackDoneMemCpy(void){return true;}

#define DMA_CHANNEL_SPI1_RX                         \
    {                                               \
        .DmaPad={.dma_num = 0, .channel = 10},      \
        .priority = 10,                             \
        .mux = DMA_REQ_FCSPI1_RX,                   \
        .num = 1,                                   \
        .name = "Spi1rx",                           \
        .aligment_source = DMA_ALIGNMENT_BYTE,      \
        .aligment_destination = DMA_ALIGNMENT_BYTE, \
        .base_addr_source = (uint32_t) fromArray,   \
        .base_addr_destination =(uint32_t) toArray, \
        .block_size = (uint32_t) DMA_MEMCPY_SIZE,   \
        .block_count =1,                            \
        .CallBackHalf= CallBackHalfSpi1Rx,          \
        .CallBackDone= CallBackDoneSpi1Rx,          \
        .dir = DMA_MCAL_DIR_PERIPH_TO_MEMORY,       \
        .inc_destination = DMA_INC_ON,              \
        .inc_source = DMA_INC_OFF,                  \
        .fifo = DMA_FIFO_OFF,                       \
        .mode = DMA_MODE_NORMAL,                    \
        .memory_burst = DMA_BURST_SINGLE,           \
        .periph_burst = DMA_BURST_SINGLE,           \
        .valid = true,                              \
        .interrupt_on = true,                       \
    },

#define DMA_CHANNEL_SPI1_TX                  \
    {                                        \
 .DmaPad={.dma_num = 0,  .channel = 1},      \
 .priority = 1,                              \
 .mux = DMA_REQ_FCSPI1_TX,                   \
 .num = 2,                                   \
 .CallBackHalf= CallBackHalfSpi1Tx,          \
 .CallBackDone= CallBackDoneSpi1Tx,          \
 .block_count =1,                            \
 .dir = DMA_MCAL_DIR_MEMORY_TO_PERIPH,       \
 .mode = DMA_MODE_NORMAL,                    \
 .inc_destination = DMA_INC_ON,              \
 .interrupt_on = true,                       \
 .base_addr_source = (uint32_t)fromArray,    \
 .base_addr_destination =(uint32_t) toArray, \
 .inc_source = DMA_INC_OFF,                  \
 .aligment_source = DMA_ALIGNMENT_BYTE,      \
 .aligment_destination = DMA_ALIGNMENT_BYTE, \
 .fifo = DMA_FIFO_OFF,                       \
 .memory_burst = DMA_BURST_SINGLE,           \
 .periph_burst = DMA_BURST_SINGLE,           \
 .valid = true,                              \
 .name = "Spi1Tx",                           \
    },

#define DMA_CHANNEL_MEMCPY1                  \
    {                                        \
 .num = 4,                                   \
 .DmaPad={.dma_num = 1, .channel = 10, },    \
 .priority = 10,                             \
 .mux = 0,                                   \
 .CallBackHalf= CallBackHalfMemCpy,          \
 .CallBackDone= CallBackDoneMemCpy,          \
 .dir = DMA_MCAL_DIR_MEMORY_TO_MEMORY,       \
 .mode = DMA_MODE_NORMAL,                    \
 .inc_destination = DMA_INC_ON,              \
 .inc_source = DMA_INC_ON,                   \
 .aligment_source = DMA_ALIGNMENT_BYTE,      \
 .aligment_destination = DMA_ALIGNMENT_BYTE, \
 .block_count =1,                            \
 .fifo = DMA_FIFO_OFF,                       \
 .interrupt_on = true,                       \
 .memory_burst = DMA_BURST_SINGLE,           \
 .base_addr_source =(uint32_t) fromArray,    \
 .base_addr_destination =(uint32_t) toArray, \
 .periph_burst = DMA_BURST_SINGLE,           \
 .valid = true,                              \
 .name = "MemCpy",                           \
    },


#define DMA_CHANNEL_MEMCPY2                   \
    {                                         \
 .num = 3,                                    \
 .DmaPad={.dma_num = 0, .channel = 3,},       \
 .priority = 3,                               \
 .mux = 0,                                    \
 .CallBackHalf= CallBackHalfMemCpy,           \
 .CallBackDone= CallBackDoneMemCpy,           \
 .dir = DMA_MCAL_DIR_MEMORY_TO_MEMORY,        \
 .mode = DMA_MODE_NORMAL,                     \
 .inc_destination = DMA_INC_ON,               \
 .block_count =1,                            \
 .inc_source = DMA_INC_ON,                    \
 .aligment_source = DMA_ALIGNMENT_BYTE,       \
 .aligment_destination = DMA_ALIGNMENT_BYTE,  \
 .fifo = DMA_FIFO_OFF,                        \
 .interrupt_on = true,                        \
 .memory_burst = DMA_BURST_SINGLE,            \
 .base_addr_source = (uint32_t)fromArray,     \
 .base_addr_destination = (uint32_t)toArray,  \
 .periph_burst = DMA_BURST_SINGLE,            \
 .valid = true,                               \
 .name = "MemCpy",                            \
    },

#define DMA_CHANNEL_SPI1 \
    DMA_CHANNEL_SPI1_TX  \
    DMA_CHANNEL_SPI1_RX

#define DMA_CHANNEL_ALL  \
    DMA_CHANNEL_SPI1     \
    DMA_CHANNEL_MEMCPY1  \
    DMA_CHANNEL_MEMCPY2

const DmaChannelConfig_t SECTION_CFG_DATA DmaChannelConfig[] = {
    DMA_CHANNEL_ALL
};

volatile DmaChannelHandle_t DmaChannelInstance[] = {
    { .num = 1,  .valid = true,    },
    { .num = 2,  .valid = true,    },
    { .num = 3,  .valid = true,    },
    { .num = 4,  .valid = true,    },
};

uint32_t dma_channel_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(DmaChannelInstance);
    cnt2 = ARRAY_SIZE(DmaChannelConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
