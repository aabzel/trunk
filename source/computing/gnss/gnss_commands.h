#ifndef GNSS_COMMANDS_H
#define GNSS_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifdef HAS_GNSS_RTK
#ifndef HAS_UBLOX_COMMANDS
#error "Ublox command are needed in RTK mode"
#endif /*HAS_UBLOX_COMMANDS*/
#ifndef HAS_NMEA_COMMANDS
#error "NMEA command are needed in RTK mode"
#endif /*HAS_NMEA_COMMANDS*/
#endif /*HAS_GNSS_RTK*/


#ifdef HAS_UBLOX_COMMANDS
#include "ublox_commands.h"
#else
#define UBLOX_COMMANDS
#endif

#ifdef HAS_NMEA_COMMANDS
#include "nmea_commands.h"
#else
#define NMEA_COMMANDS
#endif

#ifdef HAS_RTCM3_COMMANDS
#include "rtcm3_commands.h"
#else
#define RTCM3_COMMANDS
#endif

#ifdef HAS_ZED_F9P_COMMANDS
#include "zed_f9p_commands.h"
#else
#define ZED_F9P_COMMANDS
#endif

#ifdef HAS_NEO_6M_COMMANDS
#include "neo_6m_commands.h"
#else
#define NEO_6M_COMMANDS
#endif

#ifdef HAS_GPS_COMMANDS
#include "gps_commands.h"
#else
#define GPS_COMMANDS
#endif

#ifdef HAS_GPS_1BIT_COMMANDS
#include "gps_1bit_commands.h"
#else
#define GPS_1BIT_COMMANDS
#endif

bool gnss_data_command(int32_t argc, char* argv[]);
bool gnss_generate_lo_command(int32_t argc, char* argv[]);
bool gnss_doppler_command(int32_t argc, char* argv[]);
bool gnss_set_location_command(int32_t argc, char* argv[]);
bool gnss_carr_pahse_err_command(int32_t argc, char* argv[]);

#define GNSS_COMMANDS                                               \
    NMEA_COMMANDS                                                   \
    GPS_COMMANDS                                                    \
    GPS_1BIT_COMMANDS                                               \
    RTCM3_COMMANDS                                                  \
    NEO_6M_COMMANDS                                                 \
    UBLOX_COMMANDS                                                  \
    ZED_F9P_COMMANDS                                                \
    SHELL_CMD("gnss_generate_lo", "glo", gnss_generate_lo_command, "GnssGenerateLocalOscilator"),   \
    SHELL_CMD("gnss_data", "gnss", gnss_data_command, "GnssData"),   \
    SHELL_CMD("gnss_carr_pahse_err", "cpe", gnss_carr_pahse_err_command, "GnssCarrPhaseErr"),   \
    SHELL_CMD("gnss_set", "gnss_set_loc", gnss_set_location_command, "GnssSelLocation"), \
    SHELL_CMD("gnss_doppler", "gd", gnss_doppler_command, "GnssDopplerCalc"),


#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /*GNSS_COMMANDS_H*/
