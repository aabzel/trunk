//**************************************************************************************************
// @Module  LIS3DH
//! \file   lis3dh_constants.h
//! \brief  Constants for the driver
//!
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 18.11.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************

#ifndef LIS3DH_CONSTANTS_H
#define LIS3DH_CONSTANTS_H



//**************************************************************************************************
// Project Includes
//**************************************************************************************************

// Get data types
#include "lis3dh_dependencies.h"

//**************************************************************************************************
// Declarations of global (public) data types
//**************************************************************************************************



//**************************************************************************************************
// Definitions of global (public) constants
//**************************************************************************************************

//! LIS3DH I2C Base address 1
#define LIS3DH_I2C_ADDR_1 0x19

//! LIS3DH I2C Base address 0
#define LIS3DH_I2C_ADDR_0 0x18

//! Number of registers
#define LIS3DH_REGISTER_CNT 42

//! LIS3DH ID value
#define LIS3DH_ID_VALUE 0x33

//! LIS3DH ADC resolution bit
#define LIS3DH_ADC_RESOLUTION_BIT 8

//! LIS3DH accelerometer data field size
#define LIS3DH_ACCEL_DATA_SIZE_BIT 16

//! LIS3DH precision in g. This value is taken from the datasheet 40mg.
#define LIS3DH_PRECISION_G 0.04

//! Data reading period
#define LIS3DH_POLLING_PERIOD_US (5000U)

//! Communication check polling period
#define LIS3DH_LINK_POLLING_PERIOD_US (5000000U)

//! Addresses of available registers
typedef enum {
    //! STATUS_REG_AUX
    LIS3DH_REGISTER_STATUS_REG_AUX = 0x07,
    //! OUT_ADC1_L
    LIS3DH_REGISTER_OUT_ADC1_L = 0x08,
    //! OUT_ADC1_H
    LIS3DH_REGISTER_OUT_ADC1_H = 0x09,
    //! OUT_ADC2_L
    LIS3DH_REGISTER_OUT_ADC2_L = 0x0A,
    //! OUT_ADC2_H
    LIS3DH_REGISTER_OUT_ADC2_H = 0x0B,
    //! OUT_ADC3_L
    LIS3DH_REGISTER_OUT_ADC3_L = 0x0C,
    //! OUT_ADC3_H
    LIS3DH_REGISTER_OUT_ADC3_H = 0x0D,
    //! WHO_AM_I
    LIS3DH_REGISTER_WHO_AM_I = 0x0F,
    //! TEMP_CFG_REG
    LIS3DH_REGISTER_TEMP_CFG_REG = 0x1F,
    //! STATUS_REG
    LIS3DH_REGISTER_STATUS_REG = 0x27,
    //! OUT_X_L
    LIS3DH_REGISTER_OUT_X_L = 0x28,
    //! OUT_X_H
    LIS3DH_REGISTER_OUT_X_H = 0x29,
    //! OUT_Y_L
    LIS3DH_REGISTER_OUT_Y_L = 0x2A,
    //! OUT_Y_H
    LIS3DH_REGISTER_OUT_Y_H = 0x2B,
    //! OUT_Z_L
    LIS3DH_REGISTER_OUT_Z_L = 0x2C,
    //! OUT_Z_H
    LIS3DH_REGISTER_OUT_Z_H = 0x2D,
    //! FIFO_SRC_REG
    LIS3DH_REGISTER_FIFO_SRC_REG = 0x2F,
    //! INT1_SRC
    LIS3DH_REGISTER_INT1_SRC = 0x31,
    //! INT2_SRC
    LIS3DH_REGISTER_INT2_SRC = 0x35,
    //! CLICK_SRC
    LIS3DH_REGISTER_CLICK_SRC = 0x39,
    //! CTRL_REG0
    LIS3DH_REGISTER_CTRL_REG0 = 0x1E,
    //! CTRL_REG1
    LIS3DH_REGISTER_CTRL_REG1 = 0x20,
    //! CTRL_REG2
    LIS3DH_REGISTER_CTRL_REG2 = 0x21,
    //! CTRL_REG3
    LIS3DH_REGISTER_CTRL_REG3 = 0x22,
    //! CTRL_REG4
    LIS3DH_REGISTER_CTRL_REG4 = 0x23,
    //! CTRL_REG5
    LIS3DH_REGISTER_CTRL_REG5 = 0x24,
    //! CTRL_REG6
    LIS3DH_REGISTER_CTRL_REG6 = 0x25,
    //! REFERENCE
    LIS3DH_REGISTER_REFERENCE = 0x26,
    //! xxxxxxx
    LIS3DH_REGISTER_FIFO_CTRL_REG = 0x2E,
    //! INT1_CFG
    LIS3DH_REGISTER_INT1_CFG = 0x30,
    //! INT1_THS
    LIS3DH_REGISTER_INT1_THS = 0x32,
    //! INT1_DURATION
    LIS3DH_REGISTER_INT1_DURATION = 0x33,
    //! INT2_CFG
    LIS3DH_REGISTER_INT2_CFG = 0x34,
    //! INT2_THS
    LIS3DH_REGISTER_INT2_THS = 0x36,
    //! INT2_DURATION
    LIS3DH_REGISTER_INT2_DURATION = 0x37,
    //! CLICK_CFG
    LIS3DH_REGISTER_CLICK_CFG = 0x38,
    //! CLICK_THS
    LIS3DH_REGISTER_CLICK_THS = 0x3A,
    //! TIME_LIMIT
    LIS3DH_REGISTER_TIME_LIMIT = 0x3B,
    //! TIME_LATENCY
    LIS3DH_REGISTER_TIME_LATENCY = 0x3C,
    //! TIME_WINDOW
    LIS3DH_REGISTER_TIME_WINDOW = 0x3D,
    //! ACT_THS
    LIS3DH_REGISTER_ACT_THS = 0x3E,
    //! ACT_DUR
    LIS3DH_REGISTER_ACT_DUR = 0x3F,
    //! REGISTER UNDEF
    LIS3DH_REGISTER_UNDEF = 0xFF,
} LIS3DH_REGISTER_ADDR;

