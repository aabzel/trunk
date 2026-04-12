//**************************************************************************************************
// @Module
// @Filename      general.c
//--------------------------------------------------------------------------------------------------
// @Description
//
//--------------------------------------------------------------------------------------------------
// @Notes
//--------------------------------------------------------------------------------------------------
// @Version       1.0.0
//--------------------------------------------------------------------------------------------------
// @Date          27.06.2013
//--------------------------------------------------------------------------------------------------
// @History       Version  Author       Comment
// 13.04.2012     1.0.0    N.Sokolov    First release.
//**************************************************************************************************



//**************************************************************************************************
// Project Includes
//**************************************************************************************************

// Get compiler specific keywords
#include "compiler.h"

// Get data type
#include "platform.h"



//**************************************************************************************************
//==================================================================================================
// Global (public) API functions
//==================================================================================================
//**************************************************************************************************



//**************************************************************************************************
// @Function      API_Buffer_Merge
//--------------------------------------------------------------------------------------------------
// @Description
//--------------------------------------------------------------------------------------------------
// @Notes
//--------------------------------------------------------------------------------------------------
// @ReturnValue   plc - new value of the place, where another array can be inserted
//--------------------------------------------------------------------------------------------------
// @Parameters    arrAddress - contains the address of the array;
//                plc - shows the place, where array should be inserted;
//                insArrAddress - contains the address of the inserted array;
//                insArrsize - contains the size of the inserted array.
//**************************************************************************************************
U16 API_Buffer_Merge16(const U32 arrAddress,
                       const U16 plc,
                       const U32 insArrAddress,
                       const U16 insArrsize)
{
    U16 newPlace = plc;
    U16 j = 0;
    U8 *arrPointer = P_NULL;
    U8 *insArrPointer = P_NULL;
    arrPointer = (U8*)arrAddress;
    insArrPointer = (U8*)insArrAddress;
    for (j = 0; j < plc; j++)
    {
        arrPointer++;
    }
    for ( j = 0; j < insArrsize; j++)
    {
        *arrPointer = *insArrPointer;
        arrPointer++;
        insArrPointer++;
        newPlace++;
    }
    return newPlace;
} // End of function API_Buffer_Merge



U8 API_Buffer_Merge_Inver(U32 arrAddress,
                    U8 plc,
                    U32 insArrAddress,
                    U8 insArrsize)
{
    U16 j = 0;
    U8 *arrPointer = P_NULL;
    U8 *insArrPointer = P_NULL;
    arrPointer = (U8*)arrAddress;
    insArrPointer = (U8*)insArrAddress;
    for (j = 0; j < plc; j++)
    {
        arrPointer++;
    }
    insArrPointer = insArrPointer + insArrsize - 1;
    for ( j = 0; j < insArrsize; j++)
    {
        *arrPointer = *insArrPointer;
        arrPointer++;
        insArrPointer--;
        plc++;
    }
    return plc;
} // End of function API_Buffer_Merge_Inver



U8 API_ReadDataByAddr(U32 arrAddress,
                      U8 plc,
                      U32 insArrAddress,
                      U16 insArrsize)
{
    U16 j = 0;
    U8 *arrPointer = P_NULL;
    U8 *insArrPointer = P_NULL;
    arrPointer = (U8*)arrAddress;
    insArrPointer = (U8*)insArrAddress;
    for (j = 0; j < plc; j++)
    {
        arrPointer++;
    }
    for ( j = 0; j < insArrsize; j++)
    {
        *arrPointer = *insArrPointer;
        arrPointer++;
        insArrPointer++;
        plc++;
    }
    return plc;
}



//****************************************** end of file *******************************************
