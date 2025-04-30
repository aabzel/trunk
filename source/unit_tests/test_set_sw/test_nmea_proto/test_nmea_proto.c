#include "test_nmea_proto.h"

#ifdef  X86_64
#include <stdio.h>
#endif /*X86_64*/

#include "data_utils.h"
#include "log.h"
#include "gnss_utils.h"
#include "nmea_protocol.h"
#include "unit_test_check.h"

const char msg_gnrmc0[] = "$GNRMC,072316.27,A,5551.84825,N,03725.60995,E,0.010,,290721,11.73,E,A,V*76";
const char msg_gnrmc1[] = "$GPRMC,223047.00,V,,,,,,,120222,,,N*7C";
const char msg_gnrmc2[] = "$GNRMC,163320.60,A,5540.70459,N,03737.93393,E,0.047,,140222,,,A,V*1B";
// tsr nmea+
bool test_nmea_proto_gnrmc(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
   rmc_t rmc= {0};
   set_log_level(NMEA, LOG_LEVEL_DEBUG);
   set_log_level(SYS, LOG_LEVEL_DEBUG);

   ASSERT_TRUE( gnss_parse_rmc((char*)msg_gnrmc2, &rmc));
   ASSERT_EQ(16,rmc.time_date.tm_hour);
   ASSERT_EQ(33,rmc.time_date.tm_min);
   ASSERT_EQ(20,rmc.time_date.tm_sec);
   ASSERT_NEAR(5540.70459l,rmc.coordinate_ddmm.latitude, 1e-6);
   ASSERT_NEAR(3737.93393l,rmc.coordinate_ddmm.longitude, 0.00001f);
   ASSERT_EQ('N',rmc.lat_dir);
   ASSERT_EQ('N',rmc.lat_dir);
   ASSERT_EQ('E',rmc.lon_dir);
   ASSERT_NEAR(0.047l,rmc.speed_knots,0.00001f);
   ASSERT_EQ('A',rmc.pos_mode);

   ASSERT_EQ(14,rmc.time_date.tm_mday);
   ASSERT_EQ(1, rmc.time_date.tm_mon); /*UBlox count from 1 time.h - from 0*/
   ASSERT_EQ(2022,rmc.time_date.tm_year);

   ASSERT_TRUE( gnss_parse_rmc((char*)msg_gnrmc0, &rmc));
   ASSERT_EQ(7,rmc.time_date.tm_hour);
   ASSERT_EQ(23,rmc.time_date.tm_min);
   ASSERT_EQ(16,rmc.time_date.tm_sec);
   ASSERT_EQ('A',rmc.data_valid);
   ASSERT_NEAR(5551.84825l,rmc.coordinate_ddmm.latitude, 1e-6);
   ASSERT_EQ('N',rmc.lat_dir);
   ASSERT_NEAR(3725.60995l,rmc.coordinate_ddmm.longitude, 0.00001f);
   ASSERT_EQ('E',rmc.lon_dir);
   ASSERT_NEAR(0.010l,rmc.speed_knots,0.00001f);

   ASSERT_EQ(29,rmc.time_date.tm_mday);
   ASSERT_EQ(6, rmc.time_date.tm_mon); /*UBlox count from 1 time.h - from 0*/
   ASSERT_EQ(2021,rmc.time_date.tm_year);

   ASSERT_NEAR(11.73l, rmc.mv, 0.00001f);
   ASSERT_EQ('E',rmc.mv_ew);
   ASSERT_EQ('A',rmc.pos_mode);
   ASSERT_TRUE( gnss_parse_rmc((char*)msg_gnrmc1, &rmc));
   ASSERT_EQ(22,rmc.time_date.tm_hour);
   ASSERT_EQ(30,rmc.time_date.tm_min);
   ASSERT_EQ(47,rmc.time_date.tm_sec);
   ASSERT_EQ(12,rmc.time_date.tm_mday);
   ASSERT_EQ(1, rmc.time_date.tm_mon); /*UBlox count from 1 time.h - from 0*/
   ASSERT_EQ(2022,rmc.time_date.tm_year);

   ASSERT_TRUE(nmea_parse((char*) msg_gnrmc0,strlen(msg_gnrmc0), &NmeaData));

   set_log_level(NMEA, LOG_LEVEL_INFO);
   set_log_level(SYS, LOG_LEVEL_INFO);
   return true;
}

