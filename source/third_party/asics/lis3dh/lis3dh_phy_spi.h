//**************************************************************************************************
// @Module  LIS3DH
//! \file   lis3dh_phy_spi.h
//! \brief  Interface of the LIS3DH module.
//!             API for LIS3DH SPI PHY
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 18.11.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************

#ifndef LIS3DH_PHY_SPI_H
#define LIS3DH_PHY_SPI_H


//**************************************************************************************************
// Project Includes
//**************************************************************************************************

// Get generic definitions
#include "platform.h"

// lis3dh types
#include "lis3dh_type.h"


//**************************************************************************************************
// Declarations of global (public) data types
//**************************************************************************************************

//! LIS3DH SPI header
typedef union {
    U8 byte;
    struct {
        //! bits 5:0   address AD(5:0). This is the address field of the indexed register
        U8 registerAddress : 6;
        //! bit 6  When 0, the address remains unchanged in multiple read/write commands
        //!        When 1, the address is auto incremented in multiple read/write commands
        U8 ms : 1;
        //! bit 7   When 0, the data DI(7:0) is written into the device
        //!         When 1, the data DO(7:0) from the device is read.
        U8 rw : 1;
    };
}LIS3DH_SPI_HEADER;

//**************************************************************************************************
// Definitions of global (public) constants
//**************************************************************************************************

//! LIS3DH SPI move multiple bit field
typedef enum {
    // When 0, the address remains unchanged in multiple read/write commands
    LIS3DH_SPI_MS_ADDR_STATIC = 0 ,
    // When 1, the address is auto incremented in multiple read/write commands
    LIS3DH_SPI_MS_ADDR_AUTO_INC = 1,
    //! undefined value
    LIS3DH_SPI_MS_UNDEF = 2,
} LIS3DH_SPI_MOVE_MULTIPLE;

//! LIS3DH_SPI direction bit field
typedef enum {
    // When 0, the data DI(7:0) is written into the device
    LIS3DH_SPI_DIR_WRITE = 0,
    // When 1, the data DO(7:0) from the device is read
    LIS3DH_SPI_DIR_READ  = 1,
    //! undefined value
    LIS3DH_SPI_DIR_UNDEF = 2,
} LIS3DH_SPI_DIRECTION;

//**************************************************************************************************
// Declarations of global (public) variables
//**************************************************************************************************



//**************************************************************************************************
// Declarations of global (public) functions
//**************************************************************************************************

//! \brief LIS3DH read register by SPI
extern STD_RESULT LIS3DH_SPI_RegReadLowLevel(LIS3DH_HANDLE* const Node,
                                             const LIS3DH_REGISTER_ADDR regAddr,
                                             U8* const rxbyte);

//! \brief read from LIS3DH a continuous piece of memory by SPI
extern STD_RESULT LIS3DH_SPI_ReadMemoryLowLevel(LIS3DH_HANDLE* const Node,
                                                const LIS3DH_REGISTER_ADDR regAddr,
                                                U8 *const data,
                                                const U32 size);

//! \brief LIS3DH write register by SPI
extern STD_RESULT LIS3DH_SPI_RegWriteLowLevel(LIS3DH_HANDLE* const Node,
                                              const LIS3DH_REGISTER_ADDR regAddr,
                                              const U8 byte);

#endif // #ifndef LIS3DH_PHY_SPI_H

//****************************************** end of file *******************************************
