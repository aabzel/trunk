#ifndef STM32F446RE_CONST_H
#define STM32F446RE_CONST_H

/*storage*/
#define RAM_SIZE (128 * K_BYTES)
#define RAM_START 0x20000000
#define RAM_END (RAM_START + RAM_SIZE)

#define ROM_START 0x08000000
#define ROM_SIZE (512 * K_BYTES)
#define ROM_END (ROM_START + ROM_SIZE)
#define NOR_FLASH_END (ROM_START+ROM_SIZE)

#define NOR_FLASH_START ROM_START

/*Analog*/
#define ADC_BIT 12
#define ADC_COUNT 3
#define DAC_COUNT 2

/*control*/
#define MCU_NAME "STM32F446RE"
#define DMA_COUNT 2
#define DMA_STREAM_COUNT 8
#define DMA_CHANNEL_COUNT DMA_STREAM_COUNT

/*Connectivity*/
#define SPI_COUNT 4
#define I2C_COUNT 4
#define I2S_COUNT 3
#define SDIO_COUNT 1
#define USB_COUNT 2
#define UART_COUNT 6
#define UART_MAX_NUM UART_COUNT
#define GPIO_COUNT 50
#define GPIO_PIN_MAX 15

/*sensetivity*/
#define TIMER_16BIT_COUNT 5
#define TIMER_32BIT_COUNT 2
#define TIMER_COUNT 14
#define TIMER_MAX_COUNT 14
#define TIMER_MAX_NUM 15
#define DMA_CNT 2
#define DMA_STREAM_CNT 8
#define PACKAGE "LQFP64"
#define LSI_FREQ 32000


#define SYS_FREQ_MAX 180000000U
#define SYS_FREQ 100000000
#define MAX_IRQ_NUM FMPI2C1_ER_IRQn

//#define AHB1_CLOCK_HZ SYS_FREQ
//#define APB2_CLOCK_HZ AHB1_CLOCK_HZ
//#define APB1_CLOCK_HZ (AHB1_CLOCK_HZ/2)


//extern const PinData_t PinConfig[];

//uint16_t pin_get_cnt(void);

#endif /* STM32F446RE_CONST_H */