const char msg_gnrgga[] = "$GNGGA,140212.00,5540.70555,N,03737.93437,E,1,12,0.58,201.3,M,13.3,M,,*45";
bool test_nmea_proto_gngga(void) {
#ifdef  X86_64
    LOG_INFO(NMEA,"%s():"CRLF,__FUNCTION__);
#endif
   gga_t gga= {0};
   ASSERT_TRUE( gnss_parse_gga((char*)msg_gnrgga, &gga));
   ASSERT_EQ(14,gga.time_date.tm_hour);
   ASSERT_EQ(2,gga.time_date.tm_min);
   ASSERT_EQ(12,gga.time_date.tm_sec);
   ASSERT_NEAR(5540.70555,gga.coordinate_ddmm.latitude,0.000001);
   ASSERT_EQ('N',gga.lat_dir);
   ASSERT_NEAR(03737.93437,gga.coordinate_ddmm.longitude,0.00001);
   ASSERT_EQ('E',gga.lon_dir);
   ASSERT_EQ(1,gga.quality);
   ASSERT_EQ(12,gga.nb_sat);
   ASSERT_NEAR(0.58,gga.hdop,0.00001);
   ASSERT_NEAR(201.3, gga.height, 0.00001);
   ASSERT_EQ('M',gga.height_unit);
   ASSERT_NEAR(13.3, gga.geoid_separation, 0.001);
   ASSERT_EQ('M',gga.geoid_unit);

   ASSERT_TRUE(nmea_parse((char*) msg_gnrgga,strlen(msg_gnrgga), &NmeaData));

   return true;
}

const char msg_gnrgll[] = "$GNGLL,5540.70584,N,03737.93404,E,140125.00,A,A*74";
const char msg_gnrgll2[] = "$GPGLL,,,,,213748.00,V,N*41";
bool test_nmea_proto_gngll(void) {
#ifdef  X86_64
    LOG_INFO(NMEA,"%s():"CRLF,__FUNCTION__);
#endif
    gll_t gll= {0};
    set_log_level(SYS, LOG_LEVEL_DEBUG);
    set_log_level(NMEA, LOG_LEVEL_DEBUG);
    ASSERT_TRUE( gnss_parse_gll((char*)msg_gnrgll2, &gll));
    ASSERT_EQ(21,gll.time_date.tm_hour);
    ASSERT_EQ(37,gll.time_date.tm_min);
    ASSERT_EQ(48,gll.time_date.tm_sec);
    ASSERT_EQ('N',gll.pos_mode);

    ASSERT_TRUE( gnss_parse_gll((char*)msg_gnrgll, &gll));
    ASSERT_EQ(14,gll.time_date.tm_hour);
    ASSERT_EQ(1,gll.time_date.tm_min);
    ASSERT_EQ(25,gll.time_date.tm_sec);
    ASSERT_NEAR(5540.70584,gll.coordinate_ddmm.latitude,0.000001);
    ASSERT_EQ('N',gll.lat_dir);
    ASSERT_NEAR(03737.93404,gll.coordinate_ddmm.longitude,0.00001);
    ASSERT_EQ('E',gll.lon_dir);
    ASSERT_EQ('A',gll.status);
    ASSERT_EQ('A',gll.pos_mode);
    set_log_level(SYS, LOG_LEVEL_INFO);
    set_log_level(NMEA, LOG_LEVEL_INFO);

    ASSERT_TRUE(nmea_parse((char*) msg_gnrgll,strlen(msg_gnrgll), &NmeaData));
    return true;
}

const char msg_gnrgsa[] = "$GNGSA,A,3,78,85,68,84,69,,,,,,,,1.04,0.58,0.86,2*0B";
const char msg_gnrgsa1[] = "$GPGSA,A,1,,,,,,,,,,,,,99.99,99.99,99.99*30";
bool test_nmea_proto_gngsa(void) {
#ifdef  X86_64
    LOG_INFO(NMEA,"%s():"CRLF,__FUNCTION__);
#endif
    gsa_t gsa= {0};
    ASSERT_TRUE( gnss_parse_gsa((char*)msg_gnrgsa, &gsa));
    ASSERT_EQ('A',gsa.opMode);
    ASSERT_EQ(3,gsa.navMode);
    ASSERT_NEAR(1.04,gsa.PDOP,0.000001);
    ASSERT_NEAR(0.58,gsa.HDOP,0.00001);
    ASSERT_NEAR(0.86,gsa.VDOP,0.00001);
    ASSERT_EQ(2,gsa.systemId);
    ASSERT_TRUE( gnss_parse_gsa((char*)msg_gnrgsa1, &gsa));
    ASSERT_TRUE(nmea_parse((char*) msg_gnrgsa,strlen(msg_gnrgsa), &NmeaData));
    return true;
}

