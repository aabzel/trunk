/******************************************
  this startup is only adapt to flagchip FC7300 with FC IDE
  Author: Beatfan
 ******************************************/

    .syntax unified
    .arch armv7-m

    .extern data_init
    .extern system_init
    .extern __Core0_StackTop
    .extern __Core0_StackLimit
    .global __vector_table

/* ================================================================================================== */
/*                                        Set vector table                                            */
/* ================================================================================================== */
    .section .isr_vector,"a",%progbits
    .align 2

    /* vector table */
__vector_table:
    .long   __Core0_StackTop                                      /* Top of Stack */
    .long   Reset_Handler                                   /* Reset Handler */
    .long   NMI_Handler                                     /* NMI Handler */
    .long   HardFault_Handler                               /* Hard Fault Handler */
    .long   MemManage_Handler                               /* MPU Fault Handler */
    .long   BusFault_Handler                                /* Bus Fault Handler */
    .long   UsageFault_Handler                              /* Usage Fault Handler */
    .long   0                                               /* Reserved */
    .long   0                                               /* Reserved */
    .long   0                                               /* Reserved */
    .long   0                                               /* Reserved */
    .long   SVC_Handler                                     /* SVCall Handler */
    .long   DebugMon_Handler                                /* Debug Monitor Handler */
    .long   0                                               /* Reserved */
    .long   PendSV_Handler                                  /* PendSV Handler */
    .long   SysTick_Handler                                 /* SysTick Handler */

                                                            /* External Interrupts*/
    .long   DMA0_IRQHandler                                 /*  DMA channel 0 transfer complete */
    .long   DMA1_IRQHandler                                 /*  DMA channel 1 transfer complete */
    .long   DMA2_IRQHandler                                 /*  DMA channel 2 transfer complete */
    .long   DMA3_IRQHandler                                 /*  DMA channel 3 transfer complete */
    .long   DMA4_IRQHandler                                 /*  DMA channel 4 transfer complete */
    .long   DMA5_IRQHandler                                 /*  DMA channel 5 transfer complete */
    .long   DMA6_IRQHandler                                 /*  DMA channel 6 transfer complete */
    .long   DMA7_IRQHandler                                 /*  DMA channel 7 transfer complete */
    .long   DMA8_IRQHandler                                 /*  DMA channel 8 transfer complete */
    .long   DMA9_IRQHandler                                 /*  DMA channel 9 transfer complete */
    .long   DMA10_IRQHandler                                /*  DMA channel 10 transfer complete */
    .long   DMA11_IRQHandler                                /*  DMA channel 11 transfer complete */
    .long   DMA12_IRQHandler                                /*  DMA channel 12 transfer complete */
    .long   DMA13_IRQHandler                                /*  DMA channel 13 transfer complete */
    .long   DMA14_IRQHandler                                /*  DMA channel 14 transfer complete */
    .long   DMA15_IRQHandler                                /*  DMA channel 15 transfer complete */
    .long   DMA16_IRQHandler                                /*  DMA channel 16 transfer complete */
    .long   DMA17_IRQHandler                                /*  DMA channel 17 transfer complete */
    .long   DMA18_IRQHandler                                /*  DMA channel 18 transfer complete */
    .long   DMA19_IRQHandler                                /*  DMA channel 19 transfer complete */
    .long   DMA20_IRQHandler                                /*  DMA channel 20 transfer complete */
    .long   DMA21_IRQHandler                                /*  DMA channel 21 transfer complete */
    .long   DMA22_IRQHandler                                /*  DMA channel 22 transfer complete */
    .long   DMA23_IRQHandler                                /*  DMA channel 23 transfer complete */
    .long   DMA24_IRQHandler                                /*  DMA channel 24 transfer complete */
    .long   DMA25_IRQHandler                                /*  DMA channel 25 transfer complete */
    .long   DMA26_IRQHandler                                /*  DMA channel 26 transfer complete */
    .long   DMA27_IRQHandler                                /*  DMA channel 27 transfer complete */
    .long   DMA28_IRQHandler                                /*  DMA channel 28 transfer complete */
    .long   DMA29_IRQHandler                                /*  DMA channel 29 transfer complete */
    .long   DMA30_IRQHandler                                /*  DMA channel 30 transfer complete */
    .long   DMA31_IRQHandler                                /*  DMA channel 31 transfer complete */
    .long   DMA_Error_IRQHandler                            /*  DMA error interrupt channels 0-63 */
    .long   CPM_IRQHandler                                  /*  FPU etc. interrupt */
    .long   FC_IRQHandler                                   /*  FC Command complete */
    .long   LVD_LVW_IRQHandler                              /*  PMC Low voltage detect interrupt */
    .long   TMU_IRQHandler                                  /*  Temperature Monitor Unit interrupt */
    .long   WDOG0_IRQHandler                                /*  interrupt request out before wdg reset out */
    .long   WDOG1_IRQHandler                                /*  interrupt request out before wdg reset out */
    .long   WDOG2_IRQHandler                                /*  interrupt request out before wdg reset out */
    .long   FCSMU0_IRQHandler                               /*  Fault Control and Safety Manage Unit */
    .long   STCU0_IRQHandler                                /*  Safety Control Unit interrupt */
    .long   ERM_fault_IRQHandler                            /*  ERM single/double bit error correction */
    .long   MAM0_IRQHandler                                 /*  Matrix Access Monitor interrupt */
    .long   MAM1_IRQHandler                                 /*  Matrix Access Monitor interrupt */
    .long   MAM2_IRQHandler                                 /*  Matrix Access Monitor interrupt */
    .long   RESERVED_62_IRQHandler                          /*  Reserved */
    .long   RGM_Pre_IRQHandler                              /*  RGM pre-reset Interrupt */
    .long   RGM_Other_IRQHandler                            /*  RGM other CPU exit reset Interrupt */
    .long   INTM0_IRQHandler                                /*  INTM alarm interrupt */
    .long   ISM0_IRQHandler                                 /*  ISM0 interrupt */
    .long   MB_IRQHandler                                   /*  Mail Box interrupt */
    .long   SCG_IRQHandler                                  /*  SCG bus interrupt request */
    .long   CMU0_IRQHandler                                 /*  CMU0 interrupt */
    .long   CMU1_IRQHandler                                 /*  CMU1 interrupt */
    .long   CMU2_IRQHandler                                 /*  CMU2 interrupt */
    .long   CMU3_IRQHandler                                 /*  CMU3 interrupt */
    .long   TSTMP0_IRQHandler                               /*  TimerStamp0 interrupt */
    .long   TSTMP1_IRQHandler                               /*  TimerStamp1 interrupt */
    .long   TSTMP2_IRQHandler                               /*  TimerStamp2 interrupt */
    .long   TSTMP3_IRQHandler                               /*  TimerStamp3 interrupt */
    .long   CORDIC_IRQHandler                               /*  CORDIC Accelerator interrupt */
    .long   HSM0_IRQHandler                                 /*  Crypto interrupt */
    .long   FCPIT0_IRQHandler                               /*  FCPIT0 interrupt */
    .long   FCPIT1_IRQHandler                               /*  FCPIT0 interrupt */
    .long   RTC_IRQHandler                                  /*  RTC alarm or seconds interrupt  */
    .long   ENET_Tx0_IRQHandler                             /*  ENET 1588 Timer Interrupt - synchronous */
    .long   ENET_Tx1_IRQHandler                             /*  ENET Data transfer done */
    .long   ENET_Rx0_IRQHandler                             /*  ENET Receive Buffer Done for Ring/Queue 0 */
    .long   ENET_Rx1_IRQHandler                             /*  ENET Receive Buffer Done for Ring/Queue 0 */
    .long   ENET_System_IRQHandler                          /** ENET System interrupt  */
    .long   AONTIMER_IRQHandler                             /*  AONTIMER interrupt request */
    .long   SWI_IRQHandler                                  /*  Software interrupt */
    .long   OSPI_IRQHandler                                 /*  All OSPI interrupts */
    .long   FREQM_IRQHandler                                /*  FREQM interrupt */
    .long   PORTA_IRQHandler                                /*  Port A pin detect interrupt */
    .long   PORTB_IRQHandler                                /*  Port B pin detect interrupt */
    .long   PORTC_IRQHandler                                /*  Port C pin detect interrupt */
    .long   PORTD_IRQHandler                                /*  Port D pin detect interrupt */
    .long   PORTE_IRQHandler                                /*  Port E pin detect interrupt */
    .long   PORTF_IRQHandler                                /*  Port F pin detect interrupt */
    .long   PORTG_IRQHandler                                /*  Port G pin detect interrupt */
    .long   PORTH_IRQHandler                                /*  Port H pin detect interrupt */
    .long   PORTI_IRQHandler                                /*  Port I pin detect interrupt */
    .long   CAN0_IRQHandler                                 /*  CAN0 Interrupt */
    .long   CAN1_IRQHandler                                 /*  CAN1 Interrupt */
    .long   CAN2_IRQHandler                                 /*  CAN2 Interrupt */
    .long   CAN3_IRQHandler                                 /*  CAN3 Interrupt */
    .long   CAN4_IRQHandler                                 /*  CAN4 Interrupt */
    .long   CAN5_IRQHandler                                 /*  CAN5 Interrupt */
    .long   CAN6_IRQHandler                                 /*  CAN6 Interrupt */
    .long   CAN7_IRQHandler                                 /*  CAN7 Interrupt */
    .long   FCIIC0_IRQHandler                               /*  FCIIC0 Interrupt */
    .long   FCIIC1_IRQHandler                               /*  FCIIC1 Interrupt */
    .long   FCSPI0_IRQHandler                               /*  FCSPI0 Interrupt */
    .long   FCSPI1_IRQHandler                               /*  FCSPI1 Interrupt */
    .long   FCSPI2_IRQHandler                               /*  FCSPI2 Interrupt */
    .long   FCSPI3_IRQHandler                               /*  FCSPI0 Interrupt */
    .long   FCSPI4_IRQHandler                               /*  FCSPI1 Interrupt */
    .long   FCSPI5_IRQHandler                               /*  FCSPI2 Interrupt */
    .long   FCUART0_RxTx_IRQHandler                         /*  FCUART0 Transmit / Receive Interrupt */
    .long   FCUART1_RxTx_IRQHandler                         /*  FCUART1 Transmit / Receive  Interrupt */
    .long   FCUART2_RxTx_IRQHandler                         /*  FCUART2 Transmit / Receive  Interrupt */
    .long   FCUART3_RxTx_IRQHandler                         /*  FCUART3 Transmit / Receive Interrupt */
    .long   FCUART4_RxTx_IRQHandler                         /*  FCUART4 Transmit / Receive  Interrupt */
    .long   FCUART5_RxTx_IRQHandler                         /*  FCUART5 Transmit / Receive  Interrupt */
    .long   FCUART6_RxTx_IRQHandler                         /*  FCUART6 Transmit / Receive Interrupt */
    .long   FCUART7_RxTx_IRQHandler                         /*  FCUART7 Transmit / Receive  Interrupt */
    .long   FCUART8_RxTx_IRQHandler                         /*  FCUART8 Transmit / Receive  Interrupt */
    .long   FCUART9_RxTx_IRQHandler                         /*  FCUART9 Transmit / Receive Interrupt */
    .long   FCUART10_RxTx_IRQHandler                        /*  FCUART10 Transmit / Receive  Interrupt */
    .long   FCUART11_RxTx_IRQHandler                        /*  FCUART11 Transmit / Receive  Interrupt */    
    .long   FCUART12_RxTx_IRQHandler                        /*  FCUART12 Transmit / Receive  Interrupt */
    .long   FCUART13_RxTx_IRQHandler                        /*  FCUART13 Transmit / Receive  Interrupt */
    .long   FCUART14_RxTx_IRQHandler                        /*  FCUART14 Transmit / Receive Interrupt */
    .long   FCUART15_RxTx_IRQHandler                        /*  FCUART15 Transmit / Receive  Interrupt */ 
    .long   FTU0_IRQHandler                                 /*  FTU0 all source interrupt */
    .long   FTU1_IRQHandler                                 /*  FTU1 all source interrupt */
    .long   FTU2_IRQHandler                                 /*  FTU2 all source interrupt */
    .long   FTU3_IRQHandler                                 /*  FTU3 all source interrupt */
    .long   FTU4_IRQHandler                                 /*  FTU4 all source interrupt */
    .long   FTU5_IRQHandler                                 /*  FTU5 all source interrupt */
    .long   FTU6_IRQHandler                                 /*  FTU6 all source interrupt */
    .long   FTU7_IRQHandler                                 /*  FTU7 all source interrupt */
    .long   FTU8_IRQHandler                                 /*  FTU4 all source interrupt */
    .long   FTU9_IRQHandler                                 /*  FTU5 all source interrupt */
    .long   FTU10_IRQHandler                                /*  FTU6 all source interrupt */
    .long   FTU11_IRQHandler                                /*  FTU7 all source interrupt */
    .long   CMP0_IRQHandler                                 /*  CMP0 interrupt request  */
    .long   CMP1_IRQHandler                                 /*  CMP1 interrupt request  */
    .long   CMP2_IRQHandler                                 /*  CMP2 interrupt request  */
    .long   ADC0_IRQHandler                                 /*  ADC0 interrupt request. */
    .long   ADC1_IRQHandler                                 /*  ADC1 interrupt request. */
    .long   ADC2_IRQHandler                                 /*  ADC2 interrupt request. */
    .long   ADC3_IRQHandler                                 /*  ADC3 interrupt request. */
    .long   PTIMER0_IRQHandler                              /*  PTIMER0 interrupt */
    .long   PTIMER1_IRQHandler                              /*  PTIMER1 interrupt */
    .long   PTIMER2_IRQHandler                              /*  PTIMER2 interrupt */
    .long   PTIMER3_IRQHandler                              /*  PTIMER3 interrupt */
    .long   SDDF0_IRQHandler                                /*  SD Digital Filter interrupt request */
    .long   MSC0_IRQHandler                                 /*  MSC interrupt */
    .long   MSC1_IRQHandler                                 /*  MSC interrupt */
    .long   CAN8_IRQHandler                                 /*  CAN6 Interrupt */
    .long   CAN9_IRQHandler                                 /*  CAN7 Interrupt */
    .long   SENT0_IRQHandler                                /*  SENT all interrupt (fast or slow) */
    .long   SENT1_IRQHandler                                /*  SENT all interrupt (fast or slow) */
    .long   FCSPI6_IRQHandler                               /*  FCSPI6 Interrupt */
    .long   FCSPI7_IRQHandler                               /*  FCSPI7 Interrupt */
    .long   FCUART16_RxTx_IRQHandler                        /*  FCUART16 Transmit / Receive Interrupt */
    .long   FCUART17_RxTx_IRQHandler                        /*  FCUART17 Transmit / Receive  Interrupt */ 
    .long   CTI0_IRQHandler                                 /*  CTI Interrupt */
    .long   CTI1_IRQHandler                                 /*  CTI Interrupt */
    .long   CTI2_IRQHandler                                 /*  CTI Interrupt */
    .long   CMU4_IRQHandler                                 /*  CMU4 Interrupt */
    .long   DefaultISR                                      /* 170 */
    .long   DefaultISR                                      /* 171 */
    .long   DefaultISR                                      /* 172 */
    .long   DefaultISR                                      /* 173 */
    .long   DefaultISR                                      /* 174 */
    .long   DefaultISR                                      /* 175 */
    .long   DefaultISR                                      /* 176 */
    .long   DefaultISR                                      /* 177 */
    .long   DefaultISR                                      /* 178 */
    .long   DefaultISR                                      /* 179 */
    .long   DefaultISR                                      /* 180 */
    .long   DefaultISR                                      /* 181 */
    .long   DefaultISR                                      /* 182 */
    .long   DefaultISR                                      /* 183 */
    .long   DefaultISR                                      /* 184 */
    .long   DefaultISR                                      /* 185 */
    .long   DefaultISR                                      /* 186 */
    .long   DefaultISR                                      /* 187 */
    .long   DefaultISR                                      /* 188 */
    .long   DefaultISR                                      /* 189 */
    .long   DefaultISR                                      /* 190 */
    .long   DefaultISR                                      /* 191 */
    .long   DefaultISR                                      /* 192 */
    .long   DefaultISR                                      /* 193 */
    .long   DefaultISR                                      /* 194 */
    .long   DefaultISR                                      /* 195 */
    .long   DefaultISR                                      /* 196 */
    .long   DefaultISR                                      /* 197 */
    .long   DefaultISR                                      /* 198 */
    .long   DefaultISR                                      /* 199 */
    .long   DefaultISR                                      /* 200 */
    .long   DefaultISR                                      /* 201 */
    .long   DefaultISR                                      /* 202 */
    .long   DefaultISR                                      /* 203 */
    .long   DefaultISR                                      /* 204 */
    .long   DefaultISR                                      /* 205 */
    .long   DefaultISR                                      /* 206 */
    .long   DefaultISR                                      /* 207 */
    .long   DefaultISR                                      /* 208 */
    .long   DefaultISR                                      /* 209 */
    .long   DefaultISR                                      /* 210 */
    .long   DefaultISR                                      /* 211 */
    .long   DefaultISR                                      /* 212 */
    .long   DefaultISR                                      /* 213 */
    .long   DefaultISR                                      /* 214 */
    .long   DefaultISR                                      /* 215 */
    .long   DefaultISR                                      /* 216 */
    .long   DefaultISR                                      /* 217 */
    .long   DefaultISR                                      /* 218 */
    .long   DefaultISR                                      /* 219 */
    .long   DefaultISR                                      /* 220 */
    .long   DefaultISR                                      /* 221 */
    .long   DefaultISR                                      /* 222 */
    .long   DefaultISR                                      /* 223 */
    .long   DefaultISR                                      /* 224 */
    .long   DefaultISR                                      /* 225 */
    .long   DefaultISR                                      /* 226 */
    .long   DefaultISR                                      /* 227 */
    .long   DefaultISR                                      /* 228 */
    .long   DefaultISR                                      /* 229 */
    .long   DefaultISR                                      /* 230 */
    .long   DefaultISR                                      /* 231 */
    .long   DefaultISR                                      /* 232 */
    .long   DefaultISR                                      /* 233 */
    .long   DefaultISR                                      /* 234 */
    .long   DefaultISR                                      /* 235 */
    .long   DefaultISR                                      /* 236 */
    .long   DefaultISR                                      /* 237 */
    .long   DefaultISR                                      /* 238 */
    .long   DefaultISR                                      /* 239 */
    .long   DefaultISR                                      /* 240 */
    .long   DefaultISR                                      /* 241 */
    .long   DefaultISR                                      /* 242 */
    .long   DefaultISR                                      /* 243 */
    .long   DefaultISR                                      /* 244 */
    .long   DefaultISR                                      /* 245 */
    .long   DefaultISR                                      /* 246 */
    .long   DefaultISR                                      /* 247 */
    .long   DefaultISR                                      /* 248 */
    .long   DefaultISR                                      /* 249 */
    .long   DefaultISR                                      /* 250 */
    .long   DefaultISR                                      /* 251 */
    .long   DefaultISR                                      /* 252 */
    .long   DefaultISR                                      /* 253 */
    .long   DefaultISR                                      /* 254 */
    .long   0xFFFFFFFF                                      /*  Reserved for user TRIM value */

    .size    __vector_table, . - __vector_table


