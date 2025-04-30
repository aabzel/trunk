#ifndef BPSK_DIAG_H
#define BPSK_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "bpsk_types.h"

bool BpskComposeLogLine(const BpskHandle_t* const Node, char* const logLine, uint32_t size);
const char* BpskNodeToStr(const BpskHandle_t* const Node);
const char* BpskConfigToStr(const BpskConfig_t* const Config);

bool bpsk_print_samples(BpskHandle_t* instance);

#ifdef __cplusplus
}
#endif

#endif /* BPSK_DIAG_H */