const char msg_gnzda[]  ="$GNZDA,122013.00,29,11,2021,00,00*71";
const char msg_gnzda1[] ="$GPZDA,214101.00,12,02,2022,00,00*62";
bool test_nmea_proto_gnzda(void) {
   LOG_INFO(NMEA,"%s()",__FUNCTION__);
    zda_t zda= {0};
    ASSERT_TRUE( gnss_parse_zda((char*)msg_gnzda, &zda));
    ASSERT_EQ(12, zda.time_date.tm_hour);
    ASSERT_EQ(20, zda.time_date.tm_min);
    ASSERT_EQ(13, zda.time_date.tm_sec);
    ASSERT_EQ(29, zda.time_date.tm_mday);
    ASSERT_EQ(11, zda.time_date.tm_mon);
    ASSERT_EQ(2021, zda.time_date.tm_year);

    ASSERT_EQ(0, zda.ltzh);
    ASSERT_EQ(0, zda.ltzn);

    ASSERT_TRUE( gnss_parse_zda((char*)msg_gnzda1, &zda));

    return true;
}


const char msg_gnrvtg[] = "$GNVTG,,T,,M,0.017,N,0.032,K,A*3A";
const char msg_gnrvtg1[] = "$GPVTG,,,,,,,,,N*30";
bool test_nmea_proto_gnvtg(void) {
    LOG_INFO(NMEA,"%s():"CRLF,__FUNCTION__);
    vtg_t vtg= {0};
    set_log_level(SYS, LOG_LEVEL_DEBUG);
    set_log_level(NMEA, LOG_LEVEL_DEBUG);
    ASSERT_TRUE( gnss_parse_vtg((char*)msg_gnrvtg, &vtg));
    ASSERT_EQ('T',vtg.cogtUnit);
    ASSERT_EQ('M',vtg.cogmUnit);
    ASSERT_NEAR(0.017,vtg.sogn,0.000001);
    ASSERT_EQ('N',vtg.sognUnit);
    ASSERT_NEAR(0.032,vtg.sogk,0.00001);
    ASSERT_EQ('K',vtg.sogkUnit);
    ASSERT_EQ('A',vtg.posMode);
    ASSERT_TRUE( gnss_parse_vtg((char*)msg_gnrvtg1, &vtg));
    set_log_level(SYS, LOG_LEVEL_INFO);
    set_log_level(NMEA, LOG_LEVEL_INFO);
    return true;
}

static bool test_nmea_checksum(void){
    LOG_INFO(NMEA,"%s():"CRLF,__FUNCTION__);
    uint8_t checksum =0;
    checksum = nmea_calc_checksum((char*)&msg_gnrmc0[1], strlen(msg_gnrmc0)-NMEA_OVERHEAD);
    ASSERT_EQ(0x76, checksum);
    checksum = nmea_calc_checksum((char*)&msg_gnrmc1[1], strlen(msg_gnrmc1)-NMEA_OVERHEAD);
    ASSERT_EQ( 0x7C, checksum);
    return true;
}

