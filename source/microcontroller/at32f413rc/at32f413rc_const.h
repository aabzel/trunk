#ifndef AT32F413RC_CONST_H
#define AT32F413RC_CONST_H



#ifdef HAS_EHAL
#include "platform.h"
typedef S16 IRQn_Type;
typedef enum
{
    /******  cortex-m4 processor exceptions numbers ***************************************************/
    Reset_IRQn                  = -15,    /* 1 reset vector, invoked on power up and warm reset   */
    NonMaskableInt_IRQn         = -14,    /* 2 non maskable interrupt                             */
    HardFault_IRQn              = -13,    /* 3 hard fault, all classes of fault                   */
    MemoryManagement_IRQn       = -12,    /* 4 cortex-m4 memory management interrupt              */
    BusFault_IRQn               = -11,    /* 5 cortex-m4 bus fault interrupt                      */
    UsageFault_IRQn             = -10,    /* 6 cortex-m4 usage fault interrupt                    */
    SVCall_IRQn                 = -5,     /* 11 cortex-m4 sv call interrupt                       */
    DebugMonitor_IRQn           = -4,     /* 12 cortex-m4 debug monitor interrupt                 */
    PendSV_IRQn                 = -2,     /* 14 cortex-m4 pend sv interrupt                       */
    SysTick_IRQn                = -1,     /* 15 cortex-m4 system tick interrupt                   */

    /******  at32 specific interrupt numbers *********************************************************/
    WWDT_IRQn                   = 0,      /* window watchdog timer interrupt                      */
    PVM_IRQn                    = 1,      /* pvm through exint line detection interrupt           */
    TAMPER_IRQn                 = 2,      /* tamper interrupt                                     */
    RTC_IRQn                    = 3,      /* rtc global interrupt                                 */
    FLASH_IRQn                  = 4,      /* flash global interrupt                               */
    CRM_IRQn                    = 5,      /* crm global interrupt                                 */
    EXINT0_IRQn                 = 6,      /* external line0 interrupt                             */
    EXINT1_IRQn                 = 7,      /* external line1 interrupt                             */
    EXINT2_IRQn                 = 8,      /* external line2 interrupt                             */
    EXINT3_IRQn                 = 9,      /* external line3 interrupt                             */
    EXINT4_IRQn                 = 10,     /* external line4 interrupt                             */
    DMA1_Channel1_IRQn          = 11,     /* dma1 channel 1 global interrupt                      */
    DMA1_Channel2_IRQn          = 12,     /* dma1 channel 2 global interrupt                      */
    DMA1_Channel3_IRQn          = 13,     /* dma1 channel 3 global interrupt                      */
    DMA1_Channel4_IRQn          = 14,     /* dma1 channel 4 global interrupt                      */
    DMA1_Channel5_IRQn          = 15,     /* dma1 channel 5 global interrupt                      */
    DMA1_Channel6_IRQn          = 16,     /* dma1 channel 6 global interrupt                      */
    DMA1_Channel7_IRQn          = 17,     /* dma1 channel 7 global interrupt                      */

    ADC1_2_IRQn                 = 18,     /* adc1 and adc2 global interrupt                       */
    USBFS_H_CAN1_TX_IRQn        = 19,     /* usb device high priority or can1 tx interrupts       */
    USBFS_L_CAN1_RX0_IRQn       = 20,     /* usb device low priority or can1 rx0 interrupts       */
    CAN1_RX1_IRQn               = 21,     /* can1 rx1 interrupt                                   */
    CAN1_SE_IRQn                = 22,     /* can1 se interrupt                                    */
    EXINT9_5_IRQn               = 23,     /* external line[9:5] interrupts                        */
    TMR1_BRK_TMR9_IRQn          = 24,     /* tmr1 brake interrupt                                 */
    TMR1_OVF_TMR10_IRQn         = 25,     /* tmr1 overflow interrupt                              */
    TMR1_TRG_HALL_TMR11_IRQn    = 26,     /* tmr1 trigger and hall interrupt                      */
    TMR1_CH_IRQn                = 27,     /* tmr1 channel interrupt                               */
    TMR2_GLOBAL_IRQn            = 28,     /* tmr2 global interrupt                                */
    TMR3_GLOBAL_IRQn            = 29,     /* tmr3 global interrupt                                */
    TMR4_GLOBAL_IRQn            = 30,     /* tmr4 global interrupt                                */
    I2C1_EVT_IRQn               = 31,     /* i2c1 event interrupt                                 */
    I2C1_ERR_IRQn               = 32,     /* i2c1 error interrupt                                 */
    I2C2_EVT_IRQn               = 33,     /* i2c2 event interrupt                                 */
    I2C2_ERR_IRQn               = 34,     /* i2c2 error interrupt                                 */
    SPI1_IRQn                   = 35,     /* spi1 global interrupt                                */
    SPI2_IRQn                   = 36,     /* spi2 global interrupt                                */
    USART1_IRQn                 = 37,     /* usart1 global interrupt                              */
    USART2_IRQn                 = 38,     /* usart2 global interrupt                              */
    USART3_IRQn                 = 39,     /* usart3 global interrupt                              */
    EXINT15_10_IRQn             = 40,     /* external line[15:10] interrupts                      */
    RTCAlarm_IRQn               = 41,     /* rtc alarm through exint line interrupt               */
    USBFSWakeUp_IRQn            = 42,     /* usb device wakeup from suspend through exint line interrupt */
    TMR8_BRK_IRQn               = 43,     /* tmr8 brake interrupt                                 */
    TMR8_OVF_IRQn               = 44,     /* tmr8 overflow interrupt                              */
    TMR8_TRG_HALL_IRQn          = 45,     /* tmr8 trigger and hall interrupt                      */
    TMR8_CH_IRQn                = 46,     /* tmr8 channel interrupt                               */
    SDIO1_IRQn                  = 49,     /* sdio1 global interrupt                               */
    TMR5_GLOBAL_IRQn            = 50,     /* tmr5 global interrupt                                */
    UART4_IRQn                  = 52,     /* uart4 global interrupt                               */
    UART5_IRQn                  = 53,     /* uart5 global interrupt                               */
    DMA2_Channel1_IRQn          = 56,     /* dma2 channel 1 global interrupt                      */
    DMA2_Channel2_IRQn          = 57,     /* dma2 channel 2 global interrupt                      */
    DMA2_Channel3_IRQn          = 58,     /* dma2 channel 3 global interrupt                      */
    DMA2_Channel4_5_IRQn        = 59,     /* dma2 channel 4 and channel 5 global interrupt        */
    CAN2_TX_IRQn                = 68,     /* can2 tx interrupt                                    */
    CAN2_RX0_IRQn               = 69,     /* can2 rx0 interrupt                                   */
    CAN2_RX1_IRQn               = 70,     /* can2 rx1 interrupt                                   */
    CAN2_SE_IRQn                = 71,     /* can2 se interrupt                                    */
    ACC_IRQn                    = 72,     /* acc interrupt                                        */
    USBFS_MAPH_IRQn             = 73,     /* usb map hp interrupt                                 */
    USBFS_MAPL_IRQn             = 74,     /* usb map lp interrupt                                 */
    DMA2_Channel6_7_IRQn        = 75      /* dma2 channel 6 and channel 7 global interrupt        */

} IrqNumber_t;
#endif

