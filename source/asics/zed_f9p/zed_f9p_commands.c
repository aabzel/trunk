#include "zed_f9p_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "convert.h"
#include "flash_fs.h"
#include "gnss_diag.h"
#include "io_utils.h"
#include "log.h"
#include "param_ids.h"
#include "time_diag.h"
#include "zed_f9p_drv.h"

bool zed_f9p_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        io_printf("UTC %d" CRLF, ZedF9P.time_zone);
        res = print_time_date("ZedF9P:", &ZedF9P.time_date, true);
        res = true;
    } else {
        LOG_ERROR(ZED_F9P, "Usage: zfd");
    }
    return res;
}

#ifdef HAS_GNSS_RTK
bool zed_f9p_base_dot_command(int32_t argc, char* argv[]) {
    bool res = false;
    GnssCoordinate_t coordinate_base;
    double altitude_sea_lev_m = 0.0;

    if(1 <= argc) {
        res = try_str2double(argv[0], &coordinate_base.latitude);
    }
    if(2 <= argc) {
        res = try_str2double(argv[1], &coordinate_base.longitude);
    }
    if(3 <= argc) {
        res = try_str2double(argv[2], &altitude_sea_lev_m);
        if(res) {
            ZedF9P.alt_base = altitude_sea_lev_m;
#ifdef HAS_PARAM
            res = mm_set(PAR_ID_BASE_ALT, (uint8_t*)&ZedF9P.alt_base, sizeof(double));
            if(false == res) {
                LOG_ERROR(ZED_F9P, "ParamSetAltError");
            } else {
                LOG_INFO(ZED_F9P, "AltOk!");
            }
#endif /*HAS_PARAM*/
        }
    }

    if((2 <= argc) && res) {
        res = is_valid_gnss_coordinates(coordinate_base);
        if(false == res) {
            LOG_ERROR(ZED_F9P, "InvalidBaseDot");
        }
    }

    if((2 <= argc) && res) {
        ZedF9P.coordinate_base = coordinate_base;
#ifdef HAS_PARAM
        res = mm_set(PAR_ID_BASE_LOCATION, (uint8_t*)&ZedF9P.coordinate_base, sizeof(GnssCoordinate_t));
        if(false == res) {
            LOG_ERROR(ZED_F9P, "ParamSetError");
        } else {
            LOG_INFO(ZED_F9P, "DotOk!");
        }
#endif /*HAS_PARAM*/
    }

    if(false == res) {
        LOG_ERROR(ZED_F9P, "Usage: zfbd lat lon alt");
    }
    return res;
}
#endif

#ifdef HAS_GNSS_RTK
bool zed_f9p_base_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 == argc) {
        res = zed_f9p_load_params();
        if(res) {
            LOG_ERROR(ZED_F9P, "BaseParamGetErr");
        }
    }

    if(res) {
        res = zed_f9p_deploy_base(ZedF9P.coordinate_base, ZedF9P.alt_base, ZedF9P.rtk_mode,
                                  ZedF9P.fixed_position_3daccuracy_mm);
        if(res) {
            LOG_INFO(ZED_F9P, "RtkBaseStarted");
        }
    }

    if(false == res) {
        LOG_ERROR(ZED_F9P, "Usage: zfb");
    }
    return res;
}
#endif

#ifdef HAS_GNSS_RTK
bool zed_f9p_rover_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = zed_f9p_deploy_rover();
        if(res) {
            LOG_INFO(ZED_F9P, "OK");
        }
    }
    if(false == res) {
        LOG_ERROR(ZED_F9P, "Usage: zfr");
    }
    return res;
}
#endif
