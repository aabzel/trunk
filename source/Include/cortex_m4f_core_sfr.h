//**************************************************************************************************
// @Module        Cortex-M4F core register file
// @Filename      cortex_m4f_core_sfr.h
//--------------------------------------------------------------------------------------------------
// @Platform      STM32F4
//--------------------------------------------------------------------------------------------------
// @Description   Cortex-M4F core register definitions. Based on PM0214 Rev 10
//                Example instantiation and use:
//                 <MODULE>.<REGISTER>.B.<BIT> = 1;
//                 <MODULE>.<REGISTER>.R       = 0x10000000;
//--------------------------------------------------------------------------------------------------
// @Version       1.2.0
//--------------------------------------------------------------------------------------------------
// @Date          04.07.2022
//--------------------------------------------------------------------------------------------------
// @History       Version  Author      Comment
// 07.06.2022     1.0.0    MAV         First version.
// 22.06.2022     1.1.0    MAV         Added CPU architecture definitions
// 04.07.2022     1.2.0    MAV         Bit fields type changed from vuint32_t to "volatile U32"
//**************************************************************************************************

#ifndef CORTEX_M4F_CORE_SFR_H
#define CORTEX_M4F_CORE_SFR_H

#include "compiler.h"



/******************************************************************************/
/*                     Processor architecture definitions                     */
/******************************************************************************/
// Processor word size
#define CPU_WORD_SIZE        (32U)

// Processor byte order
#define CPU_FIRST_HIGH_BYTE  (0U)              // Big-endian (motorola) format
#define CPU_FIRST_LOW_BYTE   (1U)              // Little-endian (intel) format
#define CPU_BYTE_ORDER       (CPU_FIRST_LOW_BYTE)



/******************************************************************************/
/*       Floating point unit coprocessor access control (FPU) memory map      */
/******************************************************************************/
struct FPU_CP_tag {
    union {
        volatile U32 R;
        struct {
            volatile U32      :20;
            volatile U32 CP10 :2;              // Access privileges for coprocessor 10
            volatile U32 CP11 :2;              // Access privileges for coprocessor 11
            volatile U32      :8;
        } B;
    } CPACR; // Coprocessor access control register (Offset: 0x00; Reset: 0x0000.0000)

}; // end of FPU_CP_tag



/******************************************************************************/
/*                    Floating point unit (FPU) memory map                    */
/******************************************************************************/
struct FPU_tag {
    union {
        volatile U32 R;
        struct {
            volatile U32 LSPACT :1;
            volatile U32 USER   :1;
            volatile U32        :1;
            volatile U32 THREAD :1;
            volatile U32 HFRDY  :1;
            volatile U32 MMRDY  :1;
            volatile U32 BFRDY  :1;
            volatile U32        :1;
            volatile U32 MONRDY :1;
            volatile U32        :21;
            volatile U32 LSPEN  :1;
            volatile U32 ASPEN  :1;
        } B;
    } FPCCR; // Floating-point context control register (Offset: 0x04; Reset: 0xC000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32         :3;
            volatile U32 ADDRESS :29;          // Location of unpopulated floating-point register space allocated on an exception stack frame
        } B;
    } FPCAR; // Floating-point context address register (Offset: 0x08; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 IOC   :1;             // Invalid operation cumulative exception bit
            volatile U32 DZC   :1;             // Division by zero cumulative exception bit
            volatile U32 OFC   :1;             // Overflow cumulative exception bit
            volatile U32 UFC   :1;             // Underflow cumulative exception bit
            volatile U32 IXC   :1;             // Inexact cumulative exception bit
            volatile U32       :2;
            volatile U32 IDC   :1;             // Input denormal cumulative exception bit
            volatile U32       :14;
            volatile U32 RMode :2;             // Rounding Mode control field
            volatile U32 FZ    :1;             // Flush-to-zero mode control bit:
            volatile U32 DN    :1;             // Default NaN mode control bit:
            volatile U32 AHP   :1;             // Alternative half-precision control bit:
            volatile U32       :1;
            volatile U32 V     :1;             // Overflow condition code flag
            volatile U32 C     :1;             // Carry condition code flag
            volatile U32 Z     :1;             // Zero condition code flag
            volatile U32 N     :1;             // Negative condition code flag
        } B;
    } FPDSCR; // Floating-point default status control register (Offset: 0x0C; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32       :22;
            volatile U32 RMode :2;             // Default value for FPSCR.RMode
            volatile U32 FZ    :1;             // Default value for FPSCR.FZ
            volatile U32 DN    :1;             // Default value for FPSCR.DN
            volatile U32 AHP   :1;             // Default value for FPSCR.AHP
            volatile U32       :5;
        } B;
    } FPSCR; // Floating-point status control register (Offset: not mapped; Reset: 0x0000.0000)

}; // end of FPU_tag



