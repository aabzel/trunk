ARM GAS  C:\Users\aabdev\AppData\Local\Temp\cclkaQHQ.s 			page 1


   1              	# 1 "C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407x
   1              	/**
   0              	
   0              	
   0              	
   2              	  ******************************************************************************
   3              	  * @file      startup_stm32f407xx.s
   4              	  * @author    MCD Application Team
   5              	  * @brief     STM32F407xx Devices vector table for GCC based toolchains. 
   6              	  *            This module performs:
   7              	  *                - Set the initial SP
   8              	  *                - Set the initial PC == Reset_Handler,
   9              	  *                - Set the vector table entries with the exceptions ISR address
  10              	  *                - Branches to main in the C library (which eventually
  11              	  *                  calls main()).
  12              	  *            After Reset the Cortex-M4 processor is in Thread mode,
  13              	  *            priority is Privileged, and the Stack is set to Main.
  14              	  ******************************************************************************
  15              	  * @attention
  16              	  *
  17              	  * Copyright (c) 2017 STMicroelectronics.
  18              	  * All rights reserved.
  19              	  *
  20              	  * This software is licensed under terms that can be found in the LICENSE file
  21              	  * in the root directory of this software component.
  22              	  * If no LICENSE file comes with this software, it is provided AS-IS.
  23              	  *
  24              	  ******************************************************************************
  25              	  */
  26              	    
  27              	  .syntax unified
  28              	  .cpu cortex-m4
  29              	  .fpu softvfp
  30              	  .thumb
  31              	
  32              	.global  g_pfnVectors
  33              	.global  Default_Handler
  34              	
  35              	/* start address for the initialization values of the .data section. 
  36              	defined in linker script */
  37 0000 00000000 	.word  _sidata
  38              	/* start address for the .data section. defined in linker script */  
  39 0004 00000000 	.word  _sdata
  40              	/* end address for the .data section. defined in linker script */
  41 0008 00000000 	.word  _edata
  42              	/* start address for the .bss section. defined in linker script */
  43 000c 00000000 	.word  _sbss
  44              	/* end address for the .bss section. defined in linker script */
  45 0010 00000000 	.word  _ebss
  46              	/* stack used for SystemInit_ExtMemCtl; always internal RAM used */
  47              	
  48              	/**
  49              	 * @brief  This is the code that gets called when the processor first
  50              	 *          starts execution following a reset event. Only the absolutely
  51              	 *          necessary set is performed, after which the application
  52              	 *          supplied main() routine is called. 
  53              	 * @param  None
ARM GAS  C:\Users\aabdev\AppData\Local\Temp\cclkaQHQ.s 			page 2


  54              	 * @retval : None
  55              	*/
  56              	
  57              	    .section  .text.Reset_Handler
  58              	  .weak  Reset_Handler
  60              	Reset_Handler:  
  61 0000 DFF834D0 	  ldr   sp, =_estack     /* set stack pointer */
  62              	
  63              	/* Copy the data segment initializers from flash to SRAM */  
  64 0004 0D48     	  ldr r0, =_sdata
  65 0006 0E49     	  ldr r1, =_edata
  66 0008 0E4A     	  ldr r2, =_sidata
  67 000a 0023     	  movs r3, #0
  68 000c 02E0     	  b LoopCopyDataInit
  69              	
  70              	CopyDataInit:
  71 000e D458     	  ldr r4, [r2, r3]
  72 0010 C450     	  str r4, [r0, r3]
  73 0012 0433     	  adds r3, r3, #4
  74              	
  75              	LoopCopyDataInit:
  76 0014 C418     	  adds r4, r0, r3
  77 0016 8C42     	  cmp r4, r1
  78 0018 F9D3     	  bcc CopyDataInit
  79              	  
  80              	/* Zero fill the bss segment. */
  81 001a 0B4A     	  ldr r2, =_sbss
  82 001c 0B4C     	  ldr r4, =_ebss
  83 001e 0023     	  movs r3, #0
  84 0020 01E0     	  b LoopFillZerobss
  85              	
  86              	FillZerobss:
  87 0022 1360     	  str  r3, [r2]
  88 0024 0432     	  adds r2, r2, #4
  89              	
  90              	LoopFillZerobss:
  91 0026 A242     	  cmp r2, r4
  92 0028 FBD3     	  bcc FillZerobss
  93              	
  94              	/* Call the clock system initialization function.*/
  95 002a FFF7FEFF 	  bl  SystemInit   
  96              	/* Call static constructors */
  97 002e FFF7FEFF 	    bl __libc_init_array
  98              	/* Call the application's entry point.*/
  99 0032 FFF7FEFF 	  bl  main
 100 0036 7047     	  bx  lr    
 102              	
 103              	/**
 104              	 * @brief  This is the code that gets called when the processor receives an 
 105              	 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 106              	 *         the system state for examination by a debugger.
 107              	 * @param  None     
 108              	 * @retval None       
 109              	*/
 110              	    .section  .text.Default_Handler,"ax",%progbits
 111              	Default_Handler:
 112              	Infinite_Loop:
