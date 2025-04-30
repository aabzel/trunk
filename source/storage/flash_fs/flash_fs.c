#include "flash_fs.h"

//#include "c_defines_generated.h" /*Temp*/
/**
 * NOR Flash Memory manager
 * This file contains implementation of key-val(file) map in Nor-Flash with
 * uniform deterioration of Nor Flash memory
 */
#include "flash_fs_types.h"

#include <string.h>

#ifdef HAS_CRC8
#include "crc8_autosar.h"
#endif
#include "data_types.h"
#include "data_utils.h"
#include "flash_config.h"
#include "flash_fs_config.h"
#include "flash_fs_ll.h"
#include "interrupt_mcal.h"
#include "nvs_config.h"
#include "std_includes.h"
#ifdef HAS_NVS
#include "nvs_drv.h"
#endif
#ifdef HAS_LOG
#include "log.h"
#endif

/* status for a active page */
const uint32_t active_page_token = FLASH_FS_ACTIV_PAGE_DWORD;
#if 0
const Type32Union_t ActivePageToken = {
    .u8[0] =0x00,
    .u8[1] =0x00,
    .u8[2] =0xa5,
    .u8[3] =0x5a,
};
#endif
// static const uint8_t mm_PageStateActive[QWORD_LEN] = {0x00, 0x00, 0xa5, 0x5a};

/*
 *    locate currently active page
 *
 *    @param    page_start - pointer where active page start address will be stored
 *    @param    mm_page_len - pointer where active page length will be stored
 *    @retval   exe status
 */
bool flash_fs_get_active_page(uint32_t* page_start, uint32_t* mm_page_len) {
    bool res = false;
    bool resAr[2] = {false, false};

    /* select active page */
    LOG_DEBUG(FLASH_FS, "GetActivePage");
    uint8_t p = 0;
    for(p = 0; p < 2; p++) {
        resAr[p] = is_flash_addr(FlashFsConfig.page[p].offset);
        if(resAr[p]) {
            LOG_DEBUG(FLASH_FS, "Page%u,0x%x", p, FlashFsConfig.page[p].offset);
        } else {
            LOG_ERROR(FLASH_FS, "Page%u,0x%x,OutOfMem", p, FlashFsConfig.page[p].offset);
        }
    }
#if 0
    res2 = is_flash_addr(FlashFsConfig.page[1].offset);
    if(res2) {
        LOG_DEBUG(FLASH_FS, "Page2 0x%x", FlashFsConfig.page[1].offset);
    } else {
        LOG_ERROR(FLASH_FS, "Page2 0x%x OutOfMem", FlashFsConfig.page[1].offset);
    }
#endif
    if(resAr[0] && resAr[1]) {
        LOG_DEBUG(FLASH_FS, "WhereIs,0x%x token", active_page_token);

        uint32_t first_qword_page2 = 0;
        memcpy((void*)&first_qword_page2, (void*)FlashFsConfig.page[1].offset, QWORD_LEN);
        LOG_DEBUG(FLASH_FS, "first_qword_page2 0x%x", first_qword_page2);

        uint32_t first_qword_page1 = 0;
        memcpy((void*)&first_qword_page1, (void*)FlashFsConfig.page[0].offset, QWORD_LEN);
        LOG_DEBUG(FLASH_FS, "first_qword_page1 0x%x", first_qword_page1);

        if(first_qword_page1 == active_page_token) {
            /* active page is #1 */
            LOG_DEBUG(FLASH_FS, "ActivePage1");
            *page_start = FlashFsConfig.page[0].offset;
            *mm_page_len = FlashFsConfig.page[0].size;
            res = true;
        } else if(first_qword_page2 == active_page_token) {
            /* active page is #2 */
            LOG_DEBUG(FLASH_FS, "ActivePage2");
            *page_start = FlashFsConfig.page[1].offset;
            *mm_page_len = FlashFsConfig.page[1].size;
            res = true;
        } else if(first_qword_page2 == active_page_token && first_qword_page1 == active_page_token) {
            LOG_ERROR(FLASH_FS, "BothActivePageSelectedErr! FirstQwords: Page1: 0x%08x Page2: 0x%08x",
                      first_qword_page1, first_qword_page2);
            res = false;
        } else {
            LOG_WARNING(FLASH_FS, "NoActivePageSelected! FirstQwords: Page1: 0x%08x Page2: 0x%08x", first_qword_page1,
                        first_qword_page2);
            res = false;
        }
    }
    LOG_DEBUG(FLASH_FS, "GetActivePageDone");
    return res;
}

