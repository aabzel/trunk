//**************************************************************************************************
// @Module  ACCEL
//! \file   accelerometer_constants.h
//! \brief  Constants of the ACCEL module.
//!
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 18.11.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************

#ifndef ACCEL_EHAL_CONSTANTS_H
#define ACCEL_EHAL_CONSTANTS_H


//**************************************************************************************************
// Project Includes
//**************************************************************************************************



//**************************************************************************************************
// Declarations of global (public) data types
//**************************************************************************************************



//**************************************************************************************************
// Definitions of global (public) constants
//**************************************************************************************************

//! accelerometer polling period in us
#define ACCEL_POLLING_PERIOD_US 10000

//! ID codes for a known accelerometer physics
typedef enum {
    //! ACCEL PHY ADXL335
    ACCELEROMETER_PHY_ADXL335 = 1,
    //! ACCEL PHY H3LIS331DL
    ACCELEROMETER_PHY_H3LIS331DL = 2,
    //! ACCEL PHY ISM330DLC
    ACCELEROMETER_PHY_ISM330DLC = 3,
    //! ACCEL PHY LIS3DH
    ACCELEROMETER_PHY_LIS3DH = 4,
    //! ACCEL PHY LIS302DL
    ACCELEROMETER_PHY_LIS302DL = 5,
    //! ACCEL PHY LIS2DS12
    ACCELEROMETER_PHY_LIS2DS12 = 6,
    //! ACCEL PHY MMA7660FC
    ACCELEROMETER_PHY_MMA7660FC= 7,
    //! ACCEL PHY MPU6050
    ACCELEROMETER_PHY_MPU6050 = 8,
    //! ACCEL PHY QMA6100P
    ACCELEROMETER_PHY_QMA6100P = 9,
    //! ACCEL PHY UNDEF
    ACCELEROMETER_PHY_UNDEF = 0,
}ACCEL_PHY;

//**************************************************************************************************
// Declarations of global (public) variables
//**************************************************************************************************



//**************************************************************************************************
// Declarations of global (public) functions
//**************************************************************************************************


#endif // #ifndef ACCEL_EHAL_CONSTANTS_H

//****************************************** end of file *******************************************