/**************************************************************/
/************************ set other  ***************************/
    .section .text
    .thumb

/* Reset Handler */

    .thumb_func
    .align 2
    .globl   Reset_Handler
    .weak    Reset_Handler
    .type    Reset_Handler, %function

Reset_Handler:
    cpsid   i               /* Mask interrupts */

    /* Init the rest of the registers */
    ldr     r1,=0
    ldr     r2,=0
    ldr     r3,=0
    ldr     r4,=0
    ldr     r5,=0
    ldr     r6,=0
    ldr     r7,=0
    mov     r8,r7
    mov     r9,r7
    mov     r10,r7
    mov     r11,r7
    mov     r12,r7

    ldr        r0, =0xE000ED08
    ldr        r1, =__vector_table
    str        r1, [r0]

    /* Initialize the stack pointer */
    ldr     r0,=__Core0_StackTop
    mov     sp,r0   ; sp=r13 

    /* Clear Stack */
    ldr r2, =__Core0_StackLimit
    ldr r4, =__Core0_StackTop
    movs r3, #0
    b LoopFillZero_STACK

FillZero_STACK:
    str  r3, [r2]
    adds r2, r2, #4

LoopFillZero_STACK:
    cmp r2, r4                   /* Compare (immediate) subtracts an immediate value from a register value. */
    bcc FillZero_STACK           /*branch if carry clear  */

    bl  load_ram_functions_binary /* Branch with Link (immediate) calls a subroutine at a PC-relative address.*/

    /* System Initialization */
    ldr     r0,=system_init       /* Load register with word */
    blx     r0                    /* Call a subroutine, optionally change instruction set */


    /* Initialize .data and .bss sections */
    ldr     r0,=data_init     /* Load register with word  */
    blx     r0                /*  Call a subroutine, optionally change instruction set */
    
    cpsie   i                 /* Unmask interrupts */
    bl      main              /*  Branch with Link (immediate) calls a subroutine at a PC-relative address. */
