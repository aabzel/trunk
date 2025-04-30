#ifndef RV32IMC_CONST_H
#define RV32IMC_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

//#define DHCSR (*    ((uint32_t*)0xE000EDF0)
//#define DCRSR (*    ((uint32_t*)0xE000EDF4)
//#define DCRDR (*    ((uint32_t*)0xE000EDF8)
//#define DEMCR (*    ((uint32_t*)0xE000EDFC)

#define BREAKPOINTS_MAX_CNT 8

//Flashpatch and Breakpoint
#define FLASH_PATCH_BASE_ADDRESS (0xE0002000)

#define FLASH_PATCH ( (FlashPatch_t*)FLASH_PATCH_BASE_ADDRESS)

typedef enum{
    FPU_MODE_OFF =0,// No floating-point context active
    FPU_MODE_ON  =1,// Floating-point context active.
}FloatingPoint_t;


// see Table B3-22 Coprocessor Access Control Register– (0xE000ED88)
typedef enum {
    COPROC_ACCESS_DENIED = 0,    // Access denied – generates a NOCP UsageFault
    COPROC_ACCESS_PRIVILEGED = 1,// Privileged access only. User access will generate a NOCP fault.
    COPROC_ACCESS_RESERVED = 2,  // Reserved (UNPREDICTABLE).
    COPROC_ACCESS_FULL = 3,      // Full access
}CoProcAccess_t;


typedef enum{
    PREVENT_EXEPTRION_OFF =0,//
    PREVENT_EXEPTRION_ON  =1,//  Prevents the activation of all exceptions except for NMI.
}FaultMask_t;


typedef enum{
    CUR_MSP =0,// MSP is the current stack pointer
    CUR_PSP =1,// PSP is the current stack pointer.
}StackPointerSel_t;

typedef enum{
    TM_PRIV=0,
    TM_UNPRIV=1,
}ThreadModePrivilegeLevel_t;

#ifdef __cplusplus
}
#endif

#endif /* RV32IMC_CONST_H */
