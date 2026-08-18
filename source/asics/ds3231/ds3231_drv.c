#include "ds3231_drv.h"

#include <string.h>

#include "data_utils.h"
#include "ds3231_config.h"
#include "ds3231_const.h"
#include "ds3231_dep.h"
#include "ds3231_diag.h"
#include "ds3231_types.h"
#include "i2c_mcal.h"
#include "log.h"
#include "time_diag.h"
#include "time_mcal.h"

/*Figure 1. Timekeeing Registers*/
const Ds3231Reg_t Ds3231RegMapStatic[] = {
    {
        .reg_addr = DS3231_REG_SECOND,
        .name = "Sec",
    },
    {
        .reg_addr = DS3231_REG_MINUTE,
        .name = "Min",
    },
    {
        .reg_addr = DS3231_REG_HOUR,
        .name = "Hours",
    },
    {
        .reg_addr = DS3231_REG_WEEK,
        .name = "Day",
    },
    {
        .reg_addr = DS3231_REG_DATE,
        .name = "Date",
    },
    {
        .reg_addr = DS3231_REG_MONTH,
        .name = "Month/Cntr",
    },
    {
        .reg_addr = DS3231_REG_YEAR,
        .name = "Year",
    },
    {
        .reg_addr = DS3231_REG_ALARM1_SECOND,
        .name = "Alrm1Sec",
    },
    {
        .reg_addr = DS3231_REG_ALARM1_MINUTE,
        .name = "Alrm1Min",
    },
    {
        .reg_addr = DS3231_REG_ALARM1_HOUR,
        .name = "Alrm1Hours",
    },
    {
        .reg_addr = DS3231_REG_ALARM1_WEEK,
        .name = "Alrm1Day/Date",
    },
    {
        .reg_addr = DS3231_REG_ALARM2_MINUTE,
        .name = "Alrm1Min",
    },
    {
        .reg_addr = DS3231_REG_ALARM2_HOUR,
        .name = "Alrm2Hours",
    },
    {
        .reg_addr = DS3231_REG_ALARM2_WEEK,
        .name = "Alrm2Day/Date",
    },
    {
        .reg_addr = DS3231_REG_CONTROL,
        .name = "Ctrl",
    },
    {
        .reg_addr = DS3231_REG_STATUS,
        .name = "Ctrl/Status",
    },
    {
        .reg_addr = DS3231_REG_XTAL,
        .name = "AgingOffset",
    },
    {
        .reg_addr = DS3231_REG_TEMPERATUREH,
        .name = "MSBofTemp",
    },
    {
        .reg_addr = DS3231_REG_TEMPERATUREL,
        .name = "LSBofTemp",
    },
};

uint8_t ds3231_get_reg_cnt(void) {
    uint8_t cnt = ARRAY_SIZE(Ds3231RegMapStatic);
    return cnt;
}

const Ds3231Config_t* Ds3231GetConfigNode(uint8_t num) {
    const Ds3231Config_t* Ds3231ConfigNode = NULL;
    uint32_t i = 0;
    for(i = 0; i < ds3231_get_cnt(); i++) {
        if(num == Ds3231Config[i].num) {
            if(Ds3231Config[i].valid) {
                Ds3231ConfigNode = &Ds3231Config[i];
                break;
            }
        }
    }
    return Ds3231ConfigNode;
}

Ds3231Handle_t* Ds3231GetNode(uint8_t num) {
    Ds3231Handle_t* Node = NULL;
    uint32_t i = 0;
    for(i = 0; i < ds3231_get_cnt(); i++) {
        if(num == Ds3231Instance[i].num) {
            if(Ds3231Instance[i].valid) {
                Node = &Ds3231Instance[i];
                break;
            }
        }
    }
    return Node;
}

bool ds3231_get_reg(uint8_t num, uint8_t reg_addr, uint8_t* reg_val) {
    bool res = false;
    res = ds3231_reg_map_get(num);
    if(res) {
        Ds3231Handle_t* Node = Ds3231GetNode(num);
        if(Node) {
            if(reg_addr < DS3231_REG_CNT) {
                *reg_val = Node->RegMap.buff[reg_addr];
            }
        }
    }
#if 0
    LOG_DEBUG(DS3231, "%u GetReg %u", num, reg_addr);
    const Ds3231Config_t* ConfigNode = Ds3231GetConfigNode(num);
    if(ConfigNode) {
        res = i2c_write_wait(ConfigNode->i2c_num, DS3231_ADDRESS, &reg_addr, 1);
        if(res) {
            res = i2c_mcal_read(ConfigNode->i2c_num, DS3231_ADDRESS, reg_val, 1);
            if(res) {

            } else {
                LOG_ERROR(DS3231, "ReadReg %u Err", reg_addr);
            }
        } else {
            LOG_ERROR(DS3231, "WriteReg %u Err", reg_addr);
        }
    }
#endif
    return res;
}

