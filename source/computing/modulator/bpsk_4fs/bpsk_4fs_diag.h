#ifndef BPSK_4FS_DIAG_H
#define BPSK_4FS_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "bpsk_4fs_types.h"

bool Bpsk4fsComposeLogLine(const Bpsk4fsHandle_t* const Node, char* const logLine, uint32_t size);
bool bpsk_4fs_print_samples(Bpsk4fsHandle_t* instance);
bool bpsk_4fs_diag(uint8_t num);

const char* Bpsk4fsNodeToStr(const Bpsk4fsHandle_t* const Node);
const char* Bpsk4fsConfigToStr(const Bpsk4fsConfig_t* const Config);

#ifdef __cplusplus
}
#endif

#endif /* BPSK_4FS_DIAG_H */
