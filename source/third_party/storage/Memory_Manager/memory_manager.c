//**************************************************************************************************
// @Module        Memory Manager
// @Filename      memory_manager.c
//--------------------------------------------------------------------------------------------------
// @Description   Implementation of the Memory Manager functionality.
//
//                Abbreviations:
//                  MEMMAN - MEMory MANager.
//
//                Global (public) functions:
//                  MEMMAN_Init()
//                  MEMMAN_DeInit()
//                  MEMMAN_SetJobCallback()
//                  MEMMAN_Load()
//                  MEMMAN_Store()
//                  MEMMAN_GetJobResult()
//                  MEMMAN_GetMemoryStatus()
//                  MEMMAN_SetMemoryStatus()
//
//                Local (private) functions:
//                  MEMMAN_DeviceCallback()
//
//--------------------------------------------------------------------------------------------------
// @Version       1.4.1
//--------------------------------------------------------------------------------------------------
// @Date          20.11.2019
//--------------------------------------------------------------------------------------------------
// @History       Version  Author      Comment
// 14.07.2016     1.0.0    SRM         First release.
// 08.11.2016     1.1.0    SRM         Now MEMMAN_Store() will work correctly even erase/write size
//                                     is not aligned to the erase/write operation size.
// 17.05.2017     1.2.0    SRM         Interface has been simplified.
// 24.04.2019     1.3.0    SRM         Configuration has been expanded.
// 16.09.2019     1.4.0    SIV         Added permissions configuration.
// 20.11.2019     1.4.1    SRM         Verification of the imported configuration parameters 
//                                     corrected due a to configuration template changing.
//**************************************************************************************************



//**************************************************************************************************
// Project Includes
//**************************************************************************************************

// Native header
#include "memory_manager.h"

// Get error tracer functions
#include "error_tracer.h"



//**************************************************************************************************
// Verification of the imported configuration parameters
//**************************************************************************************************

#if (ON == MEMMAN_INTERNAL_DIAGNOSTICS)
#error "Internal diagnostics of the program module are not supported in this version."
#endif // #if (ON == MEMMAN_INTERNAL_DIAGNOSTICS)

#if ((MEMMAN_MEMORY_BANKS_QTY < 1) || (MEMMAN_MEMORY_BANKS_QTY > 32))
#error "MEMMAN_MEMORY_BANKS_QTY constant value should be [1 ; 32]."
#endif // #if ((MEMMAN_MEMORY_BANKS_QTY < 1) || (MEMMAN_MEMORY_BANKS_QTY > 32))

#if ((MEMMAN_MEMORY_DEVICES_QTY < 1) || (MEMMAN_MEMORY_DEVICES_QTY > 8))
#error "MEMMAN_MEMORY_DEVICES_QTY constant value should be [1 ; 8]."
#endif // #if ((MEMMAN_MEMORY_DEVICES_QTY < 1) || (MEMMAN_MEMORY_DEVICES_QTY > 8))



//**************************************************************************************************
// Definitions of global (public) variables
//**************************************************************************************************

// None.



//**************************************************************************************************
// Declarations of local (private) data types
//**************************************************************************************************

// Proprietary development error definitions
typedef enum MEMMAN_DEV_ERROR_enum
{
    MEMMAN_DEV_ERROR_INTERFACE_ID   = (U8)(DEV_ERROR_LAST + 0U), // Invalid interface ID was specified
    MEMMAN_DEV_ERROR_PERM_DENIED    = (U8)(DEV_ERROR_LAST + 1U)  // Permission denied

} MEMMAN_DEV_ERROR;

// Program module API IDs
typedef enum MEMMAN_API_ID_enum
{
    MEMMAN_API_ID_INNER_FUNC   = (U8)0U,
    MEMMAN_API_ID_INIT         = (U8)1U,
    MEMMAN_API_ID_DEINIT       = (U8)2U,
    MEMMAN_API_ID_SETJOBCB     = (U8)3U,
    MEMMAN_API_ID_LOAD         = (U8)4U,
    MEMMAN_API_ID_STORE        = (U8)5U,
    MEMMAN_API_ID_GETJOBRESULT = (U8)6U,
    MEMMAN_API_ID_GETMEMSTAT   = (U8)7U,
    MEMMAN_API_ID_SETMEMSTAT   = (U8)8U

} MEMMAN_API_ID;



// Device's "Init" function prototype
typedef void(*MEMMAN_DEVICE_INIT_FUNC)(void);
// Device's "DeInit" function prototype
typedef void(*MEMMAN_DEVICE_DEINIT_FUNC)(void);
// Device's "SetJobCallback" function prototype
typedef STD_RESULT(*MEMMAN_DEVICE_SETJOBCALLBACK_FUNC)(const U8 nJobType,
                                                       const U8 nEventID,
                                                       const MEM_END_OF_JOB_CALLBACK pCallback);
// Device's "Read" function prototype
typedef STD_RESULT(*MEMMAN_DEVICE_READ_FUNC)(const U32 nTargetAddress,
                                             U8* const pDataBuffer,
                                             const U32 nDataQty);
// Device's "Write" function prototype
typedef STD_RESULT(*MEMMAN_DEVICE_WRITE_FUNC)(const U32 nTargetAddress,
                                              const U8* const pDataBuffer,
                                              const U32 nDataQty);
// Device's "GetMemoryStatus" function prototype
typedef U32 (*MEMMAN_DEVICE_GETMEMSTAT_FUNC)(void);
// Device's "SetMemoryStatus" function prototype
typedef void(*MEMMAN_DEVICE_SETMEMSTAT_FUNC)(const U32 nStatusMask);
// Device's "GetSectorSize" function prototype
typedef U32 (*MEMMAN_DEVICE_GETSECTORSIZE_FUNC)(const U32 nSectorAddress);
// Device's "Erase" function prototype
typedef STD_RESULT(*MEMMAN_DEVICE_ERASE_FUNC)(const U32 nTargetAddress,
                                              const U32 nLength);


// Container for memory bank static configuration
typedef struct MEMMAN_BANK_STATIC_CFG_str
{
    U8  nDeviceNumber;
    U8  nPermissions;
    U32 nBaseAddress;
    U32 nSize;

} MEMMAN_BANK_STATIC_CFG;

