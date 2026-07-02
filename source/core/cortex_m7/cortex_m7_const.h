#ifndef CORTEX_M7_CONST_H
#define CORTEX_M7_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    FPU_MODE_OFF = 0, // No floating-point context active
    FPU_MODE_ON = 1, // Floating-point context active.
} FloatingPoint_t;

typedef enum {
    PREVENT_EXEPTRION_OFF = 0, //
    PREVENT_EXEPTRION_ON = 1, //  Prevents the activation of all exceptions except for NMI.
} FaultMask_t;

typedef enum {
    CUR_MSP = 0, // MSP is the current stack pointer
    CUR_PSP = 1, // PSP is the current stack pointer.
} StackPointerSel_t;

typedef enum {
    TM_PRIV = 0, TM_UNPRIV = 1,
} ThreadModePrivilegeLevel_t;

#ifdef __cplusplus
}
#endif

#endif /* CORTEX_M7_CONST_H */
