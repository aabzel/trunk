//**************************************************************************************************
// @Module  MODULE
//! \file   module.c
//! \par    Platform
//!             PLATFORM_NAME
//! \par    Compatible
//!             COMPATIBLE_PROCESSOR_MODULE
//! \brief  Implementation of the MODULE functionality.
//!             [text]
//! \par    Abbreviations
//!             ABBR0 -
//!             ABBR1 -
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | XX.XX.XXXX |  1.1.0  |   XXX   | Last  release.
//! | XX.XX.XXXX |  1.0.0  |   XXX   | First release.
//**************************************************************************************************



//**************************************************************************************************
//! \defgroup   MODULE Name of Module
//! \brief      Short description of Module
//! \addtogroup MODULE
//! @{
//! \file module.c
//! \file module.h
//! \file module_cfg.h
//! @}
//**************************************************************************************************



//**************************************************************************************************
// Project Includes
//**************************************************************************************************

#include "nvram_configuration.h"

#include <inttypes.h>
#include <stdio.h>
#include <string.h>


#include "boot_driver.h"
#include "common_diag.h"
#include "general_macros.h"


//#include "nvram_diagnostic.h"
#include "nvram_types.h"


#ifdef HAS_BOOT
#include "boot_nvram.h"
#else
#define NVRAM_BOOT
#endif /*HAS_BOOT*/

#ifdef HAS_ACCEL
#include "accelerometer_nvram.h"
#else
#define NVRAM_ACCELEROMETER
#endif


#ifdef HAS_GNSS
#include "gnss_nvram.h"
#else
#define NVRAM_GNSS
#endif

#ifdef HAS_BOOTLOADER
#include "bootloader_nvram.h"
#else
#define NVRAM_BOOTLOADER
#endif


#ifdef HAS_TIME
#include "time_nvram.h"
#else
#define NVRAM_TIME
#endif

#ifdef HAS_BOARD_CUSTOM
#include "board_nvram.h"
#else
#define BOARD_NVRAMS
#endif

#ifdef HAS_WATCHDOG
#include "watchdog_nvram.h"
#else
#define NVRAM_WATCHDOG
#endif


#include "nvram_params.h"

//**************************************************************************************************
// Verification of the imported configuration parameters
//**************************************************************************************************

//**************************************************************************************************
// Definitions of global (public) variables
//**************************************************************************************************




//**************************************************************************************************
// Declarations of local (private) data types
//**************************************************************************************************

//**************************************************************************************************
// Definitions of local (private) constants
//**************************************************************************************************

#define RARAM_ARRAY_ALL            \
    NVRAM_ACCELEROMETER            \
    NVRAM_BOOT                     \
    NVRAM_BOARD                    \
    NVRAM_TEST                     \
    NVRAM_TIME                     \
    NVRAM_WATCHDOG

/*TODO: Sort by index for bin search in future*/
const NVRAM_INFO NvramArray[] = {RARAM_ARRAY_ALL};

//**************************************************************************************************
// Definitions of static global (private) variables
//**************************************************************************************************

//**************************************************************************************************
// Declarations of local (private) functions
//**************************************************************************************************

//**************************************************************************************************
//==================================================================================================
// Definitions of global (public) functions
//==================================================================================================
//**************************************************************************************************

//**************************************************************************************************
//! [Description of MODULE_FunctionZero]
//!
//! \note       [text]
//!
//! \param[in]  parameterZero - [description of parameterZero]
//!
//! \return     [Description of return value]
//**************************************************************************************************
U32 NVRAM_GetCnt(void) {
    U32 cnt = SIZE_OF_ARRAY(NvramArray);
    return cnt;
}


//**************************************************************************************************
//==================================================================================================
// Definitions of local (private) functions
//==================================================================================================
//**************************************************************************************************

//****************************************** end of file *******************************************

