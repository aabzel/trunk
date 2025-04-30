/*
	NRF52840 Startup
*/
  .syntax unified
  .arch armv8-m.main


.global  g_pfnVectors
.global  Default_Handler

/* start address for the initialization values of the .data section. 
defined in linker script */
.word  _sidata
/* start address for the .data section. defined in linker script */  
.word  _sdata
/* end address for the .data section. defined in linker script */
.word  _edata
/* start address for the .bss section. defined in linker script */
.word  _sbss
/* end address for the .bss section. defined in linker script */
.word  _ebss
/* stack used for SystemInit_ExtMemCtl; always internal RAM used */

/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called. 
 * @param  None
 * @retval : None
*/

    .section  .text.Reset_Handler
  .weak  Reset_Handler
  .type  Reset_Handler, %function
Reset_Handler: 
  ldr   sp, =_estack       /* set stack pointer */
 
/* Copy the data segment initializers from flash to SRAM */  
  movs  r1, #0
  b  LoopCopyDataInit

CopyDataInit:
  ldr  r3, =_sidata
  ldr  r3, [r3, r1]
  str  r3, [r0, r1]
  adds  r1, r1, #4
    
LoopCopyDataInit:
  ldr  r0, =_sdata
  ldr  r3, =_edata
  adds  r2, r0, r1
  cmp  r2, r3
  bcc  CopyDataInit
  ldr  r2, =_sbss
  b  LoopFillZerobss
/* Zero fill the bss segment. */  
FillZerobss:
  movs  r3, #0
  str  r3, [r2], #4
    
LoopFillZerobss:
  ldr  r3, = _ebss
  cmp  r2, r3
  bcc  FillZerobss

/* Call the clock system intitialization function.*/
  bl  SystemInit
/* Call static constructors */
    bl __libc_init_array
/* Call the application's entry point.*/
  bl  main
  bx  lr    
.size  Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an 
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 * @param  None     
 * @retval None       
*/
    .section  .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b  Infinite_Loop
  .size  Default_Handler, .-Default_Handler
/******************************************************************************
*
* The minimal vector table for a Cortex M3. Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
* 
*******************************************************************************/
   .section  .isr_vector,"a",%progbits
  .type  g_pfnVectors, %object
  .size  g_pfnVectors, .-g_pfnVectors
   
g_pfnVectors:
  .word  _estack
  .word  Reset_Handler

  .word  NMI_Handler
  .word  HardFault_Handler
  .word  MemManage_Handler
  .word  BusFault_Handler
  .word  UsageFault_Handler
  .word  SecureFault_Handler
  .word  0
  .word  0
  .word  0
  .word  SVC_Handler
  .word  DebugMon_Handler
  .word  0
  .word  PendSV_Handler
  .word  SysTick_Handler
  
  /* External Interrupts */
    .long   FPU_IRQHandler
    .long   CACHE_IRQHandler
    .long   0                           /*Reserved */
    .long   SPU_IRQHandler
    .long   0                           /*Reserved */
    .long   CLOCK_POWER_IRQHandler
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   SPIM0_SPIS0_TWIM0_TWIS0_UARTE0_IRQHandler
    .long   SPIM1_SPIS1_TWIM1_TWIS1_UARTE1_IRQHandler
    .long   SPIM4_IRQHandler
    .long   SPIM2_SPIS2_TWIM2_TWIS2_UARTE2_IRQHandler
    .long   SPIM3_SPIS3_TWIM3_TWIS3_UARTE3_IRQHandler
    .long   GPIOTE0_IRQHandler
    .long   SAADC_IRQHandler
    .long   TIMER0_IRQHandler
    .long   TIMER1_IRQHandler
    .long   TIMER2_IRQHandler
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   RTC0_IRQHandler
    .long   RTC1_IRQHandler
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   WDT0_IRQHandler
    .long   WDT1_IRQHandler
    .long   COMP_LPCOMP_IRQHandler
    .long   EGU0_IRQHandler
    .long   EGU1_IRQHandler
    .long   EGU2_IRQHandler
    .long   EGU3_IRQHandler
    .long   EGU4_IRQHandler
    .long   EGU5_IRQHandler
    .long   PWM0_IRQHandler
    .long   PWM1_IRQHandler
    .long   PWM2_IRQHandler
    .long   PWM3_IRQHandler
    .long   0                           /*Reserved */
    .long   PDM0_IRQHandler
    .long   0                           /*Reserved */
    .long   I2S0_IRQHandler
    .long   0                           /*Reserved */
    .long   IPC_IRQHandler
    .long   QSPI_IRQHandler
    .long   0                           /*Reserved */
    .long   NFCT_IRQHandler
    .long   0                           /*Reserved */
    .long   GPIOTE1_IRQHandler
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   QDEC0_IRQHandler
    .long   QDEC1_IRQHandler
    .long   0                           /*Reserved */
    .long   USBD_IRQHandler
    .long   USBREGULATOR_IRQHandler
    .long   0                           /*Reserved */
    .long   KMU_IRQHandler
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   CRYPTOCELL_IRQHandler
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */
    .long   0                           /*Reserved */

  
