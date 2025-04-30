#ifndef NMEA_TYPES_H
#define NMEA_TYPES_H

#include <time.h>

#include "std_includes.h"
#include "nmea_constants.h"
#include "fifo_char.h"
#include "gnss_types.h"
#include "protocol_types.h"

//extern NmeaProtocol_t NmeaProto;

typedef struct  {
    uint32_t cnt;   /*proc counter*/
    uint32_t h_cnt; /*header counter*/
} FrameCnt_t;

/* Recommended minimum specific GPS/Transit data */
typedef struct  {
    FrameCnt_t fcnt;
    struct tm time_date;
    char data_valid; /* validity - A-ok, V-invalid */
    GnssCoordinate_t coordinate_ddmm;
    GnssCoordinate_t coordinate_dd;
    char lat_dir;       /* Latitude direction */
    char lon_dir;       /* Longitude direction */
    double speed_knots; /* Speed over ground (knots) */
    double true_course; /* Course Made Good, True */
    double mv;          /* Magnetic variation */
    char mv_ew;         /* Magnetic variation direction */
    char pos_mode;      /* A = autonom, D=DGPS, E=DR */
    char nav_status;    /* */
} rmc_t;

/* Global Positioning System Fix Data */
typedef struct  {
    FrameCnt_t fcnt;
    uint32_t utc; /* UTC hour in hhmmss format */
    struct tm time_date;
    GnssCoordinate_t coordinate_ddmm;
    GnssCoordinate_t coordinate_dd;
    char lat_dir;            /* Latitude direction */
    char lon_dir;            /* Longitude direction */
    uint16_t quality;        /*Quality indicator for position fix*/
    uint16_t nb_sat;         /*Number of satellites used*/
    double hdop;             /*Horizontal Dilution of Precision*/
    double height;           /*Altitude above mean sea level*/
    char height_unit;        /*Altitude units: M (meters, fixed field*/
    double geoid_separation; /*difference between ellipsoid and mean sea level*/
    char geoid_unit;         /*Geoid separation units: M (meters, fixed field)*/
    double diff_gps_age;     /*Age of differential corrections (null when DGPS is notused)*/
    uint32_t diffStation;    /*ID of station providing differential corrections*/
} gga_t;

/* Latitude and longitude, with time of position fix and status */
typedef struct  {
    struct tm time_date;
    char lat_dir; /* North/South indicator */
    GnssCoordinate_t coordinate_ddmm;
    char lon_dir;  /* Longitude direction East/West indicator */
    char status;   /*Data validity status*/
    char pos_mode; /*Positioning mode, see position fix flags description*/
    FrameCnt_t fcnt;
} gll_t;

typedef struct  {
    char opMode;      /* Operation mode:*/
    uint8_t navMode;  /* Navigation mode  */
    double PDOP;      /* Position dilution of precision */
    double HDOP;      /* Horizontal dilution of precision */
    double VDOP;      /* Vertical dilution of precision */
    uint8_t systemId; /* NMEA-defined GNSS system ID*/
    FrameCnt_t fcnt;
} gsa_t;

/*Course over ground and ground speed*/
typedef struct  {
    double cogt;   /*Course over ground (true)*/
    double cogm;   /*Course over ground (magnetic)*/
    double sogn;   /*Speed over ground knot/s*/
    double sogk;   /*Speed over ground km/h*/
    char cogtUnit; /*Course over ground units: T (degrees true, fixed field)*/
    char cogmUnit; /*Course over ground units: M (degrees magnetic, fixed field)*/
    char sognUnit; /*Speed over ground units: N (knots, fixed field)*/
    char sogkUnit; /*Speed over ground units: K*/
    char posMode;  /*Mode indicator*/
    FrameCnt_t fcnt;
} vtg_t;

typedef struct  {
    uint8_t msg_id;
    struct tm time_date;
    FrameCnt_t fcnt;
} pbux_t;

typedef struct  {
    uint16_t svid; /*Satellite ID*/
    uint8_t elv;   /*Elevation (<= 90)*/
    uint16_t az;   /*Azimuth (range: 0-359)*/
    uint8_t cno;   /*Signal strength (C/N0, range: 0-99), null when not tracking*/
} Satellite_t;

