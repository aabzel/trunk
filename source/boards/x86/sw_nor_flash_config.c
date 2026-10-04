#include "sw_nor_flash_config.h"

#include "data_utils.h"
//uint8_t SwNorFlashMem[SW_NOR_FLASH_FLASH_SIZE];

static uint8_t Fc7300x[SW_NOR_FLASH_FLASH_SIZE]={0};

const SwNorFlashConfig_t SwNorFlashConfig[] = {
    {
    .size=ARRAY_SIZE(Fc7300x),
    .name="FC7300",
    .memory=Fc7300x,
    .page_size=SW_NOR_FLASH_PAGE_SIZE,
    .sector_size=8*1024,
    .num = 1,
    .valid = true,
    .re_record=false,
    .block_size=8*1024,
    },
};




SwNorFlashHandle_t SwNorFlashInstance[]={
    {.num=1, .valid=true, },
};


COMPONENT_GET_CNT(SwNorFlash, sw_nor_flash)


