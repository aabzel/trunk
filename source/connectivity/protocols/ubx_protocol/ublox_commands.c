#include "ublox_commands.h"

#include <stdbool.h>
#include <stdio.h>

#include "byte_utils.h"
#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#include "gnss_diag.h"
#include "io_utils.h"
#include "log.h"
#include "table_utils.h"
#include "time_diag.h"
#include "ubx_diag.h"
#include "ublox_driver.h"
#include "ubx_protocol.h"
#include "writer_config.h"
#include "writer_generic.h"

static bool ubx_diag(void) {
    io_printf("tx pkt cnt: %u" CRLF, UbloxProtocol.tx_pkt_cnt);
    io_printf("rx pkt cnt: %u" CRLF, UbloxProtocol.rx_pkt_cnt);
    io_printf("crc cnt: %u" CRLF, UbloxProtocol.crc_err_cnt);
    io_printf("rx state: %u" CRLF, UbloxProtocol.rx_state);
    io_printf("ack cnt: %u" CRLF, UbloxProtocol.ack_cnt);
    io_printf("diag: %u" CRLF, UbloxProtocol.diag);
#if defined(HAS_UBX_DEBUG) && defined(HAS_DEBUG)
    io_printf("sync cnt: %u" CRLF, UbloxProtocol.sync_cnt);
    io_printf("min len: %u" CRLF, UbloxProtocol.min_len);
    io_printf("max len: %u" CRLF, UbloxProtocol.max_len);
#endif
    io_printf("chip id:");
    print_mem(NavInfo.id, 5, true, false, true, true);

    uint8_t i = 0;

    table_col_t cols[] = {{7, "class"}, {8, "rx_cnt"}};
    table_header(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
    for(i = 0; i < ARRAY_SIZE(tableRxClass); i++) {
        if(tableRxClass[i].class_val) {
            io_printf(TSEP "  0x%02x " TSEP, tableRxClass[i].class_val);
            io_printf(" %u ", tableRxClass[i].cnt);
            io_printf(CRLF);
        }
    }
    table_row_bottom(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
    return true;
}
#if 0
static char* ubx_print_key_val(uint16_t i) {
    static char buff[20] = "";
    if(i < UBX_KEY_CNT) {
        if(UBX_U2 == keyValTable[i].type) {
            snprintf(buff, sizeof(buff), " %u ", keyValTable[i].u_value.u16);
        }
    }
    return buff;
}
static bool ubx_key_val_diag(void) {
    uint8_t i = 0;
    table_col_t cols[] = {{7, "key"}, {8, "val"}};
    table_header(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
    for(i = 0; i < ARRAY_SIZE(keyValTable); i++) {
        if(keyValTable[i].key_id) {
            io_printf(TSEP "  0x%08x " TSEP, keyValTable[i].key_id);
            io_printf(" %s ", ubx_print_key_val(i));
            io_printf(CRLF);
        }
    }
    table_row_bottom(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
    return true;
}

bool ubx_print_key_val_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = ubx_key_val_diag();
    } else {
        LOG_ERROR(UBX, "Usage: ubk");
    }
    return res;
}
#endif


bool ubx_diag_base_command(int32_t argc, char* argv[]){
    bool res = false;
    if(0 == argc) {
        LOG_INFO(UBX,"FixType: %u %s", NavInfo.FixType, FixType2Str(NavInfo.FixType));
        io_printf("SyrveyInAcc: %f m" CRLF, ( (double) NavInfo.survey_in_mean_position_acc_mm )/ 1000.0);
        io_printf("RxMode: %u %s" CRLF, NavInfo.BaseRxMode, ReceiverMode2Str(NavInfo.BaseRxMode));
        io_printf("SvInMinDur: %u s" CRLF, NavInfo.svin_min_dur_s);
        io_printf("FixedPosAcc: %f m" CRLF, NavInfo.fixedPosAcc_mm/1000.0);
        io_printf("SvInObsTime: %u s" CRLF, NavInfo.survey_in_observation_time);
        res = true;
    }else{
        LOG_ERROR(UBX, "Usage: ubb");
    }
    return res;
}

bool ubx_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(1 <= argc) {
        res = try_str2bool(argv[0], &UbloxProtocol.diag);
        if(false == res) {
            LOG_ERROR(UBX, "Unable to extract diag");
        }
    }
    if(0 == argc) {
        res = true;
    }

    if(1 < argc) {
        LOG_ERROR(UBX, "Usage: ubd");
    }
    if(res) {
        res = ubx_diag();
    }
    return res;
}

#ifdef HAS_UBX_EXT
bool ubx_get_key_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t layers = 0;
    uint32_t key_id = 0;
    if(1 <= argc) {
        res = try_str2uint32(argv[0], &key_id);
        if(false == res) {
            LOG_ERROR(UBX, "Unable to extract key_id %s", argv[0]);
        }
    }
    if(2 <= argc) {
        res = try_str2uint8(argv[1], &layers);
        if(false == res) {
            LOG_ERROR(UBX, "Unable to extract layers %s", argv[1]);
        }
    }

    if(2 < argc) {
        LOG_ERROR(UBX, "Usage: ubg key_id");
    }
    if(res) {
        res = ubx_cfg_get_val(key_id, layers);
        if(false == res) {
            LOG_ERROR(UBX, "UbxCfgGetErr");
        }
    }
    return res;
}
#endif

