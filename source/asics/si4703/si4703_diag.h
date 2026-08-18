#ifndef SI4703_DIAG_H
#define SI4703_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "si4703_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /**/

#ifndef HAS_SI4703
#error "+HAS_SI4703"
#endif /**/

#ifndef HAS_SI4703_DIAG
#error "+HAS_SI4703_DIAG"
#endif /**/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /**/

extern const Si4703RegInfo_t Si4703RegInfo[SI4703_REG_CNT];

const Si4703RegInfo_t* Si4703GetRegInfo(const Si4703RegAddr_t addr);

uint32_t si4703_reg_cnt(void);

bool si4703_diag(void);
bool si4703_diag_one(uint8_t num);

const char* Si4703ConfigToStr(const Si4703Config_t* const Config);
const char* Si4703NodeToStr(const Si4703Handle_t* const Node);
const char* si4703_get_reg_name(uint8_t addr);
const char* Si4703SeekDirToStr(Si4703SeekDir_t seek_dir);
const char* Si4703SeekModeToStr(Si4703SeekEnd_t seek_end);
const char* Si4703ChipIDToStr(const Si4703RegChipID_t* const Reg);
const char* Si4703DeviceIDToStr(const Si4703RegDeviceID_t * const Value);
const char* Si4703ChipIdToStr(const Si4703RegChipID_t *const Value);
const char* Si4703StatusRssiToStr(const Si4703RegStatusRssi_t* const Value) ;

bool RdsBlockErrorsToStr(uint8_t bler, char block);
bool si4703_parse_chipid(uint16_t reg_val, char *keyWord1);
bool si4703_parse_deviceid(uint16_t reg_val, char *keyWord1);
bool si4703_parse_power_configuration(uint16_t reg_val, char *keyWord1);
bool si4703_parse_channel(uint16_t reg_val, char *keyWord1);
bool si4703_parse_system_configuration_1(uint16_t reg_val, char *keyWord1);
bool si4703_parse_system_configuration_2(uint16_t reg_val, char *keyWord1);
bool si4703_parse_system_configuration_3(uint16_t reg_val, char *keyWord1);
bool si4703_parse_test_1(uint16_t reg_val, char *keyWord1);
bool si4703_parse_test_2(uint16_t reg_val, char *keyWord1);
bool si4703_parse_boot_configuration(uint16_t reg_val, char *keyWord1);
bool si4703_parse_status_rssi(uint16_t reg_val, char *keyWord1);
bool si4703_parse_read_channel(uint16_t reg_val, char *keyWord1);
bool si4703_parse_rdsa(uint16_t reg_val, char *keyWord1);
bool si4703_parse_rdsb(uint16_t reg_val, char *keyWord1);
bool si4703_parse_rdsd(uint16_t reg_val, char *keyWord1);
bool si4703_parse_rdsc(uint16_t reg_val, char *keyWord1);

#ifdef __cplusplus
}
#endif

#endif /* SI4703_DIAG_H  */
