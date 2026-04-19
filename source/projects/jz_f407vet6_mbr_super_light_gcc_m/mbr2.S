/**
 * mbr.S - Simple MBR bootloader for STM32F407VE
 * No interrupt disabling - let application handle it
 */

.syntax unified
.cpu cortex-m4
.thumb

/* ============================================================ */
/*  Memory addresses                                           */
/* ============================================================ */
.equ APP_BASE,         0x08060000
.equ SRAM_BASE,        0x20000000
.equ SRAM_END,         0x2001FFFF
.equ FLASH_BASE,       0x08000000
.equ FLASH_END,        0x0807FFFF

/* SCB registers */
.equ SCB_VTOR,         0xE000ED08

/* Peripherals */
.equ RCC_BASE,         0x40023800
.equ GPIOE_BASE,       0x40021000
.equ DWT_BASE,         0xE0001000
.equ DEMCR_BASE,       0xE000EDFC

.equ RCC_AHB1ENR,      0x30
.equ GPIOE_MODER,      0x00
.equ GPIOE_ODR,        0x14
.equ DWT_CTRL,         0x00
.equ DWT_CYCCNT,       0x04
.equ DEMCR_TRCENA,     0x01000000

/* ============================================================ */
/*  Vector table for bootloader                                */
/* ============================================================ */
  .section  .isr_vector,"a",%progbits
  .type  g_pfnVectors, %object
  .size  g_pfnVectors, .-g_pfnVectors


g_pfnVectors:
    .word _estack
    .word Reset_Handler
    .word Default_Handler
    .word HardFault_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word 0
    .word 0
    .word 0
    .word 0
    .word Default_Handler
    .word Default_Handler
    .word 0
    .word Default_Handler
    .word Default_Handler
    .fill 86, 4, 0

.size g_pfnVectors, .-g_pfnVectors

/* ============================================================ */
/*  Default handler                                            */
/* ============================================================ */
.section .text.Default_Handler, "ax"
.weak Default_Handler
.type Default_Handler, %function
Default_Handler:
    b Default_Handler
.size Default_Handler, .-Default_Handler

/* ============================================================ */
/*  HardFault Handler                                          */
/* ============================================================ */
.section .text.HardFault_Handler, "ax"
.global HardFault_Handler
.type HardFault_Handler, %function

HardFault_Handler:
    bl blink_fast
    b HardFault_Handler

.size HardFault_Handler, .-HardFault_Handler