// Container for memory bank dynamic configuration
typedef struct MEMMAN_BANK_DYNAMIC_CFG_str
{
    MEM_END_OF_JOB_CALLBACK pEOJCallback;

} MEMMAN_BANK_DYNAMIC_CFG;

// Memory bank object structure
typedef struct MEMMAN_BANK_str
{
    const MEMMAN_BANK_STATIC_CFG* staticConfig;
    MEMMAN_BANK_DYNAMIC_CFG*      dynamicConfig;

} MEMMAN_BANK;

// Container for memory device static configuration
typedef struct MEMMAN_DEVICE_STATIC_CFG_str
{
    MEMMAN_DEVICE_INIT_FUNC             Init;
    MEMMAN_DEVICE_DEINIT_FUNC           DeInit;
    MEMMAN_DEVICE_SETJOBCALLBACK_FUNC   SetJobCallback;
    MEMMAN_DEVICE_READ_FUNC             Read;
    MEMMAN_DEVICE_WRITE_FUNC            Write;
    MEMMAN_DEVICE_GETMEMSTAT_FUNC       GetMemoryStatus;
    MEMMAN_DEVICE_SETMEMSTAT_FUNC       SetMemoryStatus;
    MEMMAN_DEVICE_GETSECTORSIZE_FUNC    GetSectorSize;
    MEMMAN_DEVICE_ERASE_FUNC            Erase;

} MEMMAN_DEVICE_STATIC_CFG;

// Memory device object structure
typedef struct MEMMAN_DEVICE_str
{
    const MEMMAN_DEVICE_STATIC_CFG* staticConfig;

} MEMMAN_DEVICE;



//**************************************************************************************************
// Definitions of local (private) constants
//**************************************************************************************************

// Program module ID ( = program module prefix)
static const U8 MEMMAN_moduleID[] = "MEMMAN";

// Permissions bit masks
#define MEMMAN_PERM_BIT_READ        ((U8)0x01U)
#define MEMMAN_PERM_BIT_WRITE       ((U8)0x02U)
#define MEMMAN_PERM_BIT_ERASE       ((U8)0x04U)

// Permissions
#define MEMMAN_BANK_PERM_R          (MEMMAN_PERM_BIT_READ)
#define MEMMAN_BANK_PERM_RW         (MEMMAN_PERM_BIT_READ | MEMMAN_PERM_BIT_WRITE)
#define MEMMAN_BANK_PERM_RWE        (MEMMAN_PERM_BIT_READ | MEMMAN_PERM_BIT_WRITE | \
                                     MEMMAN_PERM_BIT_ERASE)

// Memory job events
#define MEMMAN_READ_EVENT_ID        (0U)
#define MEMMAN_ERASE_EVENT_ID       (1U)
#define MEMMAN_WRITE_EVENT_ID       (2U)

// Memory jobs
#define MEMMAN_JOB_IDLE             (0U)
#define MEMMAN_JOB_LOAD             (1U)
#define MEMMAN_JOB_STORE            (2U)

// Not used function pointer
#define MEMMAN_FUNC_NOT_USED        (NULL_PTR_FUNC)

// Memory bank configuration macro
#define MEMMAN_BANK_CONFIGURE(nBankNumber)   {MEMMAN_BANK_##nBankNumber##_DEVICE_NUMBER,    \
                                              MEMMAN_BANK_##nBankNumber##_PERMISSIONS,      \
                                              MEMMAN_BANK_##nBankNumber##_BASE_ADDRESS,     \
                                              MEMMAN_BANK_##nBankNumber##_SIZE}

// Memory banks static configuration
static const MEMMAN_BANK_STATIC_CFG MEMMAN_banksStaticCfg[MEMMAN_MEMORY_BANKS_QTY] =
{
     MEMMAN_BANK_CONFIGURE(0)
    #if (MEMMAN_MEMORY_BANKS_QTY > 1U)
    ,MEMMAN_BANK_CONFIGURE(1)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 1U)
    #if (MEMMAN_MEMORY_BANKS_QTY > 2U)
    ,MEMMAN_BANK_CONFIGURE(2)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 2U)
    #if (MEMMAN_MEMORY_BANKS_QTY > 3U)
    ,MEMMAN_BANK_CONFIGURE(3)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 3U)
    #if (MEMMAN_MEMORY_BANKS_QTY > 4U)
    ,MEMMAN_BANK_CONFIGURE(4)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 4U)
    #if (MEMMAN_MEMORY_BANKS_QTY > 5U)
    ,MEMMAN_BANK_CONFIGURE(5)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 5U)
    #if (MEMMAN_MEMORY_BANKS_QTY > 6U)
    ,MEMMAN_BANK_CONFIGURE(6)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 6U)
    #if (MEMMAN_MEMORY_BANKS_QTY > 7U)
    ,MEMMAN_BANK_CONFIGURE(7)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 7U)
    #if (MEMMAN_MEMORY_BANKS_QTY > 8U)
    ,MEMMAN_BANK_CONFIGURE(8)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 8U)
    #if (MEMMAN_MEMORY_BANKS_QTY > 9U)
    ,MEMMAN_BANK_CONFIGURE(9)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 9U)
    #if (MEMMAN_MEMORY_BANKS_QTY > 10U)
    ,MEMMAN_BANK_CONFIGURE(10)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 10U)
    #if (MEMMAN_MEMORY_BANKS_QTY > 11U)
    ,MEMMAN_BANK_CONFIGURE(11)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 11U)
    #if (MEMMAN_MEMORY_BANKS_QTY > 12U)
    ,MEMMAN_BANK_CONFIGURE(12)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 12U)
    #if (MEMMAN_MEMORY_BANKS_QTY > 13U)
    ,MEMMAN_BANK_CONFIGURE(13)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 13U)
    #if (MEMMAN_MEMORY_BANKS_QTY > 14U)
    ,MEMMAN_BANK_CONFIGURE(14)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 14U)
    #if (MEMMAN_MEMORY_BANKS_QTY > 15U)
    ,MEMMAN_BANK_CONFIGURE(15)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 15U)
    #if (MEMMAN_MEMORY_BANKS_QTY > 16U)
    ,MEMMAN_BANK_CONFIGURE(16)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 16U)
    #if (MEMMAN_MEMORY_BANKS_QTY > 17U)
    ,MEMMAN_BANK_CONFIGURE(17)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 17U)
    #if (MEMMAN_MEMORY_BANKS_QTY > 18U)
    ,MEMMAN_BANK_CONFIGURE(18)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 18U)
    #if (MEMMAN_MEMORY_BANKS_QTY > 19U)
    ,MEMMAN_BANK_CONFIGURE(19)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 19U)
    #if (MEMMAN_MEMORY_BANKS_QTY > 20U)
    ,MEMMAN_BANK_CONFIGURE(20)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 20U)
    #if (MEMMAN_MEMORY_BANKS_QTY > 21U)
    ,MEMMAN_BANK_CONFIGURE(21)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 21U)
    #if (MEMMAN_MEMORY_BANKS_QTY > 22U)
    ,MEMMAN_BANK_CONFIGURE(22)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 22U)
    #if (MEMMAN_MEMORY_BANKS_QTY > 23U)
    ,MEMMAN_BANK_CONFIGURE(23)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 23U)
    #if (MEMMAN_MEMORY_BANKS_QTY > 24U)
    ,MEMMAN_BANK_CONFIGURE(24)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 24U)
    #if (MEMMAN_MEMORY_BANKS_QTY > 25U)
    ,MEMMAN_BANK_CONFIGURE(25)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 25U)
    #if (MEMMAN_MEMORY_BANKS_QTY > 26U)
    ,MEMMAN_BANK_CONFIGURE(26)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 26U)
    #if (MEMMAN_MEMORY_BANKS_QTY > 27U)
    ,MEMMAN_BANK_CONFIGURE(27)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 27U)
    #if (MEMMAN_MEMORY_BANKS_QTY > 28U)
    ,MEMMAN_BANK_CONFIGURE(28)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 28U)
    #if (MEMMAN_MEMORY_BANKS_QTY > 29U)
    ,MEMMAN_BANK_CONFIGURE(29)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 29U)
    #if (MEMMAN_MEMORY_BANKS_QTY > 30U)
    ,MEMMAN_BANK_CONFIGURE(30)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 30U)
    #if (MEMMAN_MEMORY_BANKS_QTY > 31U)
    ,MEMMAN_BANK_CONFIGURE(31)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 31U)
};

