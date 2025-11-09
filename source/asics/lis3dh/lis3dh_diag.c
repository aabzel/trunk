#include "lis3dh_diag.h"

#include <stdio.h>
#include <string.h>

#include "common_diag.h"
#include "convert.h"
#include "interfaces_diag.h"
#include "log.h"
#include "num_to_str.h"
#include "asics_types.h"
#include "lis3dh_drv.h"
#include "none_blocking_pause.h"
#include "storage_diag.h"
#include "str_utils.h"
#include "gpio_diag.h"
#include "table_utils.h"
#include "vector_mcal.h"
#include "writer_config.h"

const AsicReg8bitInfo_t Lis3dhRegInfo[] = {
    {
        .valid = true,
        .addr = LIS3DH_REG_STATUS_REG_AUX,
        .name = "STATUS_REG_AUX",
        .access = ACCESS_READ_ONLY,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_OUT_ADC1_L,
        .name = "OUT_ADC1_L",
        .access = ACCESS_READ_ONLY,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_OUT_ADC1_H,
        .name = "OUT_ADC1_H",
        .access = ACCESS_READ_ONLY,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_OUT_ADC2_L,
        .name = "OUT_ADC2_L",
        .access = ACCESS_READ_ONLY,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_OUT_ADC2_H,
        .name = "OUT_ADC2_H",
        .access = ACCESS_READ_ONLY,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_OUT_ADC3_L,
        .name = "OUT_ADC3_L",
        .access = ACCESS_READ_ONLY,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_OUT_ADC3_H,
        .name = "OUT_ADC3_H",
        .access = ACCESS_READ_ONLY,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_WHO_AM_I,
        .name = "WHO_AM_I",
        .access = ACCESS_READ_ONLY,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_TEMP_CFG_REG,
        .name = "TEMP_CFG_REG",
        .access = ACCESS_READ_ONLY,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_STATUS_REG,
        .name = "STATUS_REG",
        .access = ACCESS_READ_ONLY,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_OUT_X_L,
        .name = "OUT_X_L",
        .access = ACCESS_READ_ONLY,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_OUT_X_H,
        .name = "OUT_X_H",
        .access = ACCESS_READ_ONLY,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_OUT_Y_L,
        .name = "OUT_Y_L",
        .access = ACCESS_READ_ONLY,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_OUT_Y_H,
        .name = "OUT_Y_H",
        .access = ACCESS_READ_ONLY,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_OUT_Z_L,
        .name = "OUT_Z_L",
        .access = ACCESS_READ_ONLY,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_OUT_Z_H,
        .name = "OUT_Z_H",
        .access = ACCESS_READ_ONLY,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_FIFO_SRC_REG,
        .name = "FIFO_SRC_REG",
        .access = ACCESS_READ_ONLY,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_INT1_SRC,
        .name = "INT1_SRC",
        .access = ACCESS_READ_ONLY,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_INT2_SRC,
        .name = "INT2_SRC",
        .access = ACCESS_READ_ONLY,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_CLICK_SRC,
        .name = "CLICK_SRC",
        .access = ACCESS_READ_ONLY,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_CTRL_REG0,
        .name = "CTRL_REG0",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_CTRL_REG1,
        .name = "CTRL_REG1",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_CTRL_REG2,
        .name = "CTRL_REG2",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_CTRL_REG3,
        .name = "CTRL_REG3",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_CTRL_REG4,
        .name = "CTRL_REG4",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_CTRL_REG5,
        .name = "CTRL_REG5",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_CTRL_REG6,
        .name = "CTRL_REG6",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_REFERENCE,
        .name = "REFERENCE",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_FIFO_CTRL_REG,
        .name = "FIFO_CTRL_REG",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_INT1_CFG,
        .name = "INT1_CFG",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_INT1_THS,
        .name = "INT1_THS",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_INT1_DURATION,
        .name = "INT1_DURATION",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_INT2_CFG,
        .name = "INT2_CFG",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_INT2_THS,
        .name = "INT2_THS",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_INT2_DURATION,
        .name = "INT2_DURATION",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_CLICK_CFG,
        .name = "CLICK_CFG",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_CLICK_THS,
        .name = "CLICK_THS",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_TIME_LIMIT,
        .name = "TIME_LIMIT",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_TIME_LATENCY,
        .name = "TIME_LATENCY",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_TIME_WINDOW,
        .name = "TIME_WINDOW",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_ACT_THS,
        .name = "ACT_THS",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = LIS3DH_REG_ACT_DUR,
        .name = "ACT_DUR",
        .access = ACCESS_READ_WRITE,
    },
};

