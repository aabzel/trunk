#ifndef SONAR_COMMANDS_H
#define SONAR_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

bool cmd_sonar_diag(int32_t argc, char* argv[]);
bool sonar_v_sound_command(int32_t argc, char* argv[]);
bool cmd_sonar_zonding_signal(int32_t argc, char* argv[]);
bool cmd_sonar_correlation(int32_t argc, char* argv[]);
bool sonar_config_command(int32_t argc, char* argv[]);
bool sonar_dft_convolution_command(int32_t argc, char* argv[]);
bool sonar_chirp_to_wav_command(int32_t argc, char* argv[]);
bool sonar_chirp_correlation_command(int32_t argc, char* argv[]);
bool sonar_plot_convolution_command(int32_t argc, char* argv[]);
bool sonar_proc_record_command(int32_t argc, char* argv[]);
bool sonar_config_correlator_m_seq_command(int32_t argc, char* argv[]);
bool sonar_config_correlator_mono_command(int32_t argc, char* argv[]);
bool sonar_chirp_calculator_command(int32_t argc, char* argv[]);

#ifdef HAS_BARKER_CODE
bool sonar_config_correlator_barker_command(int32_t argc, char* argv[]);
bool sonar_calc_corr_barker_rec_command(int32_t argc, char* argv[]);

#define SONAR_BARKER_COMMANDS                                                    \
    SHELL_CMD("sonar_config_correlator_barker", "scb13", sonar_config_correlator_barker_command, "SonarConfigBarkerCmd"),                                \
    SHELL_CMD("sonar_calc_corr_barker_rec", "sccb13r", sonar_calc_corr_barker_rec_command, "SonarCalcCorrBarkerRecord"),

#else
#define SONAR_BARKER_COMMANDS
#endif

#define SONAR_BASE_COMMANDS     SONAR_BARKER_COMMANDS                                                                              \
    SHELL_CMD("sonar_chirp_calculator", "schcal", sonar_chirp_calculator_command, "SonarChirpCalculator"),    \
    SHELL_CMD("sonar_config_correlator_mono", "scmono", sonar_config_correlator_mono_command, "SonarConfigMono"),                                \
    SHELL_CMD("sonar_config_correlator_msec", "scmseq", sonar_config_correlator_m_seq_command, "SonarConfigMsequ"),                                \
    SHELL_CMD("sonar_proc_rec", "sccrec", sonar_proc_record_command, "SonarProcRecord"),                      \
    SHELL_CMD("sonar_v_sound", "svs", sonar_v_sound_command, "SonarVsound"),                                  \
    SHELL_CMD("sonar_zonding", "sozo", cmd_sonar_zonding_signal, "SonarZondingSignal"),                       \
    SHELL_CMD("sonar_correlation", "soco", cmd_sonar_correlation, "SonarCorrelation"),                        \
    SHELL_CMD("sonar_diag", "sd", cmd_sonar_diag, "SonarDiag"),                                               \
    SHELL_CMD("sonar_config", "scfg", sonar_config_command, "SonarConfigCmd"),                                \
    SHELL_CMD("sonar_chirp_to_wav", "scw", sonar_chirp_to_wav_command, "SonarChirpToWav"),                    \
    SHELL_CMD("sonar_plot_convolution", "spc", sonar_plot_convolution_command, "SonarPlotConvolution"),       \
    SHELL_CMD("sonar_dft_convolution", "sdftco", sonar_dft_convolution_command, "SonarConvolution"),                      \
    SHELL_CMD("sonar_calc_correlation", "scc", sonar_chirp_correlation_command, "SonarChirpCorrelation"),

#define SONAR_COMMANDS                                                                         \
    SONAR_BASE_COMMANDS

#ifdef __cplusplus
}
#endif

#endif /* SONAR_COMMANDS_H */