/******************************************************************************/
/*                   Memory protection unit (MPU) memory map                  */
/******************************************************************************/
struct MPU_tag {
    union {
        volatile U32 R;
        struct {
            volatile U32 SEPARATE :1;          // Separate flag
            volatile U32          :8;
            volatile U32 DREGION  :7;          // Number of MPU data regions
            volatile U32 IREGION  :8;          // Number of MPU instruction regions
            volatile U32          :8;
        } B;
    } TYPER; // MPU type register (Offset: 0x00; Reset: 0x0000.0800)

    union {
        volatile U32 R;
        struct {
            volatile U32 ENABLE     :1;        // Enables the MPU
            volatile U32 HFNMIENA   :1;        // Enables the operation of MPU during hard fault, NMI, and FAULTMASK handlers
            volatile U32 PRIVDEFENA :1;        // Enable priviliged software access to default memory map
            volatile U32            :29;
        } B;
    } CTRL; // MPU control register (Offset: 0x04; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 REGION :8;            // MPU region
            volatile U32        :24;
        } B;
    } RNR; // MPU region number register (Offset: 0x08; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 REGION :4;            // MPU region field
            volatile U32 VALID  :1;            // MPU region number valid
            volatile U32 ADDR   :27;           // Region base address field
        } B;
    } RBAR; // MPU region base address register (Offset: 0x0C; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 ENABLE :1;            // Region enable bit
            volatile U32 SIZE   :5;            // Size of the MPU protection region
            volatile U32        :2;
            volatile U32 SRD    :8;            // Subregion disable bits
            volatile U32 B      :1;            // Memory attribute
            volatile U32 C      :1;            // Memory attribute
            volatile U32 S      :1;            // Shareable memory attribute
            volatile U32 TEX    :3;            // Memory attribute
            volatile U32        :2;
            volatile U32 AP     :3;            // Access permission
            volatile U32        :1;
            volatile U32 XN     :1;            // Instruction access disable bit:
            volatile U32        :3;
        } B;
    } RASR; // MPU region attribute and size register (Offset: 0x10; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 REGION :4;            // MPU region field
            volatile U32 VALID  :1;            // MPU region number valid
            volatile U32 ADDR   :27;           // Region base address field
        } B;
    } RBAR_A1; // MPU region base address register alias 1 (Offset: 0x14; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 ENABLE :1;            // Region enable bit
            volatile U32 SIZE   :5;            // Size of the MPU protection region
            volatile U32        :2;
            volatile U32 SRD    :8;            // Subregion disable bits
            volatile U32 B      :1;            // Memory attribute
            volatile U32 C      :1;            // Memory attribute
            volatile U32 S      :1;            // Shareable memory attribute
            volatile U32 TEX    :3;            // Memory attribute
            volatile U32        :2;
            volatile U32 AP     :3;            // Access permission
            volatile U32        :1;
            volatile U32 XN     :1;            // Instruction access disable bit:
            volatile U32        :3;
        } B;
    } RASR_A1; // MPU region attribute and size register alias 1 (Offset: 0x18; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 REGION :4;            // MPU region field
            volatile U32 VALID  :1;            // MPU region number valid
            volatile U32 ADDR   :27;           // Region base address field
        } B;
    } RBAR_A2; // MPU region base address register alias 2 (Offset: 0x1C; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 ENABLE :1;            // Region enable bit
            volatile U32 SIZE   :5;            // Size of the MPU protection region
            volatile U32        :2;
            volatile U32 SRD    :8;            // Subregion disable bits
            volatile U32 B      :1;            // Memory attribute
            volatile U32 C      :1;            // Memory attribute
            volatile U32 S      :1;            // Shareable memory attribute
            volatile U32 TEX    :3;            // Memory attribute
            volatile U32        :2;
            volatile U32 AP     :3;            // Access permission
            volatile U32        :1;
            volatile U32 XN     :1;            // Instruction access disable bit:
            volatile U32        :3;
        } B;
    } RASR_A2; // MPU region attribute and size register alias 2 (Offset: 0x20; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 REGION :4;            // MPU region field
            volatile U32 VALID  :1;            // MPU region number valid
            volatile U32 ADDR   :27;           // Region base address field
        } B;
    } RBAR_A3; // MPU region base address register alias 3 (Offset: 0x24; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 ENABLE :1;            // Region enable bit
            volatile U32 SIZE   :5;            // Size of the MPU protection region
            volatile U32        :2;
            volatile U32 SRD    :8;            // Subregion disable bits
            volatile U32 B      :1;            // Memory attribute
            volatile U32 C      :1;            // Memory attribute
            volatile U32 S      :1;            // Shareable memory attribute
            volatile U32 TEX    :3;            // Memory attribute
            volatile U32        :2;
            volatile U32 AP     :3;            // Access permission
            volatile U32        :1;
            volatile U32 XN     :1;            // Instruction access disable bit:
            volatile U32        :3;
        } B;
    } RASR_A3; // MPU region attribute and size register alias 3 (Offset: 0x28; Reset: 0x0000.0000)

}; // end of MPU_tag



