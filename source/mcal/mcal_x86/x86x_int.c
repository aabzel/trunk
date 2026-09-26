#include "x86x_int.h"

#include "compiler_const.h"
#include "mcal_common.h"
//#include "c_defines_generated.h"

void NMI_Handler(void) {}

void HardFault_Handler(void) {
    /* go to infinite loop when hard fault exception occurs */
    while(1) {
    }
}

void MemManage_Handler(void) {
    /* go to infinite loop when memory manage exception occurs */
    while(1) {
    }
}

void BusFault_Handler(void) {
    /* go to infinite loop when bus fault exception occurs */
    while(1) {
    }
}

void UsageFault_Handler(void) {
    /* go to infinite loop when usage fault exception occurs */
    while(1) {
    }
}

void SVC_Handler(void) {}

void DebugMon_Handler(void) {}

void PendSV_Handler(void) {}

_WEAK_FUN_ void SysTick_Handler(void) {
#ifdef HAS_SYSTICK_INT
    SysTickIntHandler();
#endif /**/
}

void FCUART1_RxTx_IRQHandler(void) {
#ifdef HAS_UART
    UartHandle_t* Node = UartGetNode(1);
    if(Node) {
        FCUARTN_RxTx_IRQHandler(&Node->Handle);
    }
#endif
}

void FCUART2_RxTx_IRQHandler(void) {
#ifdef HAS_UART
    UartHandle_t* Node = UartGetNode(2);
    if(Node) {
        FCUARTN_RxTx_IRQHandler(&Node->Handle);
    }
#endif
}

void FCUART3_RxTx_IRQHandler(void) {
#ifdef HAS_UART
    UartHandle_t* Node = UartGetNode(3);
    if(Node) {
        FCUARTN_RxTx_IRQHandler(&Node->Handle);
    }
#endif
}

void Core0_MB_IRQHandler(void) {
#ifdef HAS_MULTICORE
    CoreX_MB_IRQHandler(1, 0);
#endif
}

void Core1_MB_IRQHandler(void) {
#ifdef HAS_MULTICORE
    CoreX_MB_IRQHandler(2, 1);
#endif
}

void Core2_MB_IRQHandler(void) {
#ifdef HAS_MULTICORE
    CoreX_MB_IRQHandler(3, 2);
#endif
}

_WEAK_FUN_ void DMA0_IRQHandler(void){};
_WEAK_FUN_ void DMA1_IRQHandler(void){};
_WEAK_FUN_ void DMA2_IRQHandler(void){};
_WEAK_FUN_ void DMA3_IRQHandler(void){};
_WEAK_FUN_ void DMA4_IRQHandler(void){};
_WEAK_FUN_ void DMA5_IRQHandler(void){};
_WEAK_FUN_ void DMA6_IRQHandler(void){};
_WEAK_FUN_ void DMA7_IRQHandler(void){};
_WEAK_FUN_ void DMA8_IRQHandler(void){};
_WEAK_FUN_ void DMA9_IRQHandler(void){};
_WEAK_FUN_ void DMA10_IRQHandler(void){};
_WEAK_FUN_ void DMA11_IRQHandler(void){};
_WEAK_FUN_ void DMA12_IRQHandler(void){};
_WEAK_FUN_ void DMA13_IRQHandler(void){};
_WEAK_FUN_ void DMA14_IRQHandler(void){};
_WEAK_FUN_ void DMA15_IRQHandler(void){};
_WEAK_FUN_ void DMA16_IRQHandler(void){};
_WEAK_FUN_ void DMA17_IRQHandler(void){};
_WEAK_FUN_ void DMA18_IRQHandler(void){};
_WEAK_FUN_ void DMA19_IRQHandler(void){};
_WEAK_FUN_ void DMA20_IRQHandler(void){};
_WEAK_FUN_ void DMA21_IRQHandler(void){};
_WEAK_FUN_ void DMA22_IRQHandler(void){};
_WEAK_FUN_ void DMA23_IRQHandler(void){};
_WEAK_FUN_ void DMA24_IRQHandler(void){};
_WEAK_FUN_ void DMA25_IRQHandler(void){};
_WEAK_FUN_ void DMA26_IRQHandler(void){};
_WEAK_FUN_ void DMA27_IRQHandler(void){};
_WEAK_FUN_ void DMA28_IRQHandler(void){};
_WEAK_FUN_ void DMA29_IRQHandler(void){};
_WEAK_FUN_ void DMA30_IRQHandler(void){};
_WEAK_FUN_ void DMA31_IRQHandler(void){};
_WEAK_FUN_ void DMA_Error_IRQHandler(void){};
_WEAK_FUN_ void CPM_IRQHandler(void){};
_WEAK_FUN_ void FC_IRQHandler(void){};
_WEAK_FUN_ void LVD_LVW_IRQHandler(void){};
_WEAK_FUN_ void TMU_IRQHandler(void){};
_WEAK_FUN_ void WDOG0_IRQHandler(void){};
_WEAK_FUN_ void WDOG1_IRQHandler(void){};
_WEAK_FUN_ void WDOG2_IRQHandler(void){};
_WEAK_FUN_ void FCSMU0_IRQHandler(void){};
_WEAK_FUN_ void STCU0_IRQHandler(void){};
_WEAK_FUN_ void ERM_fault_IRQHandler(void){};
_WEAK_FUN_ void MAM0_IRQHandler(void){};
_WEAK_FUN_ void MAM1_IRQHandler(void){};
_WEAK_FUN_ void MAM2_IRQHandler(void){};
_WEAK_FUN_ void RESERVED_62_IRQHandler(void){};
_WEAK_FUN_ void RGM_Pre_IRQHandler(void){};
_WEAK_FUN_ void RGM_Other_IRQHandler(void){};
_WEAK_FUN_ void INTM0_IRQHandler(void){};
_WEAK_FUN_ void ISM0_IRQHandler(void){};

