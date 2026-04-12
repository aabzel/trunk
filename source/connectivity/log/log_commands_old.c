#include "log_commands.h"

#include <string.h>

#include "convert.h"
#include "data_utils.h"
#include "log.h"
#include "log_utils.h"
#ifdef HAS_DIAG
#include "common_diag.h"
#include "system_diag.h"
#endif
//#include "table_utils.h"
#include "terminal_codes.h"
//#include "writer_config.h"

bool cmd_log_level(int32_t argc, char* argv[]) {
    bool res = true;
    facility_t facility = UNKNOWN_FACILITY;
    log_level_t level = LOG_LEVEL_UNKNOWN;

    if(0 == argc) {
        res = true;
    }

    if(1 <= argc) {
        facility = str2facility(argv[0]);
        if(UNKNOWN_FACILITY == facility) {
            LOG_WARNING(LOG, "UnknownFacility %s", argv[0]);
            res = true;
        } else {
#ifdef HAS_SYSTEM_DIAG
            LOG_INFO(LOG, "Spot %u=%s", facility, FacilityToStr(facility));
#endif
            res = true;
        }
    }

    if(2 <= argc) {
        level = str2level(argv[1]);
        if(LOG_LEVEL_UNKNOWN == level) {
            LOG_ERROR(LOG, "Unknown log level name %s", argv[1]);
            res = false;
        }
    }

    if(res) {
        switch(argc) {
        case 0: {
            res = log_level_diag("");
        } break;
        case 1: {
            res = log_level_diag(argv[0]);
            // if(ALL_FACILITY == facility) {
            //    res = log_levele_diag("","");
            //} else {
            //    cli_printf("%s %s " CRLF, FacilityToStr(facility), log_level_name_long(log_level_get(facility)));
            //}
            // res = false;

        } break;
        case 2: {
            res = set_log_level(facility, level);

        } break;
        default: {
            LOG_ERROR(LOG, "Usage log_level [facility|*|ALL [log_level]]");
            res = false;

        } break;
        }
    }

    return res;
}

#ifdef HAS_LOG_EXT_CMD
bool cmd_log_color(int32_t argc, char* argv[]) {
    bool res = false;
    bool colored = false;
    if(1 == argc) {
        res = try_str2bool(argv[0], &colored);
        if(false == res) {
            LOG_ERROR(LOG, "ParseErr value %s", argv[0]);
        }
    }
    if(res) {
#ifdef HAS_LOG_COLOR
        Log.colored = colored;
#endif
    } else {
        LOG_ERROR(LOG, "Usage: lc OnOff");
    }
    return res;
}
#endif

bool cmd_log_try_color(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t style = 0;
    uint8_t text_color = 34;
    uint8_t back_color = 40;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &style);
        if(false == res) {
            LOG_ERROR(LOG, "ParseErr style %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &text_color);
        if(false == res) {
            LOG_ERROR(LOG, "ParseErr text_color %s", argv[1]);
        }
    }
    if(3 <= argc) {
        res = try_str2uint8(argv[2], &back_color);
        if(false == res) {
            LOG_ERROR(LOG, "ParseErr value %s", argv[2]);
        }
    }
    if(res) {
        cli_printf("\x1b[%u;%u;%um"
                   "TextSample"
                   "%s" CRLF,
                   style, text_color, back_color, VT_SETCOLOR_NORMAL);
    } else {
    }
    return res;
}

#ifdef HAS_LOG_EXT_CMD
bool cmd_log_flush(int32_t argc, char* argv[]) {
    bool flag = false;
    if(argc != 1) {
        LOG_ERROR(LOG, "Usage log_flush on|off");
        return false;
    }
    if(!try_str2bool(argv[0], &flag)) {
        LOG_ERROR(LOG, "ParseErr value %s", argv[0]);
        return false;
    }
    Log.flush = flag;
    return true;
}
#endif

bool cmd_log_diag(int32_t argc, char* argv[]) {
    bool res = true;
    LOG_INFO(LOG, "Flush  %s", OnOffToStr(Log.flush));
    LOG_INFO(LOG, "NewLine %s", OnOffToStr(Log.new_line));
#ifdef HAS_LOG_DIAG
    LOG_INFO(LOG, "FacilityName %s", OnOffToStr(Log.facility_name));
#endif

#ifdef HAS_LOG_TIME_STAMP
    LOG_INFO(LOG, "TimeStamp %s", OnOffToStr(Log.time_stamp));
#endif

#ifdef HAS_LOG_COLOR
    LOG_INFO(LOG, "Colored:%s", OnOffToStr(Log.colored));
#endif
    return res;
}

bool cmd_log_init(int32_t argc, char* argv[]) {
    bool res = true;
    res = log_mcal_init();
    return res;
}

bool log_time_stamp_command(int32_t argc, char* argv[]) {
    bool res = true;
    bool on_off = true;

    if(1 <= argc) {
        res = try_str2bool(argv[0], &on_off);
        log_info_res(LOG, res, "OnOff");
    }

    if(res) {
        res = log_level_time_stamp(on_off);
        log_info_res(LOG, res, "TimeStamp");
    }
    return res;
}