/*GNSS satellites in view*/
typedef struct  {
    uint8_t numMsg;   /*Number of messages, total number of GSV messages being output (range: 1-9)*/
    uint8_t msgNum;   /*Number of this message*/
    uint8_t signalId; /*NMEA-defined GNSS signal ID*/
    Satellite_t sat[NUM_OF_PARSED_SAT];
    uint16_t numSV; /*Number of known satellites in view regarding both the talker ID and the signalId*/
    FrameCnt_t fcnt;
} gsv_t;

/*Time and date*/
typedef struct  {
    struct tm time_date;
    uint8_t ltzh;
    uint8_t ltzn;
    FrameCnt_t fcnt;
} zda_t;

typedef struct  {
    FrameCnt_t fcnt;
} txt_t;


#define NMEA_MESSAGES                                 \
    rmc_t rmc;   /*Recommended minimum data*/         \
    gll_t gll;   /*Latitude and longitude, with time of position fix and status*/      \
    vtg_t vtg;   /*Course over ground and ground speed*/      \
    gga_t gga;   /*Global positioning system fix data*/      \
    gsa_t gsa;   /*GNSS DOP and active satellites*/          \
    gsv_t gsv;   /*GNSS satellites in view*/      \
    txt_t txt; /*Text transmission*/                 \
    zda_t zda; /*Time and date*/

#define NMEA_DATA                                    \
    NMEA_MESSAGES                                    \
    struct tm time_date;                             \
    uint32_t gnss_time_stamp;                        \
    uint32_t rtk_start_cnt;                          \
    double height; /*Altitude above mean sea level*/ \
    uint8_t is_initialized;                          \
    pbux_t pbux; /*Proprietary NMEA messages for u-blox positioning receivers*/      \
    GnssCoordinate_t coordinate_dd;

#define NMEA_COMMON_VARIABLE   \
    uint32_t baud_rate;        \
    uint8_t valid;             \
    uint8_t uart_num;          \
    uint32_t rx_buff_size;     \
    uint8_t* RxFifoArray;      \
    uint8_t num;

typedef struct  {
    NMEA_COMMON_VARIABLE
} NmeaConfig_t;

#define NMEA_CRC_VARIABLES                    \
    uint32_t crc_err_cnt;                     \
    uint32_t crc_err_cnt_prev;                \
    uint32_t crc_read_cnt;                    \
    uint8_t crc_nibble;                       \
    uint8_t crc_read;                         \
    uint32_t crc_ok_cnt;

#define NMEA_ERROR_VARIABLES                  \
    uint32_t err_parse_prev;                  \
    uint32_t err_parse;                       \
    uint32_t err_cnt;


#define NMEA_PROTOCOL                         \
    NMEA_CRC_VARIABLES                        \
    NMEA_ERROR_VARIABLES                      \
    uint16_t pos;                             \
    uint32_t msg_cnt;                         \
    uint32_t undef_err_cnt;                   \
    RxState_t state;                          \
    uint32_t len_min;                         \
    uint32_t len_max;                         \
    uint32_t rx_byte_cnt;                     \
    uint32_t overflow;                        \
    uint32_t proc_msg_cnt;                    \
    uint32_t rx_error_cnt;                    \
    uint32_t rtk_fixed_start_ms;              \
    uint32_t rtk_fixed_max_duration_ms;       \
    uint32_t cur_rtk_fixed_duration;          \
    bool got_massege;                         \
    char message[NMEA_MSG_SIZE];              \
    char fix_message[NMEA_MSG_SIZE];          \
    char undef_message[NMEA_MSG_SIZE];        \
    PositionMode_t pos_mode;

typedef struct {
    NMEA_COMMON_VARIABLE
    NMEA_DATA
    NMEA_PROTOCOL


#ifdef HAS_FIFO_CHAR
    FifoChar_t RxFifo;
#endif
} NmeaHandle_t;

#endif /* NMEA_TYPES_H */
