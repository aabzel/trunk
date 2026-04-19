/**
 * mbr_bootloader.s - Ultra-compact MBR bootloader for STM32F407VE
 * Runs at 16MHz (HSI), checks vector table at 0x08060000
 * Jumps there or blinks LED on PE13 at 10Hz
 *
 * Target: STM32F407VE (512KB Flash)
 * CPU: 16MHz HSI (no PLL, no external crystal)
 * Application start: 0x08060000 (Sector 7)
 */

.syntax unified
.cpu cortex-m4
.thumb

/* ============================================================ */
/*  Memory addresses                                           */
/* ============================================================ */
.equ APP_BASE,         0x08060000
.equ SRAM_BASE,        0x20000000
.equ SRAM_END,         0x2001FFFF      /* 128KB for STM32F407VE */
.equ FLASH_BASE,       0x08000000
.equ FLASH_END,        0x0807FFFF      /* 512KB */

/* ============================================================ */
/*  Peripheral addresses (direct access, no HAL)               */
/* ============================================================ */
.equ RCC_BASE,         0x40023800
.equ GPIOE_BASE,       0x40021000
.equ DWT_BASE,         0xE0001000
.equ DEMCR_BASE,       0xE000EDFC      /* Debug Exception Monitor Control Register */

.equ RCC_AHB1ENR,      0x30            /* Offset from RCC_BASE */
.equ GPIOE_MODER,      0x00            /* Offset from GPIOE_BASE */
.equ GPIOE_ODR,        0x14            /* Offset from GPIOE_BASE */
.equ DWT_CTRL,         0x00            /* Offset from DWT_BASE */
.equ DWT_CYCCNT,       0x04            /* Offset from DWT_BASE */
.equ DEMCR_TRCENA,     (1 << 24)       /* Enable trace in DEMCR */

/* ============================================================ */
/*  Vector table definition (for bootloader itself)            */
/* ============================================================ */
.section .vectors, "ax"
.global g_pfnVectors
.type g_pfnVectors, %object

g_pfnVectors:
    .word _estack                    /* Initial stack pointer */
    .word Reset_Handler              /* Reset handler */
    .word Default_Handler            /* NMI */
    .word Default_Handler            /* HardFault */
    .word Default_Handler            /* MemManage */
    .word Default_Handler            /* BusFault */
    .word Default_Handler            /* UsageFault */
    .word 0                          /* Reserved */
    .word 0                          /* Reserved */
    .word 0                          /* Reserved */
    .word 0                          /* Reserved */
    .word Default_Handler            /* SVC */
    .word Default_Handler            /* DebugMon */
    .word 0                          /* Reserved */
    .word Default_Handler            /* PendSV */
    .word Default_Handler            /* SysTick */
    /* Fill rest with zeros for simplicity */
    .fill 86, 4, 0

.size g_pfnVectors, .-g_pfnVectors

/* ============================================================ */
/*  Default handler for all interrupts (infinite loop)         */
/* ============================================================ */
.section .text.Default_Handler, "ax"
.weak Default_Handler
.type Default_Handler, %function
Default_Handler:
    b Default_Handler
.size Default_Handler, .-Default_Handler

/* ============================================================ */
/*  Main Reset Handler                                         */
/* ============================================================ */
.section .text.Reset_Handler, "ax"
.global Reset_Handler
.type Reset_Handler, %function