const char msg_pubx[] = "$PUBX,00,001417.00,0000.00000,N,00000.00000,E,0.000,NF,5303356,3750039,0.000,0.00,0.000,,99.99,99.99,99.99,0,0,0*21";
bool test_nmea_proto_pubx(void) {

    LOG_INFO(NMEA,"%s():"CRLF,__FUNCTION__);

    pbux_t pbux= {0};
    ASSERT_TRUE( gnss_parse_pbux_pos((char*)msg_pubx, &pbux));
    ASSERT_EQ(0,pbux.msg_id);//00,001417.00,0000.00000,N,00000.00000,E,0.000,NF,5303356,3750039,0.000,0.00,0.000,,99.99,99.99,99.99,0,0,0*21
    ASSERT_EQ(17,pbux.time_date.tm_sec);//001417.00,0000.00000,N,00000.00000,E,0.000,NF,5303356,3750039,0.000,0.00,0.000,,99.99,99.99,99.99,0,0,0*21
    ASSERT_EQ(14,pbux.time_date.tm_min);
    ASSERT_EQ(0,pbux.time_date.tm_hour);
#if 0
    ASSERT_NEAR(0000.0,pbux.latitude,0.000001);//0000.00000,N,00000.00000,E,0.000,NF,5303356,3750039,0.000,0.00,0.000,,99.99,99.99,99.99,0,0,0*21
    ASSERT_NEAR(0000.0,pbux.longitude,0.000001);//00000.00000,E,0.000,NF,5303356,3750039,0.000,0.00,0.000,,99.99,99.99,99.99,0,0,0*21
    ASSERT_EQ('N',pbux.ns_indicator);//N,00000.00000,E,0.000,NF,5303356,3750039,0.000,0.00,0.000,,99.99,99.99,99.99,0,0,0*21
    ASSERT_EQ('E',pbux.ee_indicator);//E,0.000,NF,5303356,3750039,0.000,0.00,0.000,,99.99,99.99,99.99,0,0,0*21
    ASSERT_NEAR(0.0,vtg.altitude,0.00001);//
    ASSERT_STR_EQ("NF",pbux.nav_status);//
    ASSERT_NEAR(5303356, pbux.horizontal_accuracy_estimate,0.3);//
    ASSERT_NEAR(3750039, pbux.vertical_accuracy_estimate,0.3);//
    ASSERT_NEAR(0.0,pbux.speed_over_ground,0.4);//km/h
    ASSERT_NEAR(0.0, pbux.Course_over_ground,0.3);//deg
    ASSERT_NEAR(0.0, pbux.Vertical_velocity,0.3);//m/s
    ASSERT_EQ('A',pbux.posMode);
#endif
    return true;
}