/******************************************************************************/
/*           Nested vectored interrupt controller (NVIC) memory map           */
/******************************************************************************/
struct NVIC_tag {
    union {
        volatile U32 R;
        struct {
            volatile U32 SETENA :32;           // Interrupt set-enable bits
        } B;
    } ISER[8]; // Interrupt set-enable register (Offset: 0x000-0x01F; Reset: 0x0000.0000)

    U32 NVIC_Reserved0[24U];                   // Reserved: 0x020-0x079

    union {
        volatile U32 R;
        struct {
            volatile U32 CLRENA :32;           // Interrupt clear-enable bits
        } B;
    } ICER[8]; // Interrupt clear-enable register (Offset: 0x080-0x09F; Reset: 0x0000.0000)

    U32 NVIC_Reserved1[24U];                   // Reserved: 0x0A0-0x0FF

    union {
        volatile U32 R;
        struct {
            volatile U32 SETPEND :32;          // Interrupt set-pending bits
        } B;
    } ISPR[8]; // Interrupt set-pending register (Offset: 0x100-0x11F; Reset: 0x0000.0000)

    U32 NVIC_Reserved2[24U];                   // Reserved: 0x120-0x17F

    union {
        volatile U32 R;
        struct {
            volatile U32 CLRPEND :32;          // Interrupt clear-pending bits
        } B;
    } ICPR[8]; // Interrupt clear-pending register (Offset: 0x180-0x19F; Reset: 0x0000.0000)

    U32 NVIC_Reserved3[24U];                   // Reserved: 0x1A0-0x1FF

    union {
        volatile U32 R;
        struct {
            volatile U32 ACTIVE :32;           // Interrupt active flags
        } B;
    } IABR[8]; // Interrupt active bit register (Offset: 0x200-0x21F; Reset: 0x0000.0000)

    U32 NVIC_Reserved4[56U];                   // Reserved: 0x220-0x2FF

    volatile U8 IPR[240];                      // Interrupt priority register (Offset: 0x300-0x3EF; Reset: 0x0000.0000)

    U32 NVIC_Reserved5[644U];                  // Reserved: 0x3F0-0xDFF