FlashFsPage_t flash_fs_get_active_page_num(void) {
    bool res = false;
    FlashFsPage_t page_num = FLASH_FS_PAGE_UNDEF;
    uint32_t mm_page_len = 0;
    uint32_t page_start = 0;
    res = flash_fs_get_active_page(&page_start, &mm_page_len);
    if(res) {
        page_num = addr2page_num(page_start);
    }
    return page_num;
}

static uint32_t calc_rem_size(uint32_t offset) {
    uint32_t rem_size = 0;
    uint32_t page_start = 0;
    uint32_t cur_len = 0;
    uint32_t mm_page_len = 0;
    bool res = flash_fs_get_active_page(&page_start, &mm_page_len);
    if(res) {
        if(page_start < offset) {
            cur_len = offset - page_start;
            rem_size = mm_page_len - cur_len;
        } else {
            rem_size = 0;
        }
    }
    return rem_size;
}

/**
 *       finds next valid file item
 *
 *    @param    offset - pointer to store active offset in flash
 *    @param    maxOffset - maximum offset that could be in specified storage
 *    @param    len - pointer to store complete
 */
static bool flash_fs_get_next(uint32_t* offset, uint32_t maxOffset, uint32_t* completeLen) {
    LOG_DEBUG(FLASH_FS, "GetNext Offset:0x%08x MaxOffset:0x%08x Len:%u", *offset, maxOffset, completeLen);
    bool res = false;
    FlashFsHeader_t* item = NULL;
    uint32_t rem_size = 0;
    uint32_t cur_offset = *offset;
    /* valid item could not be less that MIN_FILE_LEN bytes */
    for(cur_offset = *offset; cur_offset < (maxOffset - MIN_FILE_LEN); cur_offset++) {
        /* reference item */
        item = (FlashFsHeader_t*)cur_offset;
        if(item->id != (MASK_16BIT ^ item->nid)) {
            continue;
        }
        /*spot id!*/
        rem_size = calc_rem_size((uint32_t)cur_offset);
        /*is data with that length can be fitted in flash page?*/
        if(item->length < rem_size) {
            uint8_t calc_crc8 = crc8_autosar_calc((void*)(cur_offset + ITEM_HEADER_SZ), item->length);
            if(calc_crc8 != item->crc8) {
                continue;
            } else {
                /*spot data file valid item */
                *offset = cur_offset;
                *completeLen = item->length + sizeof(FlashFsHeader_t);
            }
        } else {
            continue;
        }
        res = true;
        break;
    }
    return res;
}

/**
 * count files in Flash File system
 *
 */