bool ds3231_reg_map_get(uint8_t num) {
    bool res = false;
    LOG_DEBUG(DS3231, "%u ReadRegMap", num);
    const Ds3231Config_t* ConfigNode = Ds3231GetConfigNode(num);
    if(ConfigNode) {
        Ds3231Handle_t* Node = Ds3231GetNode(num);
        if(Node) {
            uint8_t byte = 0;
            res = i2c_write_wait(ConfigNode->i2c_num, DS3231_ADDRESS, &byte, 1);
            if(res) {
                res = i2c_mcal_read(ConfigNode->i2c_num, DS3231_ADDRESS, Node->RegMap.buff, DS3231_REG_CNT);
            }
        }
    }
    return res;
}

bool ds3231_set_reg(uint8_t num, uint8_t reg_addr, uint8_t reg_val) {
    bool res = false;
    /*RegToRegName*/
    LOG_DEBUG(DS3231, "%u SetReg 0x%02x Val 0x%02x", num, reg_addr, reg_val);
    const Ds3231Config_t* ConfigNode = Ds3231GetConfigNode(num);
    if(ConfigNode) {
        uint8_t bytes[2] = {reg_addr, reg_val};
        res = i2c_write_wait(ConfigNode->i2c_num, DS3231_ADDRESS, bytes, 2);
        if(res) {
        } else {
            LOG_ERROR(DS3231, "SetRegErr");
        }
    }
    return res;
}

bool ds3231_is_connected_ll(const Ds3231Config_t* const Node) {
    bool res = false;
    uint8_t seconds = 0;
    res = ds3231_get_reg(Node->i2c_num, DS3231_REG_SECOND, &seconds);
    if(res) {
        if(seconds) {
            // res = true;
        } else {
            // res = false;
        }
    } else {
        LOG_ERROR(DS3231, "ReadReg %u", DS3231_REG_SECOND);
    }
    return res;
}

bool ds3231_is_connected(uint8_t num) {
    bool res = false;
    const Ds3231Config_t* ConfigNode = Ds3231GetConfigNode(num);
    if(ConfigNode) {
        res = ds3231_is_connected_ll(ConfigNode);
    }
    return res;
}

bool ds3231_get_time_date(uint8_t num, struct tm* const time_date_get) {
    bool res = false;
    Ds3231Handle_t* Node = Ds3231GetNode(num);
    if(Node) {
        res = true;
        res = ds3231_get_reg(num, DS3231_REG_SECOND, &Node->Seconds.reg_val) && res;
        res = ds3231_get_reg(num, DS3231_REG_MINUTE, &Node->Minutes.reg_val) && res;
        res = ds3231_get_reg(num, DS3231_REG_HOUR, &Node->Hours.reg_val) && res;
        res = ds3231_get_reg(num, DS3231_REG_WEEK, &Node->WeekDay.reg_val) && res;
        res = ds3231_get_reg(num, DS3231_REG_DATE, &Node->Date.reg_val) && res;
        res = ds3231_get_reg(num, DS3231_REG_MONTH, &Node->Month.reg_val) && res;
        res = ds3231_get_reg(num, DS3231_REG_YEAR, &Node->Year.reg_val) && res;

        if(res) {
            Node->time_date.tm_sec = Node->Seconds.seconds + Node->Seconds.ten_seconds * 10;
            Node->time_date.tm_min = Node->Minutes.minutes + Node->Minutes.ten_minutes * 10;
            switch(Node->Hours.hour_format_24) {
            case HOUR_MODE_24H: {
                Node->time_date.tm_hour = Node->Hours.hours_24 + Node->Hours.ten_hour_24 * 10;
            } break;

            case HOUR_MODE_12H: {
                Node->time_date.tm_hour = Node->Hours.hours_12 + Node->Hours.ten_hour_12 * 10;
            } break;
            default: break;
            }
            Node->time_date.tm_mday = Node->Date.date + Node->Date.ten_date * 10;
            Node->time_date.tm_mon = Node->Month.month + Node->Month.ten_month * 10;
            Node->time_date.tm_year = Node->Year.year + Node->Year.ten_year * 10 + 2000;
            Node->time_date.tm_wday = Node->WeekDay.week_day;
            Node->time_date.tm_yday = calc_total_day_cnt(time_date_get);
            Node->time_date.tm_isdst = 0;
            memcpy(time_date_get, &Node->time_date, sizeof(struct tm));
        }
    } else {
        LOG_ERROR(DS3231, "UndefNode: %u", num);
    }
    return res;
}

