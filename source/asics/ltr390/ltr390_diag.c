#include "ltr390_diag.h"

#include <stdint.h>
#include <stdio.h>

#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "gpio_diag.h"
#include "log.h"
#include "log_utils.h"
#include "ltr390_drv.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

static char LocalText[120] = "?";

bool ltr390_diag(char* key_word1, char* key_word2) {
    bool res = false;
    static const table_col_t cols[] = {
        {4, "No"},    {6, "I2C"},  {4, "Rsl"}, {4, "Gain"}, {9, "als"}, {9, "uvi"},       {9, "ITF"},       {5, "Err"},
        {14, "Name"}, {5, "init"}, {5, "New"}, {5, "Cnt"},  {5, "Src"}, {12, "als_data"}, {12, "uvs_data"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    uint16_t num = 0;
    uint8_t i = 0;
    uint16_t cnt = ltr390_get_cnt();
    for(i = 0; i <= cnt; i++) {
        Ltr390Handle_t* Node = Ltr390GetNode(i);
        if(Node) {
            char temp[150] = {0};
            strcpy(temp, TSEP);
            snprintf(temp, sizeof(temp), "%s %2u " TSEP, temp, num);
            snprintf(temp, sizeof(temp), "%s I2C%u " TSEP, temp, Node->i2c_num);
            snprintf(temp, sizeof(temp), "%s %2u " TSEP, temp, Node->resolution);
            snprintf(temp, sizeof(temp), "%s %2u " TSEP, temp, Node->gain);
            snprintf(temp, sizeof(temp), "%s %7.2f " TSEP, temp, Node->als_lx);
            snprintf(temp, sizeof(temp), "%s %7.2f " TSEP, temp, Node->uvi);
            snprintf(temp, sizeof(temp), "%s %7.2f " TSEP, temp, Node->integratin_time_factor);
            snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, Node->err_cnt);
            snprintf(temp, sizeof(temp), "%s %12s " TSEP, temp, Node->name);
            snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, Node->init);
            snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, Node->new_data);
            snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, Node->new_data_cnt);
            snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, Node->cur_source);
            snprintf(temp, sizeof(temp), "%s 0x%08X " TSEP, temp, Node->als_data.u32);
            snprintf(temp, sizeof(temp), "%s 0x%08X " TSEP, temp, Node->uvs_data.u32);
            res = is_contain(temp, key_word1, key_word2);
            if(res) {
                cli_printf("%s" CRLF, temp);
                num++;
            }
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

const char* Ltr390AddrToName(uint8_t reg_addr) {
    const char* name = "?";
    const Ltr390RegisterInfo_t* Info = Ltr390RegisterInfoGet(reg_addr);
    if(Info) {
        name = Info->name;
    }
    return name;
}

const char* RegAccessToStr(RegAccess_t access) {
    const char* name = "?";
    switch(access) {
    case REG_ACCESS_READ:
        name = "R";
        break;
    case REG_ACCESS_READ_WRITE:
        name = "R/W";
        break;
    default:
        break;
    }
    return name;
}