ARM GAS  C:\Users\aabdev\AppData\Local\Temp\cclkaQHQ.s 			page 3


 113 0000 FEE7     	  b  Infinite_Loop
 115              	/******************************************************************************
 116              	*
 117              	* The minimal vector table for a Cortex M3. Note that the proper constructs
 118              	* must be placed on this to ensure that it ends up at physical address
 119              	* 0x0000.0000.
 120              	* 
 121              	*******************************************************************************/
 122              	   .section  .isr_vector,"a",%progbits
 125              	    
 126              	    
 127              	g_pfnVectors:
 128 0000 00000000 	  .word  _estack
 129 0004 00000000 	  .word  Reset_Handler
 130 0008 00000000 	  .word  NMI_Handler
 131 000c 00000000 	  .word  HardFault_Handler
 132 0010 00000000 	  .word  MemManage_Handler
 133 0014 00000000 	  .word  BusFault_Handler
 134 0018 00000000 	  .word  UsageFault_Handler
 135 001c 00000000 	  .word  0
 136 0020 00000000 	  .word  0
 137 0024 00000000 	  .word  0
 138 0028 00000000 	  .word  0
 139 002c 00000000 	  .word  SVC_Handler
 140 0030 00000000 	  .word  DebugMon_Handler
 141 0034 00000000 	  .word  0
 142 0038 00000000 	  .word  PendSV_Handler
 143 003c 00000000 	  .word  SysTick_Handler
 144              	  
 145              	  /* External Interrupts */
 146 0040 00000000 	  .word     WWDG_IRQHandler                   /* Window WatchDog              */                   
 147 0044 00000000 	  .word     PVD_IRQHandler                    /* PVD through EXTI Line detection */                
 148 0048 00000000 	  .word     TAMP_STAMP_IRQHandler             /* Tamper and TimeStamps through the EXTI line */    
 149 004c 00000000 	  .word     RTC_WKUP_IRQHandler               /* RTC Wakeup through the EXTI line */               
 150 0050 00000000 	  .word     FLASH_IRQHandler                  /* FLASH                        */                   
 151 0054 00000000 	  .word     RCC_IRQHandler                    /* RCC                          */                   
 152 0058 00000000 	  .word     EXTI0_IRQHandler                  /* EXTI Line0                   */                   
 153 005c 00000000 	  .word     EXTI1_IRQHandler                  /* EXTI Line1                   */                   
 154 0060 00000000 	  .word     EXTI2_IRQHandler                  /* EXTI Line2                   */                   
 155 0064 00000000 	  .word     EXTI3_IRQHandler                  /* EXTI Line3                   */                   
 156 0068 00000000 	  .word     EXTI4_IRQHandler                  /* EXTI Line4                   */                   
 157 006c 00000000 	  .word     DMA1_Stream0_IRQHandler           /* DMA1 Stream 0                */                  
 158 0070 00000000 	  .word     DMA1_Stream1_IRQHandler           /* DMA1 Stream 1                */                   
 159 0074 00000000 	  .word     DMA1_Stream2_IRQHandler           /* DMA1 Stream 2                */                   
 160 0078 00000000 	  .word     DMA1_Stream3_IRQHandler           /* DMA1 Stream 3                */                   
 161 007c 00000000 	  .word     DMA1_Stream4_IRQHandler           /* DMA1 Stream 4                */                   
 162 0080 00000000 	  .word     DMA1_Stream5_IRQHandler           /* DMA1 Stream 5                */                   
 163 0084 00000000 	  .word     DMA1_Stream6_IRQHandler           /* DMA1 Stream 6                */                   
 164 0088 00000000 	  .word     ADC_IRQHandler                    /* ADC1, ADC2 and ADC3s         */                   
 165 008c 00000000 	  .word     CAN1_TX_IRQHandler                /* CAN1 TX                      */                   
 166 0090 00000000 	  .word     CAN1_RX0_IRQHandler               /* CAN1 RX0                     */                   
 167 0094 00000000 	  .word     CAN1_RX1_IRQHandler               /* CAN1 RX1                     */                   
 168 0098 00000000 	  .word     CAN1_SCE_IRQHandler               /* CAN1 SCE                     */                   
 169 009c 00000000 	  .word     EXTI9_5_IRQHandler                /* External Line[9:5]s          */                   
 170 00a0 00000000 	  .word     TIM1_BRK_TIM9_IRQHandler          /* TIM1 Break and TIM9          */         
 171 00a4 00000000 	  .word     TIM1_UP_TIM10_IRQHandler          /* TIM1 Update and TIM10        */         
 172 00a8 00000000 	  .word     TIM1_TRG_COM_TIM11_IRQHandler     /* TIM1 Trigger and Commutation and TIM11 */
