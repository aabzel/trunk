#include "zed_f9p_drv.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef HAS_CALENDAR
#include "calendar.h"
#endif
#include "common_diag.h"
#ifdef HAS_LOG
#include "cli_manager.h"
#include "log.h"
#endif
#include "clocks.h"
#ifdef HAS_FLASH_FS
#include "flash_fs.h"
#endif
#include "gnss_diag.h"
#ifdef HAS_NMEA
#include "nmea_protocol.h"
#endif
#include "none_blocking_pause.h"
#ifdef HAS_PARAM
#include "param_ids.h"
#endif
#include "sys_config.h"
#include "system.h"
#include "task_config.h"
#include "task_info.h"
#include "time_diag.h"
#include "time_mcal.h"
#ifdef HAS_RTCM3
#include "rtcm3_protocol.h"
#endif
#ifdef HAS_RS232
#include "rs232_drv.h"
#endif
#ifdef HAS_SX1262
#include "sx1262_drv.h"
#endif
#include "system_diag.h"
#include "uart_common.h"
#ifdef HAS_UBX_PTOTO
#include "ublox_driver.h"
#include "ubx_key_ids.h"
#include "ubx_protocol.h"
#endif
#ifdef HAS_CLI
#include "writer_config.h"
#endif
#include "zed_f9p_diag.h"

extern ZedF9P_t ZedF9P = {0};

#if((!defined(HAS_GPS_CORRECTION) && !defined(HAS_GLONASS_CORRECTION)) && defined(HAS_GNSS_RTK)) &&                    \
    (!defined(HAS_GALILEO_CORRECTION) && !defined(HAS_BEI_DOU_CORRECTION))
#error "Some corrections must be included in build"
#endif

#ifdef HAS_GNSS_RTK
static bool zed_f9p_proc_base(void) {
    bool res = false;
#ifdef HAS_SX1262
    Sx1262Instance.sync_reg = false;
#endif

    if(task_data[TASK_ID_NMEA].on) {
        task_data[TASK_ID_NMEA].on = false;
    }

    if(IF_CAN == ZedF9P.channel) {
#ifdef HAS_CLI
        res = cli_set_echo(true);
#endif
#ifdef HAS_RTCM3
        Rtcm3Protocol[IF_UART1].forwarding[IF_LORA] = false;
        Rtcm3Protocol[IF_UART1].forwarding[IF_RS232] = false;
#ifdef HAS_CAN
        Rtcm3Protocol[IF_UART1].forwarding[IF_CAN] = true;
#endif
#endif
#ifdef HAS_CAN
        task_data[TASK_ID_TCAN4550].on = true;
#endif
    }

    if(IF_RS232 == ZedF9P.channel) {
#ifdef HAS_CLI
        res = cli_set_echo(false);
#endif
#ifdef HAS_RTCM3
        Rtcm3Protocol[IF_UART1].forwarding[IF_LORA] = false;
        Rtcm3Protocol[IF_UART1].forwarding[IF_RS232] = true;
#ifdef HAS_CAN
        Rtcm3Protocol[IF_UART1].forwarding[IF_CAN] = false;
#endif
#endif
        task_data[TASK_ID_RS232].on = true;
#ifdef HAS_RS232
        rs232.ping = true;
#endif
    }

    if(IF_LORA == ZedF9P.channel) {
#ifdef HAS_RTCM3
        Rtcm3Protocol[IF_UART1].forwarding[IF_LORA] = true;
        Rtcm3Protocol[IF_UART1].forwarding[IF_RS232] = false;
#ifdef HAS_CAN
        Rtcm3Protocol[IF_UART1].forwarding[IF_CAN] = false;
#endif
#endif
        task_data[TASK_ID_RS232].on = false;
#ifdef HAS_RS232
        rs232.ping = false;
#endif
    }

    return res;
}
#endif /*HAS_GNSS_RTK*/