#ifdef  HAS_UBX_EXT
bool ubx_send_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t class_num = 0;
    uint8_t id = 0;
    uint32_t payload_len = 0U;
    uint8_t payload[100] = {0};
    if(2 <= argc) {
        res = true;
        payload_len = 0U;
        if(true == res) {
            res = try_str2uint8(argv[0], &class_num);
            if(false == res) {
                LOG_ERROR(UBX, "Unable to extract Class %s", argv[0]);
            }
        }
        if(true == res) {
            res = try_str2uint8(argv[1], &id);
            if(false == res) {
                LOG_ERROR(UBX, "Unable to extract ID %s", argv[1]);
            }
        }
    }
    if(3 == argc) {
        res = true;
        if(true == res) {
            res = try_str2array(argv[2], payload, sizeof(payload), &payload_len);
            if(false == res) {
                LOG_ERROR(UBX, "Unable to extract array %s", argv[2]);
            }
        }
    }

    if(true == res) {
        res = ubx_send_message(class_num, id, payload, payload_len);
        if(false == res) {
            LOG_ERROR(UBX, "Unable to send to Ublox");
        } else {
            LOG_INFO(UBX, "Send OK");
        }
    } else {
        LOG_ERROR(UBX, "Usage: ubs class id payload");
    }

    return res;
}
#endif

#ifdef HAS_UBX_DEBUG
static bool ubx_nav(void) {
    bool res = print_coordinate("Ubx:",NavInfo.coordinate, true);
    res = print_wgs84_coordinate(NavInfo.Wgs84Coordinate, true);

    res = print_velocity(NavInfo.velocity) && res;
    res = print_time_date("Ubx:",&NavInfo.date_time, true) && res;
    io_printf("hmsl: %d mm %d m" CRLF, NavInfo.hmsl, NavInfo.hmsl / 1000);
    io_printf("h_acc: %u mm" CRLF, NavInfo.h_acc);
    io_printf("v_acc: %u mm" CRLF, NavInfo.v_acc);

    io_printf("roll %d %f deg" CRLF, NavInfo.roll, 1e-5 * ((double)NavInfo.roll));
    io_printf("pitch %d %f deg" CRLF, NavInfo.pitch, 1e-5 * ((double)NavInfo.pitch));
    io_printf("heading %d %f deg" CRLF, NavInfo.heading, 1e-5 * ((double)NavInfo.heading));

    io_printf("accRoll %d %f deg" CRLF, NavInfo.acc_roll, 1e-5 * ((double)NavInfo.acc_roll));
    io_printf("accPitch %d %f deg" CRLF, NavInfo.acc_pitch, 1e-5 * ((double)NavInfo.acc_pitch));
    io_printf("accHeading %d %f deg" CRLF, NavInfo.acc_heading, 1e-5 * ((double)NavInfo.acc_heading));

    return res;
}
#endif

bool ubx_nav_command(int32_t argc, char* argv[]) {
    bool res = false;
#ifdef HAS_UBX_DEBUG
    if(0 == argc) {
        res = ubx_nav();
    } else {
        LOG_ERROR(UBX, "Usage: ubn");
    }
#endif
    return res;
}

#ifdef HAS_UBX_EXT
bool ubx_set_val_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t key_id = 0;
    uint8_t payload[10] = {0};
    uint32_t val_len = 0U;
    uint8_t layers = 0;
    if(3 == argc) {
        res = try_str2uint32(argv[0], &key_id);
        if(false == res) {
            LOG_ERROR(UBX, "Unable to extract key_id %s", argv[0]);
        }
        res = try_str2array(argv[1], payload, sizeof(payload), &val_len) && res;
        if(false == res) {
            LOG_ERROR(UBX, "Unable to extract value %s", argv[1]);
        } else {
            res = reverse_byte_order_array(payload, val_len) && res;
        }
        res = try_str2uint8(argv[2], &layers) && res;
        if(false == res) {
            LOG_ERROR(UBX, "Unable to extract layer %s", argv[2]);
        }
    } else {
        LOG_ERROR(UBX, "Usage: ubsv keyID val layer");
    }

    if(res) {
        res = ubx_cfg_set_val(key_id, payload, val_len, layers);
        if(res) {
            LOG_INFO(UBX, "key 0x%x len:%u set Ok!", key_id, val_len);
        } else {
            LOG_ERROR(UBX, "set error");
        }
    }
    return res;
}
#endif