    union {
        volatile U32 R;
        struct {
            volatile U32 INTID :9;             // Software generated interrupt ID
            volatile U32       :23;
        } B;
    } STIR; // Software trigger interrupt register (Offset: 0xE00; Reset: 0x0000.0000)

}; // end of NVIC_tag



/******************************************************************************/
/*                    System control block (SCB) memory map                   */
/******************************************************************************/
struct SCB_tag {
    U32 SCB_Reserved0[2U];             // Reserved: 0x000-0x007

    union {
        volatile U32 R;
        struct {
            volatile U32 DISMCYCINT :1;        // Disables interrupt of multi-cycle instructions
            volatile U32 DISDEFWBUF :1;        // This bit only affects write buffers implemented in the Cortex-M4 processor
            volatile U32 DISFOLD    :1;        // Disables folding of IT instructions
            volatile U32            :5;
            volatile U32 DISFPCA    :1;        // Disables automatic update of CONTROL.FPCA
            volatile U32 DISOOFP    :1;        // Disables floating point instructions completing out of order with respect to integer instructions
            volatile U32            :22;
        } B;
    } ACTLR; // Auxiliary control register (Offset: 0x008; Reset: 0x0000.0000)

    U32 SCB_Reserved1[829U];           // Reserved: 0x00C-0xCFF

    union {
        volatile U32 R;
        struct {
            volatile U32 Revision    :4;       // Revision number
            volatile U32 PartNo      :12;      // Part number of the processor (0xC24: Cortex-M4)
            volatile U32 Constant    :4;       // Reads as 0xF
            volatile U32 Variant     :4;       // Variant number
            volatile U32 Implementer :8;       // Implementer code (0x41: Arm)
        } B;
    } CPUID; // CPUID base register (Offset: 0xD00; Reset: 0x410F.C241)

