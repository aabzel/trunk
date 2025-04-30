#ifndef TEST_LIST_HARDWARE_H
#define TEST_LIST_HARDWARE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

bool test_clock_us(void);
bool test_clock_ms(void);

#ifndef HAS_UNIT_TEST
#error "It is needed HAS_UNIT_TEST option for that component"
#endif

#ifdef HAS_TEST_AES_HW
#include "test_aes_hw.h"
#else
#define TEST_SUIT_AES_HW
#endif

#ifdef HAS_TEST_BC127
#include "test_bc127.h"
#else
#define TEST_SUIT_BC127
#endif

#ifdef HAS_TEST_BUTTON
#include "test_button.h"
#else
#define TEST_SUIT_BUTTON
#endif

#ifdef HAS_TEST_CLOCK
#include "test_clock.h"
#else
#define TEST_SUIT_CLOCK
#endif

#ifdef HAS_TEST_DECADRIVER
#include "test_decadriver.h"
#else
#define TEST_SUIT_DECADRIVER
#endif

#ifdef HAS_TEST_DMA
#include "test_dma.h"
#else
#define TEST_SUIT_DMA
#endif

#ifdef HAS_TEST_EEPROM
#include "test_eeprom.h"
#else
#define TEST_SUIT_EEPROM
#endif


#ifdef HAS_TEST_DW1000
#include "test_dw1000.h"
#else
#define TEST_SUIT_DW1000
#endif

#ifdef HAS_TEST_DWM3000
#include "test_dwm3000.h"
#else
#define TEST_SUIT_DWM3000
#endif

#ifdef HAS_TEST_FLASH
#include "test_flash.h"
#else
#define TEST_SUIT_FLASH
#endif

#ifdef HAS_TEST_FLASH_FS
#include "test_flash_fs.h"
#else
#define TEST_SUIT_FLASH_FS
#endif

#ifdef HAS_TEST_PARAM
#include "test_params.h"
#else
#define TEST_SUIT_PARAM
#endif

#ifdef HAS_TEST_PDM
#include "test_pdm.h"
#else
#define TEST_SUIT_PDM
#endif

#ifdef HAS_TEST_TCAN4550
#include "test_tcan4550.h"
#else
#define TEST_SUIT_TCAN4550
#endif

#ifdef HAS_TEST_CAN
#include "test_can.h"
#else
#define TEST_SUIT_CAN
#endif

#ifdef HAS_TEST_LTR390
#include "test_ltr390.h"
#else
#define TEST_SUIT_LTR390
#endif

#ifdef HAS_TEST_AUTO_VOLUME
#include "test_auto_volume.h"
#else
#define TEST_SUIT_AUTO_VOLUME
#endif

#ifdef HAS_TEST_GPIO
#include "test_gpio.h"
#else
#define TEST_SUIT_GPIO
#endif

#ifdef HAS_TEST_SPI
#include "test_spi.h"
#else
#define TEST_SUIT_SPI
#endif

#ifdef HAS_TEST_SPIFI
#include "test_spifi.h"
#else
#define TEST_SUIT_SPIFI
#endif

#ifdef HAS_TEST_TIM
#include "test_tim.h"
#else
#define TEST_SUIT_TIM
#endif

#ifdef HAS_TEST_UART
#include "test_uart.h"
#else
#define TEST_SUIT_UART
#endif

#ifdef HAS_TEST_IWDG
#include "test_iwdg.h"
#else
#define TEST_SUIT_IWDG
#endif

#ifdef HAS_TEST_I2S
#include "test_i2s.h"
#else
#define TEST_SUIT_I2S
#endif

#ifdef HAS_TEST_I2C
#include "test_i2c.h"
#else
#define TEST_SUIT_I2C
#endif

#ifdef HAS_TEST_FDA801
#include "test_fda801.h"
#else
#define TEST_SUIT_FDA801
#endif

#ifdef HAS_TEST_LED_MONO
#include "test_led_mono.h"
#else
#define TEST_SUIT_LED_MONO
#endif

#ifdef HAS_TEST_LED_RGB
#include "test_led_rgb.h"
#else
#define TEST_SUIT_LED_RGB
#endif

#ifdef HAS_TEST_MAX9860
#include "test_max9860.h"
#else
#define TEST_SUIT_MAX9860
#endif

#ifdef HAS_TEST_SX1262
#include "test_sx1262.h"
#else
#define TEST_SUIT_SX1262
#endif

#ifdef HAS_TEST_RELAY
#include "test_relay.h"
#else
#define TEST_SUIT_RELAY
#endif

#ifdef HAS_TEST_RTC
#include "test_rtc.h"
#else
#define TEST_SUIT_RTC
#endif

#ifdef HAS_TEST_SDIO
#include "test_sdio.h"
#else
#define TEST_SUIT_SDIO
#endif

#ifdef HAS_TEST_DISK
#include "test_disk.h"
#else
#define TEST_SUIT_DISK
#endif

#ifdef HAS_TEST_SI4703
#include "test_si4703.h"
#else
#define TEST_SUIT_SI4703
#endif

#ifdef HAS_TEST_SI4737
#include "test_si4737.h"
#else
#define TEST_SUIT_SI4737
#endif

#ifdef HAS_TEST_SYSTICK
#include "test_systick.h"
#else
#define TEST_SUIT_SYSTICK
#endif

#ifdef HAS_TEST_DTMF
#include "test_dtmf.h"
#else
#define TEST_SUIT_DTMF
#endif

#ifdef HAS_TEST_DS3231
#include "test_ds3231.h"
#else
#define TEST_SUIT_DS3231
#endif