bool rtc_external_get(uint8_t num, struct tm* const DateTime) {
    bool res = ds3231_get_time_date(num, DateTime);
    return res;
}
// http://cppstudio.com/post/587/

bool ds3231_hour_mode_set(uint8_t num, HourMode_t hour_mode) {
    bool res = false;
    LOG_INFO(DS3231, "SetHformat %u=%u=%s Ok", num, hour_mode, HourModeToStr(hour_mode));
    Ds3231RegHours_t Hours;
    Hours.reg_val = 0;
    res = ds3231_get_reg(num, DS3231_REG_HOUR, &Hours.reg_val);
    if(res) {
        Hours.hour_format_24 = hour_mode;
        res = ds3231_set_reg(num, DS3231_REG_HOUR, Hours.reg_val);
        if(res) {
            LOG_INFO(DS3231, "SetHformat %u Ok", num);
        } else {
            LOG_ERROR(DS3231, "SetHformat %u Err", num);
        }
    }

    return res;
}

HourMode_t ds3231_hour_mode_get(uint8_t num) {
    bool res = false;
    HourMode_t hour_mode = HOUR_MODE_UNDEF;
    Ds3231RegHours_t Hours;
    Hours.reg_val = 0;
    res = ds3231_get_reg(num, DS3231_REG_HOUR, &Hours.reg_val);
    if(res) {
        hour_mode = Hours.hour_format_24;
    } else {
        LOG_ERROR(DS3231, "GetHourFormat %u Err", num);
    }

    return hour_mode;
}

bool ds3231_proc_status(Ds3231RegControlStatus_t* Reg) {
    bool res = false;
    if(Reg) {
        res = true;
        if(0 == Reg->osc) {
            LOG_ERROR(DS3231, "OscStoped");
        }
        if(1 == Reg->busy) {
            LOG_WARNING(DS3231, "Busy");
        }
    }
    return res;
}

bool ds3231_proc_one(uint8_t num) {
    bool res = false;
    Ds3231Handle_t* Node = Ds3231GetNode(num);
    if(Node) {
        LOG_DEBUG(DS3231, "Proc %u", num);
        res = ds3231_is_connected(num);
        if(res) {
            LOG_DEBUG(DS3231, "Connected %u", num);
            Node->Status.reg_val = 0;
            res = ds3231_get_reg(num, DS3231_REG_STATUS, &Node->Status.reg_val);
            if(res) {
                res = ds3231_proc_status(&Node->Status);
            }
            res = ds3231_get_time_date(num, &Node->time_date);
            res = ds3231_temperature_convert(num);
        } else {
            LOG_ERROR(DS3231, "I2C LinkLost %u", num);
        }
    }

    return res;
}

