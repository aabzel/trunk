//**************************************************************************************************
// @Module  LIS3DH
//! \file   lis3dh_phy_spi.c
//! \par    Platform
//!             Any platform with ASIC LIS3DH and SPI IF
//! \par    Compatible
//!             Any microcontroller with SPI and GPIO
//! \brief  Implementation of the LIS3DH functionality.
//!             This is a SPI PHY driver for the ASIC LIS3DH
//! \par    Abbreviations
//!             API - Application Programming Interface
//!             IF -  InterFace
//!             PHY - PHYsical layer
//!             SPI - Serial Peripheral Interface
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 18.11.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************



//**************************************************************************************************
//! \defgroup   LIS3DH Name of Module
//! \brief      Short description of Module
//! \addtogroup LIS3DH
//! @{
//! \file lis3dh_phy_spi.c
//! \file lis3dh_phy_spi.h
//! @}
//**************************************************************************************************


//**************************************************************************************************
// Project Includes
//**************************************************************************************************

// lis3dh phy spi
#include "lis3dh_phy_spi.h"

// gpio drv
#include "gpio_drv.h"

// spi drv
#include "spi_drv.h"

// spi custom drv
#include "spi_custom_drv.h"



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



//**************************************************************************************************
// Definitions of static global (private) variables
//**************************************************************************************************



//**************************************************************************************************
// Declarations of local (private) functions
//**************************************************************************************************

//! \brief extract valid byte
static U8 ExtractValidByte(const U8* const rxArray);

//**************************************************************************************************
//==================================================================================================
// Definitions of global (public) functions
//==================================================================================================
//**************************************************************************************************



//**************************************************************************************************
//! LIS3DH read register by SPI
//!
//! \note       None
//!
//! \param[in]  Node - ASIC RAM node
//! \param[in]  regAddr - ASIC internal register address
//! \param[out] byte - register value
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT LIS3DH_SPI_RegReadLowLevel(LIS3DH_HANDLE *const Node,
                                      const LIS3DH_REGISTER_ADDR regAddr,
                                      U8 *const rxbyte)
{
    STD_RESULT ret = RESULT_NOT_OK;
    if (Node)
    {
        ret = GPIO_SetPinState(Node->chipSelectPort, Node->chipSelectPin, LOGIC_0);

        LIS3DH_SPI_HEADER Header = { 0 };
        Header.registerAddress = regAddr;
        Header.rw = LIS3DH_SPI_DIR_READ;
        Header.ms = LIS3DH_SPI_MS_ADDR_STATIC;

        static U8 txArray[2]= {0};
        txArray[0] = Header.byte;
        txArray[1] = 0;
        static U8 rxArray[2] = {0};
        ret = SPI_WriteRead(Node->spiNum, txArray, rxArray, 2);
        if (RESULT_OK == ret)
        {
            if (rxbyte)
            {
                rxbyte[0] = ExtractValidByte(rxArray);
            }
        } // end of if (RESULT_OK == ret)
        ret = GPIO_SetPinState(Node->chipSelectPort, Node->chipSelectPin, LOGIC_1);
    } // end of if (Node)
    return ret;
} // end of LIS3DH_SPI_RegReadLowLevel()

//**************************************************************************************************
//! read from LIS3DH a continuous piece of memory by SPI
//!
//! \note       None
//!
//! \param[in]  Node - ASIC RAM node
//! \param[in]  regAddr - register start address
//! \param[in]  size - number of bytes to read
//! \param[out] data - array to read into
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
extern STD_RESULT LIS3DH_SPI_ReadMemoryLowLevel(LIS3DH_HANDLE* const Node,
                                                const LIS3DH_REGISTER_ADDR regAddr,
                                                U8* const data,
                                                const U32 size)
{
    STD_RESULT ret = RESULT_NOT_OK;
    if (size < 10)
    {
        GPIO_SetPinState(Node->chipSelectPort, Node->chipSelectPin, LOGIC_0);
       // wait_us(500);
        LIS3DH_SPI_HEADER Header = { 0 };
        Header.byte = 0;
        Header.registerAddress = regAddr;
        Header.rw = LIS3DH_SPI_DIR_READ;
        Header.ms = LIS3DH_SPI_MS_ADDR_AUTO_INC;
        static U8 TxBuff[10] = { 0 };
        static U8 RxBuff[10] = { 0 };
        TxBuff[0] = Header.byte;
        ret = SPI_WriteRead(Node->spiNum, TxBuff, RxBuff, 2);
        GPIO_SetPinState(Node->chipSelectPort, Node->chipSelectPin, LOGIC_1);
    } // end of if (size < 10)

    return ret;
} // end of LIS3DH_SPI_ReadMemoryLowLevel()

//**************************************************************************************************
//! LIS3DH write register by SPI
//!
//! \note       None
//!
//! \param[in]  Node - ASIC RAM node
//! \param[in]  regAddr - ASIC internal register address
//! \param[out] byte - register value
//!
//! \return     Return result of function execution,
//!             this parameter can be one of the following values:
//!             RESULT_OK       - function succeeded
//!             RESULT_NOT_OK   - function not succeeded
//**************************************************************************************************
STD_RESULT LIS3DH_SPI_RegWriteLowLevel(LIS3DH_HANDLE* const Node,
                                       const LIS3DH_REGISTER_ADDR regAddr,
                                       const U8 byte)
{
    STD_RESULT ret = RESULT_NOT_OK;
    GPIO_SetPinState(Node->chipSelectPort, Node->chipSelectPin, LOGIC_0);
   // wait_us(500);
    LIS3DH_SPI_HEADER Header = { 0 };
    Header.byte = 0;
    Header.registerAddress = regAddr;
    Header.rw = LIS3DH_SPI_DIR_WRITE;
    Header.ms = LIS3DH_SPI_MS_ADDR_STATIC;
    static U8 TxBuff[2] = { 0 };
    static U8 RxBuff[2] = { 0 };
    TxBuff[0] = Header.byte;
    TxBuff[1] = byte;

    ret = SPI_WriteRead(Node->spiNum, TxBuff, RxBuff, 2);

    GPIO_SetPinState(Node->chipSelectPort, Node->chipSelectPin, LOGIC_1);
    return ret;
} // end of LIS3DH_SPI_RegWriteLowLevel()



//**************************************************************************************************
//==================================================================================================
// Definitions of local (private) functions
//==================================================================================================
//**************************************************************************************************



//**************************************************************************************************
//! extract valid byte
//!
//! \note       None
//!
//! \param[in]  rxArray - 2 byte array
//!
//! \return     extracted valid value
//**************************************************************************************************
static U8 ExtractValidByte(const U8* const rxArray)
{
    U8 rxbyte = 0xFF;
    if ( 0xFF != rxArray[0] )
    {
        rxbyte= rxArray[0];
    }
    else
    {
        if ( 0xFF != rxArray[1] )
        {
            rxbyte = rxArray[1];
        }
        else
        {
            rxbyte = 0xFF;
        }
    } // end of if ( 0xFF == rxArray[0] )

    return rxbyte;
} // end of ExtractValidByte()

//****************************************** end of file *******************************************