bool ltr390_diag_registers(uint8_t num, char* key_word1, char* key_word2) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "No"}, {6, "Addr"}, {6, "ValueHex"}, {13, "ValueBin"}, {5, "access"}, {3, "size"}, {14, "text"},
    };
    uint16_t cnt = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    uint8_t reg_addr = 0;

    for(reg_addr = 0; reg_addr <= LTR390_REG_ADDR_LAST; reg_addr++) {
        res = ltr390_is_valid_reg_addr(reg_addr);
        if(res) {
            uint8_t reg_val = 0;
            res = ltr390_register_read(num, reg_addr, &reg_val);
            if(res) {
                char temp[120] = "";
                strcpy(temp, TSEP);
                snprintf(temp, sizeof(temp), "%s 0x%02x " TSEP, temp, reg_addr);
                snprintf(temp, sizeof(temp), "%s 0x%02x " TSEP, temp, reg_val);
#ifdef HAS_BIN_2_STR
                snprintf(temp, sizeof(temp), "%s 0b%s " TSEP, temp, utoa_bin8(reg_val));
#endif
                const Ltr390RegisterInfo_t* Info = Ltr390RegisterInfoGet(reg_addr);
                if(Info) {
                    snprintf(temp, sizeof(temp), "%s %3s " TSEP, temp, RegAccessToStr(Info->access));
                    snprintf(temp, sizeof(temp), "%s %1u " TSEP, temp, Info->size);
                    snprintf(temp, sizeof(temp), "%s %12s " TSEP, temp, Info->name);
                }
                res = is_contain(temp, key_word1, key_word2);
                if(res) {
                    cli_printf(TSEP " %3u ", cnt);
                    cli_printf("%s" CRLF, temp);
                    cnt++;
                }
            }
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

const char* SourceToStr(DataSource_t source) {
    const char* name = "?";
    switch((uint8_t)source) {
    case LTR390_SRC_ALS:
        name = "Als";
        break;
    case LTR390_SRC_UVS:
        name = "Uvs";
        break;
    default:
        break;
    }

    return name;
}

const char* Ltr390DiagToStr(Ltr390Handle_t* Node) {
    strcpy(LocalText, "");
    snprintf(LocalText, sizeof(LocalText), "%sResol:%uBit,", LocalText, Node->resolution);
    snprintf(LocalText, sizeof(LocalText), "%sGain:%u,", LocalText, Node->gain);
    snprintf(LocalText, sizeof(LocalText), "%sInteTimeFc:%4.2f,", LocalText, Node->integratin_time_factor);
    snprintf(LocalText, sizeof(LocalText), "%sCurSrc:%s,", LocalText, SourceToStr(Node->cur_source));
    return LocalText;
}

const char* Ltr390ConfigToStr(const Ltr390Config_t* const Config) {
    if(Config) {
        strcpy(LocalText, "");
        snprintf(LocalText, sizeof(LocalText), "%sN:%u,", LocalText, Config->num);
        snprintf(LocalText, sizeof(LocalText), "%sI2C:%u,", LocalText, Config->i2c_num);
        snprintf(LocalText, sizeof(LocalText), "%sIRQ:%s", LocalText, GpioPadToStr(Config->irq));
        snprintf(LocalText, sizeof(LocalText), "%s%s,", LocalText, Config->name);
    }
    return LocalText;
}

const char* Ltr390AlsDiagToStr(Ltr390Handle_t* Node) {
    // static char LocalText[120] = "?";
    strcpy(LocalText, "");
    snprintf(LocalText, sizeof(LocalText), "Resol:%uBit,AlsDat:%u=%8.3f lx,IntTime:%4.2f,CurSrc:%s", Node->resolution,
             Node->als_data.u32, Node->als_lx, Node->integratin_time_factor, SourceToStr(Node->cur_source));
    return LocalText;
}

const char* Ltr390UvsDiagToStr(Ltr390Handle_t* Node) {
    //  static char LocalText[120] = "?";
    strcpy(LocalText, "");
    snprintf(LocalText, sizeof(LocalText), "Resol:%uBit,UvsDat:%u=%6.3f UVI,CurSrc:%s", Node->resolution,
             Node->uvs_data.u32, Node->uvi, SourceToStr(Node->cur_source));
    return LocalText;
}

bool Ltr390DiagNode(Ltr390Handle_t* Node) {
    bool res = false;
    if(Node) {
        LOG_INFO(LTR390, "%s", Ltr390DiagToStr(Node));
        LOG_INFO(LTR390, "%s", Ltr390UvsDiagToStr(Node));
        LOG_INFO(LTR390, "%s", Ltr390AlsDiagToStr(Node));
        res = true;
    }
    return res;
}

bool ltr390_diag_registers_undoc(uint8_t num) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "No"}, {6, "Addr"}, {6, "ValueHex"}, {13, "ValueBin"}, {5, "access"}, {3, "size"}, {14, "LocalText"},
    };
    uint16_t cnt = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    uint16_t reg_addr = 0;

    for(reg_addr = 0; reg_addr <= 0xff; reg_addr++) {
        res = ltr390_is_valid_reg_addr(reg_addr);
        if(false == res) {
            uint8_t reg_val = 0;
            res = ltr390_register_read(num, reg_addr, &reg_val);
            if(res) {
                if(reg_val) {
                    char temp[120] = "";
                    strcpy(temp, TSEP);
                    snprintf(temp, sizeof(temp), "%s 0x%02x " TSEP, temp, reg_addr);
                    snprintf(temp, sizeof(temp), "%s 0x%02x " TSEP, temp, reg_val);
#ifdef HAS_BIN_2_STR
                    snprintf(temp, sizeof(temp), "%s 0b%s " TSEP, temp, utoa_bin8(reg_val));
#endif
                    const Ltr390RegisterInfo_t* Info = Ltr390RegisterInfoGet(reg_addr);
                    if(Info) {
                        snprintf(temp, sizeof(temp), "%s %3s " TSEP, temp, RegAccessToStr(Info->access));
                        snprintf(temp, sizeof(temp), "%s %1u " TSEP, temp, Info->size);
                        snprintf(temp, sizeof(temp), "%s %12s " TSEP, temp, Info->name);
                    }

                    cli_printf(TSEP " %3u ", cnt);
                    cli_printf("%s" CRLF, temp);
                    cnt++;
                }
            }
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
