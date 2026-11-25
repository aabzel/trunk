#include "fc7300f8mdt_diag.h"

#include "interrupt_types.h"

const IntNumInfo_t IntNumInfo[]={

 { .int_n=NonMaskableInt_IRQn , .name="NonMaskableInt", },  /* Non Maskable Interrupt */
  { .int_n=HardFault_IRQn , .name="HardFault", },  /* Cortex-M4 SV Hard Fault Interrupt */
  { .int_n=MemoryManagement_IRQn , .name="MemoryManagement", },  /* Cortex-M4 Memory Management Interrupt */
  { .int_n=BusFault_IRQn , .name="BusFault", },  /* Cortex-M4 Bus Fault Interrupt */
  { .int_n=UsageFault_IRQn , .name="UsageFault", },  /* Cortex-M4 Usage Fault Interrupt */
  { .int_n=SVCall_IRQn , .name="", },  /* Cortex-M4 SV Call Interrupt */
  { .int_n=DebugMonitor_IRQn , .name="", },  /* Cortex-M4 Debug Monitor Interrupt */
  { .int_n=PendSV_IRQn , .name="PendSV", },  /* Cortex-M4 Pend SV Interrupt */
  { .int_n=SysTick_IRQn , .name="SysTick", },  /* Cortex-M4 System Tick Interrupt */
  { .int_n=DMA0_IRQn , .name="", },  /* DMA channel 0 transfer complete */
  { .int_n=DMA1_IRQn , .name="", },  /* DMA channel 1 transfer complete */
  { .int_n=DMA2_IRQn , .name="", },  /* DMA channel 2 transfer complete */
  { .int_n=DMA3_IRQn , .name="DMA3", },  /* DMA channel 3 transfer complete */
  { .int_n=DMA4_IRQn , .name="", },  /* DMA channel 4 transfer complete */
  { .int_n=DMA5_IRQn , .name="", },  /* DMA channel 5 transfer complete */
  { .int_n=DMA6_IRQn , .name="", },  /* DMA channel 6 transfer complete */
  { .int_n=DMA7_IRQn , .name="DMA7", },  /* DMA channel 7 transfer complete */
  { .int_n=DMA8_IRQn , .name="", },  /* DMA channel 8 transfer complete */
  { .int_n=DMA9_IRQn , .name="", },  /* DMA channel 9 transfer complete */
  { .int_n=DMA10_IRQn , .name="", },  /* DMA channel 10 transfer complete */
  { .int_n=DMA11_IRQn , .name="DMA11", },  /* DMA channel 11 transfer complete */
  { .int_n=DMA12_IRQn , .name="", },  /* DMA channel 12 transfer complete */
  { .int_n=DMA13_IRQn , .name="", },  /* DMA channel 13 transfer complete */
  { .int_n=DMA14_IRQn , .name="", },  /* DMA channel 14 transfer complete */
  { .int_n=DMA15_IRQn , .name="", },  /* DMA channel 15 transfer complete */
  { .int_n=DMA16_IRQn , .name="", },  /*  DMA channel 16 transfer complete */
  { .int_n=DMA17_IRQn , .name="", },  /*  DMA channel 17 transfer complete */
  { .int_n=DMA18_IRQn , .name="", },  /*  DMA channel 18 transfer complete */
  { .int_n=DMA19_IRQn , .name="DMA19", },  /*  DMA channel 19 transfer complete */
  { .int_n=DMA20_IRQn , .name="", },  /*  DMA channel 20 transfer complete */
  { .int_n=DMA21_IRQn , .name="", },  /*  DMA channel 21 transfer complete */
  { .int_n=DMA22_IRQn , .name="", },  /*  DMA channel 22 transfer complete */
  { .int_n=DMA23_IRQn , .name="", },  /*  DMA channel 23 transfer complete */
  { .int_n=DMA24_IRQn , .name="", },  /*  DMA channel 24 transfer complete */
  { .int_n=DMA25_IRQn , .name="DMA25", },  /*  DMA channel 25 transfer complete */
  { .int_n=DMA26_IRQn , .name="DMA26", },  /*  DMA channel 26 transfer complete */
  { .int_n=DMA27_IRQn , .name="", },  /*  DMA channel 27 transfer complete */
  { .int_n=DMA28_IRQn , .name="", },  /*  DMA channel 28 transfer complete */
  { .int_n=DMA29_IRQn , .name="", },  /*  DMA channel 29 transfer complete */
  { .int_n=DMA30_IRQn , .name="", },  /*  DMA channel 30 transfer complete */
  { .int_n=DMA31_IRQn , .name="DMA31", },  /*  DMA channel 31 transfer complete */
  { .int_n=DMA_Error_IRQn , .name="DMA_Error", },  /*  DMA error interrupt channels 0-63 */
  { .int_n=CPM_IRQn , .name="CPM", },  /*  FPU etc. interrupt */
  { .int_n=FC_IRQn , .name="", },  /*  FC Command complete */
  { .int_n=LVD_LVW_IRQn , .name="", },  /*  PMC Low voltage detect interrupt */
  { .int_n=TMU_IRQn , .name="", },  /*  Temperature Monitor Unit interrupt */
  { .int_n=WDOG0_IRQn , .name="", },  /*  interrupt request out before wdg reset out */
  { .int_n=WDOG1_IRQn , .name="WDOG1", },  /*  interrupt request out before wdg reset out */
  { .int_n=WDOG2_IRQn , .name="", },  /*  interrupt request out before wdg reset out */
  { .int_n=FCSMU0_IRQn , .name="FCSMU0", },  /*  Fault Control and Safety Manage Unit */
  { .int_n=STCU0_IRQn , .name="", },  /*  Safety Control Unit interrupt */
  { .int_n=ERM_fault_IRQn , .name="", },  /*  ERM single/double bit error correction */
  { .int_n=MAM0_IRQn , .name="", },  /*  Matrix Access Monitor interrupt */
  { .int_n=MAM1_IRQn , .name="MAM1", },  /*  Matrix Access Monitor interrupt */
  { .int_n=MAM2_IRQn , .name="", },  /*  Matrix Access Monitor interrupt */
  { .int_n=RESERVED_62_IRQn , .name="RES", },  /*  Reserved */
  { .int_n=RGM_Pre_IRQn , .name="RGM_Pre", },  /*  RGM pre-reset Interrupt */
  { .int_n=RGM_Other_IRQn , .name="RGM_Other", },  /*  RGM other CPU exit reset Interrupt */
  { .int_n=INTM0_IRQn , .name="INTM0", },  /*   INTM alarm interrupt */
  { .int_n=ISM0_IRQn , .name="ISM0", },  /*  ISM0 interrupt */
  { .int_n=MB_IRQn , .name="MailBox", },  /*  Mail Box interrupt */
  { .int_n=SCG_IRQn , .name="SCG", },  /*  SCG bus interrupt request */
  { .int_n=CMU0_IRQn , .name="CMU0", },  /*  CMU0 interrupt */
  { .int_n=CMU1_IRQn , .name="CMU1", },  /*  CMU1 interrupt */
  { .int_n=CMU2_IRQn , .name="", },  /*  CMU2 interrupt */
  { .int_n=CMU3_IRQn , .name="", },  /*  CMU3 interrupt */
  { .int_n=TSTMP0_IRQn , .name="", },  /*  TimerStamp0 interrupt */
  { .int_n=TSTMP1_IRQn , .name="", },  /*  TimerStamp1 interrupt */
  { .int_n=TSTMP2_IRQn , .name="TSTMP2", },  /*  TimerStamp2 interrupt */
  { .int_n=TSTMP3_IRQn , .name="", },  /*  TimerStamp3 interrupt */
  { .int_n=CORDIC_IRQn , .name="", },  /*  CORDIC Accelerator interrupt */
  { .int_n=HSM0_IRQn , .name="", },  /*  Crypto interrupt */
  { .int_n=FCPIT0_IRQn , .name="", },  /*  FCPIT0 interrupt */
  { .int_n=FCPIT1_IRQn , .name="FCPIT1", },  /*  FCPIT0 interrupt */
  { .int_n=RTC_IRQn , .name="", },  /*  RTC alarm or seconds interrupt  */
  { .int_n=ENET_Tx0_IRQn , .name="", },  /*  ENET 1588 Timer Interrupt - synchronous */
  { .int_n=ENET_Tx1_IRQn , .name="", },  /*  ENET Data transfer done */
  { .int_n=ENET_Rx0_IRQn , .name="", },  /*  ENET Receive Buffer Done for Ring/Queue 0 */
  { .int_n=ENET_Rx1_IRQn , .name="", },  /*  ENET Receive Buffer Done for Ring/Queue 0 */
  { .int_n=ENET_System_IRQn , .name="", },  /*  ENET System interrupt */
  { .int_n=AONTIMER_IRQn , .name="", },  /*  AONTIMER interrupt request */
  { .int_n=SWI_IRQn , .name="", },  /*  Software interrupt */
  { .int_n=OSPI_IRQn , .name="", },  /*  All OSPI interrupts */
  { .int_n=FREQM_IRQn , .name="", },  /*  FREQM interrupt */
  { .int_n=PORTA_IRQn , .name="", },  /*  Port A pin detect interrupt */
  { .int_n=PORTB_IRQn , .name="", },  /*  Port B pin detect interrupt */
  { .int_n=PORTC_IRQn , .name="PORTC", },  /*  Port C pin detect interrupt */
  { .int_n=PORTD_IRQn , .name="", },  /*  Port D pin detect interrupt */
  { .int_n=PORTE_IRQn , .name="", },  /*  Port E pin detect interrupt */
  { .int_n=PORTF_IRQn , .name="", },  /*  Port F pin detect interrupt */
  { .int_n=PORTG_IRQn , .name="", },  /*  Port G pin detect interrupt */
  { .int_n=PORTH_IRQn , .name="", },  /*  Port H pin detect interrupt */
  { .int_n=PORTI_IRQn , .name="", },  /*  Port I pin detect interrupt */
  { .int_n=FlexCAN0_IRQn , .name="", },  /*  CAN0 Interrupt */
  { .int_n=FlexCAN1_IRQn , .name="", },  /*  CAN1 Interrupt */
  { .int_n=FlexCAN2_IRQn , .name="", },  /*  CAN2 Interrupt */
  { .int_n=FlexCAN3_IRQn , .name="", },  /*  CAN3 Interrupt */
  { .int_n=FlexCAN4_IRQn , .name="", },  /*  CAN4 Interrupt */
  { .int_n=FlexCAN5_IRQn , .name="", },  /*  CAN5 Interrupt */
  { .int_n=FlexCAN6_IRQn , .name="", },  /*  CAN6 Interrupt */
  { .int_n=FlexCAN7_IRQn , .name="", },  /*  CAN7 Interrupt */
  { .int_n=FCIIC0_IRQn , .name="", },  /*  FCIIC0 Interrupt */
  { .int_n=FCIIC1_IRQn , .name="", },  /*  FCIIC1 Interrupt */
  { .int_n=FCSPI0_IRQn , .name="", },  /*  FCSPI0 Interrupt */
  { .int_n=FCSPI1_IRQn , .name="SPI1", },  /*  FCSPI1 Interrupt */
  { .int_n=FCSPI2_IRQn , .name="", },  /*  FCSPI2 Interrupt */
  { .int_n=FCSPI3_IRQn , .name="", },  /*  FCSPI0 Interrupt */
  { .int_n=FCSPI4_IRQn , .name="", },  /*  FCSPI1 Interrupt */
  { .int_n=FCSPI5_IRQn , .name="", },  /*  FCSPI2 Interrupt */
  { .int_n=FCUART0_IRQn , .name="FCUART0", },  /*  FCUART0 Transmit / Receive Interrupt */
  { .int_n=FCUART1_IRQn , .name="FCUART1", },  /*  FCUART1 Transmit / Receive  Interrupt */
  { .int_n=FCUART2_IRQn , .name="FCUART2", },  /*  FCUART2 Transmit / Receive  Interrupt */
  { .int_n=FCUART3_IRQn , .name="FCUART3", },  /*  FCUART3 Transmit / Receive Interrupt */
  { .int_n=FCUART4_IRQn , .name="FCUART4", },  /*  FCUART4 Transmit / Receive  Interrupt */
  { .int_n=FCUART5_IRQn , .name="FCUART5", },  /*  FCUART5 Transmit / Receive  Interrupt */
  { .int_n=FCUART6_IRQn , .name="FCUART6", },  /*  FCUART6 Transmit / Receive Interrupt */
  { .int_n=FCUART7_IRQn , .name="FCUART7", },  /*  FCUART7 Transmit / Receive  Interrupt */
  { .int_n=FCUART8_IRQn , .name="FCUART8", },  /*  FCUART8 Transmit / Receive  Interrupt */
  { .int_n=FCUART9_IRQn , .name="FCUART9", },  /*  FCUART9 Transmit / Receive Interrupt */
  { .int_n=FCUART10_IRQn , .name="FCUART10", },  /*  FCUART10 Transmit / Receive  Interrupt */
  { .int_n=FCUART11_IRQn , .name="FCUART11", },  /*  FCUART11 Transmit / Receive  Interrupt */
  { .int_n=FCUART12_IRQn , .name="FCUART12", },  /*  FCUART12 Transmit / Receive  Interrupt */
  { .int_n=FCUART13_IRQn , .name="FCUART13", },  /*  FCUART13 Transmit / Receive  Interrupt */
  { .int_n=FCUART14_IRQn , .name="FCUART14", },  /*  FCUART14 Transmit / Receive Interrupt */
  { .int_n=FCUART15_IRQn , .name="FCUART15", },  /*  FCUART15 Transmit / Receive  Interrupt */
  { .int_n=FTU0_IRQn , .name="", },  /*  FTU0 all source interrupt */
  { .int_n=FTU1_IRQn , .name="FTU1", },  /*  FTU1 all source interrupt */
  { .int_n=FTU2_IRQn , .name="", },  /*  FTU2 all source interrupt */
  { .int_n=FTU3_IRQn , .name="", },  /*  FTU3 all source interrupt */
  { .int_n=FTU4_IRQn , .name="", },  /*  FTU4 all source interrupt */
  { .int_n=FTU5_IRQn , .name="", },  /*  FTU5 all source interrupt */
  { .int_n=FTU6_IRQn , .name="", },  /*  FTU6 all source interrupt */
  { .int_n=FTU7_IRQn , .name="", },  /*  FTU7 all source interrupt */
  { .int_n=FTU8_IRQn , .name="", },  /*  FTU4 all source interrupt */
  { .int_n=FTU9_IRQn , .name="", },  /*  FTU5 all source interrupt */
  { .int_n=FTU10_IRQn , .name="", },  /*  FTU6 all source interrupt */
  { .int_n=FTU11_IRQn , .name="", },  /*  FTU7 all source interrupt */
  { .int_n=CMP0_IRQn , .name="", },  /*  CMP0 interrupt request  */
  { .int_n=CMP1_IRQn , .name="", },  /*  CMP1 interrupt request  */
  { .int_n=CMP2_IRQn , .name="", },  /*  CMP2 interrupt request  */
  { .int_n=ADC0_IRQn , .name="ADC0", },  /*  ADC0 interrupt request. */
  { .int_n=ADC1_IRQn , .name="ADC1", },  /*  ADC1 interrupt request. */
  { .int_n=ADC2_IRQn , .name="ADC1", },  /*  ADC2 interrupt request. */
  { .int_n=ADC3_IRQn , .name="ADC3", },  /*  ADC3 interrupt request. */
  { .int_n=PTIMER0_IRQn , .name="", },  /*  PTIMER0 interrupt */
  { .int_n=PTIMER1_IRQn , .name="", },  /*  PTIMER1 interrupt */
  { .int_n=PTIMER2_IRQn , .name="", },  /*  PTIMER2 interrupt */
  { .int_n=PTIMER3_IRQn , .name="", },  /*  PTIMER3 interrupt */
  { .int_n=SDDF0_IRQn , .name="", },  /*  SD Digital Filter interrupt request */
  { .int_n=MSC0_IRQn , .name="", },  /*  MSC interrupt */
  { .int_n=MSC1_IRQn , .name="", },  /*  MSC interrupt */
  { .int_n=FlexCAN8_IRQn , .name="", },  /*  CAN6 Interrupt */
  { .int_n=FlexCAN9_IRQn , .name="", },  /*  CAN7 Interrupt */
  { .int_n=SENT0_IRQn , .name="", },  /*  SENT all interrupt (fast or slow) */
  { .int_n=SENT1_IRQn , .name="", },  /*  SENT all interrupt (fast or slow) */
  { .int_n=FCSPI6_IRQn , .name="SPI6", },  /*  FCSPI6 Interrupt */
  { .int_n=FCSPI7_IRQn , .name="SPI7", },  /*  FCSPI7 Interrupt */
  { .int_n=FCUART16_IRQn , .name="UART16", },  /*  FCUART16 Transmit / Receive Interrupt */
  { .int_n=FCUART17_IRQn , .name="UART17", },  /*  FCUART17 Transmit / Receive  Interrupt */
  { .int_n=CTI0_IRQn , .name="CMU0", },  /*  CTI Interrupt */
  { .int_n=CTI1_IRQn , .name="CMU1", },  /*  CTI Interrupt */
  { .int_n=CTI2_IRQn , .name="CMU2", },  /*  CTI Interrupt */
  { .int_n=CMU4_IRQn , .name="CMU4", },  /*  CMU4 Interrupt */
};



uint32_t interrupt_info_get_cnt(void) {
    uint32_t cnt =0;
    cnt = ARRAY_SIZE(IntNumInfo);
    return cnt;

}