JumpToSelf:
    b       JumpToSelf/*  */

    .pool
    .size Reset_Handler, . - Reset_Handler

    .align  1
    .thumb_func
    .weak DefaultISR
    .type DefaultISR, %function
DefaultISR:
    b       DefaultISR
    .size DefaultISR, . - DefaultISR

/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
    .macro def_irq_handler    handler_name
    .weak \handler_name
    .set  \handler_name, DefaultISR
    .endm

/* Exception Handlers */
    def_irq_handler NMI_Handler                                     
    def_irq_handler HardFault_Handler                               
    def_irq_handler MemManage_Handler                               
    def_irq_handler BusFault_Handler                                
    def_irq_handler UsageFault_Handler                             
    def_irq_handler SVC_Handler                                    
    def_irq_handler DebugMon_Handler                                
    def_irq_handler PendSV_Handler                                 
    def_irq_handler SysTick_Handler                            
    def_irq_handler DMA0_IRQHandler                               
    def_irq_handler DMA1_IRQHandler                                 
    def_irq_handler DMA2_IRQHandler                                   
    def_irq_handler DMA3_IRQHandler                                   
    def_irq_handler DMA4_IRQHandler                                   
    def_irq_handler DMA5_IRQHandler                                   
    def_irq_handler DMA6_IRQHandler                                   
    def_irq_handler DMA7_IRQHandler                                   
    def_irq_handler DMA8_IRQHandler                                   
    def_irq_handler DMA9_IRQHandler                                   
    def_irq_handler DMA10_IRQHandler                                  
    def_irq_handler DMA11_IRQHandler                                 
    def_irq_handler DMA12_IRQHandler                                 
    def_irq_handler DMA13_IRQHandler                                
    def_irq_handler DMA14_IRQHandler                           
    def_irq_handler DMA15_IRQHandler                              
    def_irq_handler DMA16_IRQHandler                                  
    def_irq_handler DMA17_IRQHandler                                 
    def_irq_handler DMA18_IRQHandler                               
    def_irq_handler DMA19_IRQHandler                                 
    def_irq_handler DMA20_IRQHandler                                  
    def_irq_handler DMA21_IRQHandler                              
    def_irq_handler DMA22_IRQHandler                                   
    def_irq_handler DMA23_IRQHandler                                 
    def_irq_handler DMA24_IRQHandler                                
    def_irq_handler DMA25_IRQHandler                             
    def_irq_handler DMA26_IRQHandler                              
    def_irq_handler DMA27_IRQHandler                              
    def_irq_handler DMA28_IRQHandler                             
    def_irq_handler DMA29_IRQHandler                               
    def_irq_handler DMA30_IRQHandler                                
    def_irq_handler DMA31_IRQHandler                                 
    def_irq_handler DMA_Error_IRQHandler                           
    def_irq_handler CPM_IRQHandler                                 
    def_irq_handler FC_IRQHandler                                    
    def_irq_handler LVD_LVW_IRQHandler                              
    def_irq_handler TMU_IRQHandler                                   
    def_irq_handler WDOG0_IRQHandler                                
    def_irq_handler WDOG1_IRQHandler                                 
    def_irq_handler WDOG2_IRQHandler                                
    def_irq_handler FCSMU0_IRQHandler                               
    def_irq_handler STCU0_IRQHandler                                
    def_irq_handler ERM_fault_IRQHandler                          
    def_irq_handler MAM0_IRQHandler                                  
    def_irq_handler MAM1_IRQHandler                                
    def_irq_handler MAM2_IRQHandler                               
    def_irq_handler RESERVED_62_IRQHandler                          
    def_irq_handler RGM_Pre_IRQHandler                          
    def_irq_handler RGM_Other_IRQHandler                            
    def_irq_handler INTM0_IRQHandler                             
    def_irq_handler ISM0_IRQHandler                                 
    def_irq_handler MB_IRQHandler                                    
    def_irq_handler SCG_IRQHandler                                 
    def_irq_handler CMU0_IRQHandler                          
    def_irq_handler CMU1_IRQHandler                               
    def_irq_handler CMU2_IRQHandler                                 
    def_irq_handler CMU3_IRQHandler                                
    def_irq_handler TSTMP0_IRQHandler                            
    def_irq_handler TSTMP1_IRQHandler                                 
    def_irq_handler TSTMP2_IRQHandler                                
    def_irq_handler TSTMP3_IRQHandler                               
    def_irq_handler CORDIC_IRQHandler                               
    def_irq_handler HSM0_IRQHandler                                 
    def_irq_handler FCPIT0_IRQHandler                             
    def_irq_handler FCPIT1_IRQHandler                             
    def_irq_handler RTC_IRQHandler                                  
    def_irq_handler ENET_Tx0_IRQHandler                              
    def_irq_handler ENET_Tx1_IRQHandler                           
    def_irq_handler ENET_Rx0_IRQHandler                              
    def_irq_handler ENET_Rx1_IRQHandler       
    def_irq_handler ENET_System_IRQHandler
    def_irq_handler AONTIMER_IRQHandler                              
    def_irq_handler SWI_IRQHandler                         
    def_irq_handler OSPI_IRQHandler                              
    def_irq_handler FREQM_IRQHandler                   
    def_irq_handler PORTA_IRQHandler                          
    def_irq_handler PORTB_IRQHandler                               
    def_irq_handler PORTC_IRQHandler                                
    def_irq_handler PORTD_IRQHandler                                 
    def_irq_handler PORTE_IRQHandler                                
    def_irq_handler PORTF_IRQHandler                               
    def_irq_handler PORTG_IRQHandler                              
    def_irq_handler PORTH_IRQHandler                                
    def_irq_handler PORTI_IRQHandler                            
    def_irq_handler CAN0_IRQHandler                                 
    def_irq_handler CAN1_IRQHandler                                 
    def_irq_handler CAN2_IRQHandler                               
    def_irq_handler CAN3_IRQHandler                             
    def_irq_handler CAN4_IRQHandler                               
    def_irq_handler CAN5_IRQHandler                                 
    def_irq_handler CAN6_IRQHandler                                
    def_irq_handler CAN7_IRQHandler                                 
    def_irq_handler FCIIC0_IRQHandler                              
    def_irq_handler FCIIC1_IRQHandler                                
    def_irq_handler FCSPI0_IRQHandler                                
    def_irq_handler FCSPI1_IRQHandler                                 
    def_irq_handler FCSPI2_IRQHandler                               
    def_irq_handler FCSPI3_IRQHandler                                
    def_irq_handler FCSPI4_IRQHandler                              
    def_irq_handler FCSPI5_IRQHandler                                
    def_irq_handler FCUART0_RxTx_IRQHandler                          
    def_irq_handler FCUART1_RxTx_IRQHandler                          
    def_irq_handler FCUART2_RxTx_IRQHandler                           
    def_irq_handler FCUART3_RxTx_IRQHandler                          
    def_irq_handler FCUART4_RxTx_IRQHandler                          
    def_irq_handler FCUART5_RxTx_IRQHandler                         
    def_irq_handler FCUART6_RxTx_IRQHandler                           
    def_irq_handler FCUART7_RxTx_IRQHandler                          
    def_irq_handler FCUART8_RxTx_IRQHandler                          
    def_irq_handler FCUART9_RxTx_IRQHandler                           
    def_irq_handler FCUART10_RxTx_IRQHandler                          
    def_irq_handler FCUART11_RxTx_IRQHandler                             
    def_irq_handler FCUART12_RxTx_IRQHandler                         
    def_irq_handler FCUART13_RxTx_IRQHandler                         
    def_irq_handler FCUART14_RxTx_IRQHandler                         
    def_irq_handler FCUART15_RxTx_IRQHandler                        
    def_irq_handler FTU0_IRQHandler                                 
    def_irq_handler FTU1_IRQHandler                                  
    def_irq_handler FTU2_IRQHandler                                 
    def_irq_handler FTU3_IRQHandler                               
    def_irq_handler FTU4_IRQHandler                                   
    def_irq_handler FTU5_IRQHandler                                 
    def_irq_handler FTU6_IRQHandler                            
    def_irq_handler FTU7_IRQHandler                              
    def_irq_handler FTU8_IRQHandler                            
    def_irq_handler FTU9_IRQHandler                                 
    def_irq_handler FTU10_IRQHandler                            
    def_irq_handler FTU11_IRQHandler                               
    def_irq_handler CMP0_IRQHandler                             
    def_irq_handler CMP1_IRQHandler                               
    def_irq_handler CMP2_IRQHandler                                 
    def_irq_handler ADC0_IRQHandler                               
    def_irq_handler ADC1_IRQHandler                                
    def_irq_handler ADC2_IRQHandler                              
    def_irq_handler ADC3_IRQHandler                             
    def_irq_handler PTIMER0_IRQHandler                           
    def_irq_handler PTIMER1_IRQHandler                            
    def_irq_handler PTIMER2_IRQHandler                            
    def_irq_handler PTIMER3_IRQHandler                           
    def_irq_handler SDDF0_IRQHandler                               
    def_irq_handler MSC0_IRQHandler                             
    def_irq_handler MSC1_IRQHandler                                
    def_irq_handler CAN8_IRQHandler                              
    def_irq_handler CAN9_IRQHandler                            
    def_irq_handler SENT0_IRQHandler                               
    def_irq_handler SENT1_IRQHandler                             
    def_irq_handler FCSPI6_IRQHandler                        
    def_irq_handler FCSPI7_IRQHandler                             
    def_irq_handler FCUART16_RxTx_IRQHandler                      
    def_irq_handler FCUART17_RxTx_IRQHandler                        
    def_irq_handler CTI0_IRQHandler                              
    def_irq_handler CTI1_IRQHandler                                
    def_irq_handler CTI2_IRQHandler                              
    def_irq_handler CMU4_IRQHandler                               
    .end
