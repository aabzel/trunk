//**************************************************************************************************
// @Filename      Memory placement helper macros
//--------------------------------------------------------------------------------------------------
// @Compatible    Compiler: GCC C Compiler for ARM
//--------------------------------------------------------------------------------------------------
// @Description   Macros contains in this file helps to place code and/or data
//                in a specific memory segments.
//                Interface of the macro are platform- and compiler- independent.
//--------------------------------------------------------------------------------------------------
// @Version       2.0.0
//--------------------------------------------------------------------------------------------------
// @Date          26.11.2018
//--------------------------------------------------------------------------------------------------
// @History       Version  Author  Comment
// 26.11.2018     2.0.0    SRM     Second release.
//**************************************************************************************************

#ifndef COMPILER_H
#include "compiler.h"
#endif

/* This is a usage example

#define MEM_PLACEMENT_START                              // Specify memory placement macro start
#define MEM_PLACEMENT_TYPE      MEM_PLACEMENT_RAM_DATA   // Specify memory placement type (ram/rom data/code)
#define MEM_PLACEMENT_NAME      MEMORY_SEGMENT_NAME      // Specify memory placement segment name
#include "mem_placement.h"                               // Activate memory placement macro start
U8 objectNameToBeSpecificallyPlaced;                     // Declare object to be specifically placed
#define MEM_PLACEMENT_END                                // Specify memory placement macro end
#include "mem_placement.h"                               // Activate memory placement macro end

*/

// Only this constants can be placed as a memory type specifier
// (in MEM_PLACEMENT_TYPE definition)
#define MEM_PLACEMENT_RAM_DATA  (1)
#define MEM_PLACEMENT_ROM_DATA  (2)
#define MEM_PLACEMENT_RAM_CODE  (3)
#define MEM_PLACEMENT_ROM_CODE  (4)



// Section start macros
#if defined MEM_PLACEMENT_START
    #if (MEM_PLACEMENT_TYPE == MEM_PLACEMENT_RAM_DATA)
        SEGMENT_BEGIN(constant_not_used, RAM_DATA_SEG, .MEM_PLACEMENT_NAME)
    #elif (MEM_PLACEMENT_TYPE == MEM_PLACEMENT_ROM_DATA)
        SEGMENT_BEGIN(constant_not_used, ROM_DATA_SEG, .MEM_PLACEMENT_NAME)
    #elif (MEM_PLACEMENT_TYPE == MEM_PLACEMENT_RAM_CODE)
        SEGMENT_BEGIN(constant_not_used, RAM_CODE_SEG, .MEM_PLACEMENT_NAME)
    #elif (MEM_PLACEMENT_TYPE == MEM_PLACEMENT_ROM_CODE)
        SEGMENT_BEGIN(constant_not_used, ROM_CODE_SEG, .MEM_PLACEMENT_NAME)
    #else
    #endif
    #undef MEM_PLACEMENT_START

// Section end macros
#elif defined MEM_PLACEMENT_END
    #if (MEM_PLACEMENT_TYPE == MEM_PLACEMENT_RAM_DATA)
        SEGMENT_END(constant_not_used, RAM_DATA_SEG, .MEM_PLACEMENT_NAME)
    #elif (MEM_PLACEMENT_TYPE == MEM_PLACEMENT_ROM_DATA)
        SEGMENT_END(constant_not_used, ROM_DATA_SEG, .MEM_PLACEMENT_NAME)
    #elif (MEM_PLACEMENT_TYPE == MEM_PLACEMENT_RAM_CODE)
        SEGMENT_END(constant_not_used, RAM_CODE_SEG, .MEM_PLACEMENT_NAME)
    #elif (MEM_PLACEMENT_TYPE == MEM_PLACEMENT_ROM_CODE)
        SEGMENT_END(constant_not_used, ROM_CODE_SEG, .MEM_PLACEMENT_NAME)
    #else
    #endif
    #undef MEM_PLACEMENT_END

    #undef MEM_PLACEMENT_NO_INIT
    #undef MEM_PLACEMENT_TYPE
    #undef MEM_PLACEMENT_NAME
#endif



//****************************************** end of file *******************************************
