//**************************************************************************************************
// @Module  MODULE
//! \file   module_cfg.h
//! \brief  Configuration of the required functionality of the MODULE module.
//!             [text]
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | XX.XX.XXXX |  1.1.0  |   XXX   | Last  release.
//! | XX.XX.XXXX |  1.0.0  |   XXX   | First release.
//**************************************************************************************************

#ifndef MODULE_CFG_H
#define MODULE_CFG_H



//**************************************************************************************************
// Definitions of global (public) constants
//**************************************************************************************************

//! Enable/disable the development error detection feature of the program module. \n
//! Used only for debug purposes and should be disabled in the final release. \n
//! Valid values: ON / OFF
#define MODULE_DEVELOPMENT_ERROR_DETECTION      (OFF)

//! User can enable/disable the internal diagnostic of the program module. \n
//! Used only for debug purposes and should be disabled in the final release. \n
//! Valid values: ON / OFF
#define MODULE_INTERNAL_DIAGNOSTICS             (OFF)



//! User can enable/disable... \n
//! Valid values: ON / OFF
#define MODULE_PARAMETER_ZERO                   (OFF)

//! User can specify... \n
//! Valid values: [x ; y)
#define MODULE_PARAMETER_ONE                    (0x01U)

//! User can specify... \n
//! Valid values: (a ; b]
#define MODULE_PARAMETER_TWO                    (-2)



#endif // #ifndef MODULE_CFG_H

//****************************************** end of file *******************************************