uint32_t flash_fs_cnt_files(uint32_t start_page_addr, uint32_t page_len, uint32_t* spare_cnt) {
    FlashFsHeader_t* item = NULL;
    uint32_t file_cnt = 0;
    bool res = is_flash_addr(start_page_addr);
    if(res) {
        uint32_t rem_size = 0;
        res = false;
        uint32_t cur_offset = start_page_addr;
        uint8_t* byte_p = NULL;
        *spare_cnt = 0;
        for(cur_offset = start_page_addr; cur_offset <= (start_page_addr + page_len - MIN_FILE_LEN); cur_offset++) {
            /* reference item */
            res = true;
            byte_p = (uint8_t*)cur_offset;
            if(0xFF == *byte_p) {
                (*spare_cnt)++;
            }
            item = (FlashFsHeader_t*)cur_offset;

            if(NULL == item) {
                res = false;
            }

            if(res) {
                if(item->id == (MASK_16BIT ^ item->nid)) {
                    res = true;
                    LOG_DEBUG(FLASH_FS, "SpotId %u 0x%x", item->id, item->id);
                } else {
                    res = false;
                }
            }

            if(res) {
                rem_size = start_page_addr + page_len - cur_offset;
                /*is data with that length can be fitted in flash page?*/
                if((item->length < rem_size) && (0 < item->length)) {
                    uint8_t calc_crc8 = crc8_autosar_calc((void*)(cur_offset + ITEM_HEADER_SZ), item->length);
                    if(calc_crc8 == item->crc8) {
                        /*spot data file valid item */
                        LOG_DEBUG(FLASH_FS, "Crc8 for Id %u 0x%x ok CRC8 0x%x", item->id, item->id, calc_crc8);
                        file_cnt++;
                    } else {
                        LOG_DEBUG(FLASH_FS, "Crc8 for Id %u 0x%x Err", item->id, item->id);
                    }
                }
            }
        }
    }

    return file_cnt;
}

/**
 *        search for a specified item
 *
 *     @param    page_start - start address of the page
 *     @param    mm_page_len - number of bytes within page
 *     @param    file_id - id that should be found, MM_INVALID_ID if we try to find empty space
 *     @param    item - pointer to item that was located
 *     @param    empty - poitner to first empty item
 *     @param    rem_space - pointer where remaining space will be placed
 *     @retval
 */
static bool flash_fs_find_field(uint16_t file_id, FlashFsHeader_t** item, FlashFsHeader_t** empty,
                                uint32_t* rem_space) {
    LOG_DEBUG(FLASH_FS, "FindField ID:%u", file_id);
    bool res = -1;
    uint32_t completeLen = 0;
    uint32_t prev_item_offset = 0xFFFFFFFF;
#ifdef HAS_FLASH_FS_WRITE
    FlashFsHeader_t* prevItem = NULL;
#endif
    uint32_t offset = 0;
    /* select active page */
    uint32_t mm_page_len = 0;
    uint32_t page_start = 0;
    res = flash_fs_get_active_page(&page_start, &mm_page_len);
    if(false == res) {
        return false;
    }

    /* we should store previous variable and active one */
    prev_item_offset = 0xFFFFFFFF;
    offset = page_start + QWORD_LEN;
    /* look through whole storage looking for specified item */
    while(flash_fs_get_next(&offset, page_start + mm_page_len, &completeLen)) {
        /* reference item */
        (*item) = (FlashFsHeader_t*)offset;

        /* if field's file_id match to search one, proceed it */
        if(((*item)->id == file_id) && ((*item)->id == (MASK_16BIT ^ (*item)->nid))) {
            /* if something similar was already found, we should invalidate it first */
            if(0xFFFFFFFF != prev_item_offset) {
                /* to invalidate prev item just clear its id */
                res = false;
#ifdef HAS_FLASH_FS_WRITE
                prevItem = (FlashFsHeader_t*)prev_item_offset;
                res = flash_fs_zero(prev_item_offset, sizeof(FlashFsHeader_t) + prevItem->length);
                if(false == res) {
                    return false;
                }
#endif
            }
            /* store found offset */
            prev_item_offset = offset;
        }

        /* shift offset and try again */
        offset += completeLen;
    }

    /* calculate remaining space */
    *rem_space = mm_page_len - (offset - page_start);

    /* put pointer to first empty item */
    *empty = (FlashFsHeader_t*)offset;
    /* put pointer to located item */
    if(0xFFFFFFFF != prev_item_offset) {
        (*item) = (FlashFsHeader_t*)prev_item_offset;
        return true;
    } else {
        (*item) = NULL;
        return false;
    }
}

/**
 *        returns number of bytes remained within active page
 *
 *     This function is used to select moment of time when page swap (long operation) is most suitable
 *
 *     @return    number of bytes remained within active page
 *    @note    user must keep in mind that not all available memory could be used, memory manager use 8 bytes for
 *            every write attempt
 */