#ifdef HAS_GNSS_RTK
static bool zed_f9p_proc_rover(void) {
    bool res = true;
    if(task_data[TASK_ID_UBX].on) {
        task_data[TASK_ID_UBX].on = false;
    }
#ifdef HAS_NMEA
    task_data[TASK_ID_NMEA].on = true;
#endif

    if(IF_CAN == ZedF9P.channel) {
#ifdef HAS_CLI
        res = cli_set_echo(true);
#endif
#ifdef HAS_CAN
        // can.ping = true;
#endif
    }

    if(IF_RS232 == ZedF9P.channel) {
#ifdef HAS_CLI
        res = cli_set_echo(false);
#endif
#ifdef HAS_RS232
        rs232.ping = true;
#endif
    }
    if(IF_LORA == ZedF9P.channel) {
#ifdef HAS_LORA
        task_data[TASK_ID_LORA].on = false;
#endif
#ifdef HAS_RS232
        task_data[TASK_ID_RS232].on = false;
        rs232.ping = false;
#endif
    }

    return res;
}
#endif

static bool zed_f9p_proc_none(void) {
    bool res = false;
    task_data[TASK_ID_NMEA].on = true;
    task_data[TASK_ID_UBX].on = true;
    return res;
}

bool zed_f9p_proc(void) {
    /*is new GNSS samples*/
    bool res = false;

    switch(ZedF9P.rtk_mode) {
#ifdef HAS_GNSS_RTK
    case RTK_BASE_SURVEY_IN:
    case RTK_BASE_FIX: {
        res = zed_f9p_proc_base();
    } break;

    case RTK_ROVER: {
        res = zed_f9p_proc_rover();
    } break;
#endif
    case RTK_NONE: {
        res = zed_f9p_proc_none();
    } break;
    default:
        res = false;
        break;
    }

    return res;
}
#ifdef HAS_UBLOX
/*Radio Technical Commission for Maritime Services)*/

static const keyValItem_t NormCfgLut[] = {
    {CFG_UART1_BAUDRATE, 38400, SC_NONE},
    {CFG_UART1INPROT_NMEA, 0, SC_NONE},
    {CFG_UART1OUTPROT_NMEA, 1, SC_NONE},
    {CFG_UART1OUTPROT_UBX, 1, SC_NONE},
    {CFG_MSGOUT_NMEA_ID_ZDA_UART1, 1, SC_NONE},
    {CFG_MSGOUT_UBX_NAV_PVT_UART1, 1, SC_NONE},
    {CFG_MSGOUT_UBX_NAV_PVT_USB, 1, SC_NONE},
    {CFG_MSGOUT_UBX_NAV_POSLLH_UART1, 1, SC_NONE},
    {CFG_MSGOUT_UBX_NAV_HPPOSLLH_UART1, 1, SC_NONE},
};