//! Data rate configuration (ODR - Data rate)
typedef enum {
    //! Power-down mode
    LIS3DH_DATA_SPEED_POWER_DOWN = 0,
    //! HR / Normal / Low-power mode (1 Hz)
    LIS3DH_DATA_SPEED_1_HZ = 1,
    //! HR / Normal / Low-power mode (10 Hz)
    LIS3DH_DATA_SPEED_10_HZ = 2,
    //! HR / Normal / Low-power mode (25 Hz)
    LIS3DH_DATA_SPEED_25_HZ = 3,
    //! HR / Normal / Low-power mode (50 Hz)
    LIS3DH_DATA_SPEED_50_HZ = 4,
    //! HR / Normal / Low-power mode (100 Hz)
    LIS3DH_DATA_SPEED_100_HZ = 5,
    //! HR / Normal / Low-power mode (200 Hz)
    LIS3DH_DATA_SPEED_200_HZ = 6,
    //! HR / Normal / Low-power mode (400 Hz)
    LIS3DH_DATA_SPEED_400_HZ = 7,
    //! Low power mode (1.60 kHz)
    LIS3DH_DATA_SPEED_1600_HZ = 8,
    //! HR / normal (1.344 kHz); Low-power mode (5.376 kHz)
    LIS3DH_DATA_SPEED_1344_HZ = 9,
    //! HR / normal (1.344 kHz); Low-power mode (5.376 kHz)
    LIS3DH_DATA_SPEED_5376_HZ = 10,
} LIS3DH_DATA_RATE;

//!  High-pass filter mode configuration
typedef enum {
    //! Normal mode (reset by reading REFERENCE (26h))
    LIS3DH_FILT_HIGH_PASS_NORMAL_REFERENCE = 0,
    //! Reference signal for filtering
    LIS3DH_FILT_HIGH_PASS_REFERENCE = 1,
    //! Normal mode
    LIS3DH_FILT_HIGH_PASS_NORMAL = 2,
    //! Autoreset on interrupt event
    LIS3DH_FILT_HIGH_PASS_AUTORESET = 3,
    //! FILT HIGH PASS UNDEF
    LIS3DH_FILT_HIGH_PASS_UNDEF = 4,
} LIS3DH_HIGH_PASS_FILTER_MODE;

//! Self-test mode configuration
typedef enum {
    //! Normal mode
    LIS3DH_SELFTEST_NORMAL = 0,
    //! Self-test 0
    LIS3DH_SELFTEST_0 = 1,
    //! Self-test 1
    LIS3DH_SELFTEST_1 = 2,
    //! reserved
    LIS3DH_SELFTEST_RESERV = 3,
    //! undef
    LIS3DH_SELFTEST_UNDEF = 4,
} LIS3DH_SELF_TEST;

//! LIS3DH ASIC to MCU Communication interface
typedef enum {
    //! LIS3DH ASIC to MCU Communication interface I2C
    LIS3DH_INTERFACE_I2C = 1 ,
    //! LIS3DH ASIC to MCU Communication interfaceSPI
    LIS3DH_INTERFACE_SPI = 2 ,
    //! undef
    LIS3DH_INTERFACE_UNDEF = 0 ,
} LIS3DH_INTERFACE;