uint32_t flash_fs_get_remaining_space(void) {
    FlashFsHeader_t *item = NULL, *empty = NULL;
    uint32_t rem_space = 0;

    /* get all info from private API */
    if(flash_fs_find_field(MM_INVALID_ID, &item, &empty, &rem_space)) {
        /* this is not a normal case - we have error or invalid field present, no memory available */
        return 0xFFFFFFFF;
    }

    /* return remaining free space */
    return rem_space;
}

double flash_fs_get_remaining_space_percent(void) {
    double rem_space_present = 100.0;
    uint32_t rem_space = flash_fs_get_remaining_space();

    FlashFsPage_t page_num = flash_fs_get_active_page_num();
    LOG_DEBUG(FLASH_FS, "CurPage %u", page_num);
    uint32_t page_size = flash_fs_get_page_size(page_num);
    LOG_DEBUG(FLASH_FS, "PageSize %u Byte", page_size);
    rem_space_present = 100.0 * ((double)rem_space) / ((double)page_size);
    LOG_DEBUG(FLASH_FS, "RemSize %6.2f %%", rem_space_present);
    return rem_space_present;
}

#ifdef HAS_FLASH_FS_WRITE
/*
 *  flash memory is not mapped yet, remap it
 */
bool flash_fs_format(void) {
    bool res = false;
    LOG_WARNING(FLASH_FS, "Format");
    /* invalidate second page as passive */
    res = flash_fs_zero(FlashFsConfig.page[1].offset, QWORD_LEN);
    if(res) {
        /* erase first page */
        res = nvs_erase(FlashFsConfig.page[0].offset, FlashFsConfig.page[0].size);
    }

    if(res) {
        /* indicate first page as active */
        Type32Union_t Val = {
            .u32 = FLASH_FS_ACTIV_PAGE_DWORD,
        };
        res = flash_fs_write(FlashFsConfig.page[0].offset, (uint8_t*)Val.u8, sizeof(active_page_token));
    }
    if(false == res) {
    }
    return res;
}
#endif

#ifdef HAS_FLASH_FS_WRITE
static bool flash_fs_update_toggle_cnt(void) {
    bool res = false;
    LOG_WARNING(FLASH_FS, "UpdateToggleCnt");
    FlashFs.toggle_cnt = 0;
    uint16_t read_len = 0;
    res = flash_fs_get(PAR_ID_FLASH_FS_TOGGLE_CNT, (uint8_t*)&FlashFs.toggle_cnt, 4, &read_len);
    if(res) {
        LOG_DEBUG(FLASH_FS, "CurToggleCnt: %u", FlashFs.toggle_cnt);
        FlashFs.toggle_cnt++;
        res = flash_fs_set(PAR_ID_FLASH_FS_TOGGLE_CNT, (uint8_t*)&FlashFs.toggle_cnt, 4);
    } else {
        LOG_WARNING(FLASH_FS, "LackOkToggleCnt. InitValiable");
        FlashFs.toggle_cnt = 1;
        res = flash_fs_set(PAR_ID_FLASH_FS_TOGGLE_CNT, (uint8_t*)&FlashFs.toggle_cnt, 4);
    }
    return res;
}
#endif

#ifdef HAS_FLASH_FS_WRITE
/*
 *  switch used memory manager page and copy all valid data to the next one
 */
