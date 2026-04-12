//**************************************************************************************************
// @Module  MODULE
//! \file   module.h
//! \brief  Interface of the MODULE module.
//!             [text]
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | XX.XX.XXXX |  1.1.0  |   XXX   | Last  release.
//! | XX.XX.XXXX |  1.0.0  |   XXX   | First release.
//**************************************************************************************************

#ifndef NVRAM_FILE_IDENTIFICATIONS_H
#define NVRAM_FILE_IDENTIFICATIONS_H

//**************************************************************************************************
// Project Includes
//**************************************************************************************************

#ifdef HAS_ACCEL
#include "accelerometer_nvram.h"
#else
#define NVRAM_IDS_ACCELEROMETER
#endif


#ifdef HAS_BOARD
#include "board_nvram.h"
#else
#define NVRAM_IDS_BOARD
#endif

#ifdef HAS_BOOT
#include "boot_nvram.h"
#else /*HAS_BOOT*/
#define NVRAM_IDS_BOOT
#endif /*HAS_BOOT*/

#ifdef HAS_BOOTLOADER
#include "bootloader_nvram.h"
#else /*HAS_BOOTLOADER*/
#define NVRAM_IDS_BOOTLOADER
#endif /*HAS_BOOTLOADER*/

#include "nvram_params.h"

#ifdef HAS_TIME
#include "time_nvram.h"
#else
#define NVRAM_IDS_TIME
#endif

#ifdef HAS_WATCHDOG
#include "watchdog_nvram.h"
#else /*HAS_WATCHDOG*/
#define NVRAM_IDS_WATCHDOG
#endif /*HAS_WATCHDOG*/

//**************************************************************************************************
// Declarations of global (public) data types
//**************************************************************************************************

//**************************************************************************************************
// Definitions of global (public) constants
//**************************************************************************************************

/*Do not change existing values.*/
typedef enum  {
    NVRAM_IDS_ACCELEROMETER
    NVRAM_IDS_BOOT
    NVRAM_IDS_BOARD
    NVRAM_IDS_BOOTLOADER
    NVRAM_IDS_WATCHDOG
    NVRAM_IDS_TEST
    NVRAM_IDS_TIME

    NVRAM_ID_TEST_START = 100,
    NVRAM_ID_TEST_END = 0x1FFF,
    NVRAM_ID_UNDEF = 0x2FFF,

    NVRAM_ID_CNT
} NVRAM_DATA_ID;


//**************************************************************************************************
// Declarations of global (public) variables
//**************************************************************************************************


//**************************************************************************************************
// Declarations of global (public) functions
//**************************************************************************************************


#endif // #ifndef NVRAM_FILE_IDENTIFICATIONS_H

//****************************************** end of file *******************************************

