//**************************************************************************************************
// @Module        Software Timer
// @Filename      software_timer_cfg.h
//--------------------------------------------------------------------------------------------------
// @Description   Configuration of the required functionality of the timers.
//--------------------------------------------------------------------------------------------------
// @Version       2.0.0
//--------------------------------------------------------------------------------------------------
// @Date          25.09.2015
//--------------------------------------------------------------------------------------------------
// @History       Version  Author      Comment
// 20.12.2013     1.0.0    SRM         First release.
// 25.09.2015     2.0.0    Savochkin   Second release.
//**************************************************************************************************

#ifndef SOFTWARE_TIMER_CFG_H
#define SOFTWARE_TIMER_CFG_H



//**************************************************************************************************
// Definitions of global (public) constants
//**************************************************************************************************

// Enable/disable the development error detection feature of the program module.
// Used only for debug purposes and should be disabled in the final release.
// Valid values: ON / OFF
#define SOFTTIMER_DEVELOPMENT_ERROR_DETECTION     (ON)



// Specify type of the software timer counter size.
// Valid values: U8 / U16 / U32
#define SOFTTIMER_SZ            U16

// Specify a number of supported software timers.
// Valid values: [1 ; 32]
#define SOFTTIMER_QTY           (10U)

// Specify timer tick period in nanoseconds. This parameter will be returned
// in SOFTTIMER_GetTickPeriod() function.
#define SOFTTIMER_TICK_PERIOD   (1000000U)



#endif // #ifndef SOFTWARE_TIMER_CFG_H

//****************************************** end of file *******************************************
