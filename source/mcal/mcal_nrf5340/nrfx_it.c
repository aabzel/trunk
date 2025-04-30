#include "nrfx_it.h"

#include "def.h"

#if !defined(HAS_UART0) &&!defined(HAS_SPI0) &&	!defined(HAS_I2C0)
void SPIM0_SPIS0_TWIM0_TWIS0_UARTE0_IRQHandler(void){
}
#endif

#if !defined(HAS_UART2) &&!defined(HAS_SPI2) &&	!defined(HAS_I2C2)
void SPIM2_SPIS2_TWIM2_TWIS2_UARTE2_IRQHandler(void){
}
#endif

#if !defined(HAS_UART3) &&!defined(HAS_SPI3) &&	!defined(HAS_I2C3)
void SPIM3_SPIS3_TWIM3_TWIS3_UARTE3_IRQHandler(void){

}
#endif

void SysTick_Handler(void){
#ifdef HAS_SOFTWARE_TIMER
    sw_timer_proc();
#endif /*HAS_SOFTWARE_TIMER*/
#ifdef HAS_SYSTICK
    SysTickIntHandler();
#endif /*HAS_SYSTICK*/
}

void HardFault_Handler(void){
  /* Go to infinite loop when Hard Fault exception occurs */
    while (1)  {
    }
}

void SecureFault_Handler(void){
    while(1);  /* Something went wrong */
}


extern uint32_t __isr_vector_addr;

extern uint32_t _image_start;
extern uint32_t _image_size;
__attribute__((section(".tag"))) const flash_tag_t fw_tag =
   {
    // fw info
    //
    .magic_number = 0xAAAA5555,
    .version_str  = "V200410R1",
    .board_str    = "NRF5340_PDK_B/D",
#ifdef	HAS_CORE_APP
    .name_str     = "Application",
#endif

#ifdef HAS_CORE_NET
    .name_str     = "Network",
#endif
    .date_str     = __DATE__,
    .time_str     = __TIME__,
    .addr_tag     = (uint32_t)&fw_tag,
    .addr_fw      = (uint32_t)&__isr_vector_addr,

    .load_start   = (uint32_t)&_image_start,  // load_addr
    .load_size    = (uint32_t)&_image_size,   // load_size
   };

#if 1

#ifndef HAS_CORE_APP
 void TIMER0_IRQHandler(void){}
 void TIMER1_IRQHandler(void){}
 void TIMER2_IRQHandler(void){}
#endif

#ifdef HAS_CORE_NET
void I2S0_IRQHandler(void){}
#endif

 void NMI_Handler(void){}
 void MemManage_Handler(void){}
 void BusFault_Handler(void){}
 void UsageFault_Handler(void){}
 void SVC_Handler(void){}
 void DebugMon_Handler(void){}
 void PendSV_Handler(void){}
 void FPU_IRQHandler(void){}
 void CACHE_IRQHandler(void){}
 void SPU_IRQHandler(void){}
 void CLOCK_POWER_IRQHandler(void){}
// void SPIM4_IRQHandler(void){}
// void GPIOTE0_IRQHandler(void){}
// void SAADC_IRQHandler(void){}
#ifndef HAS_RTC
void RTC0_IRQHandler(void){}
void RTC1_IRQHandler(void){}
#endif
 void WDT0_IRQHandler(void){}
 void WDT1_IRQHandler(void){}
 void COMP_LPCOMP_IRQHandler(void){}
 void EGU0_IRQHandler(void){}
 void EGU1_IRQHandler(void){}
 void EGU2_IRQHandler(void){}
 void EGU3_IRQHandler(void){}
 void EGU4_IRQHandler(void){}
 void EGU5_IRQHandler(void){}
// void PWM0_IRQHandler(void){}
 void PWM1_IRQHandler(void){}
 void PWM2_IRQHandler(void){}
 void PWM3_IRQHandler(void){}
 //void PDM0_IRQHandler(void){}
#if 0
 void IPC_IRQHandler(void){}
#endif
 void QSPI_IRQHandler(void){}
 void NFCT_IRQHandler(void){}
 void GPIOTE1_IRQHandler(void){}
 void QDEC0_IRQHandler(void){}
 void QDEC1_IRQHandler(void){}
 void USBD_IRQHandler(void){}
 void USBREGULATOR_IRQHandler(void){}
 void CRYPTOCELL_IRQHandler(void){}

#endif
 void KMU_IRQHandler(void){}