ARM GAS  C:\Users\aabdev\AppData\Local\Temp\cclkaQHQ.s 			page 4


 173 00ac 00000000 	  .word     TIM1_CC_IRQHandler                /* TIM1 Capture Compare         */                   
 174 00b0 00000000 	  .word     TIM2_IRQHandler                   /* TIM2                         */                   
 175 00b4 00000000 	  .word     TIM3_IRQHandler                   /* TIM3                         */                   
 176 00b8 00000000 	  .word     TIM4_IRQHandler                   /* TIM4                         */                   
 177 00bc 00000000 	  .word     I2C1_EV_IRQHandler                /* I2C1 Event                   */                   
 178 00c0 00000000 	  .word     I2C1_ER_IRQHandler                /* I2C1 Error                   */                   
 179 00c4 00000000 	  .word     I2C2_EV_IRQHandler                /* I2C2 Event                   */                   
 180 00c8 00000000 	  .word     I2C2_ER_IRQHandler                /* I2C2 Error                   */                   
 181 00cc 00000000 	  .word     SPI1_IRQHandler                   /* SPI1                         */                   
 182 00d0 00000000 	  .word     SPI2_IRQHandler                   /* SPI2                         */                   
 183 00d4 00000000 	  .word     USART1_IRQHandler                 /* USART1                       */                   
 184 00d8 00000000 	  .word     USART2_IRQHandler                 /* USART2                       */                   
 185 00dc 00000000 	  .word     USART3_IRQHandler                 /* USART3                       */                   
 186 00e0 00000000 	  .word     EXTI15_10_IRQHandler              /* External Line[15:10]s        */                   
 187 00e4 00000000 	  .word     RTC_Alarm_IRQHandler              /* RTC Alarm (A and B) through EXTI Line */          
 188 00e8 00000000 	  .word     OTG_FS_WKUP_IRQHandler            /* USB OTG FS Wakeup through EXTI line */            
 189 00ec 00000000 	  .word     TIM8_BRK_TIM12_IRQHandler         /* TIM8 Break and TIM12         */         
 190 00f0 00000000 	  .word     TIM8_UP_TIM13_IRQHandler          /* TIM8 Update and TIM13        */         
 191 00f4 00000000 	  .word     TIM8_TRG_COM_TIM14_IRQHandler     /* TIM8 Trigger and Commutation and TIM14 */
 192 00f8 00000000 	  .word     TIM8_CC_IRQHandler                /* TIM8 Capture Compare         */                   
 193 00fc 00000000 	  .word     DMA1_Stream7_IRQHandler           /* DMA1 Stream7                 */                   
 194 0100 00000000 	  .word     FSMC_IRQHandler                   /* FSMC                         */                   
 195 0104 00000000 	  .word     SDIO_IRQHandler                   /* SDIO                         */                   
 196 0108 00000000 	  .word     TIM5_IRQHandler                   /* TIM5                         */                   
 197 010c 00000000 	  .word     SPI3_IRQHandler                   /* SPI3                         */                   
 198 0110 00000000 	  .word     UART4_IRQHandler                  /* UART4                        */                   
 199 0114 00000000 	  .word     UART5_IRQHandler                  /* UART5                        */                   
 200 0118 00000000 	  .word     TIM6_DAC_IRQHandler               /* TIM6 and DAC1&2 underrun errors */                
 201 011c 00000000 	  .word     TIM7_IRQHandler                   /* TIM7                         */
 202 0120 00000000 	  .word     DMA2_Stream0_IRQHandler           /* DMA2 Stream 0                */                   
 203 0124 00000000 	  .word     DMA2_Stream1_IRQHandler           /* DMA2 Stream 1                */                   
 204 0128 00000000 	  .word     DMA2_Stream2_IRQHandler           /* DMA2 Stream 2                */                   
 205 012c 00000000 	  .word     DMA2_Stream3_IRQHandler           /* DMA2 Stream 3                */                   
 206 0130 00000000 	  .word     DMA2_Stream4_IRQHandler           /* DMA2 Stream 4                */                   
 207 0134 00000000 	  .word     ETH_IRQHandler                    /* Ethernet                     */                   
 208 0138 00000000 	  .word     ETH_WKUP_IRQHandler               /* Ethernet Wakeup through EXTI line */              
 209 013c 00000000 	  .word     CAN2_TX_IRQHandler                /* CAN2 TX                      */                   
 210 0140 00000000 	  .word     CAN2_RX0_IRQHandler               /* CAN2 RX0                     */                   
 211 0144 00000000 	  .word     CAN2_RX1_IRQHandler               /* CAN2 RX1                     */                   
 212 0148 00000000 	  .word     CAN2_SCE_IRQHandler               /* CAN2 SCE                     */                   
 213 014c 00000000 	  .word     OTG_FS_IRQHandler                 /* USB OTG FS                   */                   
 214 0150 00000000 	  .word     DMA2_Stream5_IRQHandler           /* DMA2 Stream 5                */                   
 215 0154 00000000 	  .word     DMA2_Stream6_IRQHandler           /* DMA2 Stream 6                */                   
 216 0158 00000000 	  .word     DMA2_Stream7_IRQHandler           /* DMA2 Stream 7                */                   
 217 015c 00000000 	  .word     USART6_IRQHandler                 /* USART6                       */                   
 218 0160 00000000 	  .word     I2C3_EV_IRQHandler                /* I2C3 event                   */                   
 219 0164 00000000 	  .word     I2C3_ER_IRQHandler                /* I2C3 error                   */                   
 220 0168 00000000 	  .word     OTG_HS_EP1_OUT_IRQHandler         /* USB OTG HS End Point 1 Out   */                   
 221 016c 00000000 	  .word     OTG_HS_EP1_IN_IRQHandler          /* USB OTG HS End Point 1 In    */                   
 222 0170 00000000 	  .word     OTG_HS_WKUP_IRQHandler            /* USB OTG HS Wakeup through EXTI */                 
 223 0174 00000000 	  .word     OTG_HS_IRQHandler                 /* USB OTG HS                   */                   
 224 0178 00000000 	  .word     DCMI_IRQHandler                   /* DCMI                         */                   
 225 017c 00000000 	  .word     0                                 /* CRYP crypto                  */                   
 226 0180 00000000 	  .word     HASH_RNG_IRQHandler               /* Hash and Rng                 */
 227 0184 00000000 	  .word     FPU_IRQHandler                    /* FPU                          */
 228              	                         
 229              	                         
