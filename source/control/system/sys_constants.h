#ifndef SYS_GENERAL_CONSTANTS_H
#define SYS_GENERAL_CONSTANTS_H

#ifdef __cplusplus
extern "C" {
#endif

//#include "c_defines_generated.h"

#ifndef HAS_SYSTEM
#error "+HAS_SYSTEM"
#endif

typedef enum {
    BUILD_TYPE_MBR = 1,
    BUILD_TYPE_BOOTLOADER = 2,
    BUILD_TYPE_GENERIC = 3,
    BUILD_TYPE_GENERIC_APP = 4,
    BUILD_TYPE_GENERIC_NET = 5,
    BUILD_TYPE_DESKTOP_APP = 6,

    BUILD_TYPE_UNDEF = 0
} BuildType_t;

typedef enum {
    UNKNOWN_FACILITY = 0, /*must be first in enum*/
#ifdef HAS_ASM
    ASM,
#endif

#ifdef HAS_AES
    AES,
    AES256,
#endif

#ifdef HAS_AD9833
    AD9833,
#endif

#ifdef HAS_BLUETOOTH
    BLUETOOTH,
#endif

#ifdef HAS_BLE_AUDIO
    BLE_AUDIO,
#endif

#ifdef HAS_BATT
    BATT,
#endif

#ifdef HAS_KEEPASS
    KEEPASS,
    CRY,
#endif

#ifdef HAS_SOFTWARE_TIMER
    SW_TIMER,
#endif

#ifdef HAS_PHOTORESISTOR
    PHOTORESISTOR,
#endif

#ifdef HAS_FONT
    FONT,
#endif

#ifdef HAS_BC127
    BC127,
#endif

#ifdef HAS_BASE16
    BASE16,
#endif

#ifdef HAS_BT1026
    BT1026,
#endif

#ifdef HAS_BOOT
    BOOT,
#endif

#ifdef HAS_HEAP
    HEAP,
#endif

#ifdef HAS_NVRAM
    NVRAM,
#endif

#ifdef HAS_APP
    APP,
#endif

#ifdef HAS_DMA
    DMA,
#endif

#ifdef HAS_FDA801
    FDA801,
#endif

#ifdef HAS_RDS
    RDS,
#endif

#ifdef HAS_BUTTON
    BUTTON,
#endif

#ifdef HAS_BOARD
    BOARD,
#endif

#ifdef HAS_CAN
    CAN,
#endif

#ifdef HAS_CAN_IF
    CAN_IF,
#endif

#ifdef HAS_CLOCK
    CLK,
	CLOCK,
#endif

#ifdef HAS_CORE
    CORE,
#endif

#ifdef HAS_CLI
    CLI,
#endif

#ifdef HAS_PC
    PC,
#endif

#ifdef HAS_IPC
    IPC,
#endif

#ifdef HAS_CRC
    LG_CRC,
#endif

#ifdef HAS_ARRAY
    ARRAY,
#endif

#ifdef HAS_CRC24
    CRC24,
#endif

#ifdef HAS_STATISTICS
    STATISTICS,
#endif

#ifdef HAS_BLE
    BLE,
#endif

#ifdef HAS_BOOTLOADER
    BOOTLOADER,
#endif

#ifdef HAS_COM
    COM,
#endif

    CRC8,
#ifdef HAS_HID
    HID,
#endif

#ifdef HAS_LC3
    LC3,
#endif

#ifdef HAS_SW_NOR_FLASH
    SW_NOR_FLASH,
#endif

#ifdef HAS_DFT
    DFT,
    IDFT,
#endif

#ifdef HAS_VOLTAGE_DIVIDER
    VOLTAGE_DIVIDER,
#endif

#ifdef HAS_KALAH
    KALAH,
#endif

#ifdef HAS_GM67
    GM67,
#endif

    DIAG,

#ifdef HAS_DW1000_GPIO
    DW1000_GPIO,
#endif

#ifdef HAS_DS3231
    DS3231,
#endif /*HAS_DS3231*/

#ifdef HAS_DW1000
    DW1000,
#endif /*HAS_DW1000*/

#ifdef HAS_DWM1000
    DWM1000,
#endif /*HAS_DWM1000*/

#ifdef HAS_DECADRIVER
    DECA,
#endif /*HAS_DECADRIVER*/

#ifdef HAS_DWM3000
    DWM3000,
#endif /*HAS_DWM3000*/
    DBG,

#ifdef HAS_COMPLEX
    COMPLEX,
#endif

#ifdef HAS_PROTOCOL
    PROTOCOL,
#endif

#ifdef HAS_MICROCONTROLLER
    MICROCONTROLLER,
#endif

#ifdef HAS_MBR
    MBR,
#endif

#ifdef HAS_LOG
    LOG,
#endif

#ifdef HAS_AUTO_VOLUME
    AUTO_VOLUME,
#endif

#ifdef HAS_MASS_STORAGE_CLASS
    MSD,
#endif

#ifdef HAS_C_GENERATOR
    C_GENERATOR,
#endif

#ifdef HAS_CODE_STYLE_CHECKER
    CODE_STYLE_CHECKER,
#endif

#ifdef HAS_SA51034
    SA51034,
#endif

#ifdef HAS_FAT_FS
    FAT_FS,
    DISK,
#endif

#ifdef HAS_FREE_RTOS
    FREE_RTOS,
#endif

#ifdef HAS_RTOS
    RTOS,
#endif

#ifdef HAS_FIFO
    FIFO,
#endif
#ifdef HAS_FLASH_FS
    FLASH_FS,
#endif

#ifdef HAS_BH1750
    BH1750,
#endif

#ifdef HAS_BPSK
    BPSK,
#endif

#ifdef HAS_GPIO
    GPIO,
#endif

#ifdef HAS_LTR390
    LTR390,
    ALS,
    UVS,
#endif

#ifdef HAS_QUADRATURE_MIXER
    QUADRATURE_MIXER,
#endif

#ifdef HAS_BQ24079
    BQ24079,
#endif

#ifdef HAS_RS2058
    RS2058,
#endif

#ifdef HAS_SWD
    SWD,
#endif

#ifdef HAS_STORAGE
    STORAGE,
#endif

#ifdef HAS_GNSS
    GNSS,
#endif

#ifdef HAS_PWM_DAC
    PWM_DAC,
#endif

#ifdef HAS_GPS
    GPS,
#endif

#ifdef HAS_DELTA_SIGMA
    DELTA_SIGMA,
#endif


#ifdef HAS_CLOCK_DIVIDER
    CLOCK_DIVIDER,
#endif

#ifdef HAS_GLONASS
    GLONASS,
#endif

#ifdef HAS_SCR1_TIMER
    SCR_TIMER,
#endif

#ifdef HAS_GFSK
    GFSK,
#endif

#ifdef HAS_FFT
    FFT,
#endif
#ifdef HAS_LIGHT_SENSOR
    LIGHT_SENSOR,
#endif

#ifdef HAS_HEX_BIN
    HEX_BIN,
#endif

#ifdef HAS_BLACK_BOX
    BLACK_BOX,
#endif

#ifdef HAS_MIC2026
    MIC2026,
#endif

#ifdef HAS_PHASE_DETECTOR
	PHASE_DETECTOR,
#endif

#ifdef HAS_UBLOX_NEO_6M
	UBLOX_NEO_6M,
#endif


    HMON,
#ifdef HAS_LIMITER
    LIMITER,
#endif

#ifdef HAS_DECAWAVE_NATIVE
    DECAWAVE_NATIVE,
#endif

#ifdef HAS_DECAWAVE
    DECAWAVE,
#endif

#ifdef HAS_MODULATOR
    MODULATOR,
#endif

#ifdef HAS_AUTO_VERSION
    AUTO_VERSION,
#endif

#ifdef HAS_STRING_READER
    STRING_READER,
#endif

#ifdef HAS_ZEPHYR_RTOS
    ZEPHYR_RTOS,
#endif

#ifdef HAS_IIR
    IIR,
#endif

#ifdef HAS_FIR
    FIR,
#endif

#ifdef HAS_FIR_INT
    FIR_INT,
#endif

#ifdef HAS_I2C
    I2C,
#endif

#ifdef HAS_DISPLAY
    DISPLAY,
#endif

#ifdef HAS_WAV
	WAV,
#endif


#ifdef HAS_IEC16022
    IEC16022,
#endif

#ifdef HAS_GRAPHVIZ_TO_TSORT
    GRAPHVIZ_TO_TSORT,
#endif

#ifdef HAS_CIRCULAR_BUFFER
    CIRCULAR_BUFFER,
#endif

#ifdef HAS_SDR
    DLL,
    FLL,
    PLL,
    SDR,
#endif

#ifdef HAS_I2S
    I2S,
    I2S_FULL_DUPLEX,
#endif

#ifdef HAS_END_OF_BLOCK
    END_OF_BLOCK,
#endif

#ifdef HAS_LED
    LED,
#endif

#ifdef HAS_LED_MONO
    LED_MONO,
#endif

#ifdef HAS_CSV
    CSV,
#endif


#ifdef HAS_ANALOG_FILTER
    ANALOG_FILTER,
#endif

#ifdef HAS_CALIBRATION_DATA
    CALIBRATION_DATA,
#endif

#ifdef HAS_LED_RGB
    LED_RGB,
#endif

#ifdef HAS_IWDG
    LG_IWDG,
#endif

#ifdef HAS_ADC
    LG_ADC,
#endif

#ifdef HAS_INPUT_CAPTURE
    INPUT_CAPTURE,
#endif

#ifdef HAS_TOPO_SORT
    TOPO_SORT,
#endif

#ifdef HAS_ADT
    ADT,
#endif

#ifdef HAS_AT24CXX
    AT24C,
#endif

#ifdef HAS_SCAN
    SCAN,
#endif

#ifdef HAS_DECIMATOR
    DECIMATOR,
#endif

#ifdef HAS_HASHSET
    HASHSET,
#endif

#ifdef HAS_GENERIC
    GENERIC,
#endif

#ifdef HAS_FILE_API
    FILE_API,
#endif

#ifdef HAS_DSP
    DSP,
#endif

#ifdef HAS_SDIO
    LG_SDIO,
#endif

#ifdef HAS_FOURIER_SERIES
    FOURIER_SERIES,
#endif


#ifdef HAS_W25Q32JV
    W25Q32JV,
#endif

#ifdef HAS_LOAD_DETECT
    LOAD_DETECT,
#endif

#ifdef HAS_WM8731
    WM8731,
#endif

#ifdef HAS_SCHEDULER
    SCHEDULER,
#endif

#ifdef HAS_CALENDAR
    LG_CAL,
#endif

#ifdef HAS_DDS
    DDS,
#endif

#ifdef HAS_DAC
    LG_DAC,
#endif

#ifdef HAS_SSD1306
    SSD1306,
#endif

#ifdef HAS_SOUND_LOCALIZATION
    SOUND_LOCALIZATION,
#endif

#ifdef HAS_CROSS_DETECT
    CROSS_DETECT,
#endif

#ifdef HAS_ASICS
    ASICS,
#endif

#ifdef HAS_EEPROM
    EEPROM,
#endif

#ifdef HAS_SET
    SET,
#endif

#ifdef HAS_RS485
    RS485,
#endif

#ifdef HAS_SONAR
	SONAR,
#endif


#ifdef HAS_LIFO
    LIFO,
#endif

#ifdef HAS_FILE_PC
    FILE_PC,
#endif

#ifdef HAS_FLASH
    LG_FLASH,
#endif

#ifdef HAS_NVIC
    LG_NVIC,
#endif

#ifdef HAS_INTERRUPT
    LG_INT,
#endif

#ifdef HAS_PWR
    LG_PWR,
#endif

#ifdef HAS_RNG
    LG_RNG,
#endif

#ifdef HAS_LOAD
    LOAD,
#endif
#ifdef HAS_LORA
    LORA,
#endif

#ifdef HAS_DTMF
    DTMF,
#endif

#ifdef HAS_RTC
    LG_RTC,
#endif

#ifdef HAS_SET_GAME
    SET_GAME,
#endif

#ifdef HAS_SUPER_CYCLE
    SUPER_CYCLE,
#endif

#ifdef HAS_SX1262
    SX1262,
#endif

#ifdef HAS_SYSTICK
    LG_SYSTICK,
#endif

#ifdef HAS_TIMER_CALC
	TIMER_CALC,
#endif /*HAS_TIMER_CALC*/

#ifdef HAS_MAX9860
    MAX9860,
#endif /*HAS_MAX9860*/

#ifdef HAS_CORRELATOR
	CORRELATOR,
#endif


#ifdef HAS_NMEA
    NMEA,
#endif

#ifdef HAS_NVS
    NVS,
#endif

#ifdef HAS_SPIFI
    SPIFI,
#endif


#ifdef HAS_TPA2013D1
    TPA2013D1,
#endif

#ifdef HAS_PLANETARIUM
    PLANETARIUM,
#endif

#ifdef HAS_DASHBOARD
    DASHBOARD,
#endif

#ifdef HAS_PARAM
    PARAM,
#endif

#ifdef HAS_PDM
    PDM,
#endif

#ifdef HAS_ISO_TP
    ISO_TP,
#endif

#ifdef HAS_UDS
    UDS,
    DID,
#endif

#ifdef HAS_PMIC
    PMIC,
#endif

#ifdef HAS_PID
    PID,
#endif

#ifdef HAS_RS232
	RS232,
#endif

#ifdef HAS_PWM
    PWM,
#endif

#ifdef HAS_RETX
    RETX,
#endif

#ifdef HAS_UWB
    UWB,
#endif

#ifdef HAS_RF
    RF,
#endif

#ifdef HAS_KEYBOARD
    KEYBOARD,
#endif

#ifdef HAS_SOCKET
    LG_SOCKET,
    LG_SOCKET_SERVER,
    LG_SOCKET_CLIENT,
#endif

#ifdef HAS_AUTO_BRIGHTNESS
    AUTO_BRIGHTNESS,
#endif

#ifdef HAS_ECHO_EFFECT
    ECHO_EFFECT,
#endif

#ifdef HAS_KEYLOG
    KEYLOG,
#endif
#ifdef HAS_RTCM
    RTCM,
#endif
#ifdef HAS_SI4703
    SI4703,
#endif

#ifdef HAS_SI4737
    SI4737,
#endif

#ifdef HAS_QSPI
    QSPI,
#endif
#ifdef HAS_SPI
    SPI,
#endif

#ifdef HAS_SALSA20
    SALSA20,
#endif
#ifdef HAS_SERIAL
    SERIAL,
#endif
    SYS,
#ifdef HAS_RADIO
    RADIO,
#endif

#ifdef HAS_NAU8814
    NAU8814,
#endif

#ifdef HAS_SOLUTION
    SOLUTION,
#endif

#ifdef HAS_MATH
    MATH,
#endif

#ifdef HAS_RELAY
    RELAY,
#endif

#ifdef HAS_RTK
    RTK,
#endif

#ifdef HAS_INTERFACES
    INTERFACES,
#endif

#ifdef HAS_SS_TWR
    SS_TWR,
#endif

#ifdef HAS_HW_VERSION
	HW_VERSION,
#endif

#ifdef HAS_DS_TWR
    DS_TWR,
#endif

#ifdef HAS_LIGHT_NAVIGATOR
    LIGHT_NAVIGATOR,
#endif

#ifdef HAS_SD_CARD
    SD_CARD,
#endif

#ifdef HAS_TBFP
    TBFP,
#endif

#ifdef HAS_XML
    XML,
#endif

#ifdef HAS_PLL_CALC
    PLL_CALC,
#endif

#ifdef HAS_PLL_SIM
    PLL_SIM,
#endif

#ifdef HAS_MX25R6435F
    MX25R6435F,
#endif

#ifdef HAS_NOR_FLASH
    NOR_FLASH,
#endif

    TEST,

#ifdef HAS_TIME
    TIME,
#endif

#ifdef HAS_TIMER
    TIMER,
#endif

#ifdef HAS_SOLVER
    SOLVER,
#endif

#ifdef HAS_UART
    UART,
#endif

#ifdef HAS_UBX
    UBX,
#endif

#ifdef HAS_PASTILDA
    PASTILDA,
#endif

#ifdef HAS_WATCHDOG
    WATCHDOG,
#endif /**/

#ifdef HAS_CRYP
    LG_CRYP,
#endif /**/

#ifdef HAS_HW_CRYP
    HW_CRYP,
#endif /**/

#ifdef HAS_HISTOGRAM
    HISTOGRAM,
#endif /**/
#ifdef HAS_SCHMITT_TRIGGER
    SCHMITT_TRIGGER,
#endif /**/

#ifdef HAS_INTERVAL
    INTERVAL,
#endif

#ifdef HAS_STRING
    LINE,
#endif

#ifdef HAS_EXT_INT
    EXT_INT,
#endif

#ifdef HAS_DISTANCE
    DISTANCE,
#endif

#ifdef HAS_RUNNING_LINE
    RUNNING_LINE,
#endif /*HAS_RUNNING_LINE*/

#ifdef HAS_USB
    USB,
    USB_TO_I2S,
    USB_AUDIO,

#ifdef HAS_USB_HOST
    USB_HOST,
#endif /*HAS_USB_HOST*/




#ifdef HAS_USB_DEVICE
    USB_DEVICE,
#endif /*HAS_USB_DEVICE*/

#endif /*HAS_USB*/

#ifdef HAS_RLE
    RLE,
#endif /*HAS_RLE*/

#ifdef HAS_MAX98357
    MAX98357,
#endif /*HAS_MAX98357*/

#ifdef HAS_ZED_F9P
    ZED_F9P,
#endif
    ALL_FACILITY, /*must be last in enum*/
} facility_t;

#ifdef __cplusplus
}
#endif

#endif /* SYS_GENERAL_CONSTANTS_H */
