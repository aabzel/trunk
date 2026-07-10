#include "sdio_config.h"

#include "clock_utils.h"
#include "data_utils.h"
#include "log_config.h"
#include "mcal_const.h"

/*
2 MHz, 1 bit, DMA - OK totalSize:1920044 Byte,Duration:12832 ms,ReadSpeed:149629 Byte/s
4 MHz, 1 bit, DMA - OK totalSize:1920044 Byte,Duration:6671 ms, ReadSpeed:287819 Byte/s
8 MHz, 1 bit, DMA - OK totalSize:1920044 Byte,Duration:3828 ms,ReadSpeed:501578 Byte/s
16 MHz, 1 bit, DMA - OK totalSize:1920044 Byte,Duration:2425 ms,ReadSpeed:791770 Byte/s=773 kByte/s
25 MHz, 1 bit, DMA - OK totalSize:1920044 Byte,Duration:1943 ms,ReadSpeed:988185 Byte/s=965.02441 kByte/s
*/

/*constant compile-time known settings in Flash*/
const SdioConfig_t SECTION_CFG_DATA SdioConfig[] = {
    {
        .num = 1,
        .valid = true,
        .interrupt_on = true,
        .name = "SdCard",
        .bus_resolution = SDIO_BUS_RESOLUTION_4BIT,
        .bit_rate_hz = MHZ_2_HZ(6.8),
        // 20MHz Write perf error timeOut
        // 10MHz Write perf error timeOut
        // 5MHz Write perf ok
        // 25MHz Unstable write/ Mount error

        /*SDIO1,PollReadBlock:0,Err:Err
        0.536,+0,266,E,[SDIO],ErrorCode 0x20=RX_OVERRUN*/
        //.move_mode = MOVE_MODE_POLLING, // FAT32 init error
        //.move_mode = MOVE_MODE_INTERRUPT, //FAT32 does not works
         .move_mode = MOVE_MODE_DMA, // FAT32 does not works
    },
};

SdioHandle_t SdioInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

COMPONENT_GET_CNT(Sdio, sdio)
