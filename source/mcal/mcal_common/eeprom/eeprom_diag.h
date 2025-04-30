#ifndef EEPROM_MCAL_DIAG_H
#define EEPROM_MCAL_DIAG_H


#include "std_includes.h"
#include "eeprom_types.h"

#ifdef HAS_EEPROM_CUSTOM
#include "eeprom_custom_diag.h"
#endif

#ifndef HAS_EEPROM
#error "+HAS_EEPROM"
#endif

#ifndef HAS_EEPROM_DIAG
#error "+HAS_EEPROM_DIAG"
#endif

const char* EepromFsmOperationToStr(const EepromOperation_t operation);
const char* EepromFsmStateToStr(const EepromState_t state);
const char* EepromNodeToStr(const EepromHandle_t* const Node);
const char* EepromFsmInputToStr(const EepromInput_t input);
const char* EepromConfigToStr(const EepromConfig_t* const Config);
bool eeprom_region_print(uint32_t addr, uint32_t byte_size);
bool eeprom_diag_usage(uint32_t chank_size);
bool EepromDiagNode(const EepromHandle_t* const Node);
bool eeprom_scan_diag(uint32_t mem_start, uint32_t mem_size);

#endif /* EEPROM_MCAL_DIAG_H  */