/* ============================================================ */
/*  Delay function                                             */
/* ============================================================ */
.section .text.delay_cycles, "ax"
.type delay_cycles, %function
delay_cycles:
    push {lr}
    ldr r1, =DWT_BASE
    ldr r2, [r1, #DWT_CYCCNT]
    adds r3, r2, r0
delay_loop:
    ldr r2, [r1, #DWT_CYCCNT]
    cmp r2, r3
    blo delay_loop
    pop {pc}

/* ============================================================ */
/*  Fast blink for HardFault (5 blinks)                        */
/* ============================================================ */
.section .text.blink_fast, "ax"
.type blink_fast, %function
blink_fast:
    push {r4-r7, lr}
    
    ldr r0, =RCC_BASE
    ldr r1, [r0, #RCC_AHB1ENR]
    orr r1, r1, #(1 << 4)
    str r1, [r0, #RCC_AHB1ENR]
    
    ldr r0, =GPIOE_BASE
    ldr r1, [r0, #GPIOE_MODER]
    bic r1, r1, #(3 << 26)
    orr r1, r1, #(1 << 26)
    str r1, [r0, #GPIOE_MODER]
    
    ldr r0, =DEMCR_BASE
    ldr r1, [r0]
    orr r1, r1, #DEMCR_TRCENA
    str r1, [r0]
    
    ldr r0, =DWT_BASE
    mov r1, #0
    str r1, [r0, #DWT_CYCCNT]
    ldr r1, [r0, #DWT_CTRL]
    orr r1, r1, #1
    str r1, [r0, #DWT_CTRL]
    
    mov r5, #5
    ldr r6, =GPIOE_BASE
    ldr r4, =1600000   /* 100ms at 16MHz */
    
blink_loop_fast:
    ldr r1, [r6, #GPIOE_ODR]
    orr r1, r1, #(1 << 13)
    str r1, [r6, #GPIOE_ODR]
    
    mov r0, r4
    bl delay_cycles
    
    ldr r1, [r6, #GPIOE_ODR]
    bic r1, r1, #(1 << 13)
    str r1, [r6, #GPIOE_ODR]
    
    mov r0, r4
    bl delay_cycles
    
    subs r5, r5, #1
    bne blink_loop_fast
    
    ldr r0, =8000000   /* 500ms pause */
    bl delay_cycles
    
    pop {r4-r7, pc}

/* ============================================================ */
/*  Single blink at startup                                    */
/* ============================================================ */
.section .text.blink_once, "ax"
.type blink_once, %function
blink_once:
    push {lr}
    
    ldr r0, =RCC_BASE
    ldr r1, [r0, #RCC_AHB1ENR]
    orr r1, r1, #(1 << 4)
    str r1, [r0, #RCC_AHB1ENR]
    
    ldr r0, =GPIOE_BASE
    ldr r1, [r0, #GPIOE_MODER]
    bic r1, r1, #(3 << 26)
    orr r1, r1, #(1 << 26)
    str r1, [r0, #GPIOE_MODER]
    
    ldr r0, =DEMCR_BASE
    ldr r1, [r0]
    orr r1, r1, #DEMCR_TRCENA
    str r1, [r0]
    
    ldr r0, =DWT_BASE
    mov r1, #0
    str r1, [r0, #DWT_CYCCNT]
    ldr r1, [r0, #DWT_CTRL]
    orr r1, r1, #1
    str r1, [r0, #DWT_CTRL]
    
    ldr r0, =GPIOE_BASE
    ldr r1, [r0, #GPIOE_ODR]
    orr r1, r1, #(1 << 13)
    str r1, [r0, #GPIOE_ODR]
    
    ldr r0, =800000   /* 50ms */
    bl delay_cycles
    
    ldr r0, =GPIOE_BASE
    ldr r1, [r0, #GPIOE_ODR]
    bic r1, r1, #(1 << 13)
    str r1, [r0, #GPIOE_ODR]
    
    pop {pc}

/* ============================================================ */
/*  Main Reset Handler                                         */
/* ============================================================ */
.section .text.Reset_Handler, "ax"
.global Reset_Handler
.type Reset_Handler, %function

Reset_Handler:
    /* Set stack pointer */
    ldr r0, =_estack
    mov sp, r0
    
    /* Debug: single blink */
    bl blink_once
    
    /* Check application vector table at APP_BASE */
    ldr r0, =APP_BASE
    
    /* Check 1: Stack pointer in SRAM range */
    ldr r1, [r0]
    ldr r2, =SRAM_BASE
    ldr r3, =SRAM_END
    
    cmp r1, r2
    blo validation_failed
    cmp r1, r3
    bhi validation_failed
    
    /* Check 2: Reset handler in Flash range */
    ldr r4, [r0, #4]
    ldr r2, =FLASH_BASE
    ldr r3, =FLASH_END
    
    mov r5, r4
    bic r5, r5, #1
    
    cmp r5, r2
    blo validation_failed
    cmp r5, r3
    bhi validation_failed
    
    /* Check 3: Thumb bit set */
    tst r4, #1
    beq validation_failed
    
    /* Check 4: First instruction not invalid */
    ldrh r6, [r5]
    mov r7, #0xFF
    orr r7, r7, #0xFF00
    cmp r6, r7
    beq validation_failed
    
    /* ================================================ */
    /*  Validation passed - jump to application         */
    /* ================================================ */

    /* Switch to application stack
    msr msp, r1*/

    /* Clear Thumb bit and jump
    bic r4, r4, #1*/
    bx r4
    
    b .

/* ============================================================ */
/*  Validation failed - blink LED                              */
/* ============================================================ */
validation_failed:
    /* Enable GPIOE clock */
    ldr r0, =RCC_BASE
    ldr r1, [r0, #RCC_AHB1ENR]
    orr r1, r1, #(1 << 4)
    str r1, [r0, #RCC_AHB1ENR]
    
    /* Configure PE13 as output */
    ldr r0, =GPIOE_BASE
    ldr r1, [r0, #GPIOE_MODER]
    bic r1, r1, #(3 << 26)
    orr r1, r1, #(1 << 26)
    str r1, [r0, #GPIOE_MODER]
    
    /* Enable DWT */
    ldr r0, =DEMCR_BASE
    ldr r1, [r0]
    orr r1, r1, #DEMCR_TRCENA
    str r1, [r0]
    
    ldr r0, =DWT_BASE
    mov r1, #0
    str r1, [r0, #DWT_CYCCNT]
    ldr r1, [r0, #DWT_CTRL]
    orr r1, r1, #1
    str r1, [r0, #DWT_CTRL]
    
    ldr r6, =GPIOE_BASE
    ldr r7, =800000   /* 50ms delay */
    
blink_loop:
    ldr r1, [r6, #GPIOE_ODR]
    orr r1, r1, #(1 << 13)
    str r1, [r6, #GPIOE_ODR]
    
    mov r0, r7
    bl delay_cycles
    
    ldr r1, [r6, #GPIOE_ODR]
    bic r1, r1, #(1 << 13)
    str r1, [r6, #GPIOE_ODR]
    
    mov r0, r7
    bl delay_cycles
    
    b blink_loop

.size Reset_Handler, .-Reset_Handler

.pool

/* End of file */