uint32_t lis3dh_reg_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(Lis3dhRegInfo);
    return cnt;
}

const AsicReg8bitInfo_t* Lis3dhRegAddrToInfo(Lis3dhRegAddr_t addr) {
    AsicReg8bitInfo_t* Info = NULL;
    uint32_t cnt = ARRAY_SIZE(Lis3dhRegInfo);
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(Lis3dhRegInfo[i].valid) {
            if(addr == Lis3dhRegInfo[i].addr) {
                Info = &Lis3dhRegInfo[i];
            }
        }
    }
    return Info;
}

const char* Lis3dhConfigToStr(const Lis3dhConfig_t* const Config) {
    static char name[80] = "";
    if(Config) {
        strcpy(name, "");
        snprintf(name, sizeof(name), "%sN:%u,", name, Config->num);
#ifdef HAS_I2C
        snprintf(name, sizeof(name), "%sI2C:%u,", name, Config->i2c_num);
        snprintf(name, sizeof(name), "%sAddr:0x%x", name, Config->chip_addr);
#endif

#ifdef HAS_SPI
        snprintf(name, sizeof(name), "%sSPI:%u,", name, Config->spi_num);
        snprintf(name, sizeof(name), "%sCS:%s", name, GpioPadToStr(Config->ChipSelect));
#endif
    }
    return name;
}

const char* Lis3dhNodeToStr(const Lis3dhHandle_t* const Node) {
    static char name[150] = "";
    if(Node) {
        strcpy(name, "");
        snprintf(name, sizeof(name), "%sN:%u,", name, Node->num);
#ifdef HAS_I2C
        snprintf(name, sizeof(name), "%sI2C:%u,", name, Node->i2c_num);
        snprintf(name, sizeof(name), "%sAddr:0x%x,", name, Node->chip_addr);
#endif
#ifdef HAS_SPI
        snprintf(name, sizeof(name), "%sSPI:%u,", name, Node->spi_num);
        snprintf(name, sizeof(name), "%sCS:%s", name, GpioPadToStr(Node->ChipSelect));
#endif
    }
    return name;
}

#if 0
static const char* Lis3dhRegDiagToStr(Lis3dhRegAddr_t addr, uint8_t value) {
    static char name[150]="";
    bool res = false;
    switch(addr) {
        case LIS3DH_REG_LATCHED_FAULT: res=RegLatchedFaultToStr(value,name);break;
        case LIS3DH_REG_STATUS_AND_LOAD_DIAGNOSTIC: res=RegStatusAndLoadDiagnosticToStr(value,name); break;
        case LIS3DH_REG_CONTROL: res=RegControlToStr(value,name);break;
    }
    return name;
}
#endif

bool Lis3dhRegDiag(Lis3dhRegAddr_t addr, uint8_t value) {
    bool res = false;
#ifdef HAS_BIN_2_STR
    LOG_WARNING(LIS3DH, "Addr 0x%x=%s,Value:0x%x=%s", addr, Lis3dhRegAddrToName(addr), value, utoa_bin8(value));
#endif
    return res;
}