ARM GAS  C:\Users\aabdev\AppData\Local\Temp\cclkaQHQ.s 			page 5


 230              	/*******************************************************************************
 231              	*
 232              	* Provide weak aliases for each Exception handler to the Default_Handler. 
 233              	* As they are weak aliases, any function with the same name will override 
 234              	* this definition.
 235              	* 
 236              	*******************************************************************************/
 237              	   .weak      NMI_Handler
 238              	   .thumb_set NMI_Handler,Default_Handler
 239              	  
 240              	   .weak      HardFault_Handler
 241              	   .thumb_set HardFault_Handler,Default_Handler
 242              	  
 243              	   .weak      MemManage_Handler
 244              	   .thumb_set MemManage_Handler,Default_Handler
 245              	  
 246              	   .weak      BusFault_Handler
 247              	   .thumb_set BusFault_Handler,Default_Handler
 248              	
 249              	   .weak      UsageFault_Handler
 250              	   .thumb_set UsageFault_Handler,Default_Handler
 251              	
 252              	   .weak      SVC_Handler
 253              	   .thumb_set SVC_Handler,Default_Handler
 254              	
 255              	   .weak      DebugMon_Handler
 256              	   .thumb_set DebugMon_Handler,Default_Handler
 257              	
 258              	   .weak      PendSV_Handler
 259              	   .thumb_set PendSV_Handler,Default_Handler
 260              	
 261              	   .weak      SysTick_Handler
 262              	   .thumb_set SysTick_Handler,Default_Handler              
 263              	
 264              	   .weak      WWDG_IRQHandler                   
 265              	   .thumb_set WWDG_IRQHandler,Default_Handler      
 266              	                  
 267              	   .weak      PVD_IRQHandler      
 268              	   .thumb_set PVD_IRQHandler,Default_Handler
 269              	               
 270              	   .weak      TAMP_STAMP_IRQHandler            
 271              	   .thumb_set TAMP_STAMP_IRQHandler,Default_Handler
 272              	            
 273              	   .weak      RTC_WKUP_IRQHandler                  
 274              	   .thumb_set RTC_WKUP_IRQHandler,Default_Handler
 275              	            
 276              	   .weak      FLASH_IRQHandler         
 277              	   .thumb_set FLASH_IRQHandler,Default_Handler
 278              	                  
 279              	   .weak      RCC_IRQHandler      
 280              	   .thumb_set RCC_IRQHandler,Default_Handler
 281              	                  
 282              	   .weak      EXTI0_IRQHandler         
 283              	   .thumb_set EXTI0_IRQHandler,Default_Handler
 284              	                  
 285              	   .weak      EXTI1_IRQHandler         
 286              	   .thumb_set EXTI1_IRQHandler,Default_Handler
