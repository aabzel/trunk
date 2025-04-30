#include "nmea_protocol.h"

#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>

#ifdef HAS_CLOCK
//#include "clocks.h"
#endif
#ifdef HAS_FLASH_FS
#include "flash_fs.h"
#endif
#ifdef HAS_PARAM
//#include "param_ids.h"
#endif
#include "log.h"
#include "rtc_mcal.h"
#ifdef HAS_LED
#include "led_drv.h"
#endif
#ifdef HAS_UART
#include "uart_mcal.h"
#endif
#include "fifo_char.h"
#include "gnss_utils.h"
#include "data_utils.h"
#include "convert.h"
#include "time_mcal.h"
#include "code_generator.h"

COMPONENT_GET_NODE(Nmea, nmea)
COMPONENT_GET_CONFIG(Nmea, nmea)


NmeaHandle_t* NmeaGetNodeByUartNum(uint8_t uart_num) {
    NmeaHandle_t* Node = NULL;
    uint32_t i = 0;
    for(i = 0; i < nmea_get_cnt(); i++) {
        if(uart_num == NmeaInstance[i].uart_num) {
            if(NmeaInstance[i].valid) {
                Node = &NmeaInstance[i];
                break;
            }
            break;
        }
    }
    return Node;
}

static bool nmea_reset_parser(NmeaHandle_t* const Node) {
    bool res = true;
    LOG_PARN(NMEA, "ResetParser");
    Node->pos = 0;
    Node->got_massege = false;
    /*Do not reset Node->pos_mode !*/
    Node->crc_nibble = 0;
    Node->state = WAIT_PREAMBLE;
    return res;
}

static bool nmea_init_custom(void){
    bool res = true;
    return res;
}

static bool nmea_init_common_one(const NmeaConfig_t* const Config,
                                 NmeaHandle_t* const Node){
    bool res = false;
    if(Config){
        if(Node){
            Node->rx_buff_size = Config->rx_buff_size;
            Node->RxFifoArray = Config->RxFifoArray;
            Node->baud_rate = Config->baud_rate;
            Node->uart_num = Config->uart_num;
            res = true;
        }
    }
    return res;
}


bool nmea_init_one(uint8_t num) {
    bool res = false;
    LOG_INFO(NMEA, "Init:%u", num);
    const NmeaConfig_t* Config=NmeaGetConfig(num);
    if(Config) {
        NmeaHandle_t* Node=NmeaGetNode(num);
        if(Node) {
            res = nmea_init_common_one(Config,Node);

            if (Config->rx_buff_size) {
                if (Config->RxFifoArray) {
                    res = fifo_init(&Node->RxFifo, (char* )Config->RxFifoArray, Config->rx_buff_size);
                }
            }

            if(res) {
#ifdef HAS_UART
                // res = uart_set_baudrate(Config->uart_num, Config->baud_rate);
#endif
                // memset(&NmeaData, 0x00, sizeof(NmeaData));
                // memset(&Node-> 0x00, sizeof(Node->);
                Node->len_min = UINT_MAX;
                res = nmea_reset_parser(Node);
            }
            set_log_level(NMEA, LOG_LEVEL_INFO);
        }
    }
    return res;
}