bool flash_fs_turn_page(void) {
    bool res = false;
    LOG_WARNING(FLASH_FS, "TurnPage");
    // interrupt_control_all(false);
    uint32_t completeLen = 0;
    uint32_t ff_page_active_start = 0, mmPageActiveLen = 0;
    uint32_t mmPagePassiveStart = 0;
    uint32_t offsetActive = 0, offsetPassive = 0;
    /* select active page */
    res = flash_fs_get_active_page(&ff_page_active_start, &mmPageActiveLen);
    if(false == res) {
        return false;
    }

    /* erase passive page and get pointer to it */
    if(FlashFsConfig.page[0].offset == ff_page_active_start) {
        /* clear page # 2 */
        res = nvs_erase(FlashFsConfig.page[1].offset, FlashFsConfig.page[1].size);
        if(false == res) {
            return false;
        }
        mmPagePassiveStart = FlashFsConfig.page[1].offset;
    } else if(FlashFsConfig.page[1].offset == ff_page_active_start) {
        /* clear page # 1 */
        res = nvs_erase(FlashFsConfig.page[0].offset, FlashFsConfig.page[0].size);
        if(false == res) {
            return false;
        }
        mmPagePassiveStart = FlashFsConfig.page[0].offset;
    } else {
        return false;
    }
    if(false == res) {
        return res;
    }

    /* we should store previous variable and active one */
    offsetActive = ff_page_active_start + QWORD_LEN;
    offsetPassive = mmPagePassiveStart + QWORD_LEN;
    /* look through whole storage looking for specified item */
    while(flash_fs_get_next(&offsetActive, ff_page_active_start + mmPageActiveLen, &completeLen)) {
        /* copy all valid items to the passive page */
        res = flash_fs_write(offsetPassive, (uint8_t*)offsetActive, completeLen);
        if(false == res) {
            return false;
        }
        /* shift offsets and look for next item */
        offsetActive += completeLen;
        offsetPassive += completeLen;
    }

    /* indicate passive page as active */
    Type32Union_t Val = {
        .u32 = FLASH_FS_ACTIV_PAGE_DWORD,
    };
    res = flash_fs_write(mmPagePassiveStart, Val.u8, sizeof(active_page_token));
    if(false == res) {
        return false;
    }
    /* indicate active page as passive */
    res = flash_fs_zero(ff_page_active_start, QWORD_LEN);
    if(false == res) {
        return false;
    }

    res = flash_fs_update_toggle_cnt();

    // interrupt_control_all(true);
    return res;
}
#endif
/**
 *       Toggle Not Flash page in case of a lack of spare space
 *     @note    call flash_fs_maintain in spare time.
 *     @retval status
 */

bool flash_fs_maintain(void) {
    // FlashFsHeader_t *prevItem = NULL, *empty = NULL;
    bool res = false;
    // uint32_t rem_space = 100 * MIN_FILE_LEN;
    /* try to find previous file of the same variable */
    // res = flash_fs_find_field(MM_INVALID_ID, &prevItem, &empty, &rem_space);
    double rem = flash_fs_get_remaining_space_percent();
    LOG_DEBUG(FLASH_FS, "RemSpace %f %%", rem);
    res = true;
    if(rem < 5.0) {
        /* we have not enough space to fit minimal payload file, turn the page */
        LOG_WARNING(FLASH_FS, "TogglePages");
        res = false;
#ifdef HAS_FLASH_FS_WRITE
        res = flash_fs_turn_page(); /*Long procedure*/
        if(res) {
            LOG_INFO(FLASH_FS, "ToggleOk");
        } else {
            LOG_ERROR(FLASH_FS, "ToggleErr");
        }
#endif
    }

    return res;
}

bool flash_fs_proc(void) {
    bool res = false;

    uint32_t spare_cnt = 0;
    uint32_t i = 0;
    for(i = 0; i < 2; i++) {
        spare_cnt = 0;
        FlashFs.page[i].files_cnt =
            flash_fs_cnt_files(FlashFsConfig.page[i].offset, FlashFsConfig.page[i].size, &spare_cnt);
        FlashFs.page[i].usage_pre_cent = 100 - ((100U * spare_cnt) / FlashFsConfig.page[i].size);
    }
    res = flash_fs_maintain();

    return res;
}