ARM GAS  C:\Users\aabdev\AppData\Local\Temp\cclkaQHQ.s 			page 6


 287              	                     
 288              	   .weak      EXTI2_IRQHandler         
 289              	   .thumb_set EXTI2_IRQHandler,Default_Handler 
 290              	                 
 291              	   .weak      EXTI3_IRQHandler         
 292              	   .thumb_set EXTI3_IRQHandler,Default_Handler
 293              	                        
 294              	   .weak      EXTI4_IRQHandler         
 295              	   .thumb_set EXTI4_IRQHandler,Default_Handler
 296              	                  
 297              	   .weak      DMA1_Stream0_IRQHandler               
 298              	   .thumb_set DMA1_Stream0_IRQHandler,Default_Handler
 299              	         
 300              	   .weak      DMA1_Stream1_IRQHandler               
 301              	   .thumb_set DMA1_Stream1_IRQHandler,Default_Handler
 302              	                  
 303              	   .weak      DMA1_Stream2_IRQHandler               
 304              	   .thumb_set DMA1_Stream2_IRQHandler,Default_Handler
 305              	                  
 306              	   .weak      DMA1_Stream3_IRQHandler               
 307              	   .thumb_set DMA1_Stream3_IRQHandler,Default_Handler 
 308              	                 
 309              	   .weak      DMA1_Stream4_IRQHandler              
 310              	   .thumb_set DMA1_Stream4_IRQHandler,Default_Handler
 311              	                  
 312              	   .weak      DMA1_Stream5_IRQHandler               
 313              	   .thumb_set DMA1_Stream5_IRQHandler,Default_Handler
 314              	                  
 315              	   .weak      DMA1_Stream6_IRQHandler               
 316              	   .thumb_set DMA1_Stream6_IRQHandler,Default_Handler
 317              	                  
 318              	   .weak      ADC_IRQHandler      
 319              	   .thumb_set ADC_IRQHandler,Default_Handler
 320              	               
 321              	   .weak      CAN1_TX_IRQHandler   
 322              	   .thumb_set CAN1_TX_IRQHandler,Default_Handler
 323              	            
 324              	   .weak      CAN1_RX0_IRQHandler                  
 325              	   .thumb_set CAN1_RX0_IRQHandler,Default_Handler
 326              	                           
 327              	   .weak      CAN1_RX1_IRQHandler                  
 328              	   .thumb_set CAN1_RX1_IRQHandler,Default_Handler
 329              	            
 330              	   .weak      CAN1_SCE_IRQHandler                  
 331              	   .thumb_set CAN1_SCE_IRQHandler,Default_Handler
 332              	            
 333              	   .weak      EXTI9_5_IRQHandler   
 334              	   .thumb_set EXTI9_5_IRQHandler,Default_Handler
 335              	            
 336              	   .weak      TIM1_BRK_TIM9_IRQHandler            
 337              	   .thumb_set TIM1_BRK_TIM9_IRQHandler,Default_Handler
 338              	            
 339              	   .weak      TIM1_UP_TIM10_IRQHandler            
 340              	   .thumb_set TIM1_UP_TIM10_IRQHandler,Default_Handler
 341              	      
 342              	   .weak      TIM1_TRG_COM_TIM11_IRQHandler      
 343              	   .thumb_set TIM1_TRG_COM_TIM11_IRQHandler,Default_Handler