    union {
        volatile U32 R;
        struct {
            volatile U32 VECTACTIVE  :9;       // Contains the active exception number
            volatile U32             :2;
            volatile U32 RETTOBASE   :1;       // Indicates whether there are preempted active exceptions
            volatile U32 VECTPENDING :10;      // Indicates the exception number of the highest priority pending enabled exception
            volatile U32 ISRPENDING  :1;       // Interrupt pending flag, excluding NMI and Faults
            volatile U32             :2;
            volatile U32 PENDSTCLR   :1;       // SysTick exception clear-pending bit
            volatile U32 PENDSTSET   :1;       // SysTick exception set-pending bit
            volatile U32 PENDSVCLR   :1;       // PendSV clear-pending bit
            volatile U32 PENDSVSET   :1;       // PendSV set-pending bit
            volatile U32             :2;
            volatile U32 NMIPENDSET  :1;       // NMI set-pending bit
        } B;
    } ICSR; // Interrupt control and state register (Offset: 0xD04; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32        :9;
            volatile U32 TBLOFF :21;           // Vector table base offset field
            volatile U32        :2;
        } B;
    } VTOR; // Vector table offset register (Offset: 0xD08; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 VECTRESET     :1;     // Reserved for Debug use. This bit reads as 0
            volatile U32 VECTCLRACTIVE :1;     // Reserved for Debug use. This bit reads as 0
            volatile U32 SYSRESETREQ   :1;     // System reset request bit is implementation defined
            volatile U32               :5;
            volatile U32 PRIGROUP      :3;     // Interrupt priority grouping field is implementation defined
            volatile U32               :4;
            volatile U32 ENDIANNESS    :1;     // Data endianness bit is implementation defined
            volatile U32 VECTKEY       :16;    // Register key
        } B;
    } AIRCR; // Application interrupt and reset control register (Offset: 0xD0C; Reset: 0xFA05.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32             :1;
            volatile U32 SLEEPONEXIT :1;       // Indicates sleep-on-exit when returning from Handler mode to Thread mode
            volatile U32 SLEEPDEEP   :1;       // Controls whether the processor uses sleep or deep sleep as its low power mode
            volatile U32             :1;
            volatile U32 SEVONPEND   :1;       // Send Event on Pending bit
            volatile U32             :27;
        } B;
    } SCR; // System control register (Offset: 0xD10; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 NONBASETHRDENA :1;    // Indicates how the processor enters Thread mode
            volatile U32 USERSETMPEND   :1;    // Enables unprivileged software access to the STIR
            volatile U32                :1;
            volatile U32 UNALIGN_TRP    :1;    // Enables unaligned access traps
            volatile U32 DIV_0_TRP      :1;    // Enables faulting or halting when the processor executes an SDIV or UDIV instruction with a divisor of 0
            volatile U32                :3;
            volatile U32 BFHFNMIGN      :1;    // Enables handlers with priority -1 or -2 to ignore data BusFaults caused by load and store instructions
            volatile U32 STKALIGN       :1;    // Indicates stack alignment on exception entry
            volatile U32                :22;
        } B;
    } CCR; // Configuration and control register (Offset: 0xD14; Reset: 0x0000.0200)

    union {
        volatile U32 R;
        struct {
            volatile U32 PRI_4 :8;             // Priority of system handler 4, MemManage
            volatile U32 PRI_5 :8;             // Priority of system handler 5, BusFault
            volatile U32 PRI_6 :8;             // Priority of system handler 6, UsageFault
            volatile U32       :8;
        } B;
    } SHPR1; // System handler priority register 1 (Offset: 0xD18; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32        :24;
            volatile U32 PRI_11 :8;            // Priority of system handler 11, SVCall
        } B;
    } SHPR2; // System handler priority register 2 (Offset: 0xD1C; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32        :16;
            volatile U32 PRI_14 :8;            // Priority of system handler 14, PendSV
            volatile U32 PRI_15 :8;            // Priority of system handler 15, SysTick exception
        } B;
    } SHPR3; // System handler priority register 3 (Offset: 0xD20; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 MEMFAULTACT    :1;    // MemManage exception active bit
            volatile U32 BUSFAULTACT    :1;    // BusFault exception active bit
            volatile U32                :1;
            volatile U32 USGFAULTACT    :1;    // UsageFault exception active bit
            volatile U32                :3;
            volatile U32 SVCALLACT      :1;    // SVCall active bit
            volatile U32 MONITORACT     :1;    // Debug monitor active bit
            volatile U32                :1;
            volatile U32 PENDSVACT      :1;    // PendSV exception active bit
            volatile U32 SYSTICKACT     :1;    // SysTick exception active bit
            volatile U32 USGFAULTPENDED :1;    // UsageFault exception pending bit
            volatile U32 MEMFAULTPENDED :1;    // MemManage exception pending bit
            volatile U32 BUSFAULTPENDED :1;    // BusFault exception pending bit
            volatile U32 SVCALLPENDED   :1;    // SVCall pending bit
            volatile U32 MEMFAULTENA    :1;    // MemManage enable bit
            volatile U32 BUSFAULTENA    :1;    // BusFault enable bit
            volatile U32 USGFAULTENA    :1;    // UsageFault enable bit
            volatile U32                :13;
        } B;
    } SHCSR; // System handler control and state register (Offset: 0xD24; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 IACCVIOL    :1;       // Instruction access violation flag
            volatile U32 DACCVIOL    :1;       // Data access violation flag
            volatile U32             :1;
            volatile U32 MUNSTKERR   :1;       // MemManage fault on unstacking for a return from exception
            volatile U32 MSTKERR     :1;       // MemManage fault on stacking for exception entry
            volatile U32 MLSPERR     :1;       // MemManage fault on floating-point lazy state
            volatile U32             :1;
            volatile U32 MMARVALID   :1;       // MemManage Fault Address Register (MMFAR) valid flag
            volatile U32 IBUSERR     :1;       // Instruction bus error
            volatile U32 PRECISERR   :1;       // Precise data bus error
            volatile U32 IMPRECISERR :1;       // Imprecise data bus error
            volatile U32 UNSTKERR    :1;       // BusFault on unstacking for a return from exception
            volatile U32 STKERR      :1;       // BusFault on stacking for exception entry
            volatile U32 LSPERR      :1;       // Bus fault on floating-point lazy state preservation
            volatile U32             :1;
            volatile U32 BFARVALID   :1;       // BusFault Address Register (BFAR) valid flag
            volatile U32 UNDEFINSTR  :1;       // Undefined instruction UsageFault
            volatile U32 INVSTATE    :1;       // Invalid state UsageFault
            volatile U32 INVPC       :1;       // Invalid PC load UsageFault
            volatile U32 NOCP        :1;       // No coprocessor UsageFault
            volatile U32             :4;
            volatile U32 UNALIGNED   :1;       // Unaligned access UsageFault
            volatile U32 DIVBYZERO   :1;       // Divide by zero UsageFault
            volatile U32             :6;
        } B;
    } CFSR; // Configurable fault status register (Offset: 0xD28; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32          :1;
            volatile U32 VECTTBL  :1;          // Indicates a BusFault on a vector table read during exception processing
            volatile U32          :28;
            volatile U32 FORCED   :1;          // Indicates a forced hard fault
            volatile U32 DEBUG_VT :1;          // Reserved for Debug use
        } B;
    } HFSR; // Hard fault status register (Offset: 0xD2C; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 MMFAR :32;            // The MMFAR contains the address of the location that generated a MemManage fault
        } B;
    } MMFAR; // Memory management fault address register (Offset: 0xD34; Reset: 0xXXXX.XXXX)

    union {
        volatile U32 R;
        struct {
            volatile U32 BFAR :32;             // The BFAR contains the address of the location that generated a BusFault
        } B;
    } BFAR; // Bus fault address register (Offset: 0xD38; Reset: 0xXXXX.XXXX)

    union {
        volatile U32 R;
        struct {
            volatile U32 IMPDEF :32;           // The bits map to the AUXFAULT input signals
        } B;
    } AFSR; // Auxiliary fault status register (Offset: 0xD3C; Reset: 0x0000.0000)

}; // end of SCB_tag



