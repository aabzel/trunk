//**************************************************************************************************
// @Module  EEPROM Emulation
//! \file   eeprom_emulation_ext.h
//! \brief  Interface of the EEPROM Emulation module.
//!
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 28.12.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************

#ifndef EEPROM_EMULATION_EXT_H
#define EEPROM_EMULATION_EXT_H



//**************************************************************************************************
// Project Includes
//**************************************************************************************************

#include "platform.h"

#include "general_types.h"

#include "eeprom_emulation_cfg.h"

//**************************************************************************************************
// Declarations of global (public) data types
//**************************************************************************************************

// None.
typedef union{
    U32 virtAddr;
    struct{
        U16 offset;
        U8 serialNumber; // 0 1 2 3
        U8 res;
    };
}EMEEP_VIRT_ADDR_TYPE;


//**************************************************************************************************
// Definitions of global (public) constants
//**************************************************************************************************

#define EMEEP_BANK_0_SIZE  (EMEEP_BANK_0_END_ADDRESS-EMEEP_BANK_0_START_ADDRESS)
#define EMEEP_BANK_1_SIZE  (EMEEP_BANK_1_END_ADDRESS-EMEEP_BANK_1_START_ADDRESS)
#define EMEEP_BANK_2_SIZE  (EMEEP_BANK_2_END_ADDRESS-EMEEP_BANK_2_START_ADDRESS)
#define EMEEP_BANK_3_SIZE  (EMEEP_BANK_3_END_ADDRESS-EMEEP_BANK_3_START_ADDRESS)


//**************************************************************************************************
// Declarations of global (public) variables
//**************************************************************************************************

// None.



//**************************************************************************************************
// Declarations of global (public) functions
//**************************************************************************************************

extern STD_RESULT EMEEP_Erase(const U32 sourceAddress,
                              const U32 size);


#endif // #ifndef EEPROM_EMULATION_EXT_H

//****************************************** end of file *******************************************