ARM GAS  C:\Users\aabdev\AppData\Local\Temp\cclkaQHQ.s 			page 7


 344              	      
 345              	   .weak      TIM1_CC_IRQHandler   
 346              	   .thumb_set TIM1_CC_IRQHandler,Default_Handler
 347              	                  
 348              	   .weak      TIM2_IRQHandler            
 349              	   .thumb_set TIM2_IRQHandler,Default_Handler
 350              	                  
 351              	   .weak      TIM3_IRQHandler            
 352              	   .thumb_set TIM3_IRQHandler,Default_Handler
 353              	                  
 354              	   .weak      TIM4_IRQHandler            
 355              	   .thumb_set TIM4_IRQHandler,Default_Handler
 356              	                  
 357              	   .weak      I2C1_EV_IRQHandler   
 358              	   .thumb_set I2C1_EV_IRQHandler,Default_Handler
 359              	                     
 360              	   .weak      I2C1_ER_IRQHandler   
 361              	   .thumb_set I2C1_ER_IRQHandler,Default_Handler
 362              	                     
 363              	   .weak      I2C2_EV_IRQHandler   
 364              	   .thumb_set I2C2_EV_IRQHandler,Default_Handler
 365              	                  
 366              	   .weak      I2C2_ER_IRQHandler   
 367              	   .thumb_set I2C2_ER_IRQHandler,Default_Handler
 368              	                           
 369              	   .weak      SPI1_IRQHandler            
 370              	   .thumb_set SPI1_IRQHandler,Default_Handler
 371              	                        
 372              	   .weak      SPI2_IRQHandler            
 373              	   .thumb_set SPI2_IRQHandler,Default_Handler
 374              	                  
 375              	   .weak      USART1_IRQHandler      
 376              	   .thumb_set USART1_IRQHandler,Default_Handler
 377              	                     
 378              	   .weak      USART2_IRQHandler      
 379              	   .thumb_set USART2_IRQHandler,Default_Handler
 380              	                     
 381              	   .weak      USART3_IRQHandler      
 382              	   .thumb_set USART3_IRQHandler,Default_Handler
 383              	                  
 384              	   .weak      EXTI15_10_IRQHandler               
 385              	   .thumb_set EXTI15_10_IRQHandler,Default_Handler
 386              	               
 387              	   .weak      RTC_Alarm_IRQHandler               
 388              	   .thumb_set RTC_Alarm_IRQHandler,Default_Handler
 389              	            
 390              	   .weak      OTG_FS_WKUP_IRQHandler         
 391              	   .thumb_set OTG_FS_WKUP_IRQHandler,Default_Handler
 392              	            
 393              	   .weak      TIM8_BRK_TIM12_IRQHandler         
 394              	   .thumb_set TIM8_BRK_TIM12_IRQHandler,Default_Handler
 395              	         
 396              	   .weak      TIM8_UP_TIM13_IRQHandler            
 397              	   .thumb_set TIM8_UP_TIM13_IRQHandler,Default_Handler
 398              	         
 399              	   .weak      TIM8_TRG_COM_TIM14_IRQHandler      
 400              	   .thumb_set TIM8_TRG_COM_TIM14_IRQHandler,Default_Handler