/*$GNZDA,122013.00,29,11,2021,00,00*71*/
bool gnss_parse_zda(char *nmea_msg, zda_t *zda) {
    bool res = true;
    uint8_t cnt = 0;
    char *ptr = strchr(nmea_msg, ',');
    // 122013.00,29,11,2021,00,00*71*/
    if (ptr) {
        uint32_t utc_time = 0;
        res = try_strl2uint32(ptr + 1, 6, &utc_time) && res;
        if (res) {
            res = parse_time_from_val(utc_time, &zda->time_date);
            if (res) {
                cnt++;
            }
        }
    }
    ptr++;

    ptr = strchr(ptr, ',');
    if (ptr) {
        /*29,11,2021,00,00*71*/
        res = try_strl2int32(ptr + 1, 2, (int32_t*) &zda->time_date.tm_mday);
        if (res) {
            cnt++;
        }
    }
    ptr++;

    ptr = strchr(ptr, ',');
    if (ptr) {
        /*11,2021,00,00*71*/
        res = try_strl2int32(ptr + 1, 2, (int32_t*) &zda->time_date.tm_mon);
        if (res) {
            cnt++;
        }
    }
    ptr++;

    ptr = strchr(ptr, ',');
    if (ptr) {
        /*2021,00,00*71*/
        res = try_strl2int32(ptr + 1, 4, (int32_t*) &zda->time_date.tm_year);
        if (res) {
            cnt++;
        }
    }
    ptr++;

    ptr = strchr(ptr, ',');
    /*00,00*71*/
    if (ptr) {
        res = try_strl2uint8(ptr + 1, 2, &zda->ltzh);
        if (res) {
            cnt++;
        }
    }
    ptr++;

    ptr = strchr(ptr, ',');
    /*00*71*/
    if (ptr) {
        res = try_strl2uint8(ptr + 1, 2, &zda->ltzn);
        if (res) {
            cnt++;
        }
    }
    if (cnt) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

#ifdef HAS_NMEA_GGA
/*$GNGGA,140213.00,5540.70555,N,03737.93436,E,1,12,0.58,201.4,M,13.3,M,,*42*/
bool gnss_parse_gga(char* nmea_msg, gga_t* gga) {
    bool res = true;
    uint8_t cnt = 0;
    char* ptr = strchr(nmea_msg, ',') + 1;
    uint32_t utc_time = 0;
    // 140213.00,5540.70555,N,03737.93436,E,1,12,0.58,201.4,M,13.3,M,,*42
    res = try_strl2uint32(ptr, 6, &utc_time);
    if(res) {
        res = parse_time_from_val(utc_time, &gga->time_date);
        if(res) {
            cnt++;
        }
    }

    ptr = strchr(ptr, ',') + 1;
    // 5540.70555,N,03737.93436,E,1,12,0.58,201.4,M,13.3,M,,*42
    res = try_strl2double(ptr, 10, &gga->coordinate_ddmm.phi);
    if(res) {
        cnt++;
    }

    ptr = strchr(ptr, ',') + 1;
    // N,03737.93436,E,1,12,0.58,201.4,M,13.3,M,,*42
    gga->lat_dir = ptr[0];

    ptr = strchr(ptr, ',') + 1;
    // 03737.93436,E,1,12,0.58,201.4,M,13.3,M,,*42
    res = try_strl2double(ptr, 11, &gga->coordinate_ddmm.lambda);
    if(res) {
        cnt++;
    }

    ptr = strchr(ptr, ',') + 1;
    // E,1,12,0.58,201.4,M,13.3,M,,*42
    gga->lon_dir = ptr[0];

    ptr = strchr(ptr, ',') + 1;
    // 1,12,0.58,201.4,M,13.3,M,,*42
    res = try_strl2uint16(ptr, 1, &gga->quality);
    if(res) {
        cnt++;
    }

    ptr = strchr(ptr, ',') + 1;
    // 12,0.58,201.4,M,13.3,M,,*42
    res = try_strl2uint16(ptr, 2, &gga->nb_sat);
    if(res) {
        cnt++;
    }

    ptr = strchr(ptr, ',') + 1;
    // 0.58,201.4,M,13.3,M,,*42
    res = try_strl2double(ptr, 4, &gga->hdop);
    if(res) {
        cnt++;
    }

    ptr = strchr(ptr, ',') + 1;
    // 201.4,M,13.3,M,,*42
    res = try_strl2double(ptr, 5, &gga->height);
    if(res) {
        cnt++;
    }

    ptr = strchr(ptr, ',') + 1;
    // M,13.3,M,,*42
    gga->height_unit = ptr[0];

    ptr = strchr(ptr, ',') + 1;
    // 13.3,M,,*42
    res = try_strl2double(ptr, 4, &gga->geoid_separation);
    if(res) {
        cnt++;
    }

    ptr = strchr(ptr, ',') + 1;
    // M,,*42
    gga->geoid_unit = ptr[0];

    res = false;
    if(cnt) {
        res = true;
    }
    return res;
}
#endif

#ifdef HAS_NMEA_GSV
//$GLGSV,3,3,10, 85,46,314,38,
//               86,04,339,,3*7A
//"$GBGSV,3,3,09,35,18,108,,3*4B",
bool gnss_parse_gsv(char* nmea_msg, gsv_t* gsv) {
    bool res = true;
    LOG_DEBUG(NMEA, "GSV [%s]", nmea_msg);
    uint8_t cnt = 0;
    char* ptr = strchr(nmea_msg, ',');
    if(ptr) {
        res = try_strl2uint8(ptr + 1, 1, &gsv->numMsg);
        if(res) {
            LOG_PARN(NMEA, "numMsg Ok");
            cnt++;
        }
    }
    if(ptr) {
        ptr++;
    }

    ptr = strchr(ptr, ',');
    if(ptr) {
        res = try_strl2uint8(ptr + 1, 1, &gsv->msgNum);
        if(res) {
            cnt++;
        }
    }
    if(ptr) {
        ptr++;
    }

    ptr = strchr(ptr, ',');
    if(ptr) {
        res = try_strl2uint16(ptr + 1, 2, &gsv->numSV);
        if(res) {
            cnt++;
        }
    }
    if(ptr) {
        ptr++;
    }
    uint8_t i = 0;
    LOG_PARN(NMEA, "Iterations %u", gsv->msgNum - 1);
    for(i = 0; i < (gsv->msgNum - 1); i++) {
        if(i < NUM_OF_PARSED_SAT) {
            ptr = strchr(ptr, ',');
            if(ptr) {
                LOG_DEBUG(NMEA, "ParseSatelliteID");
                res = try_strl2uint16(ptr + 1, 2, &gsv->sat[i].svid);
                if(res) {
                    cnt++;
                }
            }
            if(ptr) {
                LOG_DEBUG(NMEA, "IncrPtr L:%u", __LINE__);
                ptr++;
            }
            if(ptr) {

                ptr = strchr(ptr, ',');
                if(ptr) {
                    LOG_DEBUG(NMEA, "ParseElv");
                    res = try_strl2uint8(ptr + 1, 2, &gsv->sat[i].elv);
                    if(res) {
                        cnt++;
                    }
                }
            }
            if(ptr) {
                ptr++;
            }

            if(ptr) {
                ptr = strchr(ptr, ',');
                if(ptr) {
                    LOG_DEBUG(NMEA, "ParseAz");
                    res = try_strl2uint16(ptr + 1, 3, &gsv->sat[i].az);
                    if(res) {
                        cnt++;
                    }
                }
            }
            if(ptr) {
                ptr++;
            }

            if(ptr) {
                ptr = strchr(ptr, ',');
                if(ptr) {
                    LOG_DEBUG(NMEA, "ParseSignalStrength");
                    res = try_strl2uint8(ptr + 1, 2, &gsv->sat[i].cno);
                    if(res) {
                        cnt++;
                    }
                }
            }
            if(ptr) {
                ptr++;
            }
        }
    }
    if(ptr) {
        ptr = strchr(ptr, ',');
        if(ptr) {
            LOG_DEBUG(NMEA, "ParseSignalID");
            res = try_strl2uint8(ptr + 1, 1, &gsv->signalId);
            if(res) {
                cnt++;
            }
        }
    }

    res = false;
    if(cnt) {
        res = true;
    }
    return res;
}
#endif

//$GNVTG,,T,,M,0.019,N,0.036,K,A*30
//$GPVTG,,,,,,,,,N*30
//$GNVTG,,T,,M,0.017,N,0.032,K,A*3A
bool gnss_parse_vtg(char *nmea_msg, vtg_t *vtg) {
    bool res = true;
    uint8_t cnt = 0;
    char *ptr = strchr(nmea_msg, ',');
    //,T,,M,0.019,N,0.036,K,A*30  //Course over ground
    if (ptr) {
        res = try_strl2double(ptr + 1, 5, &vtg->cogt);
        if (res) {
            cnt++;
        }
    }
    ptr++;

    ptr = strchr(ptr, ',');
    // T,,M,0.019,N,0.036,K,A*30  Course over ground units
    if (ptr) {
        if (',' != ptr[1]) {
            vtg->cogtUnit = ptr[1];
            LOG_DEBUG(NMEA, "%c", ptr[1]);
            cnt++;
        }
    }
    ptr++;

    ptr = strchr(ptr, ',') + 1;
    //,M,0.019,N,0.036,K,A*30  Course over ground
    if (ptr) {
        res = try_strl2double(ptr + 1, 5, &vtg->cogm);
        if (res) {
            cnt++;
        }
    }
    ptr = strchr(ptr, ',');
    // M,0.019,N,0.036,K,A*30   Course over ground units
    if (ptr) {
        if (',' != ptr[1]) {
            cnt++;
            vtg->cogmUnit = ptr[1];
            LOG_DEBUG(NMEA, "%c", ptr[1]);
            cnt++;
        }
    }
    ptr++;

    ptr = strchr(ptr, ',');
    // 0.019,N,0.036,K,A*30  Speed over ground
    if (ptr) {
        res = try_strl2double(ptr + 1, 5, &vtg->sogn);
        if (res) {
            cnt++;
        }
    }
    ptr++;

    ptr = strchr(ptr, ',');
    // N,0.036,K,A*30  Speed over ground  Speed over ground units
    if (ptr) {
        if (',' != ptr[1]) {
            vtg->sognUnit = ptr[1];
            LOG_DEBUG(NMEA, "%c", ptr[1]);
            cnt++;
        }
    }
    ptr++;

    ptr = strchr(ptr, ',');
    // 0.036,K,A*30  Speed over ground
    if (ptr) {
        res = try_strl2double(ptr + 1, 5, &vtg->sogk);
        if (res) {
            cnt++;
        }
    }
    ptr++;

    ptr = strchr(ptr, ',');
    // K,A*30     Speed over ground units
    if (ptr) {
        if (',' != ptr[1]) {
            vtg->sogkUnit = ptr[1];
            LOG_DEBUG(NMEA, "%c", ptr[1]);
            cnt++;
        }
    }
    ptr++;

    ptr = strchr(ptr, ',');
    // A*30
    if (ptr) {
        if (',' != ptr[1]) {
            vtg->posMode = ptr[1];
            LOG_DEBUG(NMEA, "%c", ptr[1]);
            cnt++;
        }
    }

    if (cnt) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

/* GNSS DOP and active satellites */
//$GNGSA,A,3,78,85,68,84,69,,,,,,,,1.04,0.58,0.86,2*0B //18 commas
//"$GPGSA,A,1,,,,,,,,,,,,,99.99,99.99,99.99*30"  //17 commas
bool gnss_parse_gsa(char *nmea_msg, gsa_t *gsa) {
    bool res = true;

    char *ptr = strchr(nmea_msg, ',') + 1;
    // A,3,78,85,68,84,69,,,,,,,,1.04,0.58,0.86,2*0B
    gsa->opMode = ptr[0];

    ptr = strchr(ptr, ',');
    // 3,78,85,68,84,69,,,,,,,,1.04,0.58,0.86,2*0B
    if (ptr) {
        res = try_strl2uint8(ptr + 1, 1, &gsa->navMode) && res;
    }
    ptr++;

    uint8_t i = 0;
    for (i = 0; i < 12; i++) {
        ptr = strchr(ptr, ',') + 1;
    }

    ptr = strchr(ptr, ',');
    // 1.04,0.58,0.86,2*0B
    if (ptr) {
        res = try_strl2double(ptr + 1, 4, &gsa->PDOP) && res;
    }
    ptr++;

    ptr = strchr(ptr, ',');
    // 0.58,0.86,2*0B
    if (ptr) {
        res = try_strl2double(ptr + 1, 4, &gsa->HDOP) && res;
    }
    ptr++;

    ptr = strchr(ptr, ',');
    // 0.86,2*0B
    if (ptr) {
        res = try_strl2double(ptr + 1, 4, &gsa->VDOP) && res;
    }
    ptr++;

    ptr = strchr(ptr, ',');
    // 2*0B
    if (ptr) {
        res = try_strl2uint8(ptr + 1, 1, &gsa->systemId) && res;
    }
    return res;
}
#ifdef HAS_NMEA_GLL

// Latitude and longitude, with time of position fix and status
//$GNGLL,5540.70588,N,03737.93396,E,140121.00,A,A*70
//$GPGLL,,,,,213748.00,V,N*41
bool gnss_parse_gll(char* nmea_msg, gll_t* gll) {
    bool res = true;
    uint8_t cnt = 0;
    uint32_t cur_pos = 0;
    if(nmea_msg && gll) {
        char* ptr = strchr(nmea_msg, ',');
        cur_pos = (uint32_t)(ptr - nmea_msg);
        if(cur_pos < NMEA_MSG_SIZE) {
            // 5540.70588,N,03737.93396,E,140121.00,A,A*70
            res = try_strl2double(ptr + 1, 10, &gll->coordinate_ddmm.phi);
            if(res) {
                cnt++;
            }
        }
        ptr++;

        ptr = strchr(ptr, ',');
        cur_pos = (uint32_t)(ptr - nmea_msg);
        if((cur_pos < NMEA_MSG_SIZE) && (ptr)) {
            // N,03737.93396,E,140121.00,A,A*70
            gll->lat_dir = ptr[1];
        }
        ptr++;

        ptr = strchr(ptr, ',');
        cur_pos = (uint32_t)(ptr - nmea_msg);
        if((cur_pos < NMEA_MSG_SIZE) && (ptr)) {
            // 03737.93396,E,140121.00,A,A*70
            res = try_strl2double(ptr + 1, 11, &gll->coordinate_ddmm.lambda);
            if(res) {
                cnt++;
            }
        }
        ptr++;

        ptr = strchr(ptr, ',');
        cur_pos = (uint32_t)(ptr - nmea_msg);
        if((cur_pos < NMEA_MSG_SIZE) && (ptr)) {
            // E,140121.00,A,A*70
            if(',' != ptr[1]) {
                gll->lon_dir = ptr[1];
                cnt++;
            }
        }
        ptr++;

        ptr = strchr(ptr, ',');
        cur_pos = (uint32_t)(ptr - nmea_msg);
        if((cur_pos < NMEA_MSG_SIZE) && (ptr)) {
            // 140121.00,A,A*70
            uint32_t utc_time = 0;
            res = try_strl2uint32(ptr + 1, 6, &utc_time);
            if(res) {
                res = parse_time_from_val(utc_time, &gll->time_date);
                if(res) {
                    cnt++;
                }
            }
        }
        ptr++;

        ptr = strchr(ptr, ',');
        cur_pos = (uint32_t)(ptr - nmea_msg);
        if((cur_pos < NMEA_MSG_SIZE) && (ptr)) {
            // A,A*70
            if(',' != ptr[1]) {
                gll->status = ptr[1];
                cnt++;
            }
        }
        ptr++;

        ptr = strchr(ptr, ',');
        cur_pos = (uint32_t)(ptr - nmea_msg);
        if((cur_pos < NMEA_MSG_SIZE) && (ptr)) {
            // A*70
            if(',' != ptr[1]) {
                gll->pos_mode = ptr[1];
                cnt++;
            }
        }
        ptr++;

        if(cnt) {
            res = true;
        } else {
            res = false;
        }
    }

    return res;
}
#endif

//$PUBX,00,000717.00,0000.00000,N,00000.00000,E,0.000,NF,5303316,3750010,0.000,0.00,0.000,,99.99,99.99,99.99,0,0,0*2C
bool gnss_parse_pbux_pos(char *nmea_msg, pbux_t *const pbux) {
    bool res = true;
    char *ptr = strchr(nmea_msg, ',') + 1;
    res = try_strl2uint8(ptr, 2, &pbux->msg_id) && res;
    ptr = strchr(ptr, ',') + 1;
    uint32_t utc_time = 0;
    res = try_strl2uint32(ptr, 6, &utc_time) && res;
    if (res) {
        res = parse_time_from_val(utc_time, &pbux->time_date);
    }
    return res;
}
#ifdef HAS_NMEA_RMC
/*
$GNRMC,142710.60,A,5551.84214,N,03725.61511,E,0.015,,301121,,,D,V*1C
$GNRMC,072316.27,A,5551.85875,N,03755.65965,E,0.010,,290721,11.73,E,A,V*76
$GNRMC,163320.60,A,5540.70459,N,03737.93393,E,0.047,,140222,,,A,V*1B
*/
bool gnss_parse_rmc(char* nmea_msg, rmc_t* rmc) {
    bool res = true;
    bool out_res = false;
    uint8_t parse_cnt = 0;
    char* ptr = strchr(nmea_msg, ',');
    uint32_t utc_time = 0;
    if(ptr) {
        res = try_strl2uint32(ptr + 1, 6, &utc_time);
        if(res) {
            LOG_DEBUG(NMEA, "SpotTime");
            res = parse_time_from_val(utc_time, &rmc->time_date);
            if(false == res) {

            } else {
                parse_cnt++;
            }
        } else {
            LOG_ERROR(NMEA, "ParseTimeErr");
        }
    }
    ptr++;

    ptr = strchr(ptr, ',');
    if(ptr) {
        if(',' != ptr[1]) {
            rmc->data_valid = ptr[1];
            parse_cnt++;
        }
    }
    ptr++;

    ptr = strchr(ptr, ',');
    if(ptr) {
        res = try_strl2double(ptr + 1, 10, &rmc->coordinate_ddmm.phi);
        if(false == res) {

        } else {
            parse_cnt++;
        }
    }
    ptr++;

    ptr = strchr(ptr, ',');
    if(ptr) {
        if(',' != ptr[1]) {
            rmc->lat_dir = ptr[1];
            parse_cnt++;
        }
    }
    ptr++;

    ptr = strchr(ptr, ',');
    if(ptr) {
        res = try_strl2double(ptr + 1, 11, &rmc->coordinate_ddmm.lambda);
        if(false == res) {

        } else {
            parse_cnt++;
        }
    }
    ptr++;

    ptr = strchr(ptr, ',');
    if(ptr) {
        if(',' != ptr[1]) {
            rmc->lon_dir = ptr[1];
        }
    }
    ptr++;

    ptr = strchr(ptr, ',');
    if(ptr) {
        res = try_strl2double(ptr + 1, 5, &rmc->speed_knots);
        if(res) {
            parse_cnt++;
        }
    }
    ptr++;

    ptr = strchr(ptr, ',');
    if(ptr) {
        res = try_strl2double(ptr + 1, 5, &rmc->true_course);
        if(res) {
            parse_cnt++;
        }
    }
    ptr++;

    ptr = strchr(ptr, ',');
    uint32_t date = 0;
    if(ptr) {
        LOG_DEBUG(NMEA, "SpotData");
        res = try_strl2uint32(ptr + 1, 6, &date);
        if(res) {
            res = parse_date_from_val(date, &rmc->time_date);
            if(false == res) {
                LOG_ERROR(NMEA, "ParseDateErr");
            } else {
                parse_cnt++;
            }
        } else {
            LOG_DEBUG(NMEA, "SpotDateErr [%s]", ptr + 1);
        }
    }
    ptr++;

    ptr = strchr(ptr, ',');
    if(ptr) {
        try_strl2double(ptr + 1, 5, &rmc->mv);
    }
    ptr++;

    ptr = strchr(ptr, ',');
    if(ptr) {
        if(',' != ptr[1]) {
            rmc->mv_ew = ptr[1];
        }
    }
    ptr++;

    ptr = strchr(ptr, ',');
    if(ptr) {
        if(',' != ptr[1]) {
            rmc->pos_mode = ptr[1];
        }
    }
    ptr++;

    ptr = strchr(ptr, ',');
    if(ptr) {
        if(',' != ptr[1]) {
            rmc->nav_status = ptr[1];
        }
    }

    if(0 < parse_cnt) {
        out_res = true;
    } else {
        out_res = false;
    }
    return out_res;
}
#endif

uint8_t nmea_calc_checksum(char *nmea_data, uint16_t len) {
    uint8_t crc8 = 0;
    uint16_t i = 0;
    if (nmea_data) {
        for (i = 0; i < len; i++) {
            crc8 ^= nmea_data[i];
        }
    }
    return crc8;
}
/*Error in Here*/
bool nmea_parse(NmeaHandle_t* Node, char *nmea_msg, uint16_t len) {
    bool res = false;
    uint8_t read_crc = 0;
    LOG_DEBUG(NMEA, "Parse [%s] len: %u", nmea_msg, len);
    if (len < NMEA_MSG_SIZE) {
        res = true;
    } else {
        LOG_ERROR(NMEA, "lenErr: %u", len);
        Node->err_cnt++;
        res = false;
    }
    if (nmea_msg && (NMEA_OVERHEAD < len) && (0 < len)) {
        if ('$' == nmea_msg[0]) {
            res = true;
        } else {
            LOG_ERROR(NMEA, "NotAframe [%s] len: %u", nmea_msg, len);
            res = false;
        }
    } else {
        LOG_ERROR(NMEA, "LenError len: %u", len);
        res = false;
    }
    if (res) {
        uint32_t crc_pos = 0;
        char *crc_ptr = strchr(nmea_msg, '*') + 1;
        if (crc_ptr) {
            crc_pos = (uint32_t) (crc_ptr - nmea_msg);
            if (crc_pos < NMEA_MSG_SIZE) {
                res = try_strl2uint8_hex(crc_ptr, 2, &read_crc);
                if (false == res) {
                    LOG_ERROR(NMEA, "CrcParseErr [%s]", nmea_msg);
                } else {
                    LOG_PARN(NMEA, "CrcReadOk CrcRead:0x%02x", read_crc);
                }
            } else {
                Node->err_cnt++;
            }
        } else {
            LOG_ERROR(NMEA, "CrcSpotErr");
            Node->err_cnt++;
        }
    }
    if (res) {
        Node->crc_read_cnt++;
        res = false;
        uint8_t calc_crc = 0;
        calc_crc = nmea_calc_checksum(&nmea_msg[1], len - NMEA_OVERHEAD);
        if (read_crc == calc_crc) {
            Node->len_min = MIN(Node->len_min, len);
            Node->len_max = MAX(Node->len_max, len);
            LOG_DEBUG(NMEA, "CRC OK! [%s]", nmea_msg);
            res = false;
            Node->crc_ok_cnt++;

            if (!strncmp(nmea_msg + 3, "GGA", 3)) {
#ifdef HAS_NMEA_GGA
                Node->gga.fcnt.h_cnt++;
                LOG_DEBUG(NMEA, "GGA");
                res = gnss_parse_gga(nmea_msg, &Node->gga);
                if(res) {
                    Node->gga.fcnt.cnt++;
                    Node->gga.coordinate_dd = encode_gnss_coordinates(Node->gga.coordinate_ddmm);
                    Node->coordinate_dd = Node->gga.coordinate_dd;
                    Node->height = Node->gga.height;
                } else {
                    LOG_ERROR(NMEA, "UnableToParse[%s]", nmea_msg);
                    Node->err_parse++;
                }
#endif
            } else if (!strncmp(nmea_msg + 3, "RMC", 3)) {
#ifdef HAS_NMEA_RMC
                Node->rmc.fcnt.h_cnt++;
                LOG_PARN(NMEA, "RMC");
                res = gnss_parse_rmc(nmea_msg, &Node->rmc);
                if(res) {
#ifdef HAS_CLOCK
                    Node->gnss_time_stamp = time_get_ms32();
#endif
                    Node->rmc.coordinate_dd = encode_gnss_coordinates(Node->rmc.coordinate_ddmm);
                    Node->coordinate_dd = Node->rmc.coordinate_dd;
                    Node->rmc.fcnt.cnt++;
                } else {
                    LOG_ERROR(NMEA, "UnableToParse[%s]", nmea_msg);
                    Node->err_parse++;
                }
#endif
            } else if (!strncmp(nmea_msg + 3, "GLL", 3)) {
#ifdef HAS_NMEA_GLL
                Node->gll.fcnt.h_cnt++;
                LOG_DEBUG(NMEA, "GLL");
                /*here lat and lon*/
                res = gnss_parse_gll(nmea_msg, &Node->gll);
                if(res) {
#ifdef HAS_CLOCK
                    Node->gnss_time_stamp = time_get_ms32();
#endif
                    Node->gll.fcnt.cnt++;
                } else {
                    LOG_ERROR(NMEA, "UnableToParse[%s]", nmea_msg);
                    Node->err_parse++;
                }
#endif
            } else if (!strncmp(nmea_msg + 3, "GSV", 3)) {
#ifdef HAS_NMEA_GSV
                Node->gsv.fcnt.h_cnt++;
                res = gnss_parse_gsv(nmea_msg, &Node->gsv);
                if(res) {
                    Node->gsv.fcnt.cnt++;
                } else {
                    Node->err_parse++;
                }
#endif
            } else if (!strncmp(nmea_msg + 3, "VTG", 3)) {
#ifdef HAS_NMEA_VTG
                Node->vtg.fcnt.h_cnt++;
                res = gnss_parse_vtg(nmea_msg, &Node->vtg);
                if(res) {
                    Node->vtg.fcnt.cnt++;
                } else {
                    LOG_ERROR(NMEA, "UnableToParse[%s]", nmea_msg);
                    Node->err_parse++;
                }
#endif
            } else if (!strncmp(nmea_msg + 3, "GSA", 3)) {
#ifdef HAS_NMEA_GSA
                Node->gsa.fcnt.h_cnt++;
                res = gnss_parse_gsa(nmea_msg, &Node->gsa);
                if(res) {
                    Node->gsa.fcnt.cnt++;
                } else {
                    LOG_ERROR(NMEA, "UnableToParse[%s]", nmea_msg);
                    Node->err_parse++;
                }
#endif
            } else if (!strncmp(nmea_msg + 3, "ZDA", 3)) {
#ifdef HAS_NMEA_ZDA
                Node->zda.fcnt.h_cnt++;
                res = gnss_parse_zda(nmea_msg, &Node->zda);
                if(res) {
                    Node->zda.fcnt.cnt++;
                } else {
                    LOG_ERROR(NMEA, "UnableToParse[%s]", nmea_msg);
                    Node->err_parse++;
                }
#endif
            } else if (!strncmp(nmea_msg + 3, "TXT", 3)) {

                Node->txt.fcnt.h_cnt++;
            } else if (!strncmp(nmea_msg + 3, "PUBX", 4)) {
#ifdef HAS_NMEA_PBUX
                Node->pbux.fcnt.h_cnt++;
                res = gnss_parse_pbux_pos(nmea_msg, &Node->pbux);
                if(res) {
                    Node->pbux.fcnt.cnt++;
                } else {
                    LOG_ERROR(NMEA, "UnableToParse[%s]", nmea_msg);
                    Node->err_parse++;
                }
#endif
            } else {
                Node->undef_err_cnt++;
                LOG_ERROR(NMEA, "UndefMess [%s]", nmea_msg + 3);
                strncpy(Node->undef_message, nmea_msg, NMEA_MSG_SIZE);
                res = false;
            }
        } else {
            LOG_DEBUG(NMEA, "Mesg [%s] len %u", nmea_msg, len);
            LOG_DEBUG(NMEA, "CrcErr Read 0x%02x Calc 0x%02x", read_crc, calc_crc);
            Node->crc_err_cnt++;
        }
    }

    return res;
}

static bool nmea_proc_wait_preamble(NmeaHandle_t* Node, uint8_t rx_byte) {
    bool res = false;
    if ('$' == rx_byte) {
        if (0 == Node->pos) {
            memset(Node->message, 0x00, NMEA_MSG_SIZE);
            Node->message[0] = rx_byte;
            Node->state = WAIT_PAYLOAD;
            Node->pos = 1;
        } else {
            nmea_reset_parser(Node);
        }
    } else {
        nmea_reset_parser(Node);
    }
    return res;
}

static bool nmea_proc_wait_payload(NmeaHandle_t* Node, uint8_t rx_byte) {
    bool res = false;
    if ('*' == rx_byte) {
        Node->state = WAIT_CRC;
        Node->crc_nibble = 0;
        Node->crc_read = 0;
    } else {
        LOG_PARN(NMEA, "data[%u]=0x%02x", Node->pos, rx_byte);
        Node->state = WAIT_PAYLOAD;
    }

    if (Node->pos < NMEA_MSG_SIZE) {
        Node->message[Node->pos] = rx_byte;
        Node->pos++;
        res = true;
    } else {
        Node->overflow++;
        nmea_reset_parser(Node);
    }
    return res;
}

static bool nmea_proc_wait_crc(NmeaHandle_t* Node, uint8_t rx_byte) {
    bool res = false;
    res = is_hex_digit((char) rx_byte);
    if (res) {
        if (Node->pos < NMEA_MSG_SIZE) {
            Node->message[Node->pos] = rx_byte;
            Node->pos++;
            uint8_t nibble = 0xFF;
            if (0 == Node->crc_nibble) {
                Node->crc_read = 0;
                res = AsciiChar2HexNibble((char) rx_byte, &nibble);
                if (res) {
                    Node->crc_read = nibble << 4;
                }
                Node->crc_nibble = 1;
            } else if (1 == Node->crc_nibble) {
                res = AsciiChar2HexNibble((char) rx_byte, &nibble);
                if (res) {
                    Node->crc_read |= nibble;
                    Node->msg_cnt++;
                    Node->got_massege = true;
                    memset(Node->fix_message, 0x00, NMEA_MSG_SIZE);
                    memcpy(Node->fix_message, Node->message, NMEA_MSG_SIZE);
                    LOG_PARN(NMEA, "SpotLine [%s]", Node->fix_message);
                    res = nmea_parse(Node, Node->fix_message, Node->pos);
                    if (true == res) {
                        Node->proc_msg_cnt++;
                    }
                }
                res = nmea_reset_parser(Node);
                Node->crc_nibble = 2;
            } else {
                res = nmea_reset_parser(Node);
            }
        } else {
            Node->overflow++;
            res = nmea_reset_parser(Node);
        }

    } else {
        LOG_DEBUG(NMEA, "CrcFormatErr Nimble:%u 0x%02x=[%c]", Node->crc_nibble, rx_byte,
                rx_byte);
        Node->err_parse++;
        res = nmea_reset_parser(Node);
    }
    return res;
}

bool nmea_proc_byte(NmeaHandle_t* Node, uint8_t rx_byte) {
    bool res = false;
    switch (Node->state) {
    case WAIT_PREAMBLE:
        res = nmea_proc_wait_preamble(Node,rx_byte);
        break;
    case WAIT_PAYLOAD:
        res = nmea_proc_wait_payload(Node,rx_byte);
        break;
    case WAIT_CRC:
        res = nmea_proc_wait_crc(Node,rx_byte);
        break;
    default:
        res = false;
        break;
    }
    return res;
}

static bool nmea_calc_mode(PositionMode_t *pos_mode, NmeaHandle_t *Node) {
    bool res = false;
    switch (Node->gga.quality) {
    case QUA_NO_FIX: {
        (*pos_mode) = PM_NO_POSITION_FIX;
        res = true;
    }
        break;

    case QUA_AUTONOMOUS_GNSS_FIX:
    case QUA_DIFFERENTIAL_GNSS_FIX: {
        res = true;
        if (NAV_MODE_3D_FIX == Node->gsa.navMode) {
            (*pos_mode) = PM_3D_GNSS_FIX;
        } else if (NAV_MODE_2D_FIX == Node->gsa.navMode) {
            (*pos_mode) = PM_2D_GNSS_FIX;
        } else {
            res = false;
        }
    }
        break;
    case QUA_ESTIMATED_DEAD_RECKONING_FIX: {
        res = true;
        if ('A' == Node->gll.status) {
            (*pos_mode) = PM_DEAD_RECKONING_FIX;
        } else if ('V' == Node->gll.status) {
            (*pos_mode) = PM_DEAD_RECKONING_FIX_BUT_USER_LIMITS_EXCEEDED;
        } else {
            res = false;
        }
    }
        break;

    case QUA_RTK_FIXED: {
        (*pos_mode) = PM_RTK_FIXED;
        res = true;
    }
        break;
    case QUA_RTK_FLOAT: {
        (*pos_mode) = PM_RTK_FLOAT;
        res = true;
    }
        break;
    default: {
        res = false;
    }
        break;
    }

    if (POM_RTK_FIXED == Node->rmc.pos_mode) {
        (*pos_mode) = PM_RTK_FIXED;
    } else if (POM_RTK_FLOAT == Node->rmc.pos_mode) {
        (*pos_mode) = PM_RTK_FLOAT;
    }

    return res;
}
#ifdef HAS_GNSS_RTK
bool nmea_update_rtk_fixed_duration(void) {
    bool res = false;
    uint32_t cur_up_time = 0;
#ifdef HAS_CLOCK
    cur_up_time = time_get_ms32();
#endif
    Node->cur_rtk_fixed_duration = cur_up_time - Node->rtk_fixed_start_ms;
    uint16_t file_len = 0;
#ifdef HAS_FLASH_FS
    res = mm_get(PAR_ID_RTK_FIX_LONG, (uint8_t*)&Node->rtk_fixed_max_duration_ms,
            sizeof(Node->rtk_fixed_max_duration_ms), &file_len);
#endif
    if(Node->rtk_fixed_max_duration_ms < Node->cur_rtk_fixed_duration) {
        Node->rtk_fixed_max_duration_ms = Node->cur_rtk_fixed_duration;
#ifdef HAS_FLASH_FS
        res = mm_set(PAR_ID_RTK_FIX_LONG, (uint8_t*)&Node->rtk_fixed_max_duration_ms,
                sizeof(Node->rtk_fixed_max_duration_ms));
#endif
    }
    return res;
}
#endif

static bool nmea_sync_rtc_proc_one(uint8_t num) {
    bool res = false ;
    NmeaHandle_t *Node = NmeaGetNode(num);
    if(Node ){
        struct tm rtcTimeDate={0};
        res = rtc_get(1, &rtcTimeDate);
        if(res) {
            int32_t diff_sec = time_date_cmp(&rtcTimeDate, &Node->rmc.time_date);
            if(1 < abs(diff_sec)) {
                LOG_INFO(NMEA, "SpotDiff:%d sec,SyncRTC..",diff_sec);
                res = rtc_set(1, &Node->rmc.time_date);
            }else{
                res = true;
            }
        }
    }
    return res;
}

static bool nmea_proc_one(uint8_t num) {
    bool res = false;
    NmeaHandle_t *Node = NmeaGetNode(num);
    if (Node) {
        char rxArray[400]={0};
        FifoIndex_t rxLen=0;
        res = fifo_pull_array(&Node->RxFifo , rxArray, sizeof(rxArray), &rxLen);
        if(res) {
            LOG_DEBUG(NMEA, "RxLen:%u",rxLen);
            if(0<rxLen) {
                uint32_t i =0;
                for(i=0; i<rxLen; i++) {
                    res = nmea_proc_byte(Node, rxArray[i]);
                }
            }
        }




        static uint32_t call_cnt = 0;
        call_cnt++;
        static uint32_t prev_zda_cnt = 0;
        static uint32_t prev_rmc_cnt = 0;
        static uint32_t prev_gga_cnt = 0;
#ifdef HAS_CLOCK
        uint32_t cur_time_ms = time_get_ms32();
        uint32_t lack_of_frame_time_out_ms = 0;
#endif
        if (prev_zda_cnt < Node->zda.fcnt.cnt) {
            res = is_valid_time_date(&Node->zda.time_date);
            if (res) {
                Node->time_date = Node->zda.time_date;
            } else {
                LOG_DEBUG(NMEA, "InvalZdaTimeDate");
            }
        }

        if (prev_rmc_cnt < Node->rmc.fcnt.cnt) {
            Node->coordinate_dd = encode_gnss_coordinates(Node->rmc.coordinate_ddmm);
            Node->time_date = Node->rmc.time_date;
            res = is_valid_time_date(&Node->rmc.time_date);
            if (res) {
                Node->time_date = Node->rmc.time_date;
            } else {
                LOG_ERROR(NMEA, "InvalidRmcTimeDate");
            }
        }

        if (prev_gga_cnt < Node->gga.fcnt.cnt) {
            Node->coordinate_dd = encode_gnss_coordinates(Node->gga.coordinate_ddmm);
            res = is_valid_time(&Node->gga.time_date);
            if (res) {
                Node->time_date.tm_hour = Node->gga.time_date.tm_hour;
                Node->time_date.tm_min = Node->gga.time_date.tm_min;
                Node->time_date.tm_sec = Node->gga.time_date.tm_sec;
            } else {
                LOG_ERROR(NMEA, "InvalidGgaTimeDate");
            }
        }
        /*If new coordinates had not been received in the last 3 seconds, then FW would have erased the old ones*/
#if defined(HAS_LOG) && defined(HAS_CLOCK)
        lack_of_frame_time_out_ms = (cur_time_ms - Node->gnss_time_stamp);
        if (NMEA_LACK_FRAME_WARNING_TIME_OUT_MS < lack_of_frame_time_out_ms) {
            LOG_WARNING(NMEA, "LackOfFrame %u<%u s", NMEA_LACK_FRAME_WARNING_TIME_OUT_MS / 1000,
                    lack_of_frame_time_out_ms / 1000);
            if (NMEA_LACK_FRAME_ERROR_TIME_OUT_MS < lack_of_frame_time_out_ms) {
                LOG_ERROR(NMEA, "LackOfFrame %u<%u s", NMEA_LACK_FRAME_ERROR_TIME_OUT_MS / 1000,
                        lack_of_frame_time_out_ms / 1000);
                Node->coordinate_dd.phi = 0.0;
                Node->coordinate_dd.lambda = 0.0;
            }
        }
#endif
        // Node->pos_mode = PM_UNDEF;
        res = nmea_calc_mode(&Node->pos_mode, Node);
#ifdef HAS_NMEA_DIAG
    static PositionMode_t prev_pos_mode = PM_UNDEF;
    if(res) {
        if(prev_pos_mode != Node->pos_mode) {
            LOG_INFO(NMEA, "NewPosMode %s", NmeaPosModeToStd(Node->pos_mode));
#ifdef HAS_GNSS_RTK
            if(PM_RTK_FIXED == prev_pos_mode) {
                nmea_update_rtk_fixed_duration();
                Node->cur_rtk_fixed_duration = 0;
            }
#endif
            if(PM_RTK_FIXED == Node->pos_mode) {
                Node->rtk_start_cnt++;
#ifdef LED_INDEX_GREEN
                Led[LED_INDEX_GREEN].mode = LED_MODE_ON;
#endif
#ifdef HAS_CLOCK
                Node->rtk_fixed_start_ms = time_get_ms32();
#endif
            } else {
                Node->cur_rtk_fixed_duration = 0;
#ifdef LED_INDEX_GREEN
                Led[LED_INDEX_GREEN].mode = LED_MODE_PWM;
                Led[LED_INDEX_GREEN].period_ms = LED_GREEN_PERIOD_MS;
#endif
            }
        } else if(prev_pos_mode == Node->pos_mode) {
#ifdef HAS_GNSS_RTK
            if(PM_RTK_FIXED == prev_pos_mode) {
                if(0 == (call_cnt % 5)) {
                    nmea_update_rtk_fixed_duration();
                }
            }
#endif
        }
    }
    prev_pos_mode = Node->pos_mode;
#endif

        prev_zda_cnt = Node->zda.fcnt.cnt;
        prev_gga_cnt = Node->gga.fcnt.cnt;
        prev_rmc_cnt = Node->rmc.fcnt.cnt;

    } //if(Node)
    return res;
}


static uint32_t nmea_sync_rtc_get_cnt(void) {
    return nmea_get_cnt();
}


bool nmea_check(uint8_t num) {
    bool res = false;
    NmeaHandle_t* Node=NmeaGetNode(num);
    if(Node) {
        uint32_t diff = 0;
        diff = Node->crc_err_cnt - Node->crc_err_cnt_prev;
        if (0 < diff) {
            LOG_DEBUG(HMON, "NmeaCrcErr:%u times", diff);
        }
        Node->crc_err_cnt_prev = Node->crc_err_cnt;

        diff = Node->err_parse - Node->err_parse_prev;
        if (0 < diff) {
            LOG_DEBUG(HMON, "NmeaParseErr:%u", diff);
        }
        Node->err_parse_prev = Node->err_parse;

    }
    return res;
}

COMPONENT_INIT_PATTERT(NMEA, NMEA, nmea)

COMPONENT_PROC_PATTERT(NMEA, NMEA, nmea)
COMPONENT_PROC_PATTERT(NMEA, NMEA, nmea_sync_rtc)