// Device configuration macro
#define MEMMAN_DEVICE_CONFIGURE(nDeviceNumber)   {MEMMAN_DEVICE_##nDeviceNumber##_INIT_FUNC,            \
                                                  MEMMAN_DEVICE_##nDeviceNumber##_DEINIT_FUNC,          \
                                                  MEMMAN_DEVICE_##nDeviceNumber##_SETJOBCB_FUNC,        \
                                                  MEMMAN_DEVICE_##nDeviceNumber##_READ_FUNC,            \
                                                  MEMMAN_DEVICE_##nDeviceNumber##_WRITE_FUNC,           \
                                                  MEMMAN_DEVICE_##nDeviceNumber##_GETMEMSTAT_FUNC,      \
                                                  MEMMAN_DEVICE_##nDeviceNumber##_SETMEMSTAT_FUNC,      \
                                                  MEMMAN_DEVICE_##nDeviceNumber##_GETSECTORSIZE_FUNC,   \
                                                  MEMMAN_DEVICE_##nDeviceNumber##_ERASE_FUNC}

// Devices static configuration
static const MEMMAN_DEVICE_STATIC_CFG MEMMAN_devicesStaticCfg[MEMMAN_MEMORY_DEVICES_QTY] =
{
     MEMMAN_DEVICE_CONFIGURE(0)
    #if (MEMMAN_MEMORY_DEVICES_QTY > 1U)
    ,MEMMAN_DEVICE_CONFIGURE(1)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 1U)
    #if (MEMMAN_MEMORY_DEVICES_QTY > 2U)
    ,MEMMAN_DEVICE_CONFIGURE(2)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 2U)
    #if (MEMMAN_MEMORY_DEVICES_QTY > 3U)
    ,MEMMAN_DEVICE_CONFIGURE(3)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 3U)
    #if (MEMMAN_MEMORY_DEVICES_QTY > 4U)
    ,MEMMAN_DEVICE_CONFIGURE(4)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 4U)
    #if (MEMMAN_MEMORY_DEVICES_QTY > 5U)
    ,MEMMAN_DEVICE_CONFIGURE(5)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 5U)
    #if (MEMMAN_MEMORY_DEVICES_QTY > 6U)
    ,MEMMAN_DEVICE_CONFIGURE(6)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 6U)
    #if (MEMMAN_MEMORY_DEVICES_QTY > 7U)
    ,MEMMAN_DEVICE_CONFIGURE(7)
    #endif // #if (MEMMAN_MEMORY_DEVICES_QTY > 7U)
};



//**************************************************************************************************
// Definitions of static global (private) variables
//**************************************************************************************************

#if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)
// Program module initialization state
static BOOLEAN MEMMAN_bInitialized;
#endif // #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)

// End of load job callback function pointer
static MEM_END_OF_JOB_CALLBACK MEMMAN_pLoadCallback;
// End of load job callback event identifier to notify user to
static U8 MEMMAN_nLoadCallbackEventID;

// End of store job callback function pointer
static MEM_END_OF_JOB_CALLBACK MEMMAN_pStoreCallback;
// End of store job callback event identifier to notify user to
static U8 MEMMAN_nStoreCallbackEventID;

// Current memory job
static U8 MEMMAN_nCurrentJob;

// The last (current) job result
static U8 MEMMAN_nJobResult;

// Target address for write process when erase algorithms are used
static U32 MEMMAN_nTargetAddress;

// Source data pointer for write process when erase algorithms are used
static const U8* MEMMAN_pDataBuffer;

// Data quantity for write process when erase algorithms are used
static U32 MEMMAN_nDataQty;

// Memory banks dynamic configuration
static MEMMAN_BANK_DYNAMIC_CFG MEMMAN_banksDynamicCfg[MEMMAN_MEMORY_BANKS_QTY];

// Memory bank objects
static const MEMMAN_BANK MEMMAN_banks = 
{
    MEMMAN_banksStaticCfg,
    MEMMAN_banksDynamicCfg
};