#ifdef HAS_GNSS_RTK
static const keyValItem_t BaseCfgLutMain[] = {
    {CFG_UART1_BAUDRATE, 38400, SC_NONE},
    {CFG_UART1INPROT_NMEA, 0, SC_NONE},
    {CFG_UART1INPROT_RTCM3X, 0, SC_NONE},
    {CFG_UART1INPROT_UBX, 1, SC_NONE},
    {CFG_UART1OUTPROT_NMEA, 0, SC_NONE},
    {CFG_UART1OUTPROT_RTCM3X, 1, SC_NONE},
    {CFG_UART1OUTPROT_UBX, 1, SC_NONE},
    {CFG_MSGOUT_UBX_NAV_PVT_UART1, 1, SC_NONE},
    {CFG_MSGOUT_UBX_NAV_POSLLH_UART1, 1, SC_NONE},
    {CFG_MSGOUT_UBX_NAV_HPPOSLLH_UART1, 1, SC_NONE},
    {CFG_MSGOUT_UBX_NAV_SVIN_UART1, 1, SC_NONE},
    // sparkfun Output rate of the RTCM-3X-TYPE1005 Stationary RTK  reference station ARP (Input/output)
    {CFG_MSGOUT_RTCM_3X_TYPE1005_UART1, 1, SC_NONE},
    {CFG_MSGOUT_RTCM_3X_TYPE1005_USB, 1, SC_NONE},
#ifdef HAS_GPS_CORRECTION
    // sparkfun Output rate of the RTCM-3X-TYPE1074 GPS MSM4 (Input/output)
    {CFG_MSGOUT_RTCM_3X_TYPE1074_UART1, 1, SC_GPS},
    {CFG_MSGOUT_RTCM_3X_TYPE1074_USB, 1, SC_GPS},
#endif
#ifdef HAS_GLONASS_CORRECTION
    // sparkfun Output rate of the RTCM-3X-TYPE1084 GLONASS MSM4 (Input/output)
    {CFG_MSGOUT_RTCM_3X_TYPE1084_UART1, 1, SC_GLONASS},
    {CFG_MSGOUT_RTCM_3X_TYPE1084_USB, 1, SC_GLONASS},
    // sparkfun Output rate of the RTCM-3X-TYPE1230 GLONASS L1 and L2 code-phase biases (Input/output)
    {CFG_MSGOUT_RTCM_3X_TYPE1230_UART1, 5, SC_GLONASS},
    // GLONASS L1 and L2 code-phase biases (Input/output)
    {CFG_MSGOUT_RTCM_3X_TYPE1230_USB, 5, SC_GLONASS},
#endif
#ifdef HAS_GALILEO_CORRECTION
    {CFG_MSGOUT_RTCM_3X_TYPE1094_UART1, 1, SC_GALILEO}, // Galileo MSM4 (Input/output) sparkfun recomends
    {CFG_MSGOUT_RTCM_3X_TYPE1094_USB, 1, SC_GALILEO},   // Galileo MSM4 (Input/output)
#endif
#ifdef HAS_BEI_DOU_CORRECTION
    {CFG_MSGOUT_RTCM_3X_TYPE1124_UART1, 1, SC_BEI_DOU}, // sparkfun Output rate of the RTCM-3X-TYPE1124 BeiDou MSM4
    {CFG_MSGOUT_RTCM_3X_TYPE1124_USB, 1, SC_BEI_DOU},   // BeiDou MSM4 (Input/output)
#endif
    {CFG_MSGOUT_UBX_NAV_PVT_USB, 1, SC_NONE},
    {CFG_MSGOUT_UBX_NAV_SVIN_USB, 1, SC_NONE},
};
#endif

#if 0
#ifdef HAS_GNSS_RTK
static const keyValItem_t BaseCfgLutOpt[] = {
    {CFG_UART1_BAUDRATE, 38400, SC_NONE},
    {CFG_UART1INPROT_NMEA, 0, SC_NONE},
    {CFG_UART1INPROT_RTCM3X, 0, SC_NONE},
    {CFG_UART1INPROT_UBX, 1, SC_NONE},
    {CFG_UART1OUTPROT_NMEA, 0, SC_NONE},
    {CFG_UART1OUTPROT_RTCM3X, 1, SC_NONE},
    {CFG_UART1OUTPROT_UBX, 1, SC_NONE},
    // sparkfun Output rate of the RTCM-3X-TYPE1005 Stationary RTK  reference station ARP (Input/output)
    {CFG_MSGOUT_UBX_RXM_RTCM_USB, 1, SC_NONE},
    {CFG_MSGOUT_RTCM_3X_TYPE1005_UART1, 1, SC_NONE},
#ifdef HAS_GPS_CORRECTION
    // Output rate of the RTCM-3X-TYPE1077 GPS MSM7 (Input/output)
    {CFG_MSGOUT_RTCM_3X_TYPE1077_UART1, 1, SC_GPS},
#endif
#ifdef HAS_GLONASS_CORRECTION
     // Output rate of the RTCM-3X-TYPE1087 GLONASS MSM7 (Input/output)
    {CFG_MSGOUT_RTCM_3X_TYPE1087_UART1, 1, SC_GLONASS},
    // sparkfun Output rate of the RTCM-3X-TYPE1230 GLONASS L1 and L2 code-phase biases (Input/output)
    {CFG_MSGOUT_RTCM_3X_TYPE1230_UART1, 5, SC_GLONASS},
    // GLONASS L1 and L2 code-phase biases (Input/output)
    {CFG_MSGOUT_RTCM_3X_TYPE1230_USB, 5, SC_GLONASS},
#endif
#ifdef HAS_GALILEO_CORRECTION
     // Galileo MSM7 (Input/output)Output rate of the RTCM-3X-TYPE1097
    {CFG_MSGOUT_RTCM_3X_TYPE1097_UART1, 1, SC_GALILEO},
#endif
#ifdef HAS_BEI_DOU_CORRECTION
     // Output rate of the RTCM-3X-TYPE1127 BeiDou MSM7 (Input/output)
    {CFG_MSGOUT_RTCM_3X_TYPE1127_UART1, 1,  SC_BEI_DOU},
#endif
    {CFG_MSGOUT_UBX_NAV_PVT_USB, 1, SC_NONE},
    {CFG_MSGOUT_UBX_NAV_SVIN_USB, 1, SC_NONE},
};
#endif
#endif /*0*/
#endif /*HAS_UBLOX*/