/******************************************************************************/
/*                       SysTick timer (STK) memory map                       */
/******************************************************************************/
struct STK_tag {
    union {
        volatile U32 R;
        struct {
            volatile U32 ENABLE    :1;         // Counter enable
            volatile U32 TICKINT   :1;         // SysTick exception request enable
            volatile U32 CLKSOURCE :1;         // Clock source selection
            volatile U32           :13;
            volatile U32 COUNTFLAG :1;         // Returns 1 if timer counted to 0 since last time this was read
            volatile U32           :15;
        } B;
    } CTRL; // SysTick control and status register (Offset: 0x00; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 RELOAD :24;           // Reload value
            volatile U32        :8;
        } B;
    } LOAD; // SysTick reload value register (Offset: 0x04; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 CURRENT :24;          // Current counter value
            volatile U32         :8;
        } B;
    } VAL; // SysTick current value register (Offset: 0x08; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 TENMS :24;            // Calibration value
            volatile U32       :6;
            volatile U32 SKEW  :1;             // SKEW flag: Indicates whether the TENMS value is exact. Reads as one
            volatile U32 NOREF :1;             // NOREF flag. Reads as zero. Indicates that a separate reference clock is provided
        } B;
    } CALIB; // SysTick calibration value register (Offset: 0x0C; Reset: 0x0000.0000)

}; // end of STK_tag



// FPU Coprocessor access
#define FPU_COPROC           (*(volatile struct FPU_CP_tag *)        0xE000ED88UL)

// FPU
#define FPU                  (*(volatile struct FPU_tag *)           0xE000EF30UL)

// MPU
#define MPU                  (*(volatile struct MPU_tag *)           0xE000ED90UL)

// NVIC
#define NVIC                 (*(volatile struct NVIC_tag *)          0xE000E100UL)

// SCB
#define SCB                  (*(volatile struct SCB_tag *)           0xE000E000UL)

// STK
#define STK                  (*(volatile struct STK_tag *)           0xE000E010UL)



#endif // CORTEX_M4F_CORE_SFR_H