// Device objects
static const MEMMAN_DEVICE MEMMAN_devices = 
{
    MEMMAN_devicesStaticCfg
};



//**************************************************************************************************
// Declarations of local (private) functions
//**************************************************************************************************

// Calls on every end-of-job memory device event
static void MEMMAN_DeviceCallback(const U8 nEventID,
                                  const U8 nJobResult);



//**************************************************************************************************
//==================================================================================================
// Definitions of global (public) functions
//==================================================================================================
//**************************************************************************************************



//**************************************************************************************************
// @Function      MEMMAN_Init()
//--------------------------------------------------------------------------------------------------
// @Description   Initializes SW and HW resources of the program module.
//--------------------------------------------------------------------------------------------------
// @Notes         None.
//--------------------------------------------------------------------------------------------------
// @ReturnValue   RESULT_OK     - function succeeded
//                RESULT_NOT_OK - function NOT succeeded
//--------------------------------------------------------------------------------------------------
// @Parameters    None.
//**************************************************************************************************
void MEMMAN_Init(void)
{
    #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)
    // Checking whether initialization is done or not
    if (FALSE == MEMMAN_bInitialized)
    {
    #endif // #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)

        U8 nDeviceNumber = 0U;

        for (nDeviceNumber = 0U; nDeviceNumber < MEMMAN_MEMORY_DEVICES_QTY; nDeviceNumber++)
        {
            // Initialize all of the memory devices
            if (NULL_PTR != MEMMAN_devices.staticConfig[nDeviceNumber].Init)
            {
                (MEMMAN_devices.staticConfig[nDeviceNumber].Init)();
            }

            // Set all of the "end-of-job" event handlers
            if (NULL_PTR != MEMMAN_devices.staticConfig[nDeviceNumber].SetJobCallback)
            {
                if (NULL_PTR != MEMMAN_devices.staticConfig[nDeviceNumber].Erase)
                {
                    (MEMMAN_devices.staticConfig[nDeviceNumber].SetJobCallback)
                        (MEM_JOB_CALLBACK_ERASE,
                         MAKEBYTE(MEMMAN_ERASE_EVENT_ID, nDeviceNumber),
                         MEMMAN_DeviceCallback);
                }
            }
            else
            {
                // Should not get here!
                DoNothing();
            }
        }

    #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)
        MEMMAN_bInitialized = TRUE;
    }
    else
    {
        // Program module has been already initialized
        ET_ReportDevelopmentError(MEMMAN_moduleID,
                                  SIZE_OF_ARRAY(MEMMAN_moduleID) - 1U,
                                  0U,
                                  MEMMAN_API_ID_INIT,
                                  DEV_ERROR_ALREADY_INIT);
    }
    #endif // #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)

} // end of MEMMAN_Init()



//**************************************************************************************************
// @Function      MEMMAN_DeInit()
//--------------------------------------------------------------------------------------------------
// @Description   Deinitializes SW and HW resources of the program module.
//--------------------------------------------------------------------------------------------------
// @Notes         None.
//--------------------------------------------------------------------------------------------------
// @ReturnValue   RESULT_OK     - function succeeded
//                RESULT_NOT_OK - function NOT succeeded
//--------------------------------------------------------------------------------------------------
// @Parameters    None.
//**************************************************************************************************
void MEMMAN_DeInit(void)
{
    #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)
    // Checking whether initialization is done or not
    if (TRUE == MEMMAN_bInitialized)
    {
    #endif // #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)

        U8 nDeviceNumber = 0U;

        // Deinitialize all of the memory devices
        for (nDeviceNumber = 0U; nDeviceNumber < MEMMAN_MEMORY_DEVICES_QTY; nDeviceNumber++)
        {
            if (NULL_PTR != MEMMAN_devices.staticConfig[nDeviceNumber].DeInit)
            {
                (MEMMAN_devices.staticConfig[nDeviceNumber].DeInit)();
            }
        }

    #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)
        MEMMAN_bInitialized = FALSE;
    }
    else
    {
        // Program module is not initialized
        ET_ReportDevelopmentError(MEMMAN_moduleID,
                                  SIZE_OF_ARRAY(MEMMAN_moduleID) - 1U,
                                  0U,
                                  MEMMAN_API_ID_DEINIT,
                                  DEV_ERROR_NOT_INIT);
    }
    #endif // #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)

} // end of MEMMAN_DeInit()



//**************************************************************************************************
// @Function      MEMMAN_SetJobCallback()
//--------------------------------------------------------------------------------------------------
// @Description   Sets "end of job" callback function pointer(s) for the specified job type
//                (Load / Store)
//--------------------------------------------------------------------------------------------------
// @Notes         None.
//--------------------------------------------------------------------------------------------------
// @ReturnValue   RESULT_OK     - function succeeded
//                RESULT_NOT_OK - function NOT succeeded
//--------------------------------------------------------------------------------------------------
// @Parameters    nJobType  - job type: Load / Store
//                nEventID  - callback event identifier to notify user to
//                pCallback - pointer to the callback function
//**************************************************************************************************
STD_RESULT MEMMAN_SetJobCallback(const U8 nJobType,
                                 const U8 nEventID,
                                 const MEM_END_OF_JOB_CALLBACK pCallback)
{
    STD_RESULT nFuncResult = RESULT_OK;

    #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)
    // Checking whether initialization is done or not
    if (TRUE == MEMMAN_bInitialized)
    {
    #endif // #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)

        if (MEMMAN_JOB_IDLE == MEMMAN_nCurrentJob)
        {
            if (NULL_PTR == pCallback)
            {
                // Formally test input pointer for null
                // pCallback CAN be null
                DoNothing();
            }

            switch (nJobType)
            {
                case MEM_JOB_CALLBACK_LOAD:
                    MEMMAN_pLoadCallback        = pCallback;
                    MEMMAN_nLoadCallbackEventID = nEventID;
                    break;

                case MEM_JOB_CALLBACK_STORE:
                    MEMMAN_pStoreCallback        = pCallback;
                    MEMMAN_nStoreCallbackEventID = nEventID;
                    break;

                default:
                    // There is no other job types
                    DoNothing();
                    nFuncResult = RESULT_NOT_OK;
                    break;
            }
        }
        else
        {
            // Program module is busy
            ET_ReportRuntimeError(MEMMAN_moduleID,
                                  SIZE_OF_ARRAY(MEMMAN_moduleID) - 1U,
                                  0U,
                                  MEMMAN_API_ID_SETJOBCB,
                                  RT_ERROR_BUSY);

            nFuncResult = RESULT_NOT_OK;
        }

    #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)
    }
    else
    {
        // Program module is not initialized
        ET_ReportDevelopmentError(MEMMAN_moduleID,
                                  SIZE_OF_ARRAY(MEMMAN_moduleID) - 1U,
                                  0U,
                                  MEMMAN_API_ID_SETJOBCB,
                                  DEV_ERROR_NOT_INIT);

        nFuncResult = RESULT_NOT_OK;
    }
    #endif // #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)

    return nFuncResult;

} // end of MEMMAN_SetJobCallback()