static bool zed_f9p_deploy_norm(void) {
    bool res = false, out_res = true;
    uint32_t i = 0;
    for(i = 0; i < ARRAY_SIZE(NormCfgLut); i++) {
        res = ubx_cfg_set_val(NormCfgLut[i].key_id, (uint8_t*)&NormCfgLut[i].u_value.u8[0],
                              ubx_keyid_2len(NormCfgLut[i].key_id), LAYER_MASK_RAM);
        if(false == res) {
#ifdef HAS_LOG
            LOG_ERROR(ZED_F9P, "SetKeyErr 0x%08x", NormCfgLut[i].key_id);
#endif
            out_res = false;
        }
    }

    task_data[TASK_ID_NMEA].on = true;
    return out_res;
}

#ifdef HAS_GNSS_RTK
bool zed_f9p_deploy_base(GnssCoordinate_t coordinate_base, double altitude_sea_lev_m, RTKmode_t receiver_mode,
                         uint32_t fixed_position_3daccuracy_mm) {
    bool res = false, out_res = true;
    res = is_valid_gnss_coordinates(coordinate_base);
    if(res) {
        res = false;
#ifdef HAS_UBLOX
        task_data[TASK_ID_UART0_FWD].on = false;
        task_data[TASK_ID_UART1_FWD].on = false;
        /*
          perform settings from here
          https://www.youtube.com/watch?v=FpkUXmM7mrc

          reset to dflt cfg
         */
        res = ubx_reset_to_dflt();
        if(false == res) {
#ifdef HAS_LOG
            LOG_ERROR(ZED_F9P, "Set Dflt error");
#endif
            out_res = false;
        }
        uint32_t i = 0;
        for(i = 0; i < ARRAY_SIZE(BaseCfgLutMain); i++) {
            switch(BaseCfgLutMain[i].satellite_constellation) {
            case SC_GPS:
                res = ZedF9P.corrections.gps;
                break;
            case SC_GLONASS:
                res = ZedF9P.corrections.glonass;
                break;
            case SC_GALILEO:
                res = ZedF9P.corrections.galileo;
                break;
            case SC_BEI_DOU:
                res = ZedF9P.corrections.beidou;
                break;
            default:
                res = true;
                break;
            }

            if(res) {
                res = ubx_cfg_set_val(BaseCfgLutMain[i].key_id, (uint8_t*)&BaseCfgLutMain[i].u_value.u8[0],
                                      ubx_keyid_2len(BaseCfgLutMain[i].key_id), LAYER_MASK_RAM);
                if(false == res) {
#ifdef HAS_LOG
                    LOG_ERROR(ZED_F9P, "Set 0x%x error", BaseCfgLutMain[i].key_id);
#endif
                    out_res = false;
                }
            }
        }
        /*Write base station antenna coordinates*/
        // UBX-CFG-TMODE3 (0x06 0x71)
        UbxCfgTmode3Data_t data;
        data.version = 0;
        data.svin_min_dur_s = MIN_2_SEC(4);
        data.mode = receiver_mode; /**/
        data.lla = 0x01;           /*Position is given in LAT/LON/ALT*/

        data.ecefXOrLat = 1e7 * coordinate_base.latitude;
        data.ecefYOrLon = 1e7 * coordinate_base.longitude;
        data.ecefZOrAlt = altitude_sea_lev_m * 100;
        data.fixedPosAcc = 10 * fixed_position_3daccuracy_mm;
        data.svinAccLimit = 10 * fixed_position_3daccuracy_mm;
        res = ubx_send_message_ack(UBX_CLA_CFG, UBX_ID_CFG_TMODE3, (uint8_t*)&data, sizeof(data));
        if(false == res) {
#ifdef HAS_LOG
            LOG_ERROR(ZED_F9P, "SetBaseDotErr");
#endif
            out_res = false;
        } else {
#ifdef HAS_LOG
            LOG_INFO(ZED_F9P, "SetBaseDotOk");
#endif
        }

        ZedF9P.rtk_mode = receiver_mode;
        task_data[TASK_ID_NMEA].on = false;
#ifdef HAS_RTCM3
        if(IF_LORA == ZedF9P.channel) {
            Rtcm3Protocol[IF_UART1].forwarding[IF_LORA] = true;
            Rtcm3Protocol[IF_UART1].forwarding[IF_RS232] = false;
#ifdef HAS_CAN
            Rtcm3Protocol[IF_UART1].forwarding[IF_CAN] = false;
#endif
#ifdef HAS_SX1262
            Sx1262Instance.check_connectivity = false;
            Sx1262Instance.sync_rssi = false;
#endif
        }
        if(IF_RS232 == ZedF9P.channel) {
            Rtcm3Protocol[IF_UART1].forwarding[IF_LORA] = false;
            Rtcm3Protocol[IF_UART1].forwarding[IF_RS232] = true;
#ifdef HAS_CAN
            Rtcm3Protocol[IF_UART1].forwarding[IF_CAN] = false;
#endif
        }
        if(IF_CAN == ZedF9P.channel) {
            Rtcm3Protocol[IF_UART1].forwarding[IF_LORA] = false;
            Rtcm3Protocol[IF_UART1].forwarding[IF_RS232] = false;
#ifdef HAS_CAN
            Rtcm3Protocol[IF_UART1].forwarding[IF_CAN] = true;
#endif
        }
#endif /*HAS_RTCM3*/
#endif /*HAS_UBLOX*/
    } else {
#ifdef HAS_LOG
        LOG_ERROR(ZED_F9P, "InvalBaseGNSScoordinate");
#endif
    }
    return out_res;
}
#endif