#ifdef HAS_TEST_HEAP
#include "test_allocator.h"
#else
#define TEST_SUIT_HEAP
#endif

#ifdef HAS_TEST_SUIT_SYSTEM_HW
#include "test_system.h"
#else
#define TEST_SYSTEM_HW
#endif

#ifdef HAS_TEST_NVS
#include "test_nvs.h"
#else
#define TEST_SUIT_NVS
#endif

#ifdef HAS_TEST_ADC
#include "test_adc.h"
#else
#define TEST_SUIT_ADC
#endif

#ifdef HAS_TEST_AT24CXX
#include "test_at24cxx.h"
#else
#define TEST_SUIT_AT24CXX
#endif

#ifdef HAS_TEST_MX25R6435F
#include "test_mx25r6435f.h"
#else
#define TEST_SUIT_MX25R6435F
#endif

#ifdef HAS_TEST_SCR1_TIMER
#include "test_scr1_timer.h"
#else
#define TEST_SUIT_SCR1_TIMER
#endif





#ifdef HAS_TEST_MIC2026
#include "test_mic2026.h"
#else
#define TEST_SUIT_MIC2026
#endif

#ifdef HAS_TEST_CRYP_HW
#include "test_cryp_hw.h"
#else
#define TEST_SUIT_CRYP_HW
#endif

#ifdef HAS_TEST_SD_CARD
#include "test_sd_card.h"
#else
#define TEST_SUIT_SD_CARD
#endif

#ifdef HAS_TEST_SOFTWARE_TIMER
#include "test_sw_timer.h"
#else
#define TEST_SUIT_SOFTWARE_TIMER
#endif

#ifdef HAS_TEST_SSD1306
#include "test_ssd1306.h"
#else
#define TEST_SUIT_SSD1306
#endif

#ifdef HAS_TEST_WM8731
#include "test_wm8731.h"
#else
#define TEST_SUIT_WM8731
#endif

#ifdef HAS_TEST_ZED_F9P
#include "test_zed_f9p.h"
#else
#define TEST_SUIT_ZED_F9P
#endif

#ifndef HAS_HW_TESTS
#error "It is needed HAS_HW_TESTS option for that component"
#endif

#define TEST_SUIT_HW_STORAGE    \
    TEST_SUIT_NVS                                                                                                      \
    TEST_SUIT_SPIFI                                                                                                    \
    TEST_SUIT_PARAM                                                                                                    \
    TEST_SUIT_SDIO                                                                                                     \
    TEST_SUIT_SD_CARD                                                                                                  \
    TEST_SUIT_MX25R6435F                                                                                               \
    TEST_SUIT_EEPROM                                                                                                   \
    TEST_SUIT_DISK                                                                                                     \
    TEST_SUIT_AT24CXX                                                                                                  \
    TEST_SUIT_FLASH                                                                                                    \
    TEST_SUIT_FLASH_FS

/*Compile time assemble array */
#define TEST_SUIT_HW                                                                                                   \
	TEST_SUIT_HW_STORAGE                                                                                                      \
    TEST_SUIT_ADC                                                                                                      \
    TEST_SUIT_AES_HW                                                                                                   \
    TEST_SUIT_AUTO_VOLUME                                                                                              \
    TEST_SUIT_BC127                                                                                                    \
    TEST_SUIT_BUTTON                                                                                                   \
    TEST_SUIT_CAN                                                                                                      \
    TEST_SUIT_CLOCK                                                                                                    \
    TEST_SUIT_CRYP_HW                                                                                                  \
    TEST_SUIT_DECADRIVER                                                                                               \
    TEST_SUIT_DMA                                                                                                      \
    TEST_SUIT_DS3231                                                                                                   \
    TEST_SUIT_DTMF                                                                                                     \
	TEST_SUIT_SCR1_TIMER                                                                                               \
    TEST_SUIT_DW1000                                                                                                   \
    TEST_SUIT_DWM3000                                                                                                  \
    TEST_SUIT_FDA801                                                                                                   \
    TEST_SUIT_GPIO                                                                                                     \
    TEST_SUIT_I2C                                                                                                      \
    TEST_SUIT_I2S                                                                                                      \
    TEST_SUIT_IWDG                                                                                                     \
    TEST_SUIT_LED_MONO                                                                                                 \
    TEST_SUIT_LED_RGB                                                                                                  \
    TEST_SUIT_LTR390                                                                                                   \
    TEST_SUIT_MAX9860                                                                                                  \
    TEST_SUIT_MIC2026                                                                                                  \
    TEST_SUIT_PDM                                                                                                      \
    TEST_SUIT_RELAY                                                                                                    \
    TEST_SUIT_RTC                                                                                                      \
    TEST_SUIT_SI4703                                                                                                   \
    TEST_SUIT_SI4737                                                                                                   \
    TEST_SUIT_SOFTWARE_TIMER                                                                                           \
    TEST_SUIT_SPI                                                                                                      \
    TEST_SUIT_SSD1306                                                                                                  \
    TEST_SUIT_SX1262                                                                                                   \
    TEST_SUIT_SYSTICK                                                                                                  \
    TEST_SUIT_TCAN4550                                                                                                 \
    TEST_SUIT_TIM                                                                                                      \
    TEST_SUIT_UART                                                                                                     \
    TEST_SUIT_WM8731                                                                                                   \
    TEST_SUIT_ZED_F9P                                                                                                  \
    TEST_SYSTEM_HW

#ifdef __cplusplus
}
#endif

#endif /*TEST_LIST_HARDWARE_H*/