//**************************************************************************************************
// @Function      MEMMAN_Load()
//--------------------------------------------------------------------------------------------------
// @Description   Loads data from the specified logical memory bank.
//--------------------------------------------------------------------------------------------------
// @Notes         None.
//--------------------------------------------------------------------------------------------------
// @ReturnValue   RESULT_OK     - function succeeded
//                RESULT_NOT_OK - function NOT succeeded
//--------------------------------------------------------------------------------------------------
// @Parameters    nMemoryBank    - logical memory bank number
//                nAddressOffset - address offset in the specified memory bank
//                pDataBuffer    - pointer to a buffer receiving data
//                nDataQty       - data quantity to be loaded in bytes
//**************************************************************************************************
STD_RESULT MEMMAN_Load(const U8  nMemoryBank,
                       const U32 nAddressOffset,
                       U8* const pDataBuffer,
                       const U32 nDataQty)
{
    STD_RESULT nFuncResult = RESULT_OK;

    #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)
    // Checking whether initialization is done or not
    if (TRUE == MEMMAN_bInitialized)
    {
        // Check memory bank number
        if (nMemoryBank < MEMMAN_MEMORY_BANKS_QTY)
        {
            // Check data quantity
            if (0UL != nDataQty)
            {
    #endif // #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)

                // Check permissions for read
                if (MEMMAN_PERM_BIT_READ & MEMMAN_banks.staticConfig[nMemoryBank].nPermissions)
                {
                    // Check data buffer pointer
                    if (NULL_PTR != pDataBuffer)
                    {
                        // Check memory bank address range violation
                        if ((MEMMAN_banks.staticConfig[nMemoryBank].nBaseAddress +
                             nAddressOffset +
                             nDataQty) <=
                            (MEMMAN_banks.staticConfig[nMemoryBank].nBaseAddress +
                             MEMMAN_banks.staticConfig[nMemoryBank].nSize))
                        {
                            U8 nDeviceNumber = MEMMAN_banks.staticConfig[nMemoryBank].nDeviceNumber;

                            if (NULL_PTR != MEMMAN_devices.staticConfig[nDeviceNumber].Read)
                            {
                                U32 nTargetAddress = MEMMAN_banks.staticConfig[nMemoryBank].nBaseAddress +
                                                     nAddressOffset;

                                // Start read job
                                MEMMAN_nJobResult = MEM_JOB_RESULT_PENDING;

                                (MEMMAN_devices.staticConfig[nDeviceNumber].SetJobCallback)
                                    (MEM_JOB_CALLBACK_READ,
                                     MAKEBYTE(MEMMAN_READ_EVENT_ID, nDeviceNumber),
                                     MEMMAN_DeviceCallback);

                                if (RESULT_OK != (MEMMAN_devices.staticConfig[nDeviceNumber].Read)
                                                    (nTargetAddress,
                                                     pDataBuffer,
                                                     nDataQty))
                                {
                                    // Read job failed
                                    MEMMAN_nJobResult = MEM_JOB_RESULT_NOT_OK;
                                    nFuncResult = RESULT_NOT_OK;
                                }
                            }
                            else
                            {
                                // "Read" function pointer is null
                                ET_ReportRuntimeError(MEMMAN_moduleID,
                                                      SIZE_OF_ARRAY(MEMMAN_moduleID) - 1U,
                                                      nMemoryBank,
                                                      MEMMAN_API_ID_LOAD,
                                                      RT_ERROR_NULL_PTR);

                                nFuncResult = RESULT_NOT_OK;
                            }
                        }
                        else
                        {
                            // Specified data to be read is out of the specified memory bank address range
                            ET_ReportRuntimeError(MEMMAN_moduleID,
                                                  SIZE_OF_ARRAY(MEMMAN_moduleID) - 1U,
                                                  nMemoryBank,
                                                  MEMMAN_API_ID_LOAD,
                                                  DEV_ERROR_PARAM_3);

                            nFuncResult = RESULT_NOT_OK;
                        }
                    }
                    else
                    {
                        // Data buffer is null pointer
                        ET_ReportRuntimeError(MEMMAN_moduleID,
                                              SIZE_OF_ARRAY(MEMMAN_moduleID) - 1U,
                                              nMemoryBank,
                                              MEMMAN_API_ID_LOAD,
                                              RT_ERROR_NULL_PTR);

                        nFuncResult = RESULT_NOT_OK;
                    }
                }
                else
                {
                    #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)
                    // Invalid data quantity
                    ET_ReportDevelopmentError(MEMMAN_moduleID,
                                              SIZE_OF_ARRAY(MEMMAN_moduleID) - 1U,
                                              nMemoryBank,
                                              MEMMAN_API_ID_LOAD,
                                              MEMMAN_DEV_ERROR_PERM_DENIED);
                    #endif // #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)

                    nFuncResult = RESULT_NOT_OK;
                }

    #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)
            }
            else
            {
                // Invalid data quantity
                ET_ReportDevelopmentError(MEMMAN_moduleID,
                                          SIZE_OF_ARRAY(MEMMAN_moduleID) - 1U,
                                          nMemoryBank,
                                          MEMMAN_API_ID_LOAD,
                                          DEV_ERROR_PARAM_3);

                nFuncResult = RESULT_NOT_OK;
            }
        }
        else
        {
            // Invalid memory bank number
            ET_ReportDevelopmentError(MEMMAN_moduleID,
                                      SIZE_OF_ARRAY(MEMMAN_moduleID) - 1U,
                                      ET_OBJECT_NUMBER_UNKNOWN,
                                      MEMMAN_API_ID_LOAD,
                                      DEV_ERROR_PARAM_0);

            nFuncResult = RESULT_NOT_OK;
        }
    }
    else
    {
        // Program module is not initialized
        ET_ReportDevelopmentError(MEMMAN_moduleID,
                                  SIZE_OF_ARRAY(MEMMAN_moduleID) - 1U,
                                  ET_OBJECT_NUMBER_UNKNOWN,
                                  MEMMAN_API_ID_LOAD,
                                  DEV_ERROR_NOT_INIT);

        nFuncResult = RESULT_NOT_OK;
    }
    #endif // #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)

    return nFuncResult;

} // end of MEMMAN_Load()



