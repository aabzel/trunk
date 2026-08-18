#include "ds3231_commands.h"

#include <stdbool.h>
#include <stdio.h>

#include "convert.h"
#include "data_utils.h"
#include "ds3231_diag.h"
#include "ds3231_drv.h"
#include "log.h"
#include "str_utils.h"
#include "table_utils.h"
#include "time_diag.h"
#include "time_mcal.h"
#include "writer_config.h"

bool cmd_ds3231_reg_map(int32_t argc, char* argv[]) {
    bool res = false;
    char keyWord1[20] = "";
    char keyWord2[20] = "";
    if(0 <= argc) {
        strncpy(keyWord1, "", sizeof(keyWord1));
        strncpy(keyWord2, "", sizeof(keyWord2));
        res = true;
    }

    if(1 <= argc) {
        strncpy(keyWord1, argv[0], sizeof(keyWord1));
        res = true;
    }

    if(2 <= argc) {
        strncpy(keyWord2, argv[1], sizeof(keyWord2));
        res = true;
    }

    if(2 < argc) {
        LOG_ERROR(SYS, "Usage: gl keyWord");
    }
    if(true == res) {
        res = diag_ds3231(1, keyWord1, keyWord2);
    }
    return res;
}

bool cmd_ds3231_get_reg(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t reg_addr = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &reg_addr);
    }

    if(res) {
        uint8_t reg_val = 0;
        res = ds3231_get_reg(1, reg_addr, &reg_val);
        if(res) {
            LOG_INFO(DS3231, "Addr 0x%02x Val: 0x%02x", reg_addr, reg_val);
        }
    }
    return res;
}

bool cmd_ds3231_set_reg(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t reg_addr = 0;
    uint8_t reg_val = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &reg_addr);
    }
    if(2 <= argc) {
        res = try_str2uint8(argv[1], &reg_val);
    }

    if(res) {
        res = ds3231_set_reg(1, reg_addr, reg_val);
        if(res) {
            LOG_INFO(DS3231, "Addr 0x%02x Val: 0x%02x", reg_addr, reg_val);
        }
    }
    return res;
}

bool cmd_ds3231_diag(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(0 <= argc) {
        num = 1;
        res = true;
    }
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(DS3231, "Parse Num [%s] Err", argv[0]);
        }
    }

    if(res) {
        struct tm time_date_get;
        res = ds3231_get_time_date(num, &time_date_get);
        if(res) {
            res = print_time_date("RTC", &time_date_get, true);
        } else {
            LOG_ERROR(DS3231, "GetTimeError");
        }
        HourMode_t hour_mode = ds3231_hour_mode_get(num);
        LOG_INFO(DS3231, "HourMode %u=%s", hour_mode, HourModeToStr(hour_mode));

        double temp = 0.0;
        res = ds3231_temperature_get(num, &temp);
        LOG_INFO(DS3231, "Temp: %7.3f Deg", temp);
    } else {
        LOG_ERROR(DS3231, "Usage: dsd num");
    }
    return res;
}

bool cmd_ds3231_init(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 <= argc) {
        res = true;
    }

    if(res) {
        res = ds3231_mcal_init();
        if(false == res) {
            LOG_ERROR(DS3231, "InitErr");
        } else {
            LOG_INFO(DS3231, "InitOk");
        }
    }
    return res;
}

/*
 dssd 1 Sep_25_2025
 dssd 1 Oct_31_2023
 dssd 1 Aug_02_2025
 dssd 1 Nov_15_2025
 */
bool cmd_ds3231_set_date(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    struct tm time_date_set = {0};
    memset(&time_date_set, 0, sizeof(struct tm));
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(DS3231, "Parse Num [%s] Err", argv[0]);
        }
    }

    char date_str[20] = "";
    if(2 <= argc) {
        strcpy(date_str, argv[1]);
        int ret = replace_char(date_str, '_', ' ');
        if(ret) {
            LOG_INFO(DS3231, "InText [%s]->[%s]", argv[1], date_str);
            res = date_parse(&time_date_set, date_str);
            if(res) {
                LOG_INFO(DS3231, "ParseDate [%s] Ok", date_str);
            } else {
                LOG_ERROR(DS3231, "Parse Date [%s] Err", date_str);
            }
        }
    }

    if(res) {
        res = ds3231_set_date(num, &time_date_set);
        if(res) {
            LOG_INFO(DS3231, "SetDateOk");
        } else {
            LOG_ERROR(DS3231, "SetDateErr");
        }
    } else {
        LOG_ERROR(DS3231, "Usage: dssd Date");
    }
    return res;
}

/*
 https://www.utctime.net/
 dsst 1 17:36:00
 */
bool cmd_ds3231_set_time(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    struct tm time_date_set;
    memset(&time_date_set, 0, sizeof(struct tm));

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(DS3231, "Parse Num [%s] Err", argv[0]);
        }
    }

    if(2 <= argc) {
        res = time_parse(&time_date_set, argv[1]);
        if(false == res) {
            LOG_ERROR(DS3231, "Parse Time [%s] Err", argv[1]);
        }
    }

    if(res) {
        res = ds3231_set_time(num, &time_date_set);
    } else {
        LOG_ERROR(DS3231, "Usage: dsst Time");
    }
    return res;
}

bool cmd_ds3231_set_time_date(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    struct tm time_date_set;
    memset(&time_date_set, 0, sizeof(struct tm));
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }
    return res;
}

bool cmd_ds3231_run(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    bool on_off = true;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(2 <= argc) {
        res = try_str2bool(argv[1], &on_off);
    }

    if(res) {
        res = ds3231_run(num, on_off);
        if(res) {
            LOG_INFO(DS3231, "Num:%u,En:%u,Ok", num, on_off);
        } else {
            LOG_ERROR(DS3231, "Num:%u,En:%u,Err", num, on_off);
        }
    }

    return res;
}

bool cmd_ds3231_tune(int32_t argc, char* argv[]) {
    bool res = false;
    int8_t offset = 0;
    uint8_t num = 1;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(2 <= argc) {
        res = try_str2int8(argv[1], &offset);
    }

    if(res) {
        res = ds3231_tune(num, offset);
    } else {
        LOG_ERROR(DS3231, "Usage: dst Num Offset");
    }

    return res;
}