_WEAK_FUN_ void SCG_IRQHandler(void){};
_WEAK_FUN_ void CMU0_IRQHandler(void){};
_WEAK_FUN_ void CMU1_IRQHandler(void){};
_WEAK_FUN_ void CMU2_IRQHandler(void){};
_WEAK_FUN_ void CMU3_IRQHandler(void){};
_WEAK_FUN_ void TSTMP0_IRQHandler(void){};
_WEAK_FUN_ void TSTMP1_IRQHandler(void){};
_WEAK_FUN_ void TSTMP2_IRQHandler(void){};
_WEAK_FUN_ void TSTMP3_IRQHandler(void){};
_WEAK_FUN_ void CORDIC_IRQHandler(void){};
_WEAK_FUN_ void HSM0_IRQHandler(void){};
_WEAK_FUN_ void FCPIT0_IRQHandler(void){};
_WEAK_FUN_ void FCPIT1_IRQHandler(void){};
_WEAK_FUN_ void RTC_IRQHandler(void){};
_WEAK_FUN_ void ENET_Tx0_IRQHandler(void){};
_WEAK_FUN_ void ENET_Tx1_IRQHandler(void){};
_WEAK_FUN_ void ENET_Rx0_IRQHandler(void){};
_WEAK_FUN_ void ENET_Rx1_IRQHandler(void){};
_WEAK_FUN_ void ENET_System_IRQHandler(void){};
_WEAK_FUN_ void AONTIMER_IRQHandler(void){};
_WEAK_FUN_ void SWI_IRQHandler(void){};
_WEAK_FUN_ void OSPI_IRQHandler(void){};
_WEAK_FUN_ void FREQM_IRQHandler(void){};
_WEAK_FUN_ void PORTA_IRQHandler(void){};
_WEAK_FUN_ void PORTB_IRQHandler(void){};
_WEAK_FUN_ void PORTC_IRQHandler(void){};
_WEAK_FUN_ void PORTD_IRQHandler(void){};
_WEAK_FUN_ void PORTE_IRQHandler(void){};
_WEAK_FUN_ void PORTF_IRQHandler(void){};
_WEAK_FUN_ void PORTG_IRQHandler(void){};
_WEAK_FUN_ void PORTH_IRQHandler(void){};
_WEAK_FUN_ void PORTI_IRQHandler(void){};
_WEAK_FUN_ void CAN0_IRQHandler(void){};
_WEAK_FUN_ void CAN1_IRQHandler(void){};
_WEAK_FUN_ void CAN2_IRQHandler(void){};
_WEAK_FUN_ void CAN3_IRQHandler(void){};
_WEAK_FUN_ void CAN4_IRQHandler(void){};
_WEAK_FUN_ void CAN5_IRQHandler(void){};
_WEAK_FUN_ void CAN6_IRQHandler(void){};
_WEAK_FUN_ void CAN7_IRQHandler(void){};
_WEAK_FUN_ void FCIIC0_IRQHandler(void){};
_WEAK_FUN_ void FCIIC1_IRQHandler(void){};
_WEAK_FUN_ void FCSPI0_IRQHandler(void){};
_WEAK_FUN_ void FCSPI1_IRQHandler(void){};
_WEAK_FUN_ void FCSPI2_IRQHandler(void){};
_WEAK_FUN_ void FCSPI3_IRQHandler(void){};
_WEAK_FUN_ void FCSPI4_IRQHandler(void){};
_WEAK_FUN_ void FCSPI5_IRQHandler(void){};
_WEAK_FUN_ void FCUART0_RxTx_IRQHandler(void){};