#if defined(HAS_UBLOX) && defined(HAS_GNSS_RTK)
static const keyValItem_t RoverCfgLut[] = {
    {CFG_UART1_BAUDRATE, 38400, SC_NONE},
    {CFG_UART1INPROT_UBX, 1, SC_NONE},
    {CFG_UART1INPROT_NMEA, 0, SC_NONE},
    {CFG_UART1INPROT_RTCM3X, 1, SC_NONE},
    {CFG_UART1OUTPROT_UBX, 1, SC_NONE},
    {CFG_UART1OUTPROT_NMEA, 1, SC_NONE},
    {CFG_MSGOUT_UBX_NAV_PVT_UART1, 1, SC_NONE},
    {CFG_UART1OUTPROT_RTCM3X, 0, SC_NONE},
    {CFG_USBINPROT_UBX, 1, SC_NONE},
    {CFG_USBINPROT_NMEA, 1, SC_NONE},
    {CFG_USBINPROT_RTCM3X, 1, SC_NONE},
    {CFG_USBOUTPROT_UBX, 1, SC_NONE},
    {CFG_USBOUTPROT_RTCM3X, 0, SC_NONE},
    {CFG_MSGOUT_UBX_NAV_POSECEF_UART1, 1, SC_NONE},
    {CFG_MSGOUT_UBX_NAV_POSLLH_UART1, 1, SC_NONE},
    {CFG_MSGOUT_UBX_NAV_HPPOSLLH_UART1, 1, SC_NONE},
    {CFG_MSGOUT_UBX_RXM_RTCM_USB, 1, SC_NONE},
    {CFG_MSGOUT_NMEA_ID_ZDA_UART1, 1, SC_NONE},
};
#endif

