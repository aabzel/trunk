#ifndef GPS_1BIT_COMMANDS_H
#define GPS_1BIT_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

bool gps_unpack_u16_command(int32_t argc, char* argv[]);
bool gps_1bit_seek_prn_phase_command(int32_t argc, char* argv[]);
bool gps_1bit_stream_to_i8_command(int32_t argc, char* argv[]);
bool gps_1bit_lo_command(int32_t argc, char* argv[]);

#define GPS_1BIT_COMMANDS                                                          \
    SHELL_CMD("gps_unpack_u16", "gup", gps_unpack_u16_command, "Gps1BitUnPackU16"), \
    SHELL_CMD("gps_1bit_lo", "g1lo", gps_1bit_lo_command, "Gps1BitLocalOscillator"), \
    SHELL_CMD("gps_1bit_stream_to_i8", "g1t8", gps_1bit_stream_to_i8_command, "Gps1BitStreamToI8"),        \
    SHELL_CMD("gps_1bit_seek_prn_phase", "g1sp", gps_1bit_seek_prn_phase_command, "Gps1BitSeekPrnPhaseAtDoppler"),





#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /*GPS_1BIT_COMMANDS_H*/