/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler. 
* As they are weak aliases, any function with the same name will override 
* this definition.
* 
*******************************************************************************/
   .weak      NMI_Handler
   .thumb_set NMI_Handler,Default_Handler
  
   .weak      HardFault_Handler
   .thumb_set HardFault_Handler,Default_Handler
  
   .weak      MemManage_Handler
   .thumb_set MemManage_Handler,Default_Handler
  
   .weak      BusFault_Handler
   .thumb_set BusFault_Handler,Default_Handler

   .weak      UsageFault_Handler
   .thumb_set UsageFault_Handler,Default_Handler

   .weak      SecureFault_Handler
   .thumb_set SecureFault_Handler,Default_Handler

   .weak      SVC_Handler
   .thumb_set SVC_Handler,Default_Handler

   .weak      DebugMon_Handler
   .thumb_set DebugMon_Handler,Default_Handler

   .weak      PendSV_Handler
   .thumb_set PendSV_Handler,Default_Handler

   .weak      SysTick_Handler
   .thumb_set SysTick_Handler,Default_Handler              
  






   .weak      FPU_IRQHandler
   .thumb_set FPU_IRQHandler,Default_Handler
                  
   .weak      CACHE_IRQHandler
   .thumb_set CACHE_IRQHandler,Default_Handler
               
   .weak      SPU_IRQHandler
   .thumb_set SPU_IRQHandler,Default_Handler
            
   .weak      CLOCK_POWER_IRQHandler
   .thumb_set CLOCK_POWER_IRQHandler,Default_Handler
            
   .weak      SPIM0_SPIS0_TWIM0_TWIS0_UARTE0_IRQHandler
   .thumb_set SPIM0_SPIS0_TWIM0_TWIS0_UARTE0_IRQHandler,Default_Handler
                  
   .weak      SPIM1_SPIS1_TWIM1_TWIS1_UARTE1_IRQHandler
   .thumb_set SPIM1_SPIS1_TWIM1_TWIS1_UARTE1_IRQHandler,Default_Handler
                  
   .weak      SPIM4_IRQHandler
   .thumb_set SPIM4_IRQHandler,Default_Handler
                  
   .weak      SPIM2_SPIS2_TWIM2_TWIS2_UARTE2_IRQHandler
   .thumb_set SPIM2_SPIS2_TWIM2_TWIS2_UARTE2_IRQHandler,Default_Handler

   .weak      SPIM3_SPIS3_TWIM3_TWIS3_UARTE3_IRQHandler
   .thumb_set SPIM3_SPIS3_TWIM3_TWIS3_UARTE3_IRQHandler,Default_Handler

   .weak      GPIOTE0_IRQHandler
   .thumb_set GPIOTE0_IRQHandler,Default_Handler

   .weak      SAADC_IRQHandler
   .thumb_set SAADC_IRQHandler,Default_Handler

   .weak      TIMER0_IRQHandler
   .thumb_set TIMER0_IRQHandler,Default_Handler

   .weak      TIMER1_IRQHandler
   .thumb_set TIMER1_IRQHandler,Default_Handler

   .weak      TIMER2_IRQHandler
   .thumb_set TIMER2_IRQHandler,Default_Handler
                  
   .weak      RTC0_IRQHandler
   .thumb_set RTC0_IRQHandler,Default_Handler
                 
   .weak      RTC1_IRQHandler
   .thumb_set RTC1_IRQHandler,Default_Handler
                  
   .weak      WDT0_IRQHandler
   .thumb_set WDT0_IRQHandler,Default_Handler
                  
   .weak      WDT1_IRQHandler
   .thumb_set WDT1_IRQHandler,Default_Handler
                  
   .weak      COMP_LPCOMP_IRQHandler
   .thumb_set COMP_LPCOMP_IRQHandler,Default_Handler

   .weak      EGU0_IRQHandler
   .thumb_set EGU0_IRQHandler,Default_Handler
            
   .weak      EGU1_IRQHandler
   .thumb_set EGU1_IRQHandler,Default_Handler
                           
   .weak      EGU2_IRQHandler
   .thumb_set EGU2_IRQHandler,Default_Handler
            
   .weak      EGU3_IRQHandler
   .thumb_set EGU3_IRQHandler,Default_Handler
            
   .weak      EGU4_IRQHandler
   .thumb_set EGU4_IRQHandler,Default_Handler
            
   .weak      EGU5_IRQHandler
   .thumb_set EGU5_IRQHandler,Default_Handler
            
   .weak      PWM0_IRQHandler
   .thumb_set PWM0_IRQHandler,Default_Handler

   .weak      PWM1_IRQHandler
   .thumb_set PWM1_IRQHandler,Default_Handler
      
   .weak      PWM2_IRQHandler
   .thumb_set PWM2_IRQHandler,Default_Handler
                  
   .weak      PWM3_IRQHandler
   .thumb_set PWM3_IRQHandler,Default_Handler
                  
   .weak      PDM0_IRQHandler
   .thumb_set PDM0_IRQHandler,Default_Handler
                  
   .weak      I2S0_IRQHandler
   .thumb_set I2S0_IRQHandler,Default_Handler
                  
   .weak      IPC_IRQHandler
   .thumb_set IPC_IRQHandler,Default_Handler
                     
   .weak      QSPI_IRQHandler
   .thumb_set QSPI_IRQHandler,Default_Handler
                     
   .weak      NFCT_IRQHandler
   .thumb_set NFCT_IRQHandler,Default_Handler
                  
   .weak      GPIOTE1_IRQHandler
   .thumb_set GPIOTE1_IRQHandler,Default_Handler
                           
   .weak      QDEC0_IRQHandler
   .thumb_set QDEC0_IRQHandler,Default_Handler
                        
   .weak      QDEC1_IRQHandler
   .thumb_set QDEC1_IRQHandler,Default_Handler
                  
   .weak      USBD_IRQHandler
   .thumb_set USBD_IRQHandler,Default_Handler
                     
   .weak      USBREGULATOR_IRQHandler
   .thumb_set USBREGULATOR_IRQHandler,Default_Handler
                     
   .weak      KMU_IRQHandler
   .thumb_set KMU_IRQHandler,Default_Handler
                  
   .weak      CRYPTOCELL_IRQHandler
   .thumb_set CRYPTOCELL_IRQHandler,Default_Handler
               

 
   
   
