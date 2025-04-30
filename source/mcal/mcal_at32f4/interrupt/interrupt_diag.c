#include "interrupt_diag.h"

#include <stdint.h>

#include "data_utils.h"
#include "at32f435_437.h"

typedef struct  xIntName_t{
    const char *name;
    int8_t int_n;
}IntName_t;

typedef struct  xIntPriorityName_t{
    const char *name;
    uint8_t priority;
}IntPriorityName_t;

#if 0
const static IntPriorityName_t IntPriorityLut[]={
    {.priority=0 , .name="Highest",},
    {.priority=1 , .name="High6",},
    {.priority=2 , .name="High5",},
    {.priority=3 , .name="High4",},
    {.priority=4 , .name="High3",},
    {.priority=5 , .name="High2",},
    {.priority=6 , .name="High1",},
    {.priority=7 , .name="MedH",},
    {.priority=8 , .name="MedL",},
    {.priority=9 , .name="low1",},
    {.priority=10, .name="low2",},
    {.priority=11, .name="low3",},
    {.priority=12, .name="low4",},
    {.priority=13, .name="low5",},
    {.priority=14, .name="low6",},
    {.priority=15, .name="Lowest",},
};
#endif

const static IntName_t IntNameLut[]={
  {.name="NonMaskableInt",    .int_n = -14,},    /*!< 2 Non Maskable Interrupt                                          */
  {.name="MemoryManagement",    .int_n = -12,},    /*!< 4 Cortex-M4 Memory Management Interrupt                           */
  {.name="BusFault",    .int_n = -11,},    /*!< 5 Cortex-M4 Bus Fault Interrupt                                   */
  {.name="UsageFault",    .int_n = -10,},    /*!< 6 Cortex-M4 Usage Fault Interrupt                                 */
  {.name="SVCall",    .int_n = -5, },    /*!< 11 Cortex-M4 SV Call Interrupt                                    */
  {.name="DebugMonitor",    .int_n = -4, },    /*!< 12 Cortex-M4 Debug Monitor Interrupt                              */
  {.name="PendSV",    .int_n = -2, },    /*!< 14 Cortex-M4 Pend SV Interrupt                                    */
  {.name="SysTick",    .int_n = -1, },    /*!< 15 Cortex-M4 System Tick Interrupt                                */
  {.name="WWDG",    .int_n = 0,  },    /*!< Window WatchDog Interrupt                                         */
  {.name="PVD",    .int_n = 1,  },    /*!< PVD through Exti Line detection Interrupt                         */
  {.name="TAMPSTAMP",    .int_n = 2,  },    /*!< Tamper and TimeStamp interrupts through the Exti line             */
  {.name="RTC_WKUP",    .int_n = 3,  },    /*!< RTC Wakeup interrupt through the Exti line                        */
  {.name="FLASH",    .int_n = 4,  },    /*!< FLASH global Interrupt                                            */
  {.name="RCC",    .int_n = 5,  },    /*!< RCC global Interrupt                                              */
  {.name="Exti0",    .int_n = 6,  },    /*!< Exti Line0 Interrupt                                              */
  {.name="Exti1",    .int_n = 7,  },    /*!< Exti Line1 Interrupt                                              */
  {.name="Exti2",    .int_n = 8,  },    /*!< Exti Line2 Interrupt                                              */
  {.name="Exti3",    .int_n = 9,  },    /*!< Exti Line3 Interrupt                                              */
  {.name="Exti4",    .int_n = 10, },    /*!< Exti Line4 Interrupt                                              */
  {.name="Dma1Stream0",    .int_n = 11, },    /*!< Dma1 Stream 0 global Interrupt                                    */
  {.name="Dma1Stream1",    .int_n = 12, },    /*!< Dma1 Stream 1 global Interrupt                                    */
  {.name="Dma1Stream2",    .int_n = 13, },    /*!< Dma1 Stream 2 global Interrupt                                    */
  {.name="Dma1Stream3",    .int_n = 14, },    /*!< Dma1 Stream 3 global Interrupt                                    */
  {.name="Dma1Stream4",    .int_n = 15, },    /*!< Dma1 Stream 4 global Interrupt                                    */
  {.name="Dma1Stream5",    .int_n = 16, },    /*!< Dma1 Stream 5 global Interrupt                                    */
  {.name="Dma1Stream6",    .int_n = 17, },    /*!< Dma1 Stream 6 global Interrupt                                    */
  {.name="ADC",    .int_n = 18, },    /*!< ADC1, ADC2 and ADC3 global Interrupts                             */
  {.name="Can1TX",    .int_n = 19, },    /*!< Can1 TX Interrupt                                                 */
  {.name="Can1_RX0",    .int_n = 20, },    /*!< Can1 RX0 Interrupt                                                */
  {.name="Can1_RX1",    .int_n = 21, },    /*!< Can1 RX1 Interrupt                                                */
  {.name="Can1SCE",    .int_n = 22, },    /*!< Can1 SCE Interrupt                                                */
  {.name="Exti9_5",    .int_n = 23, },    /*!< External Line[9:5] Interrupts                                     */
  {.name="Tim1_BRKTim9",    .int_n = 24, },    /*!< Tim1 Break interrupt and Tim9 global interrupt                    */
  {.name="Tim1_UPTim10",    .int_n = 25, },    /*!< Tim1 Update Interrupt and Tim10 global interrupt                  */
  {.name="Tim1TRG_COMTim11",    .int_n = 26, },    /*!< Tim1 Trigger and Commutation Interrupt and Tim11 global interrupt */
  {.name="Tim1_CC",    .int_n = 27, },    /*!< Tim1 Capture Compare Interrupt                                    */
  {.name="Tim2",    .int_n = 28, },    /*!< Tim2 global Interrupt                                             */
  {.name="Tim3",    .int_n = 29, },    /*!< Tim3 global Interrupt                                             */
  {.name="Tim4",    .int_n = 30, },    /*!< Tim4 global Interrupt                                             */
  {.name="I2C1Ev",    .int_n = 31, },    /*!< I2C1 Event Interrupt                                              */
  {.name="I2C1_ER",    .int_n = 32, },    /*!< I2C1 Error Interrupt                                              */
  {.name="I2C2Ev",    .int_n = 33, },    /*!< I2C2 Event Interrupt                                              */
  {.name="I2C2_ER",    .int_n = 34, },    /*!< I2C2 Error Interrupt                                              */
  {.name="SPI1",    .int_n = 35, },    /*!< SPI1 global Interrupt                                             */
  {.name="SPI2",    .int_n = 36, },    /*!< SPI2 global Interrupt                                             */
  {.name="Usart1",    .int_n = 37, },    /*!< Usart1 global Interrupt                                           */
  {.name="Usart2",    .int_n = 38, },    /*!< Usart2 global Interrupt                                           */
  {.name="Usart3",    .int_n = 39, },    /*!< Usart3 global Interrupt                                           */
  {.name="Exti15-10",    .int_n = 40, },    /*!< External Line[15:10] Interrupts                                   */
  {.name="RTC_Alarm",    .int_n = 41, },    /*!< RTC Alarm (A and B) through Exti Line Interrupt                   */
  {.name="OTGFS_WKUP",    .int_n = 42, },    /*!< USB OTG FS Wakeup through Exti line interrupt                     */
  {.name="Tim8_BRKTim12",    .int_n = 43, },    /*!< Tim8 Break Interrupt and Tim12 global interrupt                   */
  {.name="Tim8_UPTim13",    .int_n = 44, },    /*!< Tim8 Update Interrupt and Tim13 global interrupt                  */
  {.name="Tim8TRG_COMTim14",    .int_n = 45, },    /*!< Tim8 Trigger and Commutation Interrupt and Tim14 global interrupt */
  {.name="Tim8_CC",    .int_n = 46, },    /*!< Tim8 Capture Compare global interrupt                             */
  {.name="Dma1Stream7",    .int_n = 47, },    /*!< Dma1 Stream7 Interrupt                                            */
  {.name="SDIO",    .int_n = 49, },    /*!< SDIO global Interrupt                                             */
  {.name="Tim5",    .int_n = 50, },    /*!< Tim5 global Interrupt                                             */
  {.name="SPI3",    .int_n = 51, },    /*!< SPI3 global Interrupt                                             */
  {.name="Uart4",    .int_n = 52, },    /*!< Uart4 global Interrupt                                            */
  {.name="Uart5",    .int_n = 53, },    /*!< Uart5 global Interrupt                                            */
  {.name="Tim6_DAC",    .int_n = 54, },    /*!< Tim6 global and DAC1&2 underrun error  interrupts                 */
  {.name="Tim7",    .int_n = 55, },    /*!< Tim7 global interrupt                                             */
  {.name="Dma2Stream0",    .int_n = 56, },    /*!< Dma2 Stream 0 global Interrupt                                    */
  {.name="Dma2Stream1",    .int_n = 57, },    /*!< Dma2 Stream 1 global Interrupt                                    */
  {.name="Dma2Stream2",    .int_n = 58, },    /*!< Dma2 Stream 2 global Interrupt                                    */
  {.name="Dma2Stream3",    .int_n = 59, },    /*!< Dma2 Stream 3 global Interrupt                                    */
  {.name="Dma2Stream4",    .int_n = 60, },    /*!< Dma2 Stream 4 global Interrupt                                    */
  {.name="DFSDM1FLT0",    .int_n = 61, },    /*!< DFSDM1 Filter 0 global Interrupt                                  */
  {.name="DFSDM1FLT1",    .int_n = 62, },    /*!< DFSDM1 Filter 1 global Interrupt                                  */
  {.name="Can2TX",    .int_n = 63, },    /*!< Can2 TX Interrupt                                                 */
  {.name="Can2_RX0",    .int_n = 64, },    /*!< Can2 RX0 Interrupt                                                */
  {.name="Can2_RX1",    .int_n = 65, },    /*!< Can2 RX1 Interrupt                                                */
  {.name="Can2SCE",    .int_n = 66, },    /*!< Can2 SCE Interrupt                                                */
  {.name="OTGFS",    .int_n = 67, },    /*!< USB OTG FS global Interrupt                                       */
  {.name="Dma2Stream5",    .int_n = 68, },    /*!< Dma2 Stream 5 global interrupt                                    */
  {.name="Dma2Stream6",    .int_n = 69, },    /*!< Dma2 Stream 6 global interrupt                                    */
  {.name="Dma2Stream7",    .int_n = 70, },    /*!< Dma2 Stream 7 global interrupt                                    */
  {.name="Usart6",    .int_n = 71, },    /*!< Usart6 global interrupt                                           */
  {.name="I2C3Ev",    .int_n = 72, },    /*!< I2C3 event interrupt                                              */
  {.name="I2C3_ER",    .int_n = 73, },    /*!< I2C3 error interrupt                                              */
  {.name="Can3TX",    .int_n = 74, },    /*!< Can3 TX Interrupt                                                 */
  {.name="Can3_RX0",    .int_n = 75, },    /*!< Can3 RX0 Interrupt                                                */
  {.name="Can3_RX1",    .int_n = 76, },    /*!< Can3 RX1 Interrupt                                                */
  {.name="Can3SCE",    .int_n = 77, },    /*!< Can3 SCE Interrupt                                                */
  {.name="RNG",    .int_n = 80, },    /*!< RNG global Interrupt                                              */
  {.name="FPU",    .int_n = 81, },    /*!< FPU global interrupt                                              */
  {.name="Uart7",    .int_n = 82, },    /*!< Uart7 global interrupt                                            */
  {.name="Uart8",    .int_n = 83, },    /*!< Uart8 global interrupt                                            */
  {.name="SPI4",    .int_n = 84, },    /*!< SPI4 global Interrupt                                             */
  {.name="SPI5",    .int_n = 85, },    /*!< SPI5 global Interrupt                                             */
  {.name="SAI1",    .int_n = 87, },    /*!< SAI1 global Interrupt                                             */
  {.name="Uart9",    .int_n = 88, },    /*!< Uart9 global Interrupt                                            */
  {.name="Uart10",    .int_n = 89, },    /*!< Uart10 global Interrupt                                           */
  {.name="QUADSPI",    .int_n = 92, },    /*!< QuadSPI global Interrupt                                          */
  {.name="FMPI2C1Ev",    .int_n = 95, },    /*!< FMPI2C1 Event Interrupt                                           */
  {.name="FMPI2C1_ER",    .int_n = 96, },    /*!< FMPI2C1 Error Interrupt                                           */
  {.name="LPTim1",    .int_n = 97, },    /*!< LP Tim1 interrupt                                                 */
  {.name="DFSDM2FLT0",    .int_n = 98, },    /*!< DFSDM2 Filter 0 global Interrupt                                  */
  {.name="DFSDM2FLT1",    .int_n = 99, },    /*!< DFSDM2 Filter 1 global Interrupt                                  */
  {.name="DFSDM2FLT2",    .int_n = 100,},    /*!< DFSDM2 Filter 2 global Interrupt                                  */
  {.name="DFSDM2FLT3",    .int_n = 101 },    /*!< DFSDM2 Filter 3 global Interrupt                                  */
};


const char* interrupt2Str(int8_t int_n){
    const char* name = "?";
    uint32_t i = 0;
    for(i=0;i<ARRAY_SIZE(IntNameLut);i++){
        if(int_n==IntNameLut[i].int_n){
            name=IntNameLut[i].name;
			break;
        }
    }
    return name;
}


