//**************************************************************************************************
// @Module        Memory Manager
// @Filename      memory_manager.h
//--------------------------------------------------------------------------------------------------
// @Description   Interface of the Memory Manager module.
//--------------------------------------------------------------------------------------------------
// @Version       1.1.0
//--------------------------------------------------------------------------------------------------
// @Date          17.05.2017
//--------------------------------------------------------------------------------------------------
// @History       Version  Author      Comment
// 14.07.2016     1.0.0    SRM         First release.
// 17.05.2017     1.1.0    SRM         Interface has been simplified.
//**************************************************************************************************

#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H



//**************************************************************************************************
// Project Includes
//**************************************************************************************************

// Get data types
#include "compiler.h"

// Get generic definitions
#include "general.h"

// Get configuration of the program module
#include "memory_manager_cfg.h"

// Get memory types
#include "memory_types.h"



//**************************************************************************************************
// Declarations of global (public) data types
//**************************************************************************************************

// None.



//**************************************************************************************************
// Definitions of global (public) constants
//**************************************************************************************************

// None.



//**************************************************************************************************
// Declarations of global (public) variables
//**************************************************************************************************

// None.



//**************************************************************************************************
// Declarations of global (public) functions
//**************************************************************************************************

// Initializes SW and HW resources of the program module
extern void MEMMAN_Init(void);

// Deinitializes SW and HW resources of the program module
extern void MEMMAN_DeInit(void);

// Sets "end of job" callback function pointer(s) for the specified job type
// (Load / Store)
extern STD_RESULT MEMMAN_SetJobCallback(const U8 nJobType,
                                        const U8 nEventID,
                                        const MEM_END_OF_JOB_CALLBACK pCallback);

// Loads data from the specified logical memory bank
extern STD_RESULT MEMMAN_Load(const U8  nMemoryBank,
                              const U32 nAddressOffset,
                              U8* const pDataBuffer,
                              const U32 nDataQty);

// Stores data to the specified logical memory bank
extern STD_RESULT MEMMAN_Store(const U8  nMemoryBank,
                               const U32 nAddressOffset,
                               const U8* const pDataBuffer,
                               const U32 nDataQty);

// Returns the last job result
extern U8 MEMMAN_GetJobResult(void);

// Returns memory status mask of the specified memory bank
extern U32 MEMMAN_GetMemoryStatus(const U8 nMemoryBank);

// Sets a new memory status mask of the specified memory bank
extern void MEMMAN_SetMemoryStatus(const U8  nMemoryBank,
                                   const U32 nStatusMask);



#endif // #ifndef MEMORY_MANAGER_H

//****************************************** end of file *******************************************