#ifdef HAS_FLASH_FS_WRITE
/**
 *       set new file to the variable with specified ID
 *
 *     @note    operation from user point of view is atomic - if something goes wrong during memory write,
 *             old file will be stored in memory, if old file doesn't exist - new variable will not be created
 *
 *     @param    data_id - data identifier to be written
 *             user could operate with data_id '0000' - '7FFF', other are reserved to the system
 *     @param    new_file - pointer to the new file of the variable
 *     @param    new_file_len - number of bytes within new_file
 *     @retval ok/err
 */
bool flash_fs_set(uint16_t data_id, const void* const new_file, uint16_t new_file_len) {
    LOG_DEBUG(FLASH_FS, "Set ID:%u Len:%u", data_id, new_file_len);
    FlashFsHeader_t *prevItem = NULL, *empty = NULL;
    FlashFsHeader_t newHeader = {.id = 0, .nid = 0, .length = 0, .crc8 = 0};
    bool res = 0;
    uint32_t rem_space = 0;
    uint32_t completeLen = 0;

    /* check input parameters */
    if((MM_INVALID_ID == data_id) || (NULL == new_file) || (0 == new_file_len)) {
        LOG_ERROR(FLASH_FS, "ArgErr");
        return false;
    }

    /* try to find previous file of the same variable */
    res = flash_fs_find_field(data_id, &prevItem, &empty, &rem_space);
    if(res) {
        LOG_DEBUG(FLASH_FS, "PrevFile ID:%u 0x%08p", data_id, prevItem);
        /* file was found - ensure that new file is not same to the previous one */
        if(prevItem->length == new_file_len) {
            if(0 == memcmp(new_file, (uint8_t*)prevItem + sizeof(FlashFsHeader_t), new_file_len)) {
                /* file is the same, we should not change anything */
                return true;
            }
        }
    }

    /* calculate complete length of the new item */
    completeLen = new_file_len;
    /* ensure that we have enough space within selected page to fit new file
     * variable item stores pointer to first empty item */
    if(rem_space < completeLen) {
        /* we have not enough space to fit new file, turn the page */
#ifdef FLASH_FS_AUTO_TOGGLE_PAGE
        res = flash_fs_turn_page();
        if(false == res) {
            LOG_ERROR(FLASH_FS, "PageTurnErr");
            return false;
        }

        /* refresh information about previous item, first free item and empty space */
        res = flash_fs_find_field(data_id, &prevItem, &empty, &rem_space);
        if(false == res) {
            return false;
        }

        /* ensure that now we have enough space */
        if(rem_space < completeLen) {
            LOG_ERROR(FLASH_FS, "SpaceErr RemSpace:%u,CompleetLen:%u", rem_space, completeLen);
            return false;
        }
#else
        LOG_ERROR(FLASH_FS, "SpaceErr Rem:%u com:%u", rem_space, completeLen);
        return false;
#endif /*AUTO_TOGGLE_PAGE*/
    }

    /* here we are sure that we should refresh file and have enough space to do that,
     * variable prevItem stores pointer to previous file of the item and item stores pointer to empty space */

    /* prepare header */
    newHeader.id = data_id;
    newHeader.nid = MASK_16BIT ^ data_id;
    newHeader.length = new_file_len;
    newHeader.crc8 = crc8_autosar_calc(new_file, new_file_len);
    /* write Header*/
    res = flash_fs_write((uint32_t)empty, (uint8_t*)&newHeader, sizeof(newHeader));
    if(false == res) {
        LOG_ERROR(FLASH_FS, "FlashWrHeaderErr");
        return false;
    }

    /*  write full data blocks */
    if(false == flash_fs_write((uint32_t)empty + sizeof(FlashFsHeader_t), (uint8_t*)new_file, new_file_len)) {
        LOG_ERROR(FLASH_FS, "FlashWrDataErr");
        return false;
    }

    /* invalidate previous identifier (if present) */
    if(prevItem != NULL) {
        if(false == flash_fs_zero((uint32_t)prevItem, sizeof(FlashFsHeader_t))) {
            LOG_ERROR(FLASH_FS, "FlashZeroErr");
            return false;
        }
    }

    return true;
}
#endif

