#include "flash_custom_diag.h"

#include <zephyr/drivers/flash.h>

#include "flash_drv.h"
#include "log.h"

bool flash_custom_diag(void) {
    bool res = false;
    if(FlashInstance.dev){
        int ret = 0;
        struct flash_pages_info PageInfo;
        size_t cnt = flash_get_page_count(FlashInstance.dev);
        size_t block_size = flash_get_write_block_size(FlashInstance.dev);
        LOG_INFO(LG_FLASH,"PageCnt:%u", cnt);
        LOG_INFO(LG_FLASH,"BlockSize: %u",block_size);
        const struct flash_parameters*  Node = flash_get_parameters(FlashInstance.dev);
        if (Node) {
        	LOG_INFO(LG_FLASH, "WriteBlockSize: %u",Node->write_block_size);
        	LOG_INFO(LG_FLASH, "EraseValue: %u",Node->erase_value);
        }

        //ret =  flash_get_page_info_by_offs(FlashInstance.dev, off_t offset, &PageInfo);
        //ret =  flash_get_page_info_by_idx(FlashInstance.dev, uint32_t page_index, &PageInfo);
        res = true;
    }
	return res;
}
