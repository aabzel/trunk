#ifndef RDS_PROTOCOL_CONSTANTS_H
#define RDS_PROTOCOL_CONSTANTS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rds_dep.h"

typedef enum  {
    COUNTRY_CODE_ESTONIA =2,
    COUNTRY_CODE_TYRKEY =3,
    COUNTRY_CODE_RUSSIA =7,
    COUNTRY_CODE_FINLAND =6,
    COUNTRY_CODE_UKRAINE =6,
    COUNTRY_CODE_BELARUS =0xF,
    COUNTRY_CODE_UNDEF = 0,
} CountryCode_t;

typedef enum  {
    COV_AREA_CODE_L =0,       /*Local*/
    COV_AREA_CODE_I =1,       /*International*/
    COV_AREA_CODE_N =2,       /*National*/
    COV_AREA_CODE_S =3,       /*Supre-Region*/
    COV_AREA_CODE_R1 =4,      /*Regional*/
    COV_AREA_CODE_R2 =5,      /*Regional*/
    COV_AREA_CODE_R3 =6,      /*Regional*/
    COV_AREA_CODE_R4 =7,      /*Regional*/
    COV_AREA_CODE_R5 =8,      /*Regional*/
    COV_AREA_CODE_R6 =9,      /*Regional*/
    COV_AREA_CODE_R7 =0xA,    /*Regional*/
    COV_AREA_CODE_R8 =0xB,    /*Regional*/
    COV_AREA_CODE_R9 =0xC,    /*Regional*/
    COV_AREA_CODE_R10 =0xD,   /*Regional*/
    COV_AREA_CODE_R11 =0xE,   /*Regional*/
    COV_AREA_CODE_R12 =0xF,   /*Regional*/
} CoverageAreaCode_t;


typedef enum  {
	GROUP_TYPE_A=0,
	GROUP_TYPE_B=1,

	GROUP_TYPE_UNDEF=2,
}Group_t;


typedef enum  {
    GR_TYPE_BASIC = 0, /*Basic tuning*/
    GR_TYPE_PROG_NUM = 1,
    GR_TYPE_RADIO_TEXT = 2,
    GR_TYPE_APP_ID = 3, /**/
    GR_TYPE_CLOCK_TIME_DATE = 4,
    GR_TYPE_DATA_CH= 5,
    GR_TYPE_IN_HOUSE_APP= 6, /*In house*/
    GR_TYPE_PADDING= 7,
    GR_TYPE_TRAFFIC_MES= 8,
    GR_TYPE_EMERGENCY= 9,
    GR_TYPE_PROG_TYPE_NAME= 10,
    GR_TYPE_OPEN_DATA_APP= 11,
    GR_TYPE_OPEN_DATA_APP2= 12,
    GR_TYPE_ENH_RADIO_PAGING= 13,
    GR_TYPE_ENH_OTHER_NET_INF= 14,
    GR_TYPE_RBDS = 15,
} GroupType_t;

typedef enum  {
    PROG_TYPE_UNDEF = 0,
    PROG_TYPE_NEWS = 1,
    PROG_TYPE_CURRENT_AFFAIRS = 2,
    PROG_TYPE_INFORMATION = 3,
    PROG_TYPE_SPORT = 4,
    PROG_TYPE_EDUCATION = 5,
    PROG_TYPE_DRAMA = 6,
    PROG_TYPE_CULTURE = 7,
    PROG_TYPE_SCIENCE = 8,
    PROG_TYPE_VARIED = 9,
    PROG_TYPE_POP_MUSIC = 10,
    PROG_TYPE_ROCK_MUSIC = 11,
    PROG_TYPE_EASY_LISTENING = 12,
    PROG_TYPE_LIGHT_CLASSICAL = 13,
    PROG_TYPE_SERIOUS_CLASSICAL = 14,
    PROG_TYPE_OTHER_MUSIC = 15,
    PROG_TYPE_WEATHER = 16,
    PROG_TYPE_FINANCE = 17,
    PROG_TYPE_CHILDREN_PROGRAMMES = 18,
    PROG_TYPE_SOCIAL_AFFAIRS = 19,
    PROG_TYPE_RELIGION = 20,
    PROG_TYPE_PHONE_IN = 21,
    PROG_TYPE_TRAVEL = 22,
    PROG_TYPE_LEISURE = 23,
    PROG_TYPE_JAZZ_MUSIC = 24,
    PROG_TYPE_COUNTRY_MUSIC = 25,
    PROG_TYPE_NATIONAL_MUSIC = 26,
    PROG_TYPE_OLDIES_MUSIC= 27,
    PROG_TYPE_FOLK_MUSIC= 28,
    PROG_TYPE_DOCUMENTARY= 29,
    PROG_TYPE_ALARM_TEST= 30,
    PROG_TYPE_ALARM= 31,
} RdsProgramType_t;
 

#ifdef __cplusplus
}
#endif

#endif /* RDS_PROTOCOL_CONSTANTS_H */
