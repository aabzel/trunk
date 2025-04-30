#include "rtc_mcal.h"

#include "code_generator.h"
#include "log.h"
#include "rtc_internal.h"
#include "time_diag.h"
#include "time_mcal.h"

COMPONENT_GET_NODE(Rtc, rtc)
COMPONENT_GET_CONFIG(Rtc, rtc)

bool rtc_set(uint8_t num, const struct tm* const date_time) {
    bool res = false;
    res = is_valid_time(date_time);
    if(res) {
        RtcHandle_t* Node = RtcGetNode(num);
        if(Node) {
            switch((uint32_t)Node->rtc_location) {
                case RTC_LOCATION_INTERNAL: {
                    res = rtc_internal_set(num, date_time);
                }break;
            }
        }
        LOG_WARNING(LG_RTC, "RTC%u,Set:%s", num, TimeDate2StrShort(date_time));
        if(res) {
            LOG_INFO(LG_RTC, "Date,Time,Set,Ok!");
        } else {
            LOG_ERROR(LG_RTC, "Date,Time,Set,Err");
        }
    } else {
        LOG_ERROR(LG_RTC, "NoValidTime");
    }
    return res;
}

bool rtc_set_time(uint8_t num, const struct tm* const date_time) {
    bool res = false;
    res = is_valid_time(date_time);
    if(res) {
        LOG_WARNING(LG_RTC, "RTC%u,Set:%s", num, Time2StrShort(date_time));
        res = rtc_internal_set_time(num, date_time);
        if(res) {
            LOG_INFO(LG_RTC, "DTSetTimeOk!");
        } else {
            LOG_ERROR(LG_RTC, "DTSetTimeErr");
        }
    } else {
        LOG_ERROR(LG_RTC, "NoValidTime");
    }
    return res;
}


bool rtc_set_date(uint8_t num, const struct tm* const date_time) {
    bool res = false;
    res = is_valid_date(date_time);
    if(res) {
        LOG_WARNING(LG_RTC, "RTC%u,Set:%s", num, Date2StrShort(date_time));

        RtcHandle_t* Node = RtcGetNode(num);
        if(Node) {
            switch((uint32_t)Node->rtc_location) {
                case RTC_LOCATION_INTERNAL: {
                    res = rtc_internal_set_date(num, date_time);
                } break;
                case RTC_LOCATION_EXTERAL: {

                } break;
            }// switch(Node->rtc_location)
        }// if(Node)

        if(res) {
            LOG_INFO(LG_RTC, "DTSetDateOk!");
        } else {
            LOG_ERROR(LG_RTC, "DTSetDateErr");
        }
    } else {
        LOG_ERROR(LG_RTC, "NoValidTime");
    }
    return res;
}

bool rtc_get(uint8_t num, struct tm* const date_time) {
    bool res = false;
    res = rtc_internal_get(num, date_time);
    if(res) {
        res = is_valid_time(date_time);
        if(res) {
            LOG_DEBUG(LG_RTC, "Get,Ok!");
        } else {
            LOG_ERROR(LG_RTC, "NoValidTime");
        }
    } else {
        LOG_ERROR(LG_RTC, "Get,Err");
    }
    return res;
}

bool rtc_start(uint8_t num) {
    bool res = false;
    return res;
}

bool rtc_stop(uint8_t num) {
    bool res = false;
    return res;
}



bool rtc_ctrl(uint8_t num, bool on_off) {
    bool res = false;
    if(on_off) {
        res = rtc_start(num);
    } else {
        res = rtc_stop(num);
    }
    return res;
}

static bool rtc_init_common_one(const RtcConfig_t*const Config, RtcHandle_t* const Node) {
    bool res = false;
    if(Node) {
        if(Config) {
            Node->format = Config->format;
            Node->ref_clock = Config->ref_clock;
            Node->rtc_location = Config->rtc_location;
            Node->num = Config->num;
            Node->name = Config->name;
            Node->valid = true;

            Node->init_done = false;
            Node->error_cnt = 0;
            Node->int_cnt = 0;
            res = true;
        }
    }
    return res;
}


bool rtc_init_custom(void){
    bool res = true;
    return res;
}


bool rtc_adjust_by_build_time(uint8_t num) {
    bool res = false;
    struct tm time_date_compile = {0};
    LOG_INFO(LG_RTC, "CompileDate: %s", __DATE__);
    LOG_INFO(LG_RTC, "CompileTime: %s", __TIME__);
    LOG_INFO(LG_RTC, "CompileTimeStamp: %s", __TIMESTAMP__);
    res = date_parse(&time_date_compile, __DATE__);
    if(res) {
        res = time_parse(&time_date_compile, __TIME__);
        if(res) {
            //res = print_time_date("Compile", &time_date_compile, true);

            RtcHandle_t* Node = RtcGetNode(num);
            int32_t diff = time_date_cmp(&Node->TimeDate, &time_date_compile);
            if(0 < diff) {
                LOG_WARNING(LG_RTC, "SetByCompileTimeStamp");
                res = rtc_set(num, &time_date_compile);
            } else {
                LOG_WARNING(LG_RTC, "CompileTimeStamp less then current time %d s", diff);
            }
        } else {
            LOG_ERROR(LG_RTC, "CompileTimeParseErr: %s", __TIME__);
        }
    } else {
        LOG_ERROR(LG_RTC, "CompileDateParseErr: %s", __DATE__);
    }

    return res;
}

bool rtc_init_one(uint8_t num) {
    bool res = false ;
    LOG_WARNING(LG_RTC,"RTC%u,Init...", num);
    const RtcConfig_t* Config=RtcGetConfig(num);
    if(Config) {
        RtcHandle_t* Node = RtcGetNode(num);
        if(Node) {
            res = rtc_init_common_one(Config, Node);

            switch(Node->rtc_location) {
                case RTC_LOCATION_INTERNAL: {
                    res = rtc_internal_init_one(num) ;
                } break;
                case RTC_LOCATION_EXTERAL: {
                    res = false ;
                } break;
                   default: {
                        res = false ;
                } break;
            }
            //res =  rtc_adjust_by_build_time(num);

        }
    }
    return res;
}

COMPONENT_INIT_PATTERT(LG_RTC, RTC, rtc)
