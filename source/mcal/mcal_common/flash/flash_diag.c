#include "flash_diag.h"

#include <stdio.h>
#include <string.h>

#include "array_diag.h"
#include "common_diag.h"
#include "debug_info.h"
#include "flash_mcal.h"
#include "float_diag.h"
#include "log.h"
#include "microcontroller_const.h"
#include "shared_array.h"
#include "table_utils.h"
#ifdef HAS_ARRAY_DIAG
#include "array_diag.h"
#endif
#ifdef HAS_LOG_UTILS
#include "writer_config.h"
#endif
#ifdef HAS_FLASH_CUSTOM
#include "flash_custom.h"
#endif

const char* MemContentToStr(const MemContent_t code) {
    const char* name = "?";
    switch(code) {
    case MEM_CONTENT_BOOTLADER:
        name = "Bootloader";
        break;
    case MEM_CONTENT_GENERIC_APP:
        name = "GenericApp";
        break;
    case MEM_CONTENT_GENERIC:
        name = "Generic";
        break;
    case MEM_CONTENT_GENERIC_NET:
        name = "GenericNet";
        break;
    case MEM_CONTENT_MBR:
        name = "MBR";
        break;
    case MEM_CONTENT_FLASH_FS_PAGE1:
        name = "FlashFsPage1";
        break;
    case MEM_CONTENT_FLASH_FS_PAGE2:
        name = "FlashFsPage2";
        break;
    default:
        break;
    }
    return name;
}

bool flash_diag_usage(uint32_t flash_start, uint32_t flash_size, uint32_t chunk_size) {
    bool res = false;
    LOG_INFO(LG_FLASH, "Explore:Start:0x%x,Size:%u byte,Chunk:%u byte", flash_start, flash_size, chunk_size);
    uint32_t chunk_cnt = flash_size / chunk_size;
    LOG_INFO(LG_FLASH, "ChunkCnt:%u ", chunk_cnt);
    const table_col_t cols[] = {
        {5, "No"}, {12, "Start"}, {8, "Size"}, {8, "Busy"}, {8, "Usage"}, {8, "Total"},
    };
    LOG_INFO(LG_FLASH, "number of parts %u PartSize %u byte TotalSize %u byte", chunk_cnt, chunk_size, flash_size);
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t num = 0;

    uint32_t start = 0;
    start = flash_start;
    uint32_t total = 0;
    uint32_t i = 0;
    for(i = 0; i < chunk_cnt; i++) {
        uint32_t busy = 0;
        uint32_t spare = 0;
        total += chunk_size;
        float usage_pec = 0.0;
        bool scan_res = flash_scan((uint8_t*)start, chunk_size, &usage_pec, &spare, &busy, 0xFF);

        char tempo[120] = {0};
        strcpy(tempo, TSEP);
        snprintf(tempo, sizeof(tempo), "%s %3u " TSEP, tempo, num);
        snprintf(tempo, sizeof(tempo), "%s 0x%08X " TSEP, tempo, start);
        snprintf(tempo, sizeof(tempo), "%s %6u " TSEP, tempo, chunk_size);

        if(scan_res) {
            snprintf(tempo, sizeof(tempo), "%s %6u " TSEP, tempo, busy);
            snprintf(tempo, sizeof(tempo), "%s %6s " TSEP, tempo, FloatToStr(usage_pec, 2));
        } else {
            LOG_ERROR(LG_FLASH, "ScanErr");
        }
        snprintf(tempo, sizeof(tempo), "%s %6u " TSEP, tempo, total / 1024);

        cli_printf("%s" CRLF, tempo);
        num++;
        start += chunk_size;
        res = true;
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

bool FlashDiagNode(const FlashHandle_t* const Node) {
    bool res = false;
    if(Node) {
        LOG_INFO(LG_FLASH, "Start 0x%x,TotalSize %u,PageSize %u,PageCnt %u,Byte CRC16 0x%x", Node->start, Node->size,
                 Node->page_size, Node->page_cnt, Node->crc16);
        res = true;
    }
    return res;
}

bool flash_region_print(uint32_t addr, uint32_t size) {
    bool res = false;
#ifdef HAS_ARRAY_DIAG
    uint8_t* buff = (uint8_t*)addr;
    res = array_print_hex(buff, size);
    cli_printf(CRLF);
#endif
    return res;
}

const char* FlashFsmOperationToStr(const FlashOperation_t operation) {
    char* name = "?";
    switch(operation) {
    case FLASH_OPERATION_PROGRAM_BYTE:
        name = "PrgByte";
        break;
    case FLASH_OPERATION_PROGRAM_WORD:
        name = "PrgWord";
        break;
    case FLASH_OPERATION_PROGRAM_QWORD:
        name = "PrgQword";
        break;
    case FLASH_OPERATION_ERRASE:
        name = "Erase";
        break;
    case FLASH_OPERATION_ERRASE_SECTOR:
        name = "EraseSector";
        break;
    case FLASH_OPERATION_ERRASE_BLOCK:
        name = "EraseBlock";
        break;
    case FLASH_OPERATION_ERRASE_SYS_DATA_AREA:
        name = "EraseSda";
        break;
    case FLASH_OPERATION_ERRASE_MASS:
        name = "EraseMass";
        break;
    default:
        break;
    }
    return name;
}

const char* FlashFsmStateToStr(const FlashState_t state) {
    char* name = "?";
    switch(state) {
    case FLASH_STATE_IDLE:
        name = "Idle";
        break;
    case FLASH_STATE_WAIT_END_OF_OPERATION:
        name = "WaitOpEnd";
        break;
    case FLASH_STATE_WAIT_END_OF_WRITE:
        name = "WaitEofWr";
        break;
    case FLASH_STATE_WAIT_END_OF_ERASE:
        name = "WaitEofEra";
        break;
    default:
        break;
    }
    return name;
}

const char* FlashFsmInputToStr(const FlashInput_t input) {
    char* name = "?";
    switch(input) {
    case FLASH_INPUT_NONE:
        name = "None";
        break;
    case FLASH_INPUT_OPERATION_BUSY:
        name = "Busy";
        break;
    case FLASH_INPUT_NO_OPERATION:
        name = "NoOpe";
        break;
    case FLASH_INPUT_PROGRAMMING_ERROR:
        name = "PrgErr";
        break;
    case FLASH_INPUT_ERASE_PROGRAM_PROTECTION_ERROR:
        name = "ErasePrgProtErr";
        break;
    case FLASH_INPUT_OPERATION_DONE:
        name = "OpDone";
        break;
    case FLASH_INPUT_TIMEOUT:
        name = "TineOut";
        break;
    default:
        break;
    }
    return name;
}

const char* FlashConfigToStr(const FlashConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sStart:0x%x,", text, Config->start);
        snprintf(text, sizeof(text), "%sSize:%u Byte,", text, Config->size);
        snprintf(text, sizeof(text), "%sPageSize:%u", text, Config->page_size);
        snprintf(text, sizeof(text), "%sINT:%s,", text, OnOffToStr(Config->interrupt_on));
        snprintf(text, sizeof(text), "%sEqSector:%s,", text, OnOffToStr(Config->is_equal_sectors));
        snprintf(text, sizeof(text), "%sPages:%u", text, Config->page_cnt);
        snprintf(text, sizeof(text), "%sApp:0x%x,", text, Config->app_start);
        snprintf(text, sizeof(text), "%sBoot:0x%x,", text, Config->boot_start);
        snprintf(text, sizeof(text), "%sPageArray:%p,", text, Config->PageArray);
    }
    return text;
}

const char* FlashNodeToStr(const FlashHandle_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sOp:%s,", text, FlashFsmOperationToStr(Node->operation));
        snprintf(text, sizeof(text), "%sSt:%s,", text, FlashFsmStateToStr(Node->state));
        snprintf(text, sizeof(text), "%sIn:%s,", text, FlashFsmInputToStr(Node->input));
        snprintf(text, sizeof(text), "%sDiff:%u ms,", text, Node->diff_ms);
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin_cnt);
        snprintf(text, sizeof(text), "%sWrAddr:0x%08x", text, Node->wr_flash_addr);
        snprintf(text, sizeof(text), "%sWrByte:0x%02x", text, Node->wr_byte);
    }
    return text;
}

