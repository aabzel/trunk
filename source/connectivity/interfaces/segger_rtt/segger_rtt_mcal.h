#ifndef SEGGER_RTT_MCAL_H
#define SEGGER_RTT_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "segger_rtt_config.h"
#include "segger_rtt_types.h"

#ifdef HAS_SEGGER_RTT_DIAG
#include "segger_rtt_diag.h"
#endif

/* API */
SeggerRttHandle_t* SeggerRttGetNode(uint8_t num);
const SeggerRttConfig_t* SeggerRttGetConfig(uint8_t num);
bool SeggerRttIsValidConfig(const SeggerRttConfig_t* const Config);


bool segger_rtt_mcal_init(void);
bool segger_rtt_init_custom(void);
bool segger_rtt_init_common(const SeggerRttConfig_t* const Config, SeggerRttHandle_t* const Node);
bool segger_rtt_init_node(SeggerRttHandle_t* const Node);
bool segger_rtt_init_one(uint8_t num);

bool segger_rtt_proc_one(uint8_t num);
bool segger_rtt_proc(void);

/*setters*/
bool segger_rtt_writer(const uint8_t num);
bool segger_rtt_write(uint8_t num, char* data);
bool segger_rtt1_writer_transmit(void* base);
void segger_rtt1_putc(void* stream_ptr, char ch);
void segger_rtt1_puts(void* stream_ptr, const char* str, int32_t len);

/*getters*/
bool segger_rtt_raw_reg_diag(uint8_t i) ;

#ifdef __cplusplus
}
#endif

#endif /* SEGGER_RTT_MCAL_H */