//**************************************************************************************************
// @Function      MEMMAN_Store()
//--------------------------------------------------------------------------------------------------
// @Description   Stores the specified data to the specified logical memory bank.
//--------------------------------------------------------------------------------------------------
// @Notes         None.
//--------------------------------------------------------------------------------------------------
// @ReturnValue   RESULT_OK     - function succeeded
//                RESULT_NOT_OK - function NOT succeeded
//--------------------------------------------------------------------------------------------------
// @Parameters    nMemoryBank    - logical memory bank number
//                nAddressOffset - address offset in the specified memory bank
//                pDataBuffer    - pointer to a buffer contains data to be stored
//                nDataQty       - data quantity to be stored in bytes
//**************************************************************************************************
STD_RESULT MEMMAN_Store(const U8  nMemoryBank,
                        const U32 nAddressOffset,
                        const U8* const pDataBuffer,
                        const U32 nDataQty)
{
    STD_RESULT nFuncResult = RESULT_OK;

    #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)
    // Checking whether initialization is done or not
    if (TRUE == MEMMAN_bInitialized)
    {
        // Check memory bank number
        if (nMemoryBank < MEMMAN_MEMORY_BANKS_QTY)
        {
            // Check data quantity
            if (0UL != nDataQty)
            {
    #endif // #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)

                // Check permissions for write
                if (MEMMAN_PERM_BIT_WRITE & MEMMAN_banks.staticConfig[nMemoryBank].nPermissions)
                {
                    // Check data buffer pointer
                    if (NULL_PTR != pDataBuffer)
                    {
                        // Check memory bank address range violation
                        if ((MEMMAN_banks.staticConfig[nMemoryBank].nBaseAddress +
                             nAddressOffset +
                             nDataQty) <=
                            (MEMMAN_banks.staticConfig[nMemoryBank].nBaseAddress +
                             MEMMAN_banks.staticConfig[nMemoryBank].nSize))
                        {
                            U8 nDeviceNumber = MEMMAN_banks.staticConfig[nMemoryBank].nDeviceNumber;

                            // Check permissions for erase
                            // and whether erase-before-write is needed or not
                            if ((MEMMAN_PERM_BIT_ERASE &
                                    MEMMAN_banks.staticConfig[nMemoryBank].nPermissions) &&
                                (NULL_PTR != MEMMAN_devices.staticConfig[nDeviceNumber].Erase))
                            {
                                // Erase-before-write IS needed
                                U32 nTargetAddress = MEMMAN_banks.staticConfig[nMemoryBank].nBaseAddress +
                                                     nAddressOffset;
                                U32 nEraseSize = nDataQty;

                                if (NULL_PTR != MEMMAN_devices.staticConfig[nDeviceNumber].GetSectorSize)
                                {
                                    // Align erase size to the sector size
                                    U32 nSectorSize = 0UL;

                                    nSectorSize = MEMMAN_devices.staticConfig[nDeviceNumber].GetSectorSize(nTargetAddress);

                                    if (nEraseSize < nSectorSize)
                                    {
                                        nEraseSize = nSectorSize;
                                    }
                                    else if (nEraseSize > nSectorSize)
                                    {
                                        nEraseSize += (nSectorSize - nEraseSize % nSectorSize);
                                    }
                                    else
                                    {
                                        DoNothing();
                                    }
                                }

                                // Remember write job parameters
                                MEMMAN_nTargetAddress = nTargetAddress;
                                MEMMAN_pDataBuffer    = pDataBuffer;
                                MEMMAN_nDataQty       = nDataQty;

                                // Start erase job
                                MEMMAN_nJobResult = MEM_JOB_RESULT_PENDING;

                                (MEMMAN_devices.staticConfig[nDeviceNumber].SetJobCallback)
                                    (MEM_JOB_CALLBACK_ERASE,
                                     MAKEBYTE(MEMMAN_ERASE_EVENT_ID, nDeviceNumber),
                                     MEMMAN_DeviceCallback);

                                if (RESULT_OK != (MEMMAN_devices.staticConfig[nDeviceNumber].Erase)
                                                     (nTargetAddress,
                                                      nEraseSize))
                                {
                                    // Erase job failed
                                    MEMMAN_nJobResult = MEM_JOB_RESULT_NOT_OK;
                                    nFuncResult = RESULT_NOT_OK;

                                    // Job failed
                                    if (NULL_PTR != MEMMAN_pStoreCallback)
                                    {
                                        // Notify user
                                        (MEMMAN_pStoreCallback)(MEMMAN_nStoreCallbackEventID, MEMMAN_nJobResult);
                                    }
                                }
                            }
                            else
                            {
                                // Erase-before-write is NOT needed
                                if (NULL_PTR != MEMMAN_devices.staticConfig[nDeviceNumber].Write)
                                {
                                    U32 nTargetAddress = MEMMAN_banks.staticConfig[nMemoryBank].nBaseAddress +
                                                         nAddressOffset;

                                    // Start write job
                                    MEMMAN_nJobResult = MEM_JOB_RESULT_PENDING;

                                    (MEMMAN_devices.staticConfig[nDeviceNumber].SetJobCallback)
                                        (MEM_JOB_CALLBACK_WRITE,
                                         MAKEBYTE(MEMMAN_WRITE_EVENT_ID, nDeviceNumber),
                                         MEMMAN_DeviceCallback);

                                    if (RESULT_OK != (MEMMAN_devices.staticConfig[nDeviceNumber].Write)
                                                         (nTargetAddress,
                                                          pDataBuffer,
                                                          nDataQty))
                                    {
                                        // Write job failed
                                        MEMMAN_nJobResult = MEM_JOB_RESULT_NOT_OK;
                                        nFuncResult = RESULT_NOT_OK;

                                        // Job failed
                                        if (NULL_PTR != MEMMAN_pStoreCallback)
                                        {
                                            // Notify user
                                            (MEMMAN_pStoreCallback)(MEMMAN_nStoreCallbackEventID, MEMMAN_nJobResult);
                                        }
                                    }
                                }
                                else
                                {
                                    // "Write" function pointer is null
                                    ET_ReportRuntimeError(MEMMAN_moduleID,
                                                          SIZE_OF_ARRAY(MEMMAN_moduleID) - 1U,
                                                          nMemoryBank,
                                                          MEMMAN_API_ID_STORE,
                                                          RT_ERROR_NULL_PTR);

                                    nFuncResult = RESULT_NOT_OK;
                                }
                            }
                        }
                        else
                        {
                            // Specified data to be stored is out of the specified memory bank address range
                            ET_ReportRuntimeError(MEMMAN_moduleID,
                                                  SIZE_OF_ARRAY(MEMMAN_moduleID) - 1U,
                                                  nMemoryBank,
                                                  MEMMAN_API_ID_STORE,
                                                  DEV_ERROR_PARAM_3);

                            nFuncResult = RESULT_NOT_OK;
                        }
                    }
                    else
                    {
                        // Data buffer is null pointer
                        ET_ReportRuntimeError(MEMMAN_moduleID,
                                              SIZE_OF_ARRAY(MEMMAN_moduleID) - 1U,
                                              nMemoryBank,
                                              MEMMAN_API_ID_STORE,
                                              RT_ERROR_NULL_PTR);

                        nFuncResult = RESULT_NOT_OK;
                    }
                }
                else
                {
                    #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)
                    // Invalid data quantity
                    ET_ReportDevelopmentError(MEMMAN_moduleID,
                                              SIZE_OF_ARRAY(MEMMAN_moduleID) - 1U,
                                              nMemoryBank,
                                              MEMMAN_API_ID_STORE,
                                              MEMMAN_DEV_ERROR_PERM_DENIED);
                    #endif // #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)

                    nFuncResult = RESULT_NOT_OK;
                }

    #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)
            }
            else
            {
                // Invalid data quantity
                ET_ReportDevelopmentError(MEMMAN_moduleID,
                                          SIZE_OF_ARRAY(MEMMAN_moduleID) - 1U,
                                          nMemoryBank,
                                          MEMMAN_API_ID_STORE,
                                          DEV_ERROR_PARAM_3);

                nFuncResult = RESULT_NOT_OK;
            }
        }
        else
        {
            // Invalid memory bank number
            ET_ReportDevelopmentError(MEMMAN_moduleID,
                                      SIZE_OF_ARRAY(MEMMAN_moduleID) - 1U,
                                      ET_OBJECT_NUMBER_UNKNOWN,
                                      MEMMAN_API_ID_STORE,
                                      DEV_ERROR_PARAM_0);

            nFuncResult = RESULT_NOT_OK;
        }
    }
    else
    {
        // Program module is not initialized
        ET_ReportDevelopmentError(MEMMAN_moduleID,
                                  SIZE_OF_ARRAY(MEMMAN_moduleID) - 1U,
                                  ET_OBJECT_NUMBER_UNKNOWN,
                                  MEMMAN_API_ID_STORE,
                                  DEV_ERROR_NOT_INIT);

        nFuncResult = RESULT_NOT_OK;
    }
    #endif // #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)

    return nFuncResult;

} // end of MEMMAN_Store()