bool flash_scan_diag(uint32_t mem_start, uint32_t mem_size) {
    bool res = false;
    float usage_pec = 0.0f;
    uint32_t spare = 0;
    uint32_t busy = 0;
    LOG_INFO(LG_FLASH, "Start:0x%08x,Size:%u Byte", mem_start, mem_size);
    // res = mem_scan((uint8_t*)mem_start, mem_size, &usage_pec, &spare, &busy);
    log_res(LG_FLASH, res, "Scan");
    if(res) {
        LOG_INFO(LG_FLASH, "usage:[%s] %%", FloatToStr(usage_pec, 3));
        LOG_INFO(LG_FLASH, "spare:%u Bytes %u kBytes", spare, spare / 1024);
        LOG_INFO(LG_FLASH, "busy :%u Bytes %u kBytes", busy, busy / 1024);
    }

    return res;
}

bool flash_custom_diag(void) {
    bool res = false;
#ifdef HAS_FC7300X
    LOG_INFO(LG_FLASH, "PFLASH_BANK_SIZE:%u Bytes", PFLASH_BANK_SIZE);

    const FlashInfo_t* Info = FlashGetInfo(1);
    if(Info) {
        LOG_INFO(LG_FLASH, "Info:[%s]", FlashInfoToStr(Info));
    }
#endif

#ifdef HAS_FLASH_CUSTOM
    const FlashConfig_t* Config = FlashGetConfig(1);
    if(Config) {
        LOG_INFO(LG_FLASH, "Config:[%s]", FlashConfigToStr(Config));
    }
#endif

    return res;
}