#include "macro_utils.h"

/*sensitivity*/
#define ADC_CHANNELS_COUNT 16
#define ADC_COUNT 2
#define TIMER_COUNT 9
#define TIMER_MAX_NUM 11
#define TIMER_MAX_COUNT (TIMER_COUNT+1)
#define TRNG_COUNT 1
#define MAX_IRQ_NUM (75) /*See page  DMA2_Channel6_7_IRQn    */


#define CPU_MAX_HZ 200000000
#define LSI_FREQ 32000
#define MCU_NAME "at32f413rc"
#define MCU_PACKAGE "LQFP144"
//#define SYS_FREQ 100000000
//#define AHB1_CLOCK_HZ SYS_FREQ
//#define APB1_CLOCK_HZ (AHB1_CLOCK_HZ/2)
//#define APB2_CLOCK_HZ (AHB1_CLOCK_HZ/2)

// control
#define DAC_COUNT 0
#define DMA_COUNT 2
#define DMA_CHANNEL_COUNT 14

// storage
#define RAM_START 0x20000000
#define RAM_END (RAM_START + RAM_SIZE)
#define RAM_SIZE (32 * K_BYTES)
#define ROM_SIZE (256 * K_BYTES)
#define ROM_START 0x08000000
//Main Flash memory contains bank 1 only, 256 KB, including 128 sectors, 2 K per sector.
#define FLASH_SECTOR_SIZE (2 * K_BYTES)
#define FLASH_PAGE_SIZE (FLASH_SECTOR_SIZE)
#define FLASH_SECTOR_CNT ((ROM_SIZE)/(FLASH_PAGE_SIZE))
#define ROM_END (ROM_START + ROM_SIZE)
#define NOR_FLASH_START ROM_START
#define NOR_FLASH_END (ROM_END)
#define FLASH_BANK_1_SIZE ROM_SIZE
#define FLASH_BANK_2_SIZE 0
#define FLASH_BLOCK_SIZE FLASH_SECTOR_SIZE

#ifndef FLASH_BASE
#define FLASH_BASE ((uint32_t)ROM_START)
#endif

/*interfaces*/
#define CAN_COUNT 2
#define GPIO_PIN_MAX 15
#define GPIO_COUNT 55
#define I2C_COUNT 2
#define I2S_COUNT 2
#define QSPI_COUNT 0
#define SPI_COUNT 2
#define SDIO_COUNT 1
#define UART_COUNT 5
#define USART_COUNT 1
#define USB_COUNT 1

#define UART_MAX_NUM (UART_COUNT+1)

#endif /* AT32F413RC_CONST_H */
