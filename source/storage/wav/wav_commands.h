#ifndef WAV_COMMANDS_H
#define WAV_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

bool wav_shift_right2_command(int32_t argc, char* argv[]) ;
bool wav_sample_frequency_command(int32_t argc, char* argv[]);
bool wav_diag_command(int32_t argc, char* argv[]);
bool wav_info_command(int32_t argc, char* argv[]);
bool wav_info_sample_command(int32_t argc, char* argv[]);
bool wav_proc_fir_sample_command(int32_t argc, char* argv[]);
bool wav_proc_iir_sample_command(int32_t argc, char* argv[]);
bool wav_generate_from_dds_command(int32_t argc, char* argv[]);
bool wav_generate_2_channel_command(int32_t argc, char* argv[]);
bool wav_duration_command(int32_t argc, char* argv[]);
bool wav_shift_right_command(int32_t argc, char* argv[]);
bool wav_load_command(int32_t argc, char* argv[]);
bool wav_generate_signal_command(int32_t argc, char* argv[]) ;

#define WAV_COMMANDS                                                                                     \
    SHELL_CMD("wav_generate_signal", "wgs", wav_generate_signal_command, "WavGenerateSignal"),           \
    SHELL_CMD("wav_shift_right", "wsr", wav_shift_right_command, "WavShiftRight"),                       \
    SHELL_CMD("wav_shift_right2", "wsr2", wav_shift_right2_command, "WavShiftRight2"),                   \
    SHELL_CMD("wav_gen_from_dds", "wgdds", wav_generate_from_dds_command,  "WavGenerate1Channel"),    \
    SHELL_CMD("wav_gen2ch_from_dds", "wg2ch", wav_generate_2_channel_command, "WavGenerate2Channel"),    \
    SHELL_CMD("wad", "wav_duration", wav_duration_command, "WavDuration"),                               \
    SHELL_CMD("wavsf", "wav_sample_freq", wav_sample_frequency_command, "WavSampleFreq"),                \
    SHELL_CMD("wav_proc_fir_sample", "wpfs", wav_proc_fir_sample_command, "WavProcFirSample"),           \
    SHELL_CMD("wav_proc_iir_sample", "wpis", wav_proc_iir_sample_command, "WavProcIirSample"),           \
    SHELL_CMD("wav_load", "wld", wav_load_command, "WavLoad"),                                           \
    SHELL_CMD("wavis", "wav_info_sample", wav_info_sample_command, "WavInfoSample"),                     \
    SHELL_CMD("wavi", "wav_info", wav_info_command, "WavInfo"),                                          \
    SHELL_CMD("wavd", "wav_diag", wav_diag_command, "WavDiag"),

#ifdef __cplusplus
}
#endif

#endif /* WAV_COMMANDS_H */
