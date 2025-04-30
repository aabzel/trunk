#include "eeprom_diag.h"

#include <stdio.h>
#include <string.h>

#include "common_diag.h"
#include "debug_info.h"
#include "eeprom_mcal.h"
#include "log.h"
#include "microcontroller_const.h"
#include "shared_array.h"
#include "table_utils.h"
#ifdef HAS_LOG_UTILS
#include "writer_config.h"
#endif
#ifdef HAS_ARRAY_DIAG
#include "array_diag.h"
#endif

bool eeprom_diag_usage(uint32_t chunk_size) {
    bool res = false;
    const table_col_t cols[] = {{5, "No"}, {12, "start"}, {8, "size"}, {8, "busy"}, {8, "usage"}, {8, "total"}};
    uint32_t cnt = ROM_SIZE / chunk_size;
    LOG_INFO(EEPROM, "number of parts %u PartSize %u byte TotalSize %u byte", cnt, chunk_size, ROM_SIZE);
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t spare = 0, i = 0;
    uint32_t busy = 0, num = 0;
    uint32_t total = 0;
    uint32_t start = ROM_START;
    float usage_pec = 0.0;
    char temp_str[120];

    for(i = 0; i < cnt; i++) {
        strcpy(temp_str, TSEP);

        snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str, (unsigned int)start);
        snprintf(temp_str, sizeof(temp_str), "%s %6u " TSEP, temp_str, (unsigned int)chunk_size);
        total += chunk_size;
        busy = 0;
        spare = 0;
        usage_pec = 0.0;
        res = eeprom_scan((uint8_t*)start, chunk_size, &usage_pec, &spare, &busy);
        if(res) {
            snprintf(temp_str, sizeof(temp_str), "%s %6u " TSEP, temp_str, (unsigned int)busy);
            snprintf(temp_str, sizeof(temp_str), "%s %6.2f " TSEP, temp_str, usage_pec);
        } else {
            LOG_ERROR(EEPROM, "ScanErr");
        }
        snprintf(temp_str, sizeof(temp_str), "%s %6u " TSEP, temp_str, (unsigned int)total / 1024);

        cli_printf(TSEP " %3u ", num);
        cli_printf("%s" CRLF, temp_str);
        num++;
        start += chunk_size;
        res = true;
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

bool EepromDiagNode(const EepromHandle_t* const Node) {
    bool res = false;
    if(Node) {
        LOG_INFO(EEPROM, "Start 0x%x,TotalSize %u,PageSize %u,PageCnt %u,Byte CRC16 0x%x", Node->start, Node->size);
        res = true;
    }
    return res;
}

bool eeprom_region_print(uint32_t addr, uint32_t size) {
    bool res = false;
#ifdef HAS_ARRAY_DIAG
    uint8_t* buff = (uint8_t*)addr;
    res = print_hex(buff, size);
    cli_printf(CRLF);
#endif
    return res;
}

const char* EepromFsmOperationToStr(const EepromOperation_t operation) {
    char* name = "?";
    switch(operation) {
    case EEPROM_OPERATION_PROGRAM_BYTE:
        name = "PrgByte";
        break;
    case EEPROM_OPERATION_PROGRAM_WORD:
        name = "PrgWord";
        break;
    case EEPROM_OPERATION_PROGRAM_QWORD:
        name = "PrgQword";
        break;
    case EEPROM_OPERATION_ERRASE:
        name = "Erase";
        break;
    default:
        break;
    }
    return name;
}

const char* EepromFsmStateToStr(const EepromState_t state) {
    char* name = "?";
    switch(state) {
    case EEPROM_STATE_IDLE:
        name = "Idle";
        break;
    case EEPROM_STATE_WAIT_END_OF_OPERATION:
        name = "WaitOpEnd";
        break;
    case EEPROM_STATE_WAIT_END_OF_WRITE:
        name = "WaitEofWr";
        break;
    case EEPROM_STATE_WAIT_END_OF_ERASE:
        name = "WaitEofEra";
        break;
    default:
        break;
    }
    return name;
}

const char* EepromFsmInputToStr(const EepromInput_t input) {
    char* name = "?";
    switch(input) {
    case EEPROM_INPUT_NONE:
        name = "None";
        break;
    case EEPROM_INPUT_OPERATION_BUSY:
        name = "Busy";
        break;
    case EEPROM_INPUT_NO_OPERATION:
        name = "NoOpe";
        break;
    case EEPROM_INPUT_PROGRAMMING_ERROR:
        name = "PrgErr";
        break;
    case EEPROM_INPUT_ERASE_PROGRAM_PROTECTION_ERROR:
        name = "ErasePrgProtErr";
        break;
    case EEPROM_INPUT_OPERATION_DONE:
        name = "OpDone";
        break;
    case EEPROM_INPUT_TIMEOUT:
        name = "TineOut";
        break;
    default:
        break;
    }
    return name;
}

const char* EepromNodeToStr(const EepromHandle_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sOp:%s,", text, EepromFsmOperationToStr(Node->operation));
        snprintf(text, sizeof(text), "%sSt:%s,", text, EepromFsmStateToStr(Node->state));
        snprintf(text, sizeof(text), "%sIn:%s,", text, EepromFsmInputToStr(Node->input));
        snprintf(text, sizeof(text), "%sDiff:%u ms,", text, Node->diff_ms);
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin_cnt);
        snprintf(text, sizeof(text), "%sWrAddr:0x%08x", text, Node->wr_eeprom_addr);
        snprintf(text, sizeof(text), "%sWrByte:0x%02x", text, Node->wr_byte);
    }
    return text;
}

const char* EepromConfigToStr(const EepromConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sStart:0x%x,", text, Config->start);
        snprintf(text, sizeof(text), "%sEnd:0x%x,", text, Config->start + Config->size);
        snprintf(text, sizeof(text), "%sSize:%u,", text, Config->size);
        snprintf(text, sizeof(text), "%sInt:%s", text, OnOffToStr(Config->interrupt_on));
    }
    return text;
}

bool eeprom_scan_diag(uint32_t mem_start, uint32_t mem_size) {
    bool res = false;
    float usage_pec = 0.0f;
    uint32_t spare = 0;
    uint32_t busy = 0;
    cli_printf("EepromStart: 0x%08x" CRLF, mem_start);
    cli_printf("EepromSize: %u Byte" CRLF, mem_size);
    res = mem_scan((uint8_t*)mem_start, mem_size, &usage_pec, &spare, &busy);
    log_res(EEPROM, res, "Scan");
    if(res) {
        cli_printf("usage: %f %%" CRLF, usage_pec);
        cli_printf("spare: %u Bytes %u kBytes" CRLF, spare, spare / 1024);
        cli_printf("busy : %u Bytes %u kBytes" CRLF, busy, busy / 1024);
    }

    return res;
}
