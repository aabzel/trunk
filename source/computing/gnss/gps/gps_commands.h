#ifndef GPS_COMMANDS_H
#define GPS_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

bool gps_escort_sat_command(int32_t argc, char* argv[]);
bool gps_escort_sat_epl_command(int32_t argc, char* argv[]);
bool gps_prn_autocorrelation_command(int32_t argc, char* argv[]);
bool gps_prn_command(int32_t argc, char* argv[]);
bool gps_prn_convolution_command(int32_t argc, char* argv[]);
bool gps_prn_samples_command(int32_t argc, char* argv[]);
bool gps_proc_samples_command(int32_t argc, char* argv[]);
bool gps_post_proc_command(int32_t argc, char* argv[]);
bool gps_seek_prn_phase_command(int32_t argc, char* argv[]);
bool gps_capture_prn_command(int32_t argc, char* argv[]);

#define GPS_COMMANDS                                                                                       \
    SHELL_CMD("gps_post_proc", "gpp", gps_post_proc_command, "GpsPostProc"),                               \
    SHELL_CMD("gps_proc_samples", "gps", gps_proc_samples_command, "GpsProcSample"),                       \
    SHELL_CMD("gps_prn", "gca", gps_prn_command, "GpsPrnGenerate"),                                        \
    SHELL_CMD("gps_prn_autocorrelation", "gpa", gps_prn_autocorrelation_command, "GpsPrnAutocorrelation"), \
    SHELL_CMD("gps_prn_sa", "gcs", gps_prn_samples_command, "GpsPrnGenerateSamples"),                      \
    SHELL_CMD("gps_escort_sat", "ges", gps_escort_sat_command, "GpsEscortSat"),                            \
    SHELL_CMD("gps_seek_prn_phase", "gsp", gps_seek_prn_phase_command, "GpsSeekPrnPhaseAtDoppler"),        \
    SHELL_CMD("gps_capture_prn", "gcp", gps_capture_prn_command, "GpsCaptureProc"),                        \
    SHELL_CMD("gps_prn_convolution", "gpc", gps_prn_convolution_command, "GpsPrnConvolution"),             \
    SHELL_CMD("gps_escort_sat_epl", "epl", gps_escort_sat_epl_command, "GpsEscortSatEpl"),


#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /*GPS_COMMANDS_H*/
