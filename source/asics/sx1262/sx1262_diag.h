#ifndef SX1262_DIAG_H
#define SX1262_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifdef HAS_LORA
#include "lora_constants.h"
#endif
#include "sx1262_drv.h"

const char* RxGainToStr(uint8_t rx_gain);
const char* StandbyToStr(StandbyMode_t standby_mode);
char* OpCodeToStr(uint8_t op_code);
char* dbm2wattsStr(int32_t dbm);
char* LinkDist2str(double bit_s);
char* PayloadLenToStr(uint8_t size);
const char* IqSetUpToStr(uint8_t iq_setup);
char* SyncWordToStr(uint64_t syn_word);
char* PreambleLenToStr(uint16_t pre_len);
const char* WireLessIfToStr(uint8_t packet_type);
const char* LoraHeaderTypeToStr(uint8_t header_type);
const char* LoraCrcTypeToStr(uint8_t crc_type);
bool parse_dev_stat(uint8_t dev_stat);
bool parse_irq_stat(Sx1262IRQs_t irq_stat);
const char* LowDataRateOptToStr(uint8_t packet_type);
bool parse_op_error(uint16_t op_error);
bool print_int_diag(Sx1262IrqCnt_t* irq_cnt);
bool printf_pack_stat(PaketStat_t* pack_stat, char* name);
#ifdef HAS_LORA
uint32_t spreading_factor2num(SpreadingFactor_t spreading_factor);
const char* coding_rate2str(uint8_t coding_rate);
const char* spreading_factor2str(uint8_t spreading_factor);
#endif
char* bandwidth2str(uint8_t bandwidth);
const char* chip_mode2str(uint8_t chip_mode);
const char* cmd_stat2str(uint8_t cmd_stat);

#ifdef __cplusplus
}
#endif

#endif /* SX1262_DIAG_H */
