#include "at24cxx_diag.h"

#include <stdio.h>

#include "at24cxx_drv.h"
#include "at24cxx_read_drv.h"
#include "common_diag.h"
#include "convert.h"
#include "debug_info.h"
#include "gpio_diag.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "table_utils.h"
#include "writer_config.h"

const char* ChipModel2Str(At24cChipModel_t chip_model) {
    const char* name = "?";
    switch((uint8_t)chip_model) {
    case AT24C02:
        name = "AT24C02";
        break;
    case AT24C04:
        name = "AT24C04";
        break;
    case AT24C08:
        name = "AT24C08";
        break;
    case AT24C16:
        name = "AT24C16";
        break;
    case AT24C32:
        name = "AT24C32";
        break;
    case AT24C64:
        name = "AT24C64";
        break;
    case AT24C128:
        name = "AT24C128";
        break;
    case AT24C256:
        name = "AT24C256";
        break;
    case AT24C512:
        name = "AT24C512";
        break;
    case AT24CM01:
        name = "AT24CM01";
        break;
    case AT24CM02:
        name = "AT24CM02";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

const char* At24cxxConfig2Str(const At24cxxConfig_t* const Config) {
    static char name[80] = "?";
    if(Config) {
        snprintf(name, sizeof(name), "Model:%s,I2C%u,Addr: 0x%x,Pad:%s", ChipModel2Str(Config->chip_model),
                 Config->i2c_num, Config->chip_addr, GpioPadToStr(Config->wp));
    }
    return name;
}

bool At24cxxDiagConfig(const At24cxxConfig_t* const Config) {
    bool res = false;
    if(Config) {
        LOG_NOTICE(AT24C, "%s", At24cxxConfig2Str(Config));
        res = true;
    }
    return res;
}

const char* At24cxxInfo2Str(const At24cxxInfo_t* const Info) {
    static char name[80] = "?";
    if(Info) {
        snprintf(name, sizeof(name), "Model:%s,%u Bytes,%u Pages,PageSize:%u byte, Addr %u bit",
                 ChipModel2Str(Info->chip_model), Info->capacity_bytes, Info->pages, Info->page_size, Info->addr_bit);
    }
    return name;
}

bool At24cxxDiagInfo(const At24cxxInfo_t* const Info) {
    bool res = false;
    if(Info) {
        LOG_INFO(AT24C, "%s", At24cxxInfo2Str(Info));
        res = true;
    }
    return res;
}

bool at24cxx_diag(void) {
    bool res = false;

    char line[150];
    static const table_col_t cols[] = {
        {3, "Num"},  {6, "ChAddr"}, {10, "Name"},     {8, "Addr"},
        {6, "Link"}, {7, "Pages"},  {10, "PageSize"}, {11, "TotalByte"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint16_t cnt = at24cxx_get_cnt();
    uint8_t i = 0;
    for(i = 1; i <= cnt; i++) {
        At24cxxHandle_t* Node = At24cxxGetNode(i);
        if(Node) {
            strcpy(line, TSEP);
            uint16_t address = 0;
            res = at24cxx_read_address(i, &address);
            snprintf(line, sizeof(line), "%s %1u " TSEP, line, Node->num);
            snprintf(line, sizeof(line), "%s 0x%2X " TSEP, line, Node->chip_addr);
            snprintf(line, sizeof(line), "%s %8s " TSEP, line, ChipModel2Str(Node->chip_model));
            snprintf(line, sizeof(line), "%s 0x%04x " TSEP, line, address);
            res = at24cxx_is_connected(i);
            snprintf(line, sizeof(line), "%s %4s " TSEP, line, res ? "yes" : "No");

            cli_printf("%s" CRLF, line);
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

bool at24cxx_usage(uint8_t num, uint32_t piece_size) {
    bool res = false;
    At24cxxHandle_t* Node = At24cxxGetNode(num);
    if(Node) {
        static const table_col_t cols[] = {{6, "num"}, {11, "Start"}, {11, "End"}, {7, "cont"}, {8, "Use"}};
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
#if 0
    char line_str[120];
    double usage_pec = 0.0f;
    uint32_t spare = 0;
        uint32_t flash_addr = 0;
        for(flash_addr = 0; flash_addr < Node->page_size_bytes; flash_addr += piece_size) {
            strcpy(line_str, TSEP);
            snprintf(line_str, sizeof(line_str), "%s 0x%08x" TSEP, line_str, flash_addr);
            snprintf(line_str, sizeof(line_str), "%s 0x%08x" TSEP, line_str, flash_addr + piece_size);
            snprintf(line_str, sizeof(line_str), "%s %6s" TSEP, line_str, (piece_size == spare) ? "spare" : "busy");
            snprintf(line_str, sizeof(line_str), "%s %6.2f " TSEP, line_str, usage_pec);

            wait_in_loop_ms(2);
            cli_printf(TSEP " %4u ", num);
            cli_printf("%s" CRLF, line_str);
            num++;
        }
#endif
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }
    return res;
}