bool flash_fs_set_lazy(uint16_t data_id, const void* const new_file, uint16_t new_file_len) {
    bool res = false;
    return res;
}

/**
 *       get address of the specified variable, stored within memory
 *
 *    @param    data_id - data identifier to be located
 *    @param    file_address - pointer where location of the variable will be written
 *    @param    file_len - pointer to variable that will contain length of the variable

 */
bool flash_fs_get_address(uint16_t data_id, uint8_t** file_address, uint16_t* file_len) {
    FlashFsHeader_t *item = NULL, *empty = NULL;
    bool res = false;
    uint32_t rem_space = 0;

    /* ensure that input parameters are valid */
    if(data_id == MM_INVALID_ID || file_address == NULL || file_len == NULL) {
        res = false;
    } else {
        res = true;
    }

    if(res) {
        /* find field */
        res = flash_fs_find_field(data_id, &item, &empty, &rem_space);
    }

    if(res) {
        /* return parameters */
        *file_address = (uint8_t*)item + sizeof(FlashFsHeader_t);
        *file_len = item->length;
    }
    return res;
}

/**
 *       get file of the specified variable
 *
 *    @param    data_id - data identifier to be read
 *    @param    file - pointer where data should be stored
 *    @param    size - maximum number of bytes that could be stored within file
 *    @param    file_len - actual number of bytes stored within file

 */
bool flash_fs_get(uint16_t data_id, void* const file, uint16_t size, uint16_t* file_len) {
    LOG_DEBUG(FLASH_FS, "Get ID:%u MaxLen:%u", data_id, size);
    FlashFsHeader_t *item = NULL, *empty = NULL;
    bool res = false;
    uint32_t rem_space = 0;

    /* ensure that input parameters are valid */
    if((MM_INVALID_ID == data_id) || (NULL == file) || (NULL == file_len) || (0 == size)) {
        res = false;
    } else {
        res = true;
    }

    if(res) {
        /* find field */
        res = flash_fs_find_field(data_id, &item, &empty, &rem_space);
    }

    if(res) {
        /* ensure that we have enough space in output buffer to hold new file */
        if(size < item->length) {
            res = false;
        }
    }
    if(res) {
        /* copy data */
        memcpy(file, (uint8_t*)item + sizeof(FlashFsHeader_t), item->length);
        /* return parameters */
        *file_len = item->length;
    }
    return res;
}

#ifdef HAS_FLASH_FS_WRITE
/**
 *        invalidate (erase) specified variable, all references to specified variable will be removed
 *
 *     @note    this function does not erase actual file of the variable
 *             if user need to do that (if file is very sensitive), double page swap MUST be executed
 *
 *     @param    data_id - data identifier to be invalidated
 *     @retval
 */
bool flash_fs_invalidate(uint16_t data_id) {
    bool res = false;
    FlashFsHeader_t *item = NULL, *empty = NULL;
    uint32_t rem_space = 0;
    /* find field */
    res = flash_fs_find_field(data_id, &item, &empty, &rem_space);

    if(res) {
        /* invalidate field */
        res = flash_fs_zero((uint32_t)item, sizeof(FlashFsHeader_t) + item->length);
        /*TODO measure duration*/
    }

    return res;
}
#endif

#ifdef HAS_FLASH_FS_WRITE
/**
 *       flash memory is not mapped yet, remap it
 */
bool flash_fs_erase(void) {
    bool res = true;
    /* invalidate second page as passive */
    res = nvs_erase(FlashFsConfig.page[0].offset, FlashFsConfig.page[0].size) && res;
    res = nvs_erase(FlashFsConfig.page[1].offset, FlashFsConfig.page[1].size) && res;
    return res;
}
#endif

