#ifndef FDA801_DIAG_H
#define FDA801_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "fda801_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /*HAS_LOG*/

#ifndef HAS_FDA801
#error "+HAS_FDA801"
#endif /*HAS_FDA801*/

#ifndef HAS_FDA801_DIAG
#error "+HAS_FDA801_DIAG"
#endif /*HAS_DIAG_FDA801*/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /*HAS_DIAG*/

const char* ChPwmToStr(uint8_t code);
char* ChannelToStr(Fda801ChannelNum_t code);
const char* AcDiagWarnToStr(uint8_t code);
const char* AcDiagTweetToStr(uint8_t code);
const char* AcDiagDataValidToStr(uint8_t code);
const char* DcDiagDataValidToStr(uint8_t code);
const char* ChanDiagToStr(uint8_t code);
const char* AcOperationToStr(uint8_t code);
const char* DcOperationToStr(uint8_t code);
const char* ShortLoadToStr(uint8_t code);
const char* OverCurrentToStr(uint8_t code);
const char* ShortGndToStr(uint8_t code);
const char* ShortVccToStr(uint8_t code);
const char* LoadOpenToStr(uint8_t code);
const char* fda801_get_reg_name(uint8_t addr);
const char* FirstSetUpToStr(uint8_t code);
const char* AcDigSigLvlToStr(uint8_t code);
const char* OperationToStr(uint8_t code);
const char* IprotToStr(uint8_t code);
const char* GainSelToStr(uint8_t code);
const char* PlayMuteToStr(uint8_t code);
const char* ChannelFaultToStr(uint8_t code);
const char* LcFiltSetupToStr(uint8_t code);
const char* OpenLoadToStr(uint8_t code);
const char* DigitalInSetToStr(uint8_t digital_format);
const char* ChannelStateToStr(uint8_t code);
uint32_t DigitalFrameSyncToStr(uint8_t code);
uint32_t SwFreq44kHzToStr(uint8_t code);
uint32_t SwFreq48kHzToStr(uint8_t code);
uint32_t SwFreq96kHzToStr(uint8_t code);
uint32_t SwFreq192kHzToStr(uint8_t code);
uint8_t MuteTimeSetup2Ms(uint8_t code);

bool fda801_parse_if(uint8_t reg_val, char *keyWord1);
bool fda801_parse_cr1(uint8_t reg_val, char *keyWord1);
bool fda801_parse_cr2(uint8_t reg_val, char *keyWord1);
bool fda801_parse_diag(uint8_t reg_val, char *keyWord1);
bool fda801_parse_diagsel(uint8_t reg_val, char *keyWord1);
bool fda801_parse_if(uint8_t reg_val, char *keyWord1);

bool fda801_parse_ch1_ctrl(uint8_t reg_val, char *keyWord1);
bool fda801_parse_ch2_ctrl(uint8_t reg_val, char *keyWord1);
bool fda801_parse_ch3_ctrl(uint8_t reg_val, char *keyWord1);
bool fda801_parse_ch4_ctrl(uint8_t reg_val, char *keyWord1);

bool fda801_parse_ch1_diag_phase_sel_ctrl(uint8_t reg_val, char *keyWord1);
bool fda801_parse_ch2_diag_phase_sel_ctrl(uint8_t reg_val, char *keyWord1);
bool fda801_parse_ch3_diag_phase_sel_ctrl(uint8_t reg_val, char *keyWord1);
bool fda801_parse_ch4_diag_phase_sel_ctrl(uint8_t reg_val, char *keyWord1);

bool fda801_parse_ch1_dc_out(uint8_t reg_val, char *keyWord1);
bool fda801_parse_ch2_dc_out(uint8_t reg_val, char *keyWord1);
bool fda801_parse_ch3_dc_out(uint8_t reg_val, char *keyWord1);
bool fda801_parse_ch4_dc_out(uint8_t reg_val, char *keyWord1);

bool fda801_parse_sensor(uint8_t reg_val, char *keyWord1);
bool fda801_parse_lc_filt_set(uint8_t reg_val, char *keyWord1);
bool fda801_parse_termal(uint8_t reg_val, char *keyWord1);
bool fda801_parse_digital2(uint8_t reg_val, char *keyWord1);
bool fda801_parse_ch1ch2_ac_diag(uint8_t reg_val, char *keyWord1);
bool fda801_parse_ch3ch4_ac_diag(uint8_t reg_val, char *keyWord1);

#endif /* FDA801_DIAG_H  */