static char* NmeaMessages[]={
  //    {0x0d,'b',0},
      "$GNTXT,01,01,02,u-blox AG - www.u-blox.com*4E",
      "$GNTXT,01,01,02,EXT CORE 1.00 (61b2dd)*68",
      "$GNTXT,01,01,02,ROM BASE 0x118B2060*20",
      "$GNTXT,01,01,02,FWVER=HPG 1.12*5D",
      "$GNTXT,01,01,02,PROTVER=27.11*1D",
      "$GNTXT,01,01,02,MOD=ZED-F9P*71",
      "$GNTXT,01,01,02,GPS;GLO;GAL;BDS*77",
      "$GNTXT,01,01,02,QZSS*58",
      "$GNTXT,01,01,02,ANTSUPERV=*22",
      "$GNTXT,01,01,02,ANTSTATUS=DONTKNOW*2D",
      "$GNTXT,01,01,02,PF=FDB79*36",
      "$GNTXT,01,01,02,Starting GNSS*5A",
      "$GNRMC,,V,,,,,,,,,,N,V*37",
      "$GNVTG,,,,,,,,,N*2E",
      "$GNGGA,,,,,,0,00,99.99,,,,,,*56]",
      "$GNGSA,A,1,,,,,,,,,,,,,99.99,99.99,99.99,1*33",
      "$GNGSA,A,1,,,,,,,,,,,,,99.99,99.99,99.99,2*30",
      "$GNGSA,A,1,,,,,,,,,,,,,99.99,99.99,99.99,3*31",
      "$GNGSA,A,1,,,,,,,,,,,,,99.99,99.99,99.99,4*36",
      "$GPGSV,1,1,00,1*64",
      "$GPGSV,1,1,00,6*63",
      "$GLGSV,1,1,00,1*78",
      "$GLGSV,1,1,00,3*7A",
      "$GAGSV,1,1,00,7*73",
      "$GAGSV,1,1,00,2*76",
      "$GBGSV,1,1,00,1*76",
      "$GBGSV,1,1,00,3*74",
      "$GNGLL,,,,,,V,N*7A",

     "$GBGSV,3,3,09,35,18,108,,3*4B",
     "$GBGSV,2,1,08,08,31,058,31,12,79,283,39,19,,,40,21,17,171,31,1*4A",
     "$GBGSV,2,2,08,22,46,119,42,23,16,323,39,34,48,284,41,35,18,108,38,1*70",
     "$GBGSV,3,1,09,08,31,058,41,11,,,45,12,79,283,49,13,,,44,3*77",
     "$GBGSV,3,2,09,21,17,171,,22,46,119,,23,16,323,,34,48,284,,3*74",
     "$GAGSV,2,1,07,02,37,296,47,11,85,275,44,12,38,081,43,14,18,127,37,2*7D",
     "$GAGSV,2,1,08,02,37,296,40,10,,,43,11,85,275,39,12,38,081,36,7*42",
     "$GAGSV,2,2,07,25,36,231,45,30,07,338,37,36,32,264,43,2*49",
     "$GAGSV,2,2,08,14,18,127,35,25,36,231,40,30,07,338,36,36,32,264,40,7*7A",
     "$GLGSV,3,1,09,66,04,010,35,67,39,048,43,68,42,121,46,73,11,225,31,1*7B",
     "$GLGSV,3,1,09,66,04,010,35,67,39,048,46,68,42,121,45,73,11,225,44,3*7D",
     "$GLGSV,3,2,09,74,33,269,,75,25,332,45,82,16,092,26,83,59,072,45,3*7B",
     "$GLGSV,3,2,09,74,33,269,34,75,25,332,36,82,16,092,32,83,59,072,31,1*7C",
     "$GLGSV,3,3,09,84,49,293,28,1*42",
     "$GLGSV,3,3,09,84,49,293,45,3*4B",
     "$GNGGA,185259.00,5540.70546,N,03737.93424,E,1,12,0.53,198.3,M,13.3,M,,*4B",
     "$GNGGA,185300.00,5540.70545,N,03737.93422,E,1,12,0.53,198.3,M,13.3,M,,*43",
     "$GNGSA,A,3,02,12,25,11,36,,,,,,,,1.04,0.53,0.89,3*02",
     "$GNGSA,A,3,05,10,18,15,23,26,27,29,16,,,,1.04,0.53,0.89,1*06",
     "$GNGSA,A,3,05,10,18,15,23,26,27,29,16,,,,1.04,0.53,0.89,1*06",
     "$GNGSA,A,3,22,08,23,12,34,21,35,,,,,,1.04,0.53,0.89,4*0E",
     "$GNGSA,A,3,83,74,67,68,7,21,17,171,,22,46,119,,23,16,323,,34,48,284,,3*74",
     "$GNGSA,A,3,83,74,67,68,73,,,,,,,,1.04,0.53,0.89,2*03",
     "$GNRMC,163318.60,A,5540.70487,N,03737.93359,E,0.076,,140222,,,A,V*17",
     "$GNRMC,163318.80,A,5540.70484,N,03737.93363,E,0.038,,140222,,,A,V*19",
     "$GNRMC,163319.00,A,5540.70480,N,03737.93368,E,0.048,,140222,,,A,V*18",
     "$GNRMC,163319.20,A,5540.70477,N,03737.93371,E,0.091,,140222,,,A,V*1E",
     "$GNRMC,163319.40,A,5540.70475,N,03737.93374,E,0.037,,140222,,,A,V*13",
     "$GNRMC,163319.60,A,5540.70472,N,03737.93377,E,0.041,,140222,,,A,V*14",
     "$GNRMC,163319.80,A,5540.70470,N,03737.93380,E,0.013,,140222,,,A,V*17",
     "$GNRMC,163320.00,A,5540.70468,N,03737.93383,E,0.030,,140222,,,A,V*1E",
     "$GNRMC,163320.20,A,5540.70465,N,03737.93386,E,0.018,,140222,,,A,V*1E",
     "$GNRMC,163320.40,A,5540.70463,N,03737.93388,E,0.042,,140222,,,A,V*1F",
     "$GNRMC,163320.60,A,5540.70459,N,03737.93393,E,0.047,,140222,,,A,V*1B",
     "$GNRMC,163320.80,A,5540.70456,N,03737.93398,E,0.022,,140222,,,A,V*12",
     "$GNRMC,163321.00,A,5540.70452,N,03737.93402,E,0.039,,140222,,,A,V*11",
     "$GNRMC,163321.20,A,5540.70449,N,03737.93406,E,0.017,,140222,,,A,V*11",
     "$GNRMC,163321.40,A,5540.70446,N,03737.93410,E,0.018,,140222,,,A,V*10",
     "$GNRMC,163321.60,A,5540.70443,N,03737.93413,E,0.012,,140222,,,A,V*1E",
     "$GNRMC,163321.80,A,5540.70440,N,03737.93417,E,0.014,,140222,,,A,V*11",
     "$GNRMC,163322.00,A,5540.70438,N,03737.93420,E,0.030,,140222,,,A,V*17",
     "$GNRMC,163322.20,A,5540.70436,N,03737.93422,E,0.060,,140222,,,A,V*1C",
     "$GNRMC,163322.40,A,5540.70437,N,03737.93422,E,0.135,,140222,,,A,V*1A",
     "$GNRMC,163322.60,A,5540.70435,N,03737.93423,E,0.073,,140222,,,A,V*18",
     "$GNRMC,163322.80,A,5540.70435,N,03737.93424,E,0.040,,140222,,,A,V*11",
     "$GNRMC,163323.00,A,5540.70434,N,03737.93424,E,0.045,,140222,,,A,V*1C",
     "$GNRMC,163323.20,A,5540.70433,N,03737.93424,E,0.070,,140222,,,A,V*1F",
     "$GNRMC,163323.40,A,5540.70433,N,03737.93426,E,0.042,,140222,,,A,V*1A",
     "$GNRMC,163323.60,A,5540.70431,N,03737.93427,E,0.020,,140222,,,A,V*1F",
     "$GNRMC,163323.80,A,5540.70430,N,03737.93427,E,0.040,,140222,,,A,V*16",
     "$GNRMC,163324.00,A,5540.70429,N,03737.93428,E,0.079,,140222,,,A,V*14",
     "$GNRMC,163324.20,A,5540.70428,N,03737.93430,E,0.067,,140222,,,A,V*11",
     "$GNRMC,163324.40,A,5540.70426,N,03737.93431,E,0.032,,140222,,,A,V*18",
     "$GNRMC,163324.60,A,5540.70425,N,03737.93431,E,0.018,,140222,,,A,V*11",
     "$GNRMC,163324.80,A,5540.70424,N,03737.93433,E,0.052,,140222,,,A,V*12",
     "$GNRMC,163325.00,A,5540.70422,N,03737.93435,E,0.051,,140222,,,A,V*18",
     "$GNRMC,163325.20,A,5540.70421,N,03737.93438,E,0.078,,140222,,,A,V*1F",
     "$GNRMC,163325.40,A,5540.70420,N,03737.93440,E,0.115,,140222,,,A,V*1D",
     "$GNRMC,185259.00,A,5540.70546,N,03737.93424,E,0.018,,140222,,,A,V*14",
     "$GNRMC,185300.00,A,5540.70545,N,03737.93422,E,0.009,,140222,,,A,V*1C",
     "$GNVTG,,T,,M,0.009,N,0.017,K,A*32",
     "$GNVTG,,T,,M,0.018,N,0.033,K,A*34",
     "$GPGSV,3,1,11,05,16,044,37,07,08,347,33,10,23,194,38,15,25,094,38,6*6A",
     "$GPGSV,3,1,11,05,16,044,40,07,08,347,34,10,23,194,38,15,25,094,39,1*6B",
     "$GPGSV,3,2,11,16,48,271,,18,74,081,47,23,51,172,43,26,36,224,41,6*6B",
     "$GPGSV,3,2,11,16,48,271,43,18,74,081,45,23,51,172,43,26,36,224,40,1*68",
     "$GPGSV,3,3,11,27,32,298,40,29,21,125,43,30,01,010,33,1*5D",
     "$GPGSV,3,3,11,27,32,298,45,29,21,125,38,30,01,010,24,6*55"
};

bool test_nmea_proto(void) {
  LOG_INFO(NMEA,"%s()",__FUNCTION__);
  ASSERT_EQ(16, sizeof(GnssCoordinate_t));

  ASSERT_TRUE(nmea_init());
  set_log_level(SYS, LOG_LEVEL_DEBUG);
  set_log_level(NMEA, LOG_LEVEL_DEBUG);

  uint32_t i=0;
  LOG_INFO(NMEA,"Proc: %u Messages",ARRAY_SIZE(NmeaMessages));
  for(i=0;i<ARRAY_SIZE(NmeaMessages);i++){
      /*Goat to catch HardFault*/
      LOG_INFO(NMEA,"Try[%s]",NmeaMessages[i]);
      nmea_parse((char*) NmeaMessages[i],strlen(NmeaMessages[i]), &NmeaData);
  }

  set_log_level(SYS, LOG_LEVEL_INFO);
  set_log_level(NMEA, LOG_LEVEL_INFO);
  return true;
}

bool test_nmea_crc(void){
  ASSERT_TRUE(test_nmea_checksum());
  return true;
}