//! Full-scale selection.
typedef enum {
    //! +/-2 g
    LIS3DH_RANGE_2G = 0,
    //! +/-4
    LIS3DH_RANGE_4G = 1,
    //!  +/-8 g
    LIS3DH_RANGE_8G = 2,
    //! +/-16 g
    LIS3DH_RANGE_16G = 3,
    //! undef
    LIS3DH_RANGE_UNDEF = 4,
} LIS3DH_FULL_SCALE;

//! LIS3DH bitness
typedef enum {
    //! 8
    LIS3DH_BITNESS_8 = 8,
    //! 10
    LIS3DH_BITNESS_10 = 10,
    //! 12
    LIS3DH_BITNESS_12 = 12,
    //! undef
    LIS3DH_BITNESS_UNDEF = 0
}LIS3DH_BIT_DEPTH;


//! Operating mode selection
typedef enum {
    //! Normal mode
    LIS3DH_OP_MODE_NORMAL = 0,
    //! High-resolution mode
    LIS3DH_OP_MODE_HIGH_RESOLUTION = 1,
    //! Low-power mode
    LIS3DH_OP_MODE_LOW_POWER = 2,
    //! Not allowed
    LIS3DH_OP_MODE_ERROR = 3,
    //! undef
    LIS3DH_OP_MODE_UNDEF = 4 //
} LIS3DH_OPERATION_MODE;


//! FIFO mode configuration
typedef enum {
    //! Bypass mode
    LIS3DH_FIFOMODE_BYPASS = 0,
    //! FIFO mode
    LIS3DH_FIFOMODE_FIFO = 1,
    //! Stream mode
    LIS3DH_FIFOMODE_STREAM = 2,
    //! Stream-to-FIFO
    LIS3DH_FIFOMODE_STREAM_TO_FIFO = 3,
    //! ubdef
    LIS3DH_FIFOMODE_UNDEF = 4
}LIS3DH_FIFO_MODE;

//! LIS3DH common on off constants
typedef enum {
    //! whatever it is disabled
    LIS3DH_SUBSYS_DISABLED = 0,
    //! whatever it is enabled
    LIS3DH_SUBSYS_ENABLED = 1,
    //! not defined
    LIS3DH_SUBSYS_UNDEF = 2
}LIS3DH_ON_OFF;

//! LIS3DH Temperature on off constants
typedef enum {
    //! 0: T disabled
    LIS3DH_TEMP_DISABLED = 0,
    //! 1: T enabled
    LIS3DH_TEMP_ENABLED = 1,
    //! not defined
    LIS3DH_TEMP_UNDEF = 2
}LIS3DH_TEMP_CTRL;

//! LIS3DH ADC on off constants
typedef enum {
    //! 0: ADC disabled
    LIS3DH_ADC_DISABLED = 0,
    //! 1: ADC enabled
    LIS3DH_ADC_ENABLED = 1,
    //! not defined
    LIS3DH_ADC_UNDEF = 2
}LIS3DH_ADC_CTRL;

//! output data rate ctrl code
typedef enum {
    //! Power-down mode
    LIS3DH_ODR_0HZ = 0,
    //! HR / Normal / Low-power mode (1 Hz)
    LIS3DH_ODR_1HZ = 1,
    //! HR / Normal / Low-power mode (10 Hz)
    LIS3DH_ODR_10HZ = 2,
    //! HR / Normal / Low-power mode (25 Hz)
    LIS3DH_ODR_25HZ = 3,
    //! HR / Normal / Low-power mode (50 Hz)
    LIS3DH_ODR_50HZ = 4,
    //! HR / Normal / Low-power mode (100 Hz)
    LIS3DH_ODR_100HZ = 5,
    //! HR / Normal / Low-power mode (200 Hz)
    LIS3DH_ODR_200HZ = 6,
    //! HR / Normal / Low-power mode (400 Hz)
    LIS3DH_ODR_400HZ = 7,
    //! Low power mode (1.60 kHz)
    LIS3DH_ODR_1600HZ = 8,
    //! HR / normal (1.344 kHz); Low-power mode (5.376 kHz)
    LIS3DH_ODR_5376HZ = 9,
    //! Undef
    LIS3DH_ODR_UNDEF_HZ = 10,
}LIS3DH_ODR;




//**************************************************************************************************
// Declarations of global (public) variables
//**************************************************************************************************

//**************************************************************************************************
// Declarations of global (public) functions
//**************************************************************************************************


#endif // #ifndef LIS3DH_CONSTANTS_H

//****************************************** end of file *******************************************
