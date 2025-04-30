#ifndef EEPROM_MCAL_GENERAL_TYPES_H
#define EEPROM_MCAL_GENERAL_TYPES_H


#include "std_includes.h"
#include "eeprom_const.h"

#ifdef HAS_EEPROM_CUSTOM
#include "eeprom_custom_types.h"
#else
#define EEPROM_CUSTOM_TYPES
#endif



#define EEPROM_COMMON_VARIABLES         \
    uint32_t start;                     \
    uint32_t size;                      \
    bool interrupt_on;

typedef struct {
    EEPROM_COMMON_VARIABLES
} EepromConfig_t;


#define EEPROM_FSM_VARIABLES       \
    EepromOperation_t operation;   \
    EepromInput_t input;           \
    EepromState_t state;           \
    uint32_t end;                  \
    uint32_t wr_eeprom_addr;       \
    uint32_t start_ms;             \
    uint32_t diff_ms;              \
    uint32_t spin_cnt;             \
    uint8_t wr_byte;               \
    uint16_t wr_word;              \
    uint32_t wr_qword;             \
    bool loop;

typedef struct {
    EEPROM_FSM_VARIABLES
    EEPROM_COMMON_VARIABLES
    EEPROM_CUSTOM_TYPES
    bool init;
} EepromHandle_t;


#endif /* EEPROM_MCAL_GENERAL_TYPES_H */