//**************************************************************************************************
// @Function      MEMMAN_GetJobResult()
//--------------------------------------------------------------------------------------------------
// @Description   Returns the last memory job result.
//--------------------------------------------------------------------------------------------------
// @Notes         None.
//--------------------------------------------------------------------------------------------------
// @ReturnValue   RESULT_OK     - function succeeded
//                RESULT_NOT_OK - function NOT succeeded
//--------------------------------------------------------------------------------------------------
// @Parameters    None.
//**************************************************************************************************
U8 MEMMAN_GetJobResult(void)
{
    U8 nFuncResult = MEM_JOB_RESULT_NOT_OK;

    #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)
    // Checking whether initialization is done or not
    if (TRUE == MEMMAN_bInitialized)
    {
    #endif // #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)

        nFuncResult = MEMMAN_nJobResult;

    #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)
    }
    else
    {
        // Program module is not initialized
        ET_ReportDevelopmentError(MEMMAN_moduleID,
                                  SIZE_OF_ARRAY(MEMMAN_moduleID) - 1U,
                                  0U,
                                  MEMMAN_API_ID_GETJOBRESULT,
                                  DEV_ERROR_NOT_INIT);
    }
    #endif // #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)

    return nFuncResult;

} // end of MEMMAN_GetJobResult()



//**************************************************************************************************
// @Function      MEMMAN_GetMemoryStatus()
//--------------------------------------------------------------------------------------------------
// @Description   Returns memory status mask of the specified memory bank.
//--------------------------------------------------------------------------------------------------
// @Notes         None.
//--------------------------------------------------------------------------------------------------
// @ReturnValue   RESULT_OK     - function succeeded
//                RESULT_NOT_OK - function NOT succeeded
//--------------------------------------------------------------------------------------------------
// @Parameters    nMemoryBank - memory bank number
//**************************************************************************************************
U32 MEMMAN_GetMemoryStatus(const U8 nMemoryBank)
{
    U32 nFuncResult = 0UL;

    #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)
    // Checking whether initialization is done or not
    if (TRUE == MEMMAN_bInitialized)
    {
    #endif // #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)

        U8 nDeviceNumber = MEMMAN_banks.staticConfig[nMemoryBank].nDeviceNumber;

        if (NULL_PTR != MEMMAN_devices.staticConfig[nDeviceNumber].GetMemoryStatus)
        {
            nFuncResult = ((MEMMAN_devices.staticConfig[nDeviceNumber].GetMemoryStatus)());
        }

    #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)
    }
    else
    {
        // Program module is not initialized
        ET_ReportDevelopmentError(MEMMAN_moduleID,
                                  SIZE_OF_ARRAY(MEMMAN_moduleID) - 1U,
                                  0U,
                                  MEMMAN_API_ID_GETMEMSTAT,
                                  DEV_ERROR_NOT_INIT);
    }
    #endif // #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)

    return nFuncResult;

} // end of MEMMAN_GetMemoryStatus()



