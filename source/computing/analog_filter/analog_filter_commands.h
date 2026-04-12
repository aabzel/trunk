#ifndef ANALOG_FILTER_COMMANDS_H
#define ANALOG_FILTER_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_CLI
#define "+HAS_CLI"
#endif

#ifndef HAS_DIAG
#define "+HAS_DIAG"
#endif

bool filter_colpitts_oscillator_command(int32_t argc, char* argv[]);
bool filter_lc_calc_resonant_frequency_hz_command(int32_t argc, char* argv[]);
bool analog_filter_rc_f_cut_calc_command(int32_t argc, char* argv[]);
bool analog_filter_lc_freq_calc_command(int32_t argc, char* argv[]);
bool analog_filter_cap_calc_command(int32_t argc, char* argv[]);
bool analog_filter_lc_calc_command(int32_t argc, char* argv[]);
bool analog_capasity_serial_connection_calc_command(int32_t argc, char* argv[]);

#define ANALOG_FILTER_COMMANDS                                                                       \
    SHELL_CMD("filter_colpitts_oscillator", "co", filter_colpitts_oscillator_command, "ColpittsOscillatorCalc"),   \
    SHELL_CMD("lc_calc_resonant_freq", "lcf0c", filter_lc_calc_resonant_frequency_hz_command, "AnalogFilterLcFreqCalcResonance"),   \
    SHELL_CMD("ana_serial_cap_con_calc", "sccc", analog_capasity_serial_connection_calc_command, "AnalogFilterSerialCapasityConnectionCalc"),   \
    SHELL_CMD("ana_filt_cap_calc", "cc", analog_filter_cap_calc_command, "AnalogFilterCapCalc"),   \
    SHELL_CMD("ana_filt_rc_calc", "rc", analog_filter_rc_f_cut_calc_command, "AnalogFilterRcFcutCalc"),   \
    SHELL_CMD("ana_filt_lc_calc", "lcap", analog_filter_lc_calc_command, "AnalogFilterLcCalc"),

#ifdef __cplusplus
}
#endif

#endif /* ANALOG_FILTER_COMMANDS_H  */
