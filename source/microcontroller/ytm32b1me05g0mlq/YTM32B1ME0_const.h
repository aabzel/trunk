 
#ifndef YTM32B1ME0_CONST_H_ 
#define YTM32B1ME0_CONST_H_
 

 
/**
 * @brief Defines the Interrupt Numbers definitions
 *
 * This enumeration is used to configure the interrupts.
 *
 * Implements : IRQn_Type_Class
 */
typedef enum
{
  /* Auxiliary constants */
  NotAvail_IRQn     = -128,                /**< Not available device specific interrupt */

  /* Core interrupts */
  NMI_IRQn                    =  -14,                /**< NMI Interrupt */ 
  HardFault_IRQn              =  -13,                /**< HardFault Interrupt */ 
  MemManage_IRQn              =  -12,                /**< MemManage Interrupt */ 
  BusFault_IRQn               =  -11,                /**< BusFault Interrupt */ 
  UsageFault_IRQn             =  -10,                /**< UsageFault Interrupt */ 
  SVC_IRQn                    =   -5,                /**< SVC Interrupt */ 
  DebugMon_IRQn               =   -4,                /**< DebugMon Interrupt */ 
  PendSV_IRQn                 =   -2,                /**< PendSV Interrupt */ 
  SysTick_IRQn                =   -1,                /**< SysTick Interrupt */ 
  /* Device specific interrupts */
  DMA0_IRQn                   =    0,                /**< DMA0 Interrupt */ 
  DMA1_IRQn                   =    1,                /**< DMA1 Interrupt */ 
  DMA2_IRQn                   =    2,                /**< DMA2 Interrupt */ 
  DMA3_IRQn                   =    3,                /**< DMA3 Interrupt */ 
  DMA4_IRQn                   =    4,                /**< DMA4 Interrupt */ 
  DMA5_IRQn                   =    5,                /**< DMA5 Interrupt */ 
  DMA6_IRQn                   =    6,                /**< DMA6 Interrupt */ 
  DMA7_IRQn                   =    7,                /**< DMA7 Interrupt */ 
  DMA8_IRQn                   =    8,                /**< DMA8 Interrupt */ 
  DMA9_IRQn                   =    9,                /**< DMA9 Interrupt */ 
  DMA10_IRQn                  =   10,                /**< DMA10 Interrupt */ 
  DMA11_IRQn                  =   11,                /**< DMA11 Interrupt */ 
  DMA12_IRQn                  =   12,                /**< DMA12 Interrupt */ 
  DMA13_IRQn                  =   13,                /**< DMA13 Interrupt */ 
  DMA14_IRQn                  =   14,                /**< DMA14 Interrupt */ 
  DMA15_IRQn                  =   15,                /**< DMA15 Interrupt */ 
  DMA_Error_IRQn              =   16,                /**< DMA_Error Interrupt */ 
  FPU_IRQn                    =   17,                /**< FPU Interrupt */ 
  EFM_IRQn                    =   18,                /**< EFM Interrupt */ 
  EFM_Error_IRQn              =   19,                /**< EFM_Error Interrupt */ 
  PCU_IRQn                    =   20,                /**< PCU Interrupt */ 
  EFM_Ecc_IRQn                =   21,                /**< EFM_Ecc Interrupt */ 
  WDG_IRQn                    =   22,                /**< WDG Interrupt */ 
  RCU_IRQn                    =   23,                /**< RCU Interrupt */ 
  I2C0_Master_IRQn            =   24,                /**< I2C0_Master Interrupt */ 
  I2C0_Slave_IRQn             =   25,                /**< I2C0_Slave Interrupt */ 
  SPI0_IRQn                   =   26,                /**< SPI0 Interrupt */ 
  SPI1_IRQn                   =   27,                /**< SPI1 Interrupt */ 
  SPI2_IRQn                   =   28,                /**< SPI2 Interrupt */ 
  I2C1_Master_IRQn            =   29,                /**< I2C1_Master Interrupt */ 
  I2C1_Slave_IRQn             =   30,                /**< I2C1_Slave Interrupt */ 
  LINFlexD0_IRQn              =   31,                /**< LINFlexD0 Interrupt */ 
  Reserved5_IRQn              =   32,                /**< Reserved5 Interrupt */ 
  LINFlexD1_IRQn              =   33,                /**< LINFlexD1 Interrupt */ 
  Reserved6_IRQn              =   34,                /**< Reserved6 Interrupt */ 
  LINFlexD2_IRQn              =   35,                /**< LINFlexD2 Interrupt */ 
  Reserved7_IRQn              =   36,                /**< Reserved7 Interrupt */ 
  Reserved8_IRQn              =   37,                /**< Reserved8 Interrupt */ 
  Reserved9_IRQn              =   38,                /**< Reserved9 Interrupt */ 
  ADC0_IRQn                   =   39,                /**< ADC0 Interrupt */ 
  ADC1_IRQn                   =   40,                /**< ADC1 Interrupt */ 
  ACMP0_IRQn                  =   41,                /**< ACMP0 Interrupt */ 
  Reserved10_IRQn             =   42,                /**< Reserved10 Interrupt */ 
  Reserved11_IRQn             =   43,                /**< Reserved11 Interrupt */ 
  EMU_IRQn                    =   44,                /**< EMU Interrupt */ 
  Reserved12_IRQn             =   45,                /**< Reserved12 Interrupt */ 
  RTC_IRQn                    =   46,                /**< RTC Interrupt */ 
  RTC_Seconds_IRQn            =   47,                /**< RTC_Seconds Interrupt */ 
  pTMR_Ch0_IRQn               =   48,                /**< pTMR_Ch0 Interrupt */ 
  pTMR_Ch1_IRQn               =   49,                /**< pTMR_Ch1 Interrupt */ 
  pTMR_Ch2_IRQn               =   50,                /**< pTMR_Ch2 Interrupt */ 
  pTMR_Ch3_IRQn               =   51,                /**< pTMR_Ch3 Interrupt */ 
  PTU0_IRQn                   =   52,                /**< PTU0 Interrupt */ 
  Reserved13_IRQn             =   53,                /**< Reserved13 Interrupt */ 
  Reserved14_IRQn             =   54,                /**< Reserved14 Interrupt */ 
  Reserved15_IRQn             =   55,                /**< Reserved15 Interrupt */ 
  Reserved16_IRQn             =   56,                /**< Reserved16 Interrupt */ 
  SCU_IRQn                    =   57,                /**< SCU Interrupt */ 
  lpTMR0_IRQn                 =   58,                /**< lpTMR0 Interrupt */ 
  GPIOA_IRQn                  =   59,                /**< GPIOA Interrupt */ 
  GPIOB_IRQn                  =   60,                /**< GPIOB Interrupt */ 
  GPIOC_IRQn                  =   61,                /**< GPIOC Interrupt */ 
  GPIOD_IRQn                  =   62,                /**< GPIOD Interrupt */ 
  GPIOE_IRQn                  =   63,                /**< GPIOE Interrupt */ 
  Reserved17_IRQn             =   64,                /**< Reserved17 Interrupt */ 
  Reserved18_IRQn             =   65,                /**< Reserved18 Interrupt */ 
  Reserved19_IRQn             =   66,                /**< Reserved19 Interrupt */ 
  Reserved20_IRQn             =   67,                /**< Reserved20 Interrupt */ 
  PTU1_IRQn                   =   68,                /**< PTU1 Interrupt */ 
  Reserved21_IRQn             =   69,                /**< Reserved21 Interrupt */ 
  Reserved22_IRQn             =   70,                /**< Reserved22 Interrupt */ 
  Reserved23_IRQn             =   71,                /**< Reserved23 Interrupt */ 
  Reserved24_IRQn             =   72,                /**< Reserved24 Interrupt */ 
  Reserved25_IRQn             =   73,                /**< Reserved25 Interrupt */ 
  Reserved26_IRQn             =   74,                /**< Reserved26 Interrupt */ 
  Reserved27_IRQn             =   75,                /**< Reserved27 Interrupt */ 
  Reserved28_IRQn             =   76,                /**< Reserved28 Interrupt */ 
  Reserved29_IRQn             =   77,                /**< Reserved29 Interrupt */ 
  CAN0_ORed_IRQn              =   78,                /**< CAN0_ORed Interrupt */ 
  CAN0_Error_IRQn             =   79,                /**< CAN0_Error Interrupt */ 
  CAN0_Wake_Up_IRQn           =   80,                /**< CAN0_Wake_Up Interrupt */ 
  CAN0_ORed_0_15_MB_IRQn      =   81,                /**< CAN0_ORed_0_15_MB Interrupt */ 
  CAN0_ORed_16_31_MB_IRQn     =   82,                /**< CAN0_ORed_16_31_MB Interrupt */ 
  CAN0_ORed_32_47_MB_IRQn     =   83,                /**< CAN0_ORed_32_47_MB Interrupt */ 
  CAN0_ORed_48_63_MB_IRQn     =   84,                /**< CAN0_ORed_48_63_MB Interrupt */ 
  CAN1_ORed_IRQn              =   85,                /**< CAN1_ORed Interrupt */ 
  CAN1_Error_IRQn             =   86,                /**< CAN1_Error Interrupt */ 
  CAN1_Wake_Up_IRQn           =   87,                /**< CAN1_Wake_Up Interrupt */ 
  CAN1_ORed_0_15_MB_IRQn      =   88,                /**< CAN1_ORed_0_15_MB Interrupt */ 
  CAN1_ORed_16_31_MB_IRQn     =   89,                /**< CAN1_ORed_16_31_MB Interrupt */ 
  CAN1_ORed_32_47_MB_IRQn     =   90,                /**< CAN1_ORed_32_47_MB Interrupt */ 
  CAN1_ORed_48_63_MB_IRQn     =   91,                /**< CAN1_ORed_48_63_MB Interrupt */ 
  CAN2_ORed_IRQn              =   92,                /**< CAN2_ORed Interrupt */ 
  CAN2_Error_IRQn             =   93,                /**< CAN2_Error Interrupt */ 
  CAN2_Wake_Up_IRQn           =   94,                /**< CAN2_Wake_Up Interrupt */ 
  CAN2_ORed_0_15_MB_IRQn      =   95,                /**< CAN2_ORed_0_15_MB Interrupt */ 
  CAN2_ORed_16_31_MB_IRQn     =   96,                /**< CAN2_ORed_16_31_MB Interrupt */ 
  CAN2_ORed_32_47_MB_IRQn     =   97,                /**< CAN2_ORed_32_47_MB Interrupt */ 
  CAN2_ORed_48_63_MB_IRQn     =   98,                /**< CAN2_ORed_48_63_MB Interrupt */ 
  eTMR0_Ch0_Ch1_IRQn          =   99,                /**< eTMR0_Ch0_Ch1 Interrupt */ 
  eTMR0_Ch2_Ch3_IRQn          =  100,                /**< eTMR0_Ch2_Ch3 Interrupt */ 
  eTMR0_Ch4_Ch5_IRQn          =  101,                /**< eTMR0_Ch4_Ch5 Interrupt */ 
  eTMR0_Ch6_Ch7_IRQn          =  102,                /**< eTMR0_Ch6_Ch7 Interrupt */ 
  eTMR0_Fault_IRQn            =  103,                /**< eTMR0_Fault Interrupt */ 
  eTMR0_Ovf_IRQn              =  104,                /**< eTMR0_Ovf Interrupt */ 
  eTMR1_Ch0_Ch1_IRQn          =  105,                /**< eTMR1_Ch0_Ch1 Interrupt */ 
  eTMR1_Ch2_Ch3_IRQn          =  106,                /**< eTMR1_Ch2_Ch3 Interrupt */ 
  eTMR1_Ch4_Ch5_IRQn          =  107,                /**< eTMR1_Ch4_Ch5 Interrupt */ 
  eTMR1_Ch6_Ch7_IRQn          =  108,                /**< eTMR1_Ch6_Ch7 Interrupt */ 
  eTMR1_Fault_IRQn            =  109,                /**< eTMR1_Fault Interrupt */ 
  eTMR1_Ovf_IRQn              =  110,                /**< eTMR1_Ovf Interrupt */ 
  eTMR2_Ch0_Ch1_IRQn          =  111,                /**< eTMR2_Ch0_Ch1 Interrupt */ 
  eTMR2_Ch2_Ch3_IRQn          =  112,                /**< eTMR2_Ch2_Ch3 Interrupt */ 
  eTMR2_Ch4_Ch5_IRQn          =  113,                /**< eTMR2_Ch4_Ch5 Interrupt */ 
  eTMR2_Ch6_Ch7_IRQn          =  114,                /**< eTMR2_Ch6_Ch7 Interrupt */ 
  eTMR2_Fault_IRQn            =  115,                /**< eTMR2_Fault Interrupt */ 
  eTMR2_Ovf_IRQn              =  116,                /**< eTMR2_Ovf Interrupt */ 
  eTMR3_Ch0_Ch1_IRQn          =  117,                /**< eTMR3_Ch0_Ch1 Interrupt */ 
  eTMR3_Ch2_Ch3_IRQn          =  118,                /**< eTMR3_Ch2_Ch3 Interrupt */ 
  eTMR3_Ch4_Ch5_IRQn          =  119,                /**< eTMR3_Ch4_Ch5 Interrupt */ 
  eTMR3_Ch6_Ch7_IRQn          =  120,                /**< eTMR3_Ch6_Ch7 Interrupt */ 
  eTMR3_Fault_IRQn            =  121,                /**< eTMR3_Fault Interrupt */ 
  eTMR3_Ovf_IRQn              =  122,                /**< eTMR3_Ovf Interrupt */ 
  eTMR4_Ch0_Ch1_IRQn          =  123,                /**< eTMR4_Ch0_Ch1 Interrupt */ 
  eTMR4_Ch2_Ch3_IRQn          =  124,                /**< eTMR4_Ch2_Ch3 Interrupt */ 
  eTMR4_Ch4_Ch5_IRQn          =  125,                /**< eTMR4_Ch4_Ch5 Interrupt */ 
  eTMR4_Ch6_Ch7_IRQn          =  126,                /**< eTMR4_Ch6_Ch7 Interrupt */ 
  eTMR4_Fault_IRQn            =  127,                /**< eTMR4_Fault Interrupt */ 
  eTMR4_Ovf_IRQn              =  128,                /**< eTMR4_Ovf Interrupt */ 
  eTMR5_Ch0_Ch1_IRQn          =  129,                /**< eTMR5_Ch0_Ch1 Interrupt */ 
  eTMR5_Ch2_Ch3_IRQn          =  130,                /**< eTMR5_Ch2_Ch3 Interrupt */ 
  eTMR5_Ch4_Ch5_IRQn          =  131,                /**< eTMR5_Ch4_Ch5 Interrupt */ 
  eTMR5_Ch6_Ch7_IRQn          =  132,                /**< eTMR5_Ch6_Ch7 Interrupt */ 
  eTMR5_Fault_IRQn            =  133,                /**< eTMR5_Fault Interrupt */ 
  eTMR5_Ovf_IRQn              =  134,                /**< eTMR5_Ovf Interrupt */ 
  Reserved30_IRQn             =  135,                /**< Reserved30 Interrupt */ 
  Reserved31_IRQn             =  136,                /**< Reserved31 Interrupt */ 
  Reserved32_IRQn             =  137,                /**< Reserved32 Interrupt */ 
  Reserved33_IRQn             =  138,                /**< Reserved33 Interrupt */ 
  Reserved34_IRQn             =  139,                /**< Reserved34 Interrupt */ 
  Reserved35_IRQn             =  140,                /**< Reserved35 Interrupt */ 
  Reserved36_IRQn             =  141,                /**< Reserved36 Interrupt */ 
  Reserved37_IRQn             =  142,                /**< Reserved37 Interrupt */ 
  Reserved38_IRQn             =  143,                /**< Reserved38 Interrupt */ 
  Reserved39_IRQn             =  144,                /**< Reserved39 Interrupt */ 
  Reserved40_IRQn             =  145,                /**< Reserved40 Interrupt */ 
  Reserved41_IRQn             =  146,                /**< Reserved41 Interrupt */ 
  Reserved42_IRQn             =  147,                /**< Reserved42 Interrupt */ 
  Reserved43_IRQn             =  148,                /**< Reserved43 Interrupt */ 
  Reserved44_IRQn             =  149,                /**< Reserved44 Interrupt */ 
  Reserved45_IRQn             =  150,                /**< Reserved45 Interrupt */ 
  Reserved46_IRQn             =  151,                /**< Reserved46 Interrupt */ 
  Reserved47_IRQn             =  152,                /**< Reserved47 Interrupt */ 
  Reserved48_IRQn             =  153,                /**< Reserved48 Interrupt */ 
  Reserved49_IRQn             =  154,                /**< Reserved49 Interrupt */ 
  Reserved50_IRQn             =  155,                /**< Reserved50 Interrupt */ 
  TRNG_IRQn                   =  156,                /**< TRNG Interrupt */ 
  HCU_IRQn                    =  157,                /**< HCU Interrupt */ 
  INTM_IRQn                   =  158,                /**< INTM Interrupt */ 
  TMR0_Ch0_IRQn               =  159,                /**< TMR0_Ch0 Interrupt */ 
  TMR0_Ch1_IRQn               =  160,                /**< TMR0_Ch1 Interrupt */ 
  TMR0_Ch2_IRQn               =  161,                /**< TMR0_Ch2 Interrupt */ 
  TMR0_Ch3_IRQn               =  162,                /**< TMR0_Ch3 Interrupt */ 
  LINFlexD3_IRQn              =  163,                /**< LINFlexD3 Interrupt */ 
  LINFlexD4_IRQn              =  164,                /**< LINFlexD4 Interrupt */ 
  LINFlexD5_IRQn              =  165,                /**< LINFlexD5 Interrupt */ 
  I2C2_Master_IRQn            =  166,                /**< I2C2_Master Interrupt */ 
  I2C2_Slave_IRQn             =  167,                /**< I2C2_Slave Interrupt */ 
  SPI3_IRQn                   =  168,                /**< SPI3 Interrupt */ 
  SPI4_IRQn                   =  169,                /**< SPI4 Interrupt */ 
  SPI5_IRQn                   =  170,                /**< SPI5 Interrupt */ 
  CAN3_ORed_IRQn              =  171,                /**< CAN3_ORed Interrupt */ 
  CAN3_Error_IRQn             =  172,                /**< CAN3_Error Interrupt */ 
  CAN3_Wake_Up_IRQn           =  173,                /**< CAN3_Wake_Up Interrupt */ 
  CAN3_ORed_0_15_MB_IRQn      =  174,                /**< CAN3_ORed_0_15_MB Interrupt */ 
  CAN3_ORed_16_31_MB_IRQn     =  175,                /**< CAN3_ORed_16_31_MB Interrupt */ 
  Reserved51_IRQn             =  176,                /**< Reserved51 Interrupt */ 
  Reserved52_IRQn             =  177,                /**< Reserved52 Interrupt */ 
  CAN4_ORed_IRQn              =  178,                /**< CAN4_ORed Interrupt */ 
  CAN4_Error_IRQn             =  179,                /**< CAN4_Error Interrupt */ 
  CAN4_Wake_Up_IRQn           =  180,                /**< CAN4_Wake_Up Interrupt */ 
  CAN4_ORed_0_15_MB_IRQn      =  181,                /**< CAN4_ORed_0_15_MB Interrupt */ 
  CAN4_ORed_16_31_MB_IRQn     =  182,                /**< CAN4_ORed_16_31_MB Interrupt */ 
  Reserved53_IRQn             =  183,                /**< Reserved53 Interrupt */ 
  Reserved54_IRQn             =  184,                /**< Reserved54 Interrupt */ 
  CAN5_ORed_IRQn              =  185,                /**< CAN5_ORed Interrupt */ 
  CAN5_Error_IRQn             =  186,                /**< CAN5_Error Interrupt */ 
  CAN5_Wake_Up_IRQn           =  187,                /**< CAN5_Wake_Up Interrupt */ 
  CAN5_ORed_0_15_MB_IRQn      =  188,                /**< CAN5_ORed_0_15_MB Interrupt */ 
  CAN5_ORed_16_31_MB_IRQn     =  189,                /**< CAN5_ORed_16_31_MB Interrupt */ 
  WKU_IRQn                    =  190,                /**< WKU Interrupt */ 
  ALIGN_0_IRQn                =  191,                /**< ALIGN_0 Interrupt */ 
} IRQn_Type;





#endif