//**************************************************************************************************
// @Function      MEMMAN_SetMemoryStatus()
//--------------------------------------------------------------------------------------------------
// @Description   Sets a new memory status mask of the specified memory bank.
//--------------------------------------------------------------------------------------------------
// @Notes         None.
//--------------------------------------------------------------------------------------------------
// @ReturnValue   RESULT_OK     - function succeeded
//                RESULT_NOT_OK - function NOT succeeded
//--------------------------------------------------------------------------------------------------
// @Parameters    nMemoryBank - memory bank number
//                nStatusMask - new memory status mask
//**************************************************************************************************
void MEMMAN_SetMemoryStatus(const U8  nMemoryBank,
                            const U32 nStatusMask)
{
    #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)
    // Checking whether initialization is done or not
    if (TRUE == MEMMAN_bInitialized)
    {
    #endif // #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)

        // Reset the specified status flags
        U8 nDeviceNumber = MEMMAN_banks.staticConfig[nMemoryBank].nDeviceNumber;

        if (NULL_PTR != MEMMAN_devices.staticConfig[nDeviceNumber].SetMemoryStatus)
        {
            ((MEMMAN_devices.staticConfig[nDeviceNumber].SetMemoryStatus)(nStatusMask));
        }

    #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)
    }
    else
    {
        // Program module is not initialized
        ET_ReportDevelopmentError(MEMMAN_moduleID,
                                  SIZE_OF_ARRAY(MEMMAN_moduleID) - 1U,
                                  0U,
                                  MEMMAN_API_ID_SETMEMSTAT,
                                  DEV_ERROR_NOT_INIT);
    }
    #endif // #if (ON == MEMMAN_DEVELOPMENT_ERROR_DETECTION)

} // end of MEMMAN_SetMemoryStatus()



//**************************************************************************************************
//==================================================================================================
// Definitions of local (private) functions
//==================================================================================================
//**************************************************************************************************



//**************************************************************************************************
// @Function      MEMMAN_DeviceCallback()
//--------------------------------------------------------------------------------------------------
// @Description   Calls on every end-of-job memory device event.
//--------------------------------------------------------------------------------------------------
// @Notes         None.
//--------------------------------------------------------------------------------------------------
// @ReturnValue   None.
//--------------------------------------------------------------------------------------------------
// @Parameters    nEventID   - identifier of the memory device event
//                nJobResult - flash job result
//**************************************************************************************************
static void MEMMAN_DeviceCallback(const U8 nEventID,
                                  const U8 nJobResult)
{
    U8 nDeviceNumber = HINIBBLE(nEventID);
    U8 nDeviceEvent  = LONIBBLE(nEventID);

    switch (nDeviceEvent)
    {
        case MEMMAN_READ_EVENT_ID:
            if (MEM_JOB_RESULT_OK == nJobResult)
            {
                MEMMAN_nJobResult = MEM_JOB_RESULT_OK;
            }
            else
            {
                MEMMAN_nJobResult = MEM_JOB_RESULT_NOT_OK;
            }

            // Job complete
            MEMMAN_nCurrentJob = MEMMAN_JOB_IDLE;

            if (NULL_PTR != MEMMAN_pLoadCallback)
            {
                // Notify user
                (MEMMAN_pLoadCallback)(MEMMAN_nLoadCallbackEventID, MEMMAN_nJobResult);
            }
            break;

        case MEMMAN_ERASE_EVENT_ID:
            if (MEM_JOB_RESULT_OK == nJobResult)
            {
                (MEMMAN_devices.staticConfig[nDeviceNumber].SetJobCallback)
                                (MEM_JOB_CALLBACK_WRITE,
                                 MAKEBYTE(MEMMAN_WRITE_EVENT_ID, nDeviceNumber),
                                 MEMMAN_DeviceCallback);

                if (RESULT_OK != (MEMMAN_devices.staticConfig[nDeviceNumber].Write)
                                     (MEMMAN_nTargetAddress,
                                      MEMMAN_pDataBuffer,
                                      MEMMAN_nDataQty))
                {
                    // Job failed
                    MEMMAN_nJobResult  = MEM_JOB_RESULT_NOT_OK;
                    MEMMAN_nCurrentJob = MEMMAN_JOB_IDLE;

                    if (NULL_PTR != MEMMAN_pStoreCallback)
                    {
                        // Notify user
                        (MEMMAN_pStoreCallback)(MEMMAN_nStoreCallbackEventID, MEMMAN_nJobResult);
                    }
                }
            }
            else
            {
                // Job failed
                MEMMAN_nJobResult = MEM_JOB_RESULT_NOT_OK;
                MEMMAN_nCurrentJob = MEMMAN_JOB_IDLE;

                if (NULL_PTR != MEMMAN_pStoreCallback)
                {
                    // Notify user
                    (MEMMAN_pStoreCallback)(MEMMAN_nStoreCallbackEventID, MEMMAN_nJobResult);
                }
            }
            break;

        case MEMMAN_WRITE_EVENT_ID:
            if (MEM_JOB_RESULT_OK == nJobResult)
            {
                MEMMAN_nJobResult = MEM_JOB_RESULT_OK;
            }
            else
            {
                MEMMAN_nJobResult = MEM_JOB_RESULT_NOT_OK;
            }

            // Job complete
            MEMMAN_nCurrentJob = MEMMAN_JOB_IDLE;

            if (NULL_PTR != MEMMAN_pStoreCallback)
            {
                // Notify user
                (MEMMAN_pStoreCallback)(MEMMAN_nStoreCallbackEventID, MEMMAN_nJobResult);
            }
            break;

        default:
            // Should not get here, 'cause there is no other events
            DoNothing();
            break;
    }

} // end of MEMMAN_DeviceCallback()



//****************************************** end of file *******************************************