_WEAK_FUN_ void FCUART4_RxTx_IRQHandler(void){};
_WEAK_FUN_ void FCUART5_RxTx_IRQHandler(void){};
_WEAK_FUN_ void FCUART6_RxTx_IRQHandler(void){};
_WEAK_FUN_ void FCUART7_RxTx_IRQHandler(void){};
_WEAK_FUN_ void FCUART8_RxTx_IRQHandler(void){};
_WEAK_FUN_ void FCUART9_RxTx_IRQHandler(void){};
_WEAK_FUN_ void FCUART10_RxTx_IRQHandler(void){};
_WEAK_FUN_ void FCUART11_RxTx_IRQHandler(void){};
_WEAK_FUN_ void FCUART12_RxTx_IRQHandler(void){};
_WEAK_FUN_ void FCUART13_RxTx_IRQHandler(void){};
_WEAK_FUN_ void FCUART14_RxTx_IRQHandler(void){};
_WEAK_FUN_ void FCUART15_RxTx_IRQHandler(void){};
_WEAK_FUN_ void FTU0_IRQHandler(void){};
_WEAK_FUN_ void FTU1_IRQHandler(void){};
_WEAK_FUN_ void FTU2_IRQHandler(void){};
_WEAK_FUN_ void FTU3_IRQHandler(void){};
_WEAK_FUN_ void FTU4_IRQHandler(void){};
_WEAK_FUN_ void FTU5_IRQHandler(void){};
_WEAK_FUN_ void FTU6_IRQHandler(void){};
_WEAK_FUN_ void FTU7_IRQHandler(void){};
_WEAK_FUN_ void FTU8_IRQHandler(void){};
_WEAK_FUN_ void FTU9_IRQHandler(void){};
_WEAK_FUN_ void FTU10_IRQHandler(void){};
_WEAK_FUN_ void FTU11_IRQHandler(void){};
_WEAK_FUN_ void CMP0_IRQHandler(void){};
_WEAK_FUN_ void CMP1_IRQHandler(void){};
_WEAK_FUN_ void CMP2_IRQHandler(void){};
_WEAK_FUN_ void ADC0_IRQHandler(void){};
_WEAK_FUN_ void ADC1_IRQHandler(void){};
_WEAK_FUN_ void ADC2_IRQHandler(void){};
_WEAK_FUN_ void ADC3_IRQHandler(void){};
_WEAK_FUN_ void PTIMER0_IRQHandler(void){};
_WEAK_FUN_ void PTIMER1_IRQHandler(void){};
_WEAK_FUN_ void PTIMER2_IRQHandler(void){};
_WEAK_FUN_ void PTIMER3_IRQHandler(void){};
_WEAK_FUN_ void SDDF0_IRQHandler(void){};
_WEAK_FUN_ void MSC0_IRQHandler(void){};
_WEAK_FUN_ void MSC1_IRQHandler(void){};
_WEAK_FUN_ void CAN8_IRQHandler(void){};
_WEAK_FUN_ void CAN9_IRQHandler(void){};
_WEAK_FUN_ void SENT0_IRQHandler(void){};
_WEAK_FUN_ void SENT1_IRQHandler(void){};
_WEAK_FUN_ void FCSPI6_IRQHandler(void){};
_WEAK_FUN_ void FCSPI7_IRQHandler(void){};
_WEAK_FUN_ void FCUART16_RxTx_IRQHandler(void){};
_WEAK_FUN_ void FCUART17_RxTx_IRQHandler(void){};
_WEAK_FUN_ void CTI0_IRQHandler(void){};
_WEAK_FUN_ void CTI1_IRQHandler(void){};
_WEAK_FUN_ void CTI2_IRQHandler(void){};
