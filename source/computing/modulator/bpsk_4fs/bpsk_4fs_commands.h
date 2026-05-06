#ifndef BPSK_4FS_COMMANDS_H
#define BPSK_4FS_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif


#include "std_includes.h"

#ifdef HAS_WAV
bool bpsk_4fs_encode_to_wav_command(int32_t argc, char* argv[]);
bool bpsk_4fs_decode_wav_command(int32_t argc, char* argv[]);

#define BPSK_4FS_WAW_COMMANDS                                                                              \
    SHELL_CMD("bpsk_4fs_encode_to_wav", "bpsk_4fsew", bpsk_4fs_encode_to_wav_command, "Bpsk4fsEncodeToWav"),      \
    SHELL_CMD("bpsk_4fs_decode_wav", "bpsk_4fsdw", bpsk_4fs_decode_wav_command, "Bpsk4fsDecodeWav"),              \

#else
#define BPSK_4FS_WAW_COMMANDS
#endif

bool bpsk_4fs_diag_command(int32_t argc, char* argv[]);
bool bpsk_4fs_rx_bit_phase_command(int32_t argc, char* argv[]);

#define BPSK_4FS_COMMANDS                                                                       \
    BPSK_4FS_WAW_COMMANDS                                                                       \
    SHELL_CMD("bpsk_4fs_diag", "bpsk_4fsd", bpsk_4fs_diag_command, "Bpsk4fsDiag"),              \
    SHELL_CMD("bpsk_4fs_rx_bit_phase", "brbp", bpsk_4fs_rx_bit_phase_command, "Bpsk4fsRxBitPhase"),

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /*BPSK_4FS_COMMANDS_H*/