bool ds3231_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(DS3231, "Init %u", num);
    const Ds3231Config_t* ConfigNode = Ds3231GetConfigNode(num);
    if(ConfigNode) {
        Ds3231Handle_t* Node = Ds3231GetNode(num);
        if(Node) {
            Node->num = ConfigNode->num;
            Node->valid = true;
            Node->i2c_num = ConfigNode->i2c_num;
            res = ds3231_is_connected_ll(ConfigNode);
            if(res) {
                LOG_INFO(DS3231, "Connected %u!", num);
                res = ds3231_tune(num, ConfigNode->offset);
                Ds3231RegControl_t RegCtrl;
                RegCtrl.reg_val = 0;

                RegCtrl.eosc = 0;
                RegCtrl.bbsqw = 1;
                RegCtrl.conv = 1;
                RegCtrl.rs = ConfigNode->rate_select;
                RegCtrl.intcn = 0;
                RegCtrl.a1ie = 0;
                RegCtrl.a2ie = 0;
                res = ds3231_set_reg(num, DS3231_REG_CONTROL, RegCtrl.reg_val);
                res = ds3231_hour_mode_set(num, ConfigNode->hour_mode);

                res = ds3231_get_time_date(num, &Node->time_date);
                if(res) {
                    res = print_time_date("RTC", &Node->time_date, true);
                }

                struct tm time_date_compile;
                LOG_INFO(SYS, "CompileDate: %s", __DATE__);
                LOG_INFO(SYS, "CompileTime: %s", __TIME__);
                LOG_INFO(SYS, "CompileTimeStamp: %s", __TIMESTAMP__);
                res = date_parse(&time_date_compile, __DATE__);
                if(res) {
                    res = time_parse(&time_date_compile, __TIME__);
                    if(res) {
                        res = print_time_date("Compile1", &time_date_compile, true);
                        res = print_time_date("Compile2", &time_date_compile, true);

                        int32_t diff = time_date_cmp(&Node->time_date, &time_date_compile);
                        if(0 < diff) {
#ifdef HAS_INIT_BY_COMPILE_TIME
                            LOG_WARNING(SYS, "Init RTC by CompileTimeStamp");
                            res = ds3231_set_time_date(num, &time_date_compile);
#endif
                        } else {
                            LOG_WARNING(SYS, "CompileTimeStamp less then current time %d s", diff);
                        }
                    } else {
                        LOG_ERROR(SYS, "CompileTimeParseErr: %s", __TIME__);
                    }
                } else {
                    LOG_ERROR(SYS, "CompileDateParseErr: %s", __DATE__);
                }

            } else {
                LOG_ERROR(DS3231, "I2C LinkLost %u", num);
            }

            Node->init = true;
        }
    }
    return res;
}

bool rtc_external_init_one(uint8_t num) {
    bool res = ds3231_init_one(num);
    return res;
}

bool ds3231_set_time(uint8_t num, const struct tm* const time_date) {
    bool res = false;
    LOG_WARNING(DS3231, "SetTime %u", num);
    Ds3231Handle_t* Node = Ds3231GetNode(num);
    if(Node) {
        res = is_valid_time(time_date);
        if(res) {
            LOG_INFO(DS3231, "ValidTime! %u", num);
            res = print_time(time_date);
            res = ds3231_run(num, false);
            Node->Seconds.reg_val = 0;
            Node->Seconds.seconds = time_date->tm_sec % 10;
            Node->Seconds.ten_seconds = time_date->tm_sec / 10;
            res = ds3231_set_reg(num, DS3231_REG_SECOND, Node->Seconds.reg_val);

            Node->Minutes.reg_val = 0;
            Node->Minutes.minutes = time_date->tm_min % 10;
            Node->Minutes.ten_minutes = time_date->tm_min / 10;
            res = ds3231_set_reg(num, DS3231_REG_MINUTE, Node->Minutes.reg_val);

            Node->Hours.reg_val = 0;
            Node->Hours.hours_24 = time_date->tm_hour % 10;
            Node->Hours.ten_hour_24 = time_date->tm_hour / 10;
            Node->Hours.hour_format_24 = HOUR_MODE_24H;
            res = ds3231_set_reg(num, DS3231_REG_HOUR, Node->Hours.reg_val);

            res = ds3231_run(num, true);

        } else {
            LOG_ERROR(DS3231, "InValidTime %u", num);
            res = print_time(time_date);
        }
    }
    return res;
}

bool ds3231_run(uint8_t num, bool on_off) {
    bool res = false;
    const Ds3231Config_t* ConfigNode = Ds3231GetConfigNode(num);
    if(ConfigNode) {
        Ds3231RegControl_t RegCtrl;
        res = ds3231_get_reg(num, DS3231_REG_CONTROL, &RegCtrl.reg_val);
        if(res) {
            switch((uint8_t)on_off) {
            case true:
                RegCtrl.eosc = 0;
                break;
            case false:
                RegCtrl.eosc = 1;
                break;
            default : break;
            }

            res = ds3231_set_reg(num, DS3231_REG_CONTROL, RegCtrl.reg_val);
        }
    }
    return res;
}