ARM GAS  C:\Users\aabdev\AppData\Local\Temp\cclkaQHQ.s 			page 8


 401              	      
 402              	   .weak      TIM8_CC_IRQHandler   
 403              	   .thumb_set TIM8_CC_IRQHandler,Default_Handler
 404              	                  
 405              	   .weak      DMA1_Stream7_IRQHandler               
 406              	   .thumb_set DMA1_Stream7_IRQHandler,Default_Handler
 407              	                     
 408              	   .weak      FSMC_IRQHandler            
 409              	   .thumb_set FSMC_IRQHandler,Default_Handler
 410              	                     
 411              	   .weak      SDIO_IRQHandler            
 412              	   .thumb_set SDIO_IRQHandler,Default_Handler
 413              	                     
 414              	   .weak      TIM5_IRQHandler            
 415              	   .thumb_set TIM5_IRQHandler,Default_Handler
 416              	                     
 417              	   .weak      SPI3_IRQHandler            
 418              	   .thumb_set SPI3_IRQHandler,Default_Handler
 419              	                     
 420              	   .weak      UART4_IRQHandler         
 421              	   .thumb_set UART4_IRQHandler,Default_Handler
 422              	                  
 423              	   .weak      UART5_IRQHandler         
 424              	   .thumb_set UART5_IRQHandler,Default_Handler
 425              	                  
 426              	   .weak      TIM6_DAC_IRQHandler                  
 427              	   .thumb_set TIM6_DAC_IRQHandler,Default_Handler
 428              	               
 429              	   .weak      TIM7_IRQHandler            
 430              	   .thumb_set TIM7_IRQHandler,Default_Handler
 431              	         
 432              	   .weak      DMA2_Stream0_IRQHandler               
 433              	   .thumb_set DMA2_Stream0_IRQHandler,Default_Handler
 434              	               
 435              	   .weak      DMA2_Stream1_IRQHandler               
 436              	   .thumb_set DMA2_Stream1_IRQHandler,Default_Handler
 437              	                  
 438              	   .weak      DMA2_Stream2_IRQHandler               
 439              	   .thumb_set DMA2_Stream2_IRQHandler,Default_Handler
 440              	            
 441              	   .weak      DMA2_Stream3_IRQHandler               
 442              	   .thumb_set DMA2_Stream3_IRQHandler,Default_Handler
 443              	            
 444              	   .weak      DMA2_Stream4_IRQHandler               
 445              	   .thumb_set DMA2_Stream4_IRQHandler,Default_Handler
 446              	            
 447              	   .weak      ETH_IRQHandler      
 448              	   .thumb_set ETH_IRQHandler,Default_Handler
 449              	                  
 450              	   .weak      ETH_WKUP_IRQHandler                  
 451              	   .thumb_set ETH_WKUP_IRQHandler,Default_Handler
 452              	            
 453              	   .weak      CAN2_TX_IRQHandler   
 454              	   .thumb_set CAN2_TX_IRQHandler,Default_Handler
 455              	                           
 456              	   .weak      CAN2_RX0_IRQHandler                  
 457              	   .thumb_set CAN2_RX0_IRQHandler,Default_Handler
ARM GAS  C:\Users\aabdev\AppData\Local\Temp\cclkaQHQ.s 			page 9


 458              	                           
 459              	   .weak      CAN2_RX1_IRQHandler                  
 460              	   .thumb_set CAN2_RX1_IRQHandler,Default_Handler
 461              	                           
 462              	   .weak      CAN2_SCE_IRQHandler                  
 463              	   .thumb_set CAN2_SCE_IRQHandler,Default_Handler
 464              	                           
 465              	   .weak      OTG_FS_IRQHandler      
 466              	   .thumb_set OTG_FS_IRQHandler,Default_Handler
 467              	                     
 468              	   .weak      DMA2_Stream5_IRQHandler               
 469              	   .thumb_set DMA2_Stream5_IRQHandler,Default_Handler
 470              	                  
 471              	   .weak      DMA2_Stream6_IRQHandler               
 472              	   .thumb_set DMA2_Stream6_IRQHandler,Default_Handler
 473              	                  
 474              	   .weak      DMA2_Stream7_IRQHandler               
 475              	   .thumb_set DMA2_Stream7_IRQHandler,Default_Handler
 476              	                  
 477              	   .weak      USART6_IRQHandler      
 478              	   .thumb_set USART6_IRQHandler,Default_Handler
 479              	                        
 480              	   .weak      I2C3_EV_IRQHandler   
 481              	   .thumb_set I2C3_EV_IRQHandler,Default_Handler
 482              	                        
 483              	   .weak      I2C3_ER_IRQHandler   
 484              	   .thumb_set I2C3_ER_IRQHandler,Default_Handler
 485              	                        
 486              	   .weak      OTG_HS_EP1_OUT_IRQHandler         
 487              	   .thumb_set OTG_HS_EP1_OUT_IRQHandler,Default_Handler
 488              	               
 489              	   .weak      OTG_HS_EP1_IN_IRQHandler            
 490              	   .thumb_set OTG_HS_EP1_IN_IRQHandler,Default_Handler
 491              	               
 492              	   .weak      OTG_HS_WKUP_IRQHandler         
 493              	   .thumb_set OTG_HS_WKUP_IRQHandler,Default_Handler
 494              	            
 495              	   .weak      OTG_HS_IRQHandler      
 496              	   .thumb_set OTG_HS_IRQHandler,Default_Handler
 497              	                  
 498              	   .weak      DCMI_IRQHandler            
 499              	   .thumb_set DCMI_IRQHandler,Default_Handler
 500              	                                   
 501              	   .weak      HASH_RNG_IRQHandler                  
 502              	   .thumb_set HASH_RNG_IRQHandler,Default_Handler   
 503              	
 504              	   .weak      FPU_IRQHandler                  
 505              	   .thumb_set FPU_IRQHandler,Default_Handler  