#ifdef HAS_GNSS_RTK
bool zed_f9p_deploy_rover(void) {
    bool out_res = true;
#ifdef HAS_UBLOX
    bool res = false;
#ifdef HAS_SX1262
    Sx1262Instance.sync_reg = false;
#endif
    task_data[TASK_ID_PARAM].on = false;
    task_data[TASK_ID_UBX].on = false;
    /*
      perform settings from here
      https://www.youtube.com/watch?v=FpkUXmM7mrc
     */
    res = ubx_reset_to_dflt();
    if(false == res) {
#ifdef HAS_LOG
        LOG_ERROR(ZED_F9P, "Set Dflt error");
#endif
        // out_res = false;
    }

    uint32_t i = 0;
    for(i = 0; i < ARRAY_SIZE(RoverCfgLut); i++) {

        res = ubx_cfg_set_val(RoverCfgLut[i].key_id, (uint8_t*)&RoverCfgLut[i].u_value.u8[0],
                              ubx_keyid_2len(RoverCfgLut[i].key_id), LAYER_MASK_RAM);

        if(false == res) {
#ifdef HAS_LOG
            LOG_ERROR(ZED_F9P, "Key:0x%08x set Error", RoverCfgLut[i].key_id);
#endif
            out_res = false;
        }
    }
    /*adjust output rate*/
    res = ubx_set_rate(ZedF9P.rate_ms, TIME_UTC);
    if(false == res) {
#ifdef HAS_LOG
        LOG_ERROR(ZED_F9P, "SetRateUtcErr");
#endif
        out_res = false;
    }
    res = ubx_set_rate(ZedF9P.rate_ms, TIME_GPS);
    if(false == res) {
#ifdef HAS_LOG
        LOG_ERROR(ZED_F9P, "SetRateGpsErr");
#endif
        out_res = false;
    }
    res = ubx_set_rate(ZedF9P.rate_ms, TIME_GLONASS);
    if(false == res) {
#ifdef HAS_LOG
        LOG_ERROR(ZED_F9P, "SetRateGloErr");
#endif
        out_res = false;
    }
    res = ubx_set_rate(ZedF9P.rate_ms, TIME_GALILEO);
    if(false == res) {
#ifdef HAS_LOG
        LOG_ERROR(ZED_F9P, "SetRateGalErr");
#endif
        out_res = false;
    }
    res = ubx_set_rate(ZedF9P.rate_ms, TIME_BEIDOU);
    if(false == res) {
#ifdef HAS_LOG
        LOG_ERROR(ZED_F9P, "SetRateBeErr");
#endif
        out_res = false;
    }
#endif
    return out_res;
}
#endif

#ifdef HAS_LOG
#define LOAD_PARAM_ZED(PAR_ID, VARIABLE, EXP_LEN, VAR_NAME, DEF_VAL, PARSER_FUNC)                                      \
    do {                                                                                                               \
        uint16_t file_len = 0;                                                                                         \
        res = mm_get(PAR_ID, (uint8_t*)&VARIABLE, sizeof(VARIABLE), &file_len);                                        \
        if((true == res) && ((EXP_LEN) == file_len)) {                                                                 \
            if((EXP_LEN) <= 4) {                                                                                       \
                LOG_INFO(ZED_F9P, "Set" VAR_NAME "FromParams %u [%s]", VARIABLE, PARSER_FUNC(VARIABLE));               \
            } else {                                                                                                   \
                LOG_INFO(ZED_F9P, "Set" VAR_NAME "FromParams [%s]", PARSER_FUNC(VARIABLE));                            \
            }                                                                                                          \
        } else {                                                                                                       \
            LOG_WARNING(ZED_F9P, "SetDflt" VAR_NAME " [%s]", PARSER_FUNC(DEF_VAL));                                    \
            /*memcpy((void *)&VARIABLE , (void *)&DEF_VAL, EXP_LEN);*/                                                 \
            VARIABLE = DEF_VAL;                                                                                        \
            res = false;                                                                                               \
            out_res = false;                                                                                           \
        }                                                                                                              \
    } while(0)
#else
#define LOAD_PARAM_ZED(PAR_ID, VARIABLE, EXP_LEN, VAR_NAME, DEF_VAL, PARSER_FUNC)                                      \
    do {                                                                                                               \
        uint16_t file_len = 0;                                                                                         \
        res = mm_get(PAR_ID, (uint8_t*)&VARIABLE, sizeof(VARIABLE), &file_len);                                        \
        if(!((true == res) && ((EXP_LEN) == file_len))) {                                                              \
            VARIABLE = DEF_VAL;                                                                                        \
            res = false;                                                                                               \
            out_res = false;                                                                                           \
        }                                                                                                              \
    } while(0)
#endif

