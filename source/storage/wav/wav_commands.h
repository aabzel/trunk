#ifndef WAV_COMMANDS_H
#define WAV_COMMANDS_H

#include "std_includes.h"

#ifdef __cplusplus
extern "C" {
#endif

bool wav_diag_command(int32_t argc, char* argv[]);
bool wav_info_command(int32_t argc, char* argv[]);
bool wav_info_sample_command(int32_t argc, char* argv[]);
bool wav_proc_fir_sample_command(int32_t argc, char* argv[]);
bool wav_proc_iir_sample_command(int32_t argc, char* argv[]);
bool wav_generate_from_dds_command(int32_t argc, char* argv[]);
bool wav_generate_2_channel_command(int32_t argc, char* argv[]);
bool wav_load_command(int32_t argc, char* argv[]);

#define WAV_COMMANDS                                                                                     \
    SHELL_CMD("wav_gen1ch_from_dds", "wg1ch", wav_generate_from_dds_command,  "WavGenerate1Channel"),    \
    SHELL_CMD("wav_gen2ch_from_dds", "wg2ch", wav_generate_2_channel_command, "WavGenerate2Channel"),    \
    SHELL_CMD("wav_proc_fir_sample", "wpfs", wav_proc_fir_sample_command, "WavProcFirSample"),           \
    SHELL_CMD("wav_proc_iir_sample", "wpis", wav_proc_iir_sample_command, "WavProcIirSample"),           \
    SHELL_CMD("wav_load", "wld", wav_load_command, "WavLoad"),                                           \
    SHELL_CMD("wavis", "wav_info_sample", wav_info_sample_command, "WavInfoSample"),                                \
    SHELL_CMD("wavi", "wav_info", wav_info_command, "WavInfo"),                                               \
    SHELL_CMD("wavd", "wav_diag", wav_diag_command, "WavDiag"),

#ifdef __cplusplus
}
#endif

#endif /* WAV_COMMANDS_H */