ARM GAS  C:\Users\aabdev\AppData\Local\Temp\cclkaQHQ.s 			page 10


DEFINED SYMBOLS
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:127    .isr_vector:00000000 g_pfnVectors
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 Default_Handler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:60     .text.Reset_Handler:00000000 Reset_Handler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:61     .text.Reset_Handler:00000000 $t
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:75     .text.Reset_Handler:00000014 LoopCopyDataInit
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:70     .text.Reset_Handler:0000000e CopyDataInit
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:90     .text.Reset_Handler:00000026 LoopFillZerobss
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:86     .text.Reset_Handler:00000022 FillZerobss
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:112    .text.Default_Handler:00000000 Infinite_Loop
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:113    .text.Default_Handler:00000000 $t
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 NMI_Handler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 HardFault_Handler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 MemManage_Handler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 BusFault_Handler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 UsageFault_Handler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 SVC_Handler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 DebugMon_Handler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 PendSV_Handler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 SysTick_Handler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 WWDG_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 PVD_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 TAMP_STAMP_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 RTC_WKUP_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 FLASH_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 RCC_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 EXTI0_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 EXTI1_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 EXTI2_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 EXTI3_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 EXTI4_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 DMA1_Stream0_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 DMA1_Stream1_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 DMA1_Stream2_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 DMA1_Stream3_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 DMA1_Stream4_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 DMA1_Stream5_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 DMA1_Stream6_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 ADC_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 CAN1_TX_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 CAN1_RX0_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 CAN1_RX1_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 CAN1_SCE_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 EXTI9_5_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 TIM1_BRK_TIM9_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 TIM1_UP_TIM10_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 TIM1_TRG_COM_TIM11_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 TIM1_CC_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 TIM2_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 TIM3_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 TIM4_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 I2C1_EV_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 I2C1_ER_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 I2C2_EV_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 I2C2_ER_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 SPI1_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 SPI2_IRQHandler
ARM GAS  C:\Users\aabdev\AppData\Local\Temp\cclkaQHQ.s 			page 11


C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 USART1_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 USART2_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 USART3_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 EXTI15_10_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 RTC_Alarm_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 OTG_FS_WKUP_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 TIM8_BRK_TIM12_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 TIM8_UP_TIM13_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 TIM8_TRG_COM_TIM14_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 TIM8_CC_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 DMA1_Stream7_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 FSMC_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 SDIO_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 TIM5_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 SPI3_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 UART4_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 UART5_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 TIM6_DAC_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 TIM7_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 DMA2_Stream0_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 DMA2_Stream1_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 DMA2_Stream2_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 DMA2_Stream3_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 DMA2_Stream4_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 ETH_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 ETH_WKUP_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 CAN2_TX_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 CAN2_RX0_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 CAN2_RX1_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 CAN2_SCE_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 OTG_FS_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 DMA2_Stream5_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 DMA2_Stream6_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 DMA2_Stream7_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 USART6_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 I2C3_EV_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 I2C3_ER_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 OTG_HS_EP1_OUT_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 OTG_HS_EP1_IN_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 OTG_HS_WKUP_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 OTG_HS_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 DCMI_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 HASH_RNG_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:111    .text.Default_Handler:00000000 FPU_IRQHandler
C:/projects/workspace/code_base_firmware/source/microcontroller/stm32f407vg/startup_stm32f407xx.S:505    .text.Reset_Handler:00000038 $d
                            .text:00000000 $d

UNDEFINED SYMBOLS
_sidata
_sdata
_edata
_sbss
_ebss
_estack
SystemInit
__libc_init_array
main
ARM GAS  C:\Users\aabdev\AppData\Local\Temp\cclkaQHQ.s 			page 12