Reset_Handler:
    /* Set stack pointer immediately */
    ldr r0, =_estack
    mov sp, r0
    
    /* ======================================================== */
    /*  Check application vector table at APP_BASE             */
    /* ======================================================== */
    ldr r0, =APP_BASE          /* R0 = pointer to application vector table */
    
    /* Check 1: Stack pointer must be in SRAM range */
    ldr r1, [r0]               /* R1 = application stack pointer */
    ldr r2, =SRAM_BASE
    ldr r3, =SRAM_END
    cmp r1, r2
    blo validation_failed
    cmp r1, r3
    bhi validation_failed
    
    /* Check 2: Reset handler must be in Flash range */
    ldr r4, [r0, #4]           /* R4 = application reset handler address */
    ldr r2, =FLASH_BASE
    ldr r3, =FLASH_END
    mov r5, r4
    bic r5, r5, #1             /* Clear Thumb bit for address check */
    cmp r5, r2
    blo validation_failed
    cmp r5, r3
    bhi validation_failed
    
    /* Check 3: Must be Thumb mode (LSB = 1) */
    tst r4, #1
    beq validation_failed
    
    /* Validation passed - jump to application */
    msr msp, r1                /* Set main stack pointer to app's SP */
    bic r4, r4, #1             /* Clear LSB for function call */
    bx r4                      /* Jump to application reset handler */
    
    /* Should never reach here */
    b .

/* ============================================================ */
/*  Validation failed - blink LED on PE13 at 10Hz              */
/*  CPU runs at 16MHz HSI (16,000,000 cycles per second)       */
/*  10Hz = 100ms period = 50ms on, 50ms off                    */
/*  50ms at 16MHz = 800,000 cycles                             */
/* ============================================================ */
validation_failed:
    /* Enable GPIOE clock (RCC AHB1ENR, bit 4) */
    ldr r0, =RCC_BASE
    ldr r1, [r0, #RCC_AHB1ENR]
    orr r1, r1, #(1 << 4)
    str r1, [r0, #RCC_AHB1ENR]
    
    /* Configure PE13 as output (MODER bits 26-27 = 01) */
    ldr r0, =GPIOE_BASE
    ldr r1, [r0, #GPIOE_MODER]
    bic r1, r1, #(3 << 26)     /* Clear bits 26-27 */
    orr r1, r1, #(1 << 26)     /* Set as output (01) */
    str r1, [r0, #GPIOE_MODER]
    
    /* Enable DWT cycle counter */
    /* First, enable TRCENA in DEMCR */
    ldr r0, =DEMCR_BASE
    ldr r1, [r0]
    orr r1, r1, #DEMCR_TRCENA
    str r1, [r0]
    
    /* Enable DWT cycle counter */
    ldr r0, =DWT_BASE
    ldr r1, [r0, #DWT_CTRL]
    orr r1, r1, #1
    str r1, [r0, #DWT_CTRL]
    
    /* Reset cycle counter to 0 */
    mov r1, #0
    str r1, [r0, #DWT_CYCCNT]

    /* Delay constant for 50ms at 16MHz = 800,000 cycles */
    .equ DELAY_50MS, 800000

blink_loop:
    /* Turn LED on (PE13 high) */
    ldr r0, =GPIOE_BASE
    ldr r1, [r0, #GPIOE_ODR]
    orr r1, r1, #(1 << 13)
    str r1, [r0, #GPIOE_ODR]
    
    /* Delay 50ms */
    ldr r0, =DWT_BASE
    ldr r2, [r0, #DWT_CYCCNT]  /* Get start count */
    ldr r3, =DELAY_50MS
    add r3, r3, r2              /* End count = start + 800,000 */
delay_on:
    ldr r4, [r0, #DWT_CYCCNT]
    cmp r4, r3
    blo delay_on
    
    /* Turn LED off (PE13 low) */
    ldr r0, =GPIOE_BASE
    ldr r1, [r0, #GPIOE_ODR]
    bic r1, r1, #(1 << 13)
    str r1, [r0, #GPIOE_ODR]
    
    /* Delay 50ms */
    ldr r0, =DWT_BASE
    ldr r2, [r0, #DWT_CYCCNT]  /* Get start count */
    ldr r3, =DELAY_50MS
    add r3, r3, r2              /* End count = start + 800,000 */
delay_off:
    ldr r4, [r0, #DWT_CYCCNT]
    cmp r4, r3
    blo delay_off
    
    b blink_loop

.size Reset_Handler, .-Reset_Handler

/* End of file */