bool lis3dh_diag_low_level(uint8_t num, const char* const key_word) {
    bool res = false;
    uint32_t addr = 0;
    uint32_t cnt = 0;

    for(addr = 0; addr < 0xFF; addr++) {
        const AsicReg8bitInfo_t* Info = Lis3dhRegAddrToInfo(addr);
        if(Info) {
            uint8_t value = 0;
            res = lis3dh_reg_read(num, addr, &value);
            if(res) {
                res = Lis3dhRegDiag(addr, value);
                if(res) {
                    cnt++;
                }
            }
        }
    }

    if(0 < cnt) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

static const char* ValU8ToStar(uint8_t byte) {
    const char* name = "";
    if(0 < byte) {
        name = "*";
    }
    return name;
}

bool lis3dh_reg_hazy(uint8_t num) {
    bool res = false;
    LOG_INFO(LIS3DH, "HazyRegs");
    static const table_col_t cols[] = {
        {5, "No"},         {6, "addrD"}, {6, "addrH"}, {6, "val"},
#ifdef HAS_BIN_2_STR
        {11, "val [bin]"},
#endif
        {6, "mark"},
    };
    char text[120] = "";
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    uint32_t i = 0;
    uint32_t cnt = 0;
    for(i = 0; i <= 127; i++) {
        uint8_t some_addr = i;
        res = lis3dh_is_valid_addr(some_addr);
        if(false == res) {
            uint8_t value = 0;
            res = lis3dh_reg_read(num, some_addr, &value);
            if(res) {
                if(value) {
                    strcpy(text, TSEP);
                    snprintf(text, sizeof(text), "%s %4u " TSEP, text, some_addr);
                    snprintf(text, sizeof(text), "%s 0x%02x " TSEP, text, some_addr);
                    snprintf(text, sizeof(text), "%s 0x%02x " TSEP, text, value);
#ifdef HAS_BIN_2_STR
                    snprintf(text, sizeof(text), "%s %9s " TSEP, text, utoa_bin8(value));
#endif
                    snprintf(text, sizeof(text), "%s %4s " TSEP, text, ValU8ToStar(value));
                    cli_printf(TSEP " %3u ", cnt);
                    cli_printf("%s" CRLF, text);
                    wait_in_loop_ms(10);
                    cnt++;
                }
            }
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    if(0 < cnt) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

bool lis3dh_reg_map_hidden_diag(uint8_t num) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "No"}, {6, "addr"}, {6, "addr"}, {6, "val"}, {11, "val [bin]"},
    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    char text[120] = "";
    int32_t i = 0;
    int32_t cnt = 0;
    for(i = 0; i <= 127; i++) {
        uint8_t some_addr = i;
        res = lis3dh_is_valid_addr(some_addr);
        if(false == res) {
            uint8_t value = 0;
            res = lis3dh_reg_read(num, some_addr, &value);
            if(res) {
                strcpy(text, TSEP);
                snprintf(text, sizeof(text), "%s %4u " TSEP, text, some_addr);
                snprintf(text, sizeof(text), "%s 0x%02x " TSEP, text, some_addr);
                snprintf(text, sizeof(text), "%s 0x%02x " TSEP, text, value);
#ifdef HAS_BIN_2_STR
                snprintf(text, sizeof(text), "%s %9s " TSEP, text, utoa_bin8(value));
#endif
                cli_printf(TSEP " %3u ", cnt);
                cli_printf("%s" CRLF, text);
                cnt++;
            }
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

const char* Lis3dhAccelerationToStr(const Lis3dhAcceleration_t* const Acceleration) {
    static char text[100] = "";
    if(Acceleration) {
        float norm = vector_calc_norm_f(&Acceleration->AccelReal);
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sX:%6.2f,", text, Acceleration->AccelReal.dx);
        snprintf(text, sizeof(text), "%sY:%6.2f,", text, Acceleration->AccelReal.dy);
        snprintf(text, sizeof(text), "%sZ:%6.2f,", text, Acceleration->AccelReal.dz);
        snprintf(text, sizeof(text), "%sA:%6.2f", text, norm);
    }
    return text;
}

bool lis3dh_diag_high_level(uint8_t num) {
    bool res = false;
    LOG_INFO(LIS3DH, "DiagHighLevel");

    res = lis3dh_is_connected(num);
    if(res) {
        LOG_INFO(LIS3DH, "Connected %s", OnOffToStr(res));
        Lis3dhHandle_t* Node = Lis3dhGetNode(num);
        if(Node) {
        }
    }

    return res;
}

const char* Lis3dhRegAddrToName(Lis3dhRegAddr_t addr) {
    const char* name = "?";
    const AsicReg8bitInfo_t* Info = Lis3dhRegAddrToInfo(addr);
    if(Info) {
        name = Info->name;
    }
    return name;
}

bool lis3dh_reg_map_diag(uint8_t num, char* key_word, char* key_word2) {
    bool res = false;
    uint32_t addr = 0;
    uint32_t cnt = 0;
    static const table_col_t cols[] = {
        {5, "No"}, {25, "name"}, {8, "access"}, {6, "addrD"}, {6, "addrH"}, {6, "val"}, {11, "val [bin]"},
    };
    char text[120] = "";
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    for(addr = 0; addr < 0xFF; addr++) {
        const AsicReg8bitInfo_t* RegInfo = Lis3dhRegAddrToInfo(addr);
        if(RegInfo) {
            uint8_t value = 0;
            res = lis3dh_reg_read(num, addr, &value);
            if(res) {
                strcpy(text, TSEP);
                cli_printf(TSEP " %3u ", cnt);
                snprintf(text, sizeof(text), "%s %23s " TSEP, text, RegInfo->name);
                snprintf(text, sizeof(text), "%s %6s " TSEP, text, StorageAccessToStr(RegInfo->access));
                snprintf(text, sizeof(text), "%s %4u " TSEP, text, addr);
                snprintf(text, sizeof(text), "%s 0x%02x " TSEP, text, addr);
                snprintf(text, sizeof(text), "%s 0x%02x " TSEP, text, value);
                snprintf(text, sizeof(text), "%s %9s " TSEP, text, utoa_bin8(value));
                cli_printf("%s" CRLF, text);
                wait_in_loop_ms(10);
                cnt++;
            }
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    if(0 < cnt) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

const char* Lis3dhOpModeToStr(Lis3dhOperationMode_t operation_mode) {
    char* name = "?";
    Lis3dhOperationModeInfo_t* OpInfo = Lis3dhOpModeInfoGetByOpMode(operation_mode);
    if(OpInfo) {
        name = OpInfo->name;
    }
    return name;
}

bool lis3dh_diag(void) {
    bool res = false;
    static const table_col_t cols[] = {
        {4, "No"}, {4, "bit"}, {4, "mg"}, {10, "Op"}, {8, "X"},   {8, "Y"},   {8, "Z"},
        {7, "X"},  {7, "Y"},   {7, "Z"},  {7, "min"}, {7, "Abs"}, {7, "max"},
    };

    char text[120] = "";
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t cnt = lis3dh_get_cnt();
    uint32_t i = 0;
    for(i = 0; i <= cnt; i++) {
        Lis3dhHandle_t* Node = Lis3dhGetNode(i);
        if(Node) {
            Lis3dhOperationMode_t operation_mode = LIS3DH_OPERATION_MODE_UNDEF;
            res = lis3dh_operation_mode_get_ll(Node, &operation_mode);
            Lis3dhOperationModeInfo_t* OpInfo = Lis3dhOpModeInfoGetByOpMode(operation_mode);
            if(OpInfo) {
                lis3dh_adc_to_real(&Node->Acceleration, Node->sensitivity, Node->bit_depth);
                strcpy(text, TSEP);
                snprintf(text, sizeof(text), "%s %2u " TSEP, text, i);
                snprintf(text, sizeof(text), "%s %2u " TSEP, text, Node->bit_depth);
                snprintf(text, sizeof(text), "%s %2d " TSEP, text, Node->sensitivity);
                snprintf(text, sizeof(text), "%s %8s " TSEP, text, OpInfo->name);
                snprintf(text, sizeof(text), "%s %6d " TSEP, text, Node->Acceleration.X.s16);
                snprintf(text, sizeof(text), "%s %6d " TSEP, text, Node->Acceleration.Y.s16);
                snprintf(text, sizeof(text), "%s %6d " TSEP, text, Node->Acceleration.Z.s16);

                snprintf(text, sizeof(text), "%s %6.2f " TSEP, text, Node->Acceleration.AccelReal.dx);
                snprintf(text, sizeof(text), "%s %6.2f " TSEP, text, Node->Acceleration.AccelReal.dy);
                snprintf(text, sizeof(text), "%s %6.2f " TSEP, text, Node->Acceleration.AccelReal.dz);
                snprintf(text, sizeof(text), "%s %6.2f " TSEP, text, Node->abs_accel.min);
                snprintf(text, sizeof(text), "%s %6.2f " TSEP, text, Node->abs_accel.cur);
                snprintf(text, sizeof(text), "%s %6.2f " TSEP, text, Node->abs_accel.max);
                cli_printf("%s" CRLF, text);
                res = true;
            }
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
