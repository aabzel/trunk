#ifndef BPSK_COMMANDS_H
#define BPSK_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif


#include "std_includes.h"

bool bpsk_diag_command(int32_t argc, char* argv[]);
bool bpsk_decode_wav_command(int32_t argc, char* argv[]);
bool bpsk_encode_to_wav_command(int32_t argc, char* argv[]);

#define BPSK_COMMANDS                                                                              \
    SHELL_CMD("bpsk_encode_to_wav", "bpskew", bpsk_encode_to_wav_command, "BpskEncodeToWav"),      \
    SHELL_CMD("bpsk_decode_wav", "bpskdw", bpsk_decode_wav_command, "BpskDecodeWav"),              \
    SHELL_CMD("bpsk_diag", "bpskd", bpsk_diag_command, "BpskDiag"),

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /*BPSK_COMMANDS_H*/