bool ds3231_set_date(uint8_t num, const struct tm* const time_date) {
    bool res = false;
    LOG_WARNING(DS3231, "SetDate %u", num);
    Ds3231Handle_t* Node = Ds3231GetNode(num);
    if(Node) {
        res = is_valid_date(time_date);
        if(res) {
            Node->Date.date = time_date->tm_mday % 10;
            Node->Date.ten_date = time_date->tm_mday / 10;
            res = ds3231_set_reg(num, DS3231_REG_DATE, Node->Date.reg_val);

            Node->Month.month = time_date->tm_mon % 10;
            Node->Month.ten_month = time_date->tm_mon / 10;
            res = ds3231_set_reg(num, DS3231_REG_MONTH, Node->Month.reg_val);

            int abs_year = time_date->tm_year - 2000;
            Node->Year.year = abs_year % 10;
            Node->Year.ten_year = abs_year / 10;
            res = ds3231_set_reg(num, DS3231_REG_YEAR, Node->Year.reg_val);

            Node->WeekDay.week_day = time_date->tm_wday;
            res = ds3231_set_reg(num, DS3231_REG_WEEK, Node->WeekDay.reg_val);
        } else {
            LOG_ERROR(DS3231, "InvalidDate[%s]", TimeDateToStrShort(time_date));
        }
    } else {
        LOG_ERROR(DS3231, "NodeErr %u", num);
    }
    return res;
}

bool ds3231_set_time_date(uint8_t num, const struct tm* const time_date_set) {
    bool res = false;
    res = ds3231_set_time(num, time_date_set);
    res = ds3231_set_date(num, time_date_set);
    return res;
}

bool rtc_external_set_date(uint8_t num, const struct tm* const time_date) { return ds3231_set_date(num, time_date); }

bool rtc_external_set_time(uint8_t num, const struct tm* const time_date) { return ds3231_set_time(num, time_date); }

bool rtc_external_set(uint8_t num, const struct tm* const DateTime) {
    bool res = ds3231_set_time_date(num, DateTime);
    return res;
}

bool ds3231_mcal_init(void) {
    set_log_level(I2C, LOG_LEVEL_DEBUG);
    set_log_level(DS3231, LOG_LEVEL_DEBUG);
    bool res = false;
    uint32_t i = 0;
    uint32_t ok_cnt = 0;
    uint32_t cnt = ds3231_get_cnt();
    LOG_WARNING(DS3231, "Init %u", cnt);
    for(i = 0; i <= cnt; i++) {
        res = ds3231_init_one(i);
        if(res) {
            ok_cnt++;
        }
    }

    if(ok_cnt) {
        res = true;
    } else {
        res = false;
    }
    set_log_level(I2C, LOG_LEVEL_INFO);
    set_log_level(DS3231, LOG_LEVEL_INFO);
    return res;
}

bool ds3231_proc(void) {
    bool res = false;
    uint32_t i = 0;
    LOG_DEBUG(DS3231, "Proc");
    uint32_t cnt = ds3231_get_cnt();
    for(i = 0; i <= cnt; i++) {
        res = ds3231_proc_one(i);
    }
    return res;
}

bool ds3231_temperature_get(uint8_t num, double* const temp) {
    bool res = false;
    Ds3231Handle_t* Node = Ds3231GetNode(num);
    if(Node) {
        res = true;
        Type16Union_t un16;
        un16.u16 = 0;
        res = ds3231_get_reg(num, DS3231_REG_TEMPERATUREH, &un16.u8[1]);
        res = ds3231_get_reg(num, DS3231_REG_TEMPERATUREL, &un16.u8[0]);
        Node->temp_code = un16.u16;

        LOG_DEBUG(DS3231, "TempCode 0x%04x=%u", Node->temp_code, Node->temp_code);
        Node->temp_code = Node->temp_code >> 6;
        Node->temp = 0.25 * ((double)Node->temp_code);

        if(temp) {
            *temp = Node->temp;
        }
    }
    return res;
}

bool ds3231_temperature_convert(uint8_t num) {
    bool res = false;
    LOG_DEBUG(DS3231, "Convert");
    Ds3231RegControl_t RegCtrl;
    RegCtrl.reg_val = 0;

    RegCtrl.eosc = 0;
    RegCtrl.bbsqw = 1;
    RegCtrl.conv = 1;
    RegCtrl.rs = RS_8192_HZ;
    RegCtrl.intcn = 0;
    RegCtrl.a1ie = 0;
    RegCtrl.a2ie = 0;
    res = ds3231_set_reg(num, DS3231_REG_CONTROL, RegCtrl.reg_val);
    return res;
}

bool ds3231_tune(uint8_t num, int8_t offset) {
    bool res = false;
    Ds3231Handle_t* Node = Ds3231GetNode(num);
    if(Node) {
        LOG_INFO(DS3231, "Tune %d", offset);
        res = ds3231_set_reg(num, DS3231_REG_XTAL, offset);
    }
    return res;
}
