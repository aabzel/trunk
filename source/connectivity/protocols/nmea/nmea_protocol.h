#ifndef NMEA_PARSER_H
#define NMEA_PARSER_H

#include "std_includes.h"
#include "nmea_types.h"
#include "nmea_config.h"
#include "nmea_isr.h"
#ifdef HAS_NMEA_DIAG
#include "nmea_diag.h"
#endif

//extern NmeaProtocol_t NmeaProto;
//extern NmeaData_t NmeaData;


NmeaHandle_t* NmeaGetNodeByUartNum(uint8_t uart_num);
NmeaHandle_t* NmeaGetNode(uint8_t num);
const NmeaConfig_t* NmeaGetConfig(uint8_t num);

uint8_t nmea_calc_checksum(char* nmea_data, uint16_t len);
bool nmea_check(uint8_t num);
bool nmea_init_one(uint8_t num);
bool nmea_mcal_init(void);
bool nmea_proc_byte(NmeaHandle_t* Node, uint8_t rx_byte);
//bool nmea_proc_one(uint8_t num);
bool nmea_proc(void);
bool nmea_sync_rtc_proc(void);

bool nmea_parse(NmeaHandle_t* Node, char* nmea_msg, uint16_t len);
bool gnss_parse_zda(char* nmea_msg, zda_t* zda);
bool gnss_parse_rmc(char* nmea_msg, rmc_t* rmc);
bool gnss_parse_vtg(char* nmea_msg, vtg_t* vtg);
bool gnss_parse_gga(char* nmea_msg, gga_t* gga);
bool gnss_parse_gsa(char* nmea_msg, gsa_t* gsa);
bool gnss_parse_pbux_pos(char* nmea_msg, pbux_t* const pbux);
bool gnss_parse_gll(char* nmea_msg, gll_t* gll);

#endif /* NMEA_PARSER_H */