bool zed_f9p_load_params(void) {
    bool res = true;
#if defined(HAS_FLASH_FS) && defined(HAS_PARAM)
    bool out_res = true;
    ZedF9P.time_zone = 0;
    ZedF9P.coordinate_base.longitude = 0.0;
    ZedF9P.fixed_position_3daccuracy_mm = METER_TO_MM(1);
    ZedF9P.coordinate_base.latitude = 0.0;
    ZedF9P.corrections.gps = true;
    ZedF9P.corrections.glonass = true;
    ZedF9P.corrections.galileo = true;
    ZedF9P.corrections.beidou = true;
    LOAD_PARAM_ZED(PAR_ID_GNSS_MODE, ZedF9P.rtk_mode, 1, "mode", RTK_BASE_SURVEY_IN, rtk_mode2str);

#ifdef HAS_GNSS_RTK
    LOAD_PARAM_ZED(PAR_ID_GPS, ZedF9P.corrections.gps, 1, "GpsCor", 1, OnOffToStr);
    LOAD_PARAM_ZED(PAR_ID_GLONASS, ZedF9P.corrections.glonass, 1, "GlonassCor", 0, OnOffToStr);
    LOAD_PARAM_ZED(PAR_ID_GALILEO, ZedF9P.corrections.galileo, 1, "GalileoCor", 0, OnOffToStr);
    LOAD_PARAM_ZED(PAR_ID_BEI_DOU, ZedF9P.corrections.beidou, 1, "BeiDouCor", 0, OnOffToStr);
    LOAD_PARAM_ZED(PAR_ID_BASE_ACC, ZedF9P.fixed_position_3daccuracy_mm, 4, "BaseAcc", METER_TO_MM(1), mm2str);
    LOAD_PARAM_ZED(PAR_ID_RTK_CHANNEL, ZedF9P.channel, 1, "RTKchannel", IF_LORA, interface2str);
#endif
    LOAD_PARAM_ZED(PAR_ID_TIME_ZONE, ZedF9P.time_zone, 1, "TimeZone UTC+", 3, uint2str);

#ifdef HAS_GNSS_RTK
    switch(ZedF9P.rtk_mode) {
    case RTK_BASE_SURVEY_IN:
    case RTK_BASE_FIX: {
        GnssCoordinate_t dflt_coordinate_base = {55.678422826, 37.632228014};
        LOAD_PARAM_ZED(PAR_ID_BASE_ALT, ZedF9P.alt_base, 8, "RTKBaseAlt", 200.0, Distance2str);
        LOAD_PARAM_ZED(PAR_ID_BASE_LOCATION, ZedF9P.coordinate_base, 16, "RTKBaseDot", dflt_coordinate_base,
                       GnssDot2str);

    } break;
    case RTK_ROVER: {
        LOAD_PARAM_ZED(PAR_ID_GNSS_PERIOD, ZedF9P.rate_ms, 2, "GnssPeriod", DFLT_GNSS_PER_MS, mSec2str);
    } break;
    default:
        break;
    }
#endif

#endif /*HAS_FLASH_FS && HAS_PARAM*/
    if(out_res) {
        ZedF9P.is_init = true;
    }
    return out_res;
}

bool zed_f9p_init(void) {
    bool res = true;
#ifdef HAS_LOG
    res = set_log_level(ZED_F9P, LOG_LEVEL_INFO);
#endif
    ZedF9P.rate_ms = DFLT_GNSS_PER_MS;
    ZedF9P.channel = IF_LORA;
    res = zed_f9p_load_params();
    if(res) {
        switch(ZedF9P.rtk_mode) {
        case RTK_NONE:
            res = zed_f9p_deploy_norm();
            break;
#ifdef HAS_GNSS_RTK
        case RTK_BASE_SURVEY_IN:
        case RTK_BASE_FIX:
            res = zed_f9p_deploy_base(ZedF9P.coordinate_base, ZedF9P.alt_base, ZedF9P.rtk_mode,
                                      ZedF9P.fixed_position_3daccuracy_mm);
            break;
        case RTK_ROVER:
            res = zed_f9p_deploy_rover();
            break;
#endif
        default:
#ifdef HAS_LOG
            LOG_ERROR(ZED_F9P, "rtkMode:%u=%s", ZedF9P.rtk_mode, rtk_mode2str(ZedF9P.rtk_mode));
#endif
            res = false;
            break;
        }
    } else {
#ifdef HAS_LOG
        LOG_ERROR(ZED_F9P, "ParLoadErr");
#endif
    }
    return res;
}