bool flash_fs_init(void) {
    bool res = false;
    LOG_WARNING(FLASH_FS, "Init");
    set_log_level(FLASH_FS, LOG_LEVEL_INFO);

    uint8_t i = 0;
    for(i = 0; i < 2; i++) {
        LOG_INFO(FLASH_FS, "Page%u Start:0x%08x", i + 1, FlashFsConfig.page[i].offset);
        LOG_INFO(FLASH_FS, "Page%u Size: %u Byte %u kByte", i + 1, FlashFsConfig.page[i].size,
                 FlashFsConfig.page[i].size / 1024);
        res = is_flash_addr(FlashFsConfig.page[i].offset);
        if(false == res) {
            LOG_ERROR(FLASH_FS, "WrongPage%u StartAddr: 0x%08x", i + 1, FlashFsConfig.page[i].offset);
        }
    }

    uint32_t page_start = 0;
    uint32_t mm_page_len = 0;
    res = flash_fs_get_active_page(&page_start, &mm_page_len);
    if(false == res) {
        LOG_WARNING(FLASH_FS, "format Flash FS");
#ifdef HAS_FLASH_FS_WRITE
        res = flash_fs_format();
#endif
    } else {
        LOG_INFO(FLASH_FS, "start: 0x%08x len %u", page_start, mm_page_len);
    }
    uint16_t reboot_cnt = 0;
    uint16_t file_len = 0;
    res = flash_fs_get(PAR_ID_REBOOT_CNT, (uint8_t*)&reboot_cnt, sizeof(reboot_cnt), &file_len);
    if(res) {
        reboot_cnt++;
        LOG_INFO(FLASH_FS, "reboot cnt: %u", reboot_cnt);
        res = false;
#ifdef HAS_FLASH_FS_WRITE
        res = flash_fs_set(PAR_ID_REBOOT_CNT, (uint8_t*)&reboot_cnt, sizeof(reboot_cnt));
#endif
        if(false == res) {
            LOG_ERROR(FLASH_FS, "RebootCntSetErr");
        }
    } else {
        LOG_WARNING(FLASH_FS, "lack of reboot counter");
        reboot_cnt = 0;
        res = false;
#ifdef HAS_FLASH_FS_WRITE
        res = flash_fs_set(PAR_ID_REBOOT_CNT, (uint8_t*)&reboot_cnt, sizeof(reboot_cnt));
#endif
        if(false == res) {
            LOG_WARNING(FLASH_FS, "ResetRebootCounter");
        }
    }
    return res;
}

uint32_t flash_fs_get_page_base_addr(uint8_t page_num) {
    uint32_t page_base_addr = 0;
    if(1 == page_num) {
        page_base_addr = FlashFsConfig.page[0].offset;
    } else if(2 == page_num) {
        page_base_addr = FlashFsConfig.page[1].offset;
    } else {
        page_base_addr = 0;
    }
    return page_base_addr;
}

uint32_t flash_fs_get_page_size(uint8_t page_num) {
    uint32_t page_size = 0;
    if(1 == page_num) {
        page_size = FlashFsConfig.page[0].size;
    } else if(2 == page_num) {
        page_size = FlashFsConfig.page[1].size;
    } else {
        page_size = 0;
    }
    return page_size;
}

FlashFsPage_t addr2page_num(uint32_t page_start) {
    FlashFsPage_t page_num = FLASH_FS_PAGE_UNDEF;
    if(page_start == FlashFsConfig.page[0].offset) {
        page_num = FLASH_FS_PAGE_1;
    } else if(page_start == FlashFsConfig.page[1].offset) {
        page_num = FLASH_FS_PAGE_2;
    } else {
        page_num = 0x55;
    }
    return page_num;
}

bool is_flash_fs_addr(uint32_t addr) {
    bool res = false;
    res = is_nvs_addr(addr);
    return res;
}

bool flash_fs_is_active(uint8_t page_num) {
    bool res = false;
    uint32_t page_base_addr = flash_fs_get_page_base_addr(page_num);
    uint32_t page_start = 0;
    uint32_t mm_page_len = 0;
    res = flash_fs_get_active_page(&page_start, &mm_page_len);
    if(res) {
        if(page_base_addr == page_start) {
            res = true;
        } else {
            res = false;
        }
    }
    return res;
}
