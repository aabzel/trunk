/*
 * Copyright 2020-2022 Yuntu Microelectronics co.,ltd
 * All rights reserved.
 *
 * YUNTU Confidential. This software is owned or controlled by YUNTU and may only be
 * used strictly in accordance with the applicable license terms. By expressly
 * accepting such terms or by downloading, installing, activating and/or otherwise
 * using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms. If you do not agree to be
 * bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software. The production use license in
 * Section 2.3 is expressly granted for this software.
 */

/*!
 * @file YTM32B1ME0_features.h
 * @brief Chip specific module features
 */

#ifndef YTM32B1ME0_FEATURES_H
#define YTM32B1ME0_FEATURES_H

/* ERRATA sections*/

/* @brief Number of cores. */
#define NUMBER_OF_CORES                     (1u)

/* SOC module features */

/* @brief PORT availability on the SoC. */
#define FEATURE_SOC_PORT_COUNT              (5)

#define FEATURE_SOC_IPC_COUNT               (1)
/* @brief Power down mode availability on the SoC. */
#define FEATURE_SOC_SUPPORT_POWERDOWN_MODE  (1)

#ifdef FPGA_PLATFORM
/* @brief Slow IRC clock frequency(12MHz). */
#define FEATURE_SCU_SIRC_FREQ               (2000000U)
/* @brief Fast IRC trimmed clock frequency(96MHz). */
#define FEATURE_SCU_FIRC_FREQ               (20000000U)
/* @brief FXOSC clock frequency(24MHz). */
#define FEATURE_SCU_FXOSC_FREQ              (20000000U)
/* @brief SXOSC clock frequency(32.768K). */
#define FEATURE_SCU_SXOSC_FREQ              (32768U)
#else
/* @brief Slow IRC clock frequency(12MHz). */
#define FEATURE_SCU_SIRC_FREQ               (12000000U)
/* @brief Fast IRC trimmed clock frequency(96MHz). */
#define FEATURE_SCU_FIRC_FREQ               (96000000U)
/* @brief FXOSC clock frequency(24MHz). */
#define FEATURE_SCU_FXOSC_FREQ              (24000000U)
/* @brief SCU FXOSC support GAIN configuration. */
#define FEATURE_SCU_FXOSC_SUPPORT_GAIN_SEL  (1)
/* @brief SCU support PLL clock. */
#define FEATURE_SCU_SUPPORT_PLL             (1)
/* @brief SCU support CMU reference clock selection. */
#define FEATURE_SCU_SUPPORT_CMU_REFCLK_SEL  (1)
/* @brief SCU support SXOSC 32.768K clock. */
#define FEATURE_SCU_SUPPORT_SXOSC           (1)
#if FEATURE_SCU_SUPPORT_SXOSC
/* @brief SXOSC clock frequency(32.768K). */
#define FEATURE_SCU_SXOSC_FREQ              (32768U)
#endif /* FEATURE_SCU_SUPPORT_SXOSC */
#endif /* FPGA_PLATFORM */
/* @brief Clock switch PLL lock timeout loop count. */
#define FEATURE_CLOCK_TIMEOUT_LOOP_CNT      (0x1FFFF)

/* FLASH module features */

/* @brief Flash block count. */
#define FEATURE_EFM_BLOCK_COUNT             (3u)
/* @brief Flash program flash start address. */
#define FEATURE_EFM_MAIN_ARRAY_START_ADDRESS  (0x0U)
/* @brief Flash program flash end address. */
#define FEATURE_EFM_MAIN_ARRAY_END_ADDRESS  (0xFFFFFU)
/* @brief Flash sector size. */
#define FEATURE_EFM_MAIN_ARRAY_SECTOR_SIZE  (0x800u)
/* @brief Flash has data flash. */
#define FEATURE_EFM_HAS_DATA_FLASH          (1)
#if FEATURE_EFM_HAS_DATA_FLASH
/* @brief Flash data flash start address. */
#define FEATURE_EFM_DATA_ARRAY_START_ADDRESS (0x100000U)
/* @brief Flash data flash end address. */
#define FEATURE_EFM_DATA_ARRAY_END_ADDRESS  (0x13FFFFU)
/* @brief Flash data flash sector size. */
#define FEATURE_EFM_DATA_ARRAY_SECTOR_SIZE  (0x400u)
#endif /* FEATURE_EFM_HAS_DATA_FLASH */
#define FEATURE_EFM_HAS_NVR_FLASH          (1)
#if FEATURE_EFM_HAS_NVR_FLASH
/* @brief Flash NVR start address. */
#define FEATURE_EFM_NVR_ARRAY_START_ADDRESS (0x10000000U)
/* @brief Flash NVR end address. */
#define FEATURE_EFM_NVR_ARRAY_END_ADDRESS   (0x110403FFU)
/* @brief Flash NVR sector size. */
#define FEATURE_EFM_NVR_ARRAY_SECTOR_SIZE   (0x400u)
#endif /* FEATURE_EFM_HAS_NVR_FLASH */

/* @brief Flash sector minimum size. */
#define FEATURE_EFM_FLASH_MIN_SECTOR_SIZE   (0x400u)

/* @brief Flash write unit size. */
#define FEATURE_EFM_WRITE_UNIT_SIZE                    (8u)
/* @brief Flash write unit size in words. */
#define FEATURE_EFM_WRITE_UNIT_WORD_SIZE               (FEATURE_EFM_WRITE_UNIT_SIZE >> 2)
/* @brief Flash Program unit command. */
#define FEATURE_EFM_PROGRAM_CMD_CODE                   (0x02u)
/* @brief Flash Program unit and verify command. */
#define FEATURE_EFM_PROGRAM_VERIFY_CMD_CODE            (0x03u)
/* @brief Flash Erase Sector command. */
#define FEATURE_EFM_ERASE_SECTOR_CMD_CODE              (0x10u)
/* @brief Flash Erase Sector and verify command. */
#define FEATURE_EFM_ERASE_SECTOR_VERIFY_CMD_CODE       (0x11u)
/* @brief Erase Flash Block command. */
#define FEATURE_EFM_ERASE_BLOCK_CMD_CODE               (0x12u)
/* @brief Flash Erase Block and verify command. */
#define FEATURE_EFM_ERASE_BLOCK_VERIFY_CMD_CODE        (0x13u)
/* @brief Flash Load AES KEY command. */
#define FEATURE_EFM_LOAD_AES_KEY_CMD_CODE              (0x20u)
/* @brief Flash NVR program command. */
#define FEATURE_EFM_PROGRAM_NVR_CMD_CODE               (0x40u)
/* @brief Flash NVR read command. */
#define FEATURE_EFM_READ_NVR_CMD_CODE                  (0x42u)
/* @brief Flash NVR erase command. */
#define FEATURE_EFM_ERASE_NVR_CMD_CODE                 (0x41u)
/* @brief Flash Boot Swap command. */
#define FEATURE_EFM_BOOT_SWAP_CMD_CODE                 (0x30u)
/* @brief Flash Status Error Code Mask. */
#define FEATURE_EFM_CMD_ERROR_MASK                     (EFM_STS_FAIL_MASK | EFM_STS_ACCERR_MASK | EFM_STS_UNRECOVERR_MASK | EFM_STS_RECOVERR_MASK)
/* @brief Flash Unlock command register. */
#define EFM_UNLOCK_CMD_REGISTER()     \
    do                                \
    {                                 \
        EFM->CMD_UNLOCK = 0xfd9573f5; \
    } while (0)
/* @brief Flash enable flash write commands. */
#define EFM_ENABLE_WE_COMMAND() \
    do                          \
    {                           \
        ARM_MPU_Disable();      \
    } while (0)
/* @brief Flash disable flash write commands. */
#define EFM_DISABLE_WE_COMMAND()                 \
    do                                           \
    {                                            \
        ARM_MPU_Enable(MPU_CTRL_PRIVDEFENA_Msk); \
    } while (0)

/* RCU module features */
/* @brief Reset pin output feature */
#define FEATURE_RCU_HAS_PIN_OUTPUT                  (1U)

/* WDG module features */

/*!
 * @brief WDG clock source.
 * Implements : wdg_clock_source_t_Class
 */
typedef enum
{
    WDG_SIRC_CLOCK = 0x00U, /*!< SIRC clock */
    WDG_SXOSC_CLOCK = 0x01U, /*!< SXOSC clock */
} wdg_clock_source_t;
/* @brief The 32-bit value used for unlocking the WDG. */
#define FEATURE_WDG_UNLOCK_VALUE_1                      (0xB631)
#define FEATURE_WDG_UNLOCK_VALUE_2                      (0xC278)
/* @brief The 32-bit value used for resetting the WDG counter. */
#define FEATURE_WDG_TRIGGER_VALUE_1                     (0xA518)
#define FEATURE_WDG_TRIGGER_VALUE_2                     (0xD826)
/* @brief The reset value of the timeout register. */
#define FEATURE_WDG_TOVR_RESET_VALUE                    (0x400U)
/* @brief The value minimum of the timeout register. */
#define FEATURE_WDG_MINIMUM_TIMEOUT_VALUE               (0x0U)
/* @brief The reset value of the window register. */
#define FEATURE_WDG_WVR_RESET_VALUE                     (0x0U)
/* @brief The mask of the reserved bit in the CS register. */
#define FEATURE_WDG_CS_RESERVED_MASK                    (0x2000U)
/* @brief The value used to set WDG source clock from LPO. */
#define FEATURE_WDG_CLK_FROM_LPO                        (0x1UL)

/* @brief Default reset value of the CS register. */
#define FEATURE_WDG_CR_RESET_VALUE                      (0x2520U)

/* EWDG module features */
/* @brief First byte of the EWM Service key        */
#define FEATURE_EWDG_KEY_FIRST_BYTE                      (0xA8U)
/* @brief Second byte of the EWM Service key       */
#define FEATURE_EWDG_KEY_SECOND_BYTE                     (0x6CU)
/* @brief EWDG maximum compare high value. */
#define FEATURE_EWDG_CMPH_MAX_VALUE                      (0xFEU)
/* @brief EWDG minimum compare low value. */
#define FEATURE_EWDG_CMPL_MIN_VALUE                      (0x00U)


/* Interrupt module features */

/* @brief Lowest interrupt request number. */
#define FEATURE_INTERRUPT_IRQ_MIN                       (NMI_IRQn)
/* @brief Highest interrupt request number. */
#define FEATURE_INTERRUPT_IRQ_MAX                       (WKU_IRQn)
/**< Number of priority bits implemented in the NVIC */
#define FEATURE_NVIC_PRIO_BITS                          (3U)
/* @brief Has software interrupt. */
#define FEATURE_INTERRUPT_HAS_SOFTWARE_IRQ              (0u)
/* @brief Has pending interrupt state. */
#define FEATURE_INTERRUPT_HAS_PENDING_STATE             (1u)
/* @brief Has active interrupt state. */
#define FEATURE_INTERRUPT_HAS_ACTIVE_STATE              (0u)
/* @brief Multicore support for interrupts */
#define FEATURE_INTERRUPT_MULTICORE_SUPPORT             (0u)
/* @brief Registers in which the start of interrupt vector table needs to be configured */
#define FEATURE_INTERRUPT_INT_VECTORS                   {&SCB->VTOR}

/* eTMR module features */

/* @brief Number of PWM channels */
#define FEATURE_eTMR_CHANNEL_COUNTS                     {8U, 8U, 8U, 8U, 8U, 8U}
#define FEATURE_eTMR_CHANNEL_INTERRUPT_COUNTS           (4U)
#define FEATURE_eTMR_CHANNEL_MAX_COUNT                  (8U)
#define FEATURE_eTMR0_CHANNEL_MAX_COUNT                 (8U)
#define FEATURE_eTMR1_CHANNEL_MAX_COUNT                 (8U)
#define FEATURE_eTMR2_CHANNEL_MAX_COUNT                 (8U)
#define FEATURE_eTMR3_CHANNEL_MAX_COUNT                 (8U)
#define FEATURE_eTMR4_CHANNEL_MAX_COUNT                 (8U)
#define FEATURE_eTMR5_CHANNEL_MAX_COUNT                 (8U)
/* @brief Number of fault channels */
#define FEATURE_eTMR_FAULT_CHANNELS                     (4U)
/* @brief Output channel offset */
#define FEATURE_eTMR_OUTPUT_CHANNEL_OFFSET              (16U)
/* @brief Max counter value */
#define FEATURE_eTMR_CNT_MAX_VALUE_U32                  (0xFFFFFFFFU)
/* @brief Input capture for single shot */
#define FEATURE_eTMR_INPUT_CAPTURE_SINGLE_SHOT          (2U)
/* @brief Number of interrupt vector for channels of the eTMR module. */
#define FEATURE_eTMR_HAS_NUM_IRQS_CHANS                 (4U)
/* @brief Deadtime prescaler */
#define FEATURE_eTMR_HAS_DEAD_TIME_PRESCALER            (0U)
/* @brief Double switch */
#define FEATURE_eTMR_HAS_DOUBLE_SWITCH                  (1U)
/* @brief Combination capture mode */
#define FEATURE_eTMR_HAS_COMBINATION_CAPTURE_MODE       (0U)
/* @brief Capture hold */
#define FEATURE_eTMR_HAS_CAPTURE_HOLD                   (0U)
/* @brief Output trigger width */
#define FEATURE_eTMR_HAS_OUTPUT_TRIGGER_WIDTH           (1U)
/* @brief MID feature */
#define FEATURE_eTMR_HAS_MID                            (1U)
/* @brief Support to configure counter initial value source */
#define FEATURE_eTMR_HAS_CNT_INIT_SRC                   (1U)
/* @brief Counter initial value configurable */
#define FEATURE_eTMR_HAS_INIT_REG                       (1U)
/* @brief CHINIT bit is in Channel CTRL register */
#define FEATURE_eTMR_HAS_CHINIT_BIT                     (1U)
/* @brief Support quad decoder mod register */
#define FEATURE_eTMR_HAS_QUAD_DECODER_MOD               (1U)
/* @brief Support configure dead time alone */
#define FEATURE_eTMR_DEADTIME_CONFIG_EACH_CHANNEL       (1U)
/* @brief Counter count from INIT+1 */
#define FEATURE_eTMR_COUNT_FROM_INIT_PLUS_ONE           (0U)
/* @brief eTMR internal clock source */
#define eTMR_INTERNAL_CLOCK                             (FAST_BUS_CLK)
/* @brief eTMR external clock source frequency */
#define FEATURE_eTMR_EXTERNAL_CLOCK_FREQ                (1000000U)
/* @brief eTMR Dither MOD configuration */
#define FEATURE_eTMR_HAS_DITHERING                      (1U)
/* @brief eTMR support center align calculation by hardware */
#define FEATURE_eTMR_HAS_HW_CENTER_ALIGN_CALCULATION    (0U)
/* @brief eTMR support channel val0, val1 match interrupt in PWM mode */
#define FEATURE_eTMR_HAS_CHANNEL_VALUE_MATCH_INTERRUPT_IN_PWM_MODE  (0U)

/* @brief eTMR  */

/* I2C module features */

/* @brief DMA instance used for I2C module */
#define I2C_DMA_INSTANCE                                (0U)

/* @brief DMA requests for I2C module. */
#define I2C_DMA_REQ                                     {{(uint8_t)DMA_REQ_I2C0_TX, (uint8_t)DMA_REQ_I2C0_RX}, \
                                                            {(uint8_t)DMA_REQ_I2C1_TX, (uint8_t)DMA_REQ_I2C1_RX}, \
                                                            {(uint8_t)DMA_REQ_I2C2_TX, (uint8_t)DMA_REQ_I2C2_RX}}
/* @brief IPC clocks for I2C module. */
#define I2C_IPC_CLOCKS                                  {I2C0_CLK, I2C1_CLK, I2C2_CLK}

#define I2C_SLAVE_SUPPORT                               {1U, 1U, 1U}

/* @brief Disable high-speed and ultra-fast operating modes */
#define I2C_HAS_FAST_PLUS_MODE                          (1U)
#define I2C_HAS_HIGH_SPEED_MODE                         (1U)
#define I2C_HAS_ULTRA_FAST_MODE                         (1U)

/* CRC module features */

/* @brief CRC module */
/* @brief Default CRC bit width */
#define FEATURE_CRC_DEFAULT_WIDTH                       CRC_BITS_16
/* @brief CRC support CRC 4 mode*/
#define FEATURE_CRC_SUPPORT_CRC4                        (1)
/* @brief Default CRC read transpose */
#define FEATURE_CRC_DEFAULT_READ_TRANSPOSE              CRC_TRANSPOSE_NONE
/* @brief Default CRC write transpose */
#define FEATURE_CRC_DEFAULT_WRITE_TRANSPOSE             CRC_TRANSPOSE_NONE
/* @brief Default polynomial 0x1021U */
#define FEATURE_CRC_DEFAULT_POLYNOMIAL                  (0x1021U)
/* @brief Default seed value is 0xFFFFU */
#define FEATURE_CRC_DEFAULT_SEED                        (0xFFFFU)

/* PCTRL module features */
/* @brief Has control lock. */
#define FEATURE_PCTRL_HAS_PIN_CONTROL_LOCK              (0)
/* @brief Has open drain control. */
#define FEATURE_PINS_HAS_OPEN_DRAIN                     (0)
/* @brief Has digital filter. */
#define FEATURE_PINS_HAS_DIGITAL_FILTER                 (1)
/* @brief Has digital filter clock selection. */
#define FEATURE_PINS_HAS_FILTER_CLOCK_SEL               (0)
/* @brief Has trigger output to trigger other peripherals. */
#define FEATURE_PINS_HAS_TRIGGER_OUT                    (0)
/* @brief Has setting flag only. */
#define FEATURE_PINS_HAS_FLAG_SET_ONLY                  (0)
/* @brief Has pull resistor selection available. */
#define FEATURE_PINS_HAS_PULL_SELECTION                 (1)
/* @brief Has slew rate control. */
#define FEATURE_PINS_HAS_SLEW_RATE                      (1)
/* @brief Has filter clock selection control. */
#define FEATURE_PINS_HAS_FILTER_CLOCK_SELECTION         (0)
/* @brief Has passive filter. */
#define FEATURE_PINS_HAS_PASSIVE_FILTER                 (1)
/* @brief Has drive strength. */
#define FEATURE_PINS_HAS_DRIVE_STRENGTH                 (1)
/* @brief Has drive strength control bits*/
#define FEATURE_PINS_HAS_DRIVE_STRENGTH_CONTROL         (1)
/* @brief Has port input disable control bits*/
#define FEATURE_PINS_HAS_INPUT_DISABLE                  (1)


/* ACMP module features */

/* @brief Comparator has internal DAC module */
#define FEATURE_ACMP_HAS_DAC                            (1U)
/* @brief Comparator has power mode control */
#define FEATURE_ACMP_HAS_POWER_MODE                     (1U)
/* @brief Comparator has pin output enable */
#define FEATURE_ACMP_HAS_PINOUT_ENABLE                  (0U)
/* @brief Comparator has mode config */
#define FEATURE_ACMP_HAS_MODE_CFG                       (1U)
/* @brief ACMP Function Clock Selection */
#define FEATURE_ACMP_HAS_CLK_SRC_SEL                    (1U)
/* @brief ACMP DAC reference voltage selection */
#define FEATURE_ACMP_HAS_DAC_VOLTAGE_REF_SRC            (1U)
/* @brief ACMP DAC output enable */
#define FEATURE_ACMP_HAS_DAC_OUTPUT                     (0U)
/* @brief ACMP Auto disable hard block */
#define FEATURE_ACMP_HAS_AUTODIS                        (1U)
/* @brief ACMP comparator offset control */
#define FEATURE_ACMP_HAS_OFFSET_CONTROL                 (1U)
/* @brief ACMP internal current control */
#define FEATURE_ACMP_INTERNAL_CURRENT_CONTROL           (1U)
/* @brief ACMP support sxosc clock */
#define FEATURE_ACMP_SUPPORT_SXOSC_CLK                  (1U)

#define FEATURE_ACMP_CTRL_RESET_VALUE                   (0x00000000)
#define FEATURE_ACMP_STS_CLEAR_MASK                     (0x00FF0000)
#define FEATURE_ACMP_STS_CH_OUT_MASK                    (0xFF000000)
#define FEATURE_ACMP_STS_CH_OUT_SHIFT                   (24)
#define FEATURE_ACMP_STS_CH_FLAG_MASK                   (0x00FF0000)
#define FEATURE_ACMP_STS_CH_FLAG_SHIFT                  (16)
#define FEATURE_ACMP_DEFAULT_CONT_PERIOD                (0x30)
#define FEATURE_ACMP_DEFAULT_CONT_POS                   (0x18)

#if FEATURE_ACMP_HAS_DAC
/* @brief Comparator fix DAC input to mux side */
#define FEATURE_ACMP_DAC_FIX_SELECTION                  (0U)
#define ACMP_DAC_RESOLUTION                             (255U)
#endif /* FEATURE_ACMP_HAS_DAC */


/* @brief Supports peripheral clock source. */
#define FEATURE_HAS_PERIPHERAL_CLOCK_SOURCE             (0U)
/*! @brief Clock names. */
typedef enum {
    /* IPC clocks */
    DMA_CLK                  =  0U, /*!< DMA        clock source */
    TRACE_CLK                =  1U, /*!< TRACE      clock source */
    EFM_CLK                  =  2U, /*!< EFM        clock source */
    GPIO_CLK                 =  3U, /*!< GPIO       clock source */
    PCTRLA_CLK               =  4U, /*!< PCTRLA     clock source */
    PCTRLB_CLK               =  5U, /*!< PCTRLB     clock source */
    PCTRLC_CLK               =  6U, /*!< PCTRLC     clock source */
    PCTRLD_CLK               =  7U, /*!< PCTRLD     clock source */
    PCTRLE_CLK               =  8U, /*!< PCTRLE     clock source */
    LINFlexD0_CLK            =  9U, /*!< LINFlexD0  clock source */
    LINFlexD1_CLK            = 10U, /*!< LINFlexD1  clock source */
    LINFlexD2_CLK            = 11U, /*!< LINFlexD2  clock source */
    LINFlexD3_CLK            = 12U, /*!< LINFlexD3  clock source */
    LINFlexD4_CLK            = 13U, /*!< LINFlexD4  clock source */
    LINFlexD5_CLK            = 14U, /*!< LINFlexD5  clock source */
    I2C0_CLK                 = 15U, /*!< I2C0       clock source */
    I2C1_CLK                 = 16U, /*!< I2C1       clock source */
    I2C2_CLK                 = 17U, /*!< I2C2       clock source */
    SPI0_CLK                 = 18U, /*!< SPI0       clock source */
    SPI1_CLK                 = 19U, /*!< SPI1       clock source */
    SPI2_CLK                 = 20U, /*!< SPI2       clock source */
    SPI3_CLK                 = 21U, /*!< SPI3       clock source */
    SPI4_CLK                 = 22U, /*!< SPI4       clock source */
    SPI5_CLK                 = 23U, /*!< SPI5       clock source */
    FlexCAN0_CLK             = 24U, /*!< FlexCAN0   clock source */
    FlexCAN1_CLK             = 25U, /*!< FlexCAN1   clock source */
    FlexCAN2_CLK             = 26U, /*!< FlexCAN2   clock source */
    FlexCAN3_CLK             = 27U, /*!< FlexCAN3   clock source */
    FlexCAN4_CLK             = 28U, /*!< FlexCAN4   clock source */
    FlexCAN5_CLK             = 29U, /*!< FlexCAN5   clock source */
    ADC0_CLK                 = 30U, /*!< ADC0       clock source */
    ADC1_CLK                 = 31U, /*!< ADC1       clock source */
    ACMP0_CLK                = 32U, /*!< ACMP0      clock source */
    PTU0_CLK                 = 33U, /*!< PTU0       clock source */
    PTU1_CLK                 = 34U, /*!< PTU1       clock source */
    TMU_CLK                  = 35U, /*!< TMU        clock source */
    eTMR0_CLK                = 36U, /*!< eTMR0      clock source */
    eTMR1_CLK                = 37U, /*!< eTMR1      clock source */
    eTMR2_CLK                = 38U, /*!< eTMR2      clock source */
    eTMR3_CLK                = 39U, /*!< eTMR3      clock source */
    eTMR4_CLK                = 40U, /*!< eTMR4      clock source */
    eTMR5_CLK                = 41U, /*!< eTMR5      clock source */
    TMR0_CLK                 = 42U, /*!< TMR0       clock source */
    pTMR0_CLK                = 43U, /*!< pTMR0      clock source */
    lpTMR0_CLK               = 44U, /*!< lpTMR0     clock source */
    RTC_CLK                  = 45U, /*!< RTC        clock source */
    REGFILE_CLK              = 46U, /*!< REGFILE    clock source */
    WKU_CLK                  = 47U, /*!< WKU        clock source */
    CRC_CLK                  = 48U, /*!< CRC        clock source */
    TRNG_CLK                 = 49U, /*!< TRNG       clock source */
    HCU_CLK                  = 50U, /*!< HCU        clock source */
    WDG_CLK                  = 51U, /*!< WDG        clock source */
    EWDG_CLK                 = 52U, /*!< EWDG       clock source */
    INTM_CLK                 = 53U, /*!< INTM       clock source */
    EMU_CLK                  = 54U, /*!< EMU        clock source */
    STU_CLK                  = 55U, /*!< STU        clock source */
    CIM_CLK                  = 56U, /*!< CIM        clock source */
    SCU_CLK                  = 57U, /*!< SCU        clock source */
    PCU_CLK                  = 58U, /*!< PCU        clock source */
    RCU_CLK                  = 59U, /*!< RCU        clock source */

    IPC_PERI_END_OF_CLOCK    = 60U, /*!< IPC_PERI_END_OF_CLOCK */
    IPC_SIRC_CLK             = 61U, /*!< IPC_SIRC   clock source */
    IPC_FIRC_CLK             = 62U, /*!< IPC_FIRC   clock source */
    IPC_FXOSC_CLK            = 63U, /*!< IPC_FXOSC  clock source */
    IPC_SXOSC_CLK            = 64U, /*!< IPC_SXOSC  clock source */
    IPC_PLL_CLK              = 65U, /*!< IPC_PLL    clock source */

    IPC_END_OF_CLOCK         = 66U, /*!< IPC_END_OF_CLOCK */
    CORE_CLK                 = 67U, /*!< CORE       clock source */
    FAST_BUS_CLK             = 68U, /*!< FAST_BUS   clock source */
    SLOW_BUS_CLK             = 69U, /*!< SLOW_BUS   clock source */

    CLOCK_NAME_COUNT         = 70U, /*!< CLOCK_NAME_COUNT */
} clock_names_t;
/*! @brief IPC clock name mappings
 *  Mappings between clock names and peripheral clock control indexes.
 *  If there is no peripheral clock control index for a clock name,
 *  then the corresponding value is IPC_INVALID_INDEX.
 */
#define IPC_DMA_INDEX          (  8U)
#define IPC_TRACE_INDEX        ( 15U)
#define IPC_EFM_INDEX          ( 16U)
#define IPC_GPIO_INDEX         ( 17U)
#define IPC_PCTRLA_INDEX       ( 18U)
#define IPC_PCTRLB_INDEX       ( 19U)
#define IPC_PCTRLC_INDEX       ( 20U)
#define IPC_PCTRLD_INDEX       ( 21U)
#define IPC_PCTRLE_INDEX       ( 22U)
#define IPC_LINFlexD0_INDEX    ( 27U)
#define IPC_LINFlexD1_INDEX    ( 28U)
#define IPC_LINFlexD2_INDEX    ( 29U)
#define IPC_LINFlexD3_INDEX    ( 30U)
#define IPC_LINFlexD4_INDEX    ( 31U)
#define IPC_LINFlexD5_INDEX    ( 32U)
#define IPC_I2C0_INDEX         ( 35U)
#define IPC_I2C1_INDEX         ( 36U)
#define IPC_I2C2_INDEX         ( 37U)
#define IPC_SPI0_INDEX         ( 42U)
#define IPC_SPI1_INDEX         ( 43U)
#define IPC_SPI2_INDEX         ( 44U)
#define IPC_SPI3_INDEX         ( 45U)
#define IPC_SPI4_INDEX         ( 46U)
#define IPC_SPI5_INDEX         ( 47U)
#define IPC_FlexCAN0_INDEX     ( 48U)
#define IPC_FlexCAN1_INDEX     ( 52U)
#define IPC_FlexCAN2_INDEX     ( 56U)
#define IPC_FlexCAN3_INDEX     ( 60U)
#define IPC_FlexCAN4_INDEX     ( 61U)
#define IPC_FlexCAN5_INDEX     ( 62U)
#define IPC_ADC0_INDEX         ( 64U)
#define IPC_ADC1_INDEX         ( 65U)
#define IPC_ACMP0_INDEX        ( 67U)
#define IPC_PTU0_INDEX         ( 70U)
#define IPC_PTU1_INDEX         ( 71U)
#define IPC_TMU_INDEX          ( 72U)
#define IPC_eTMR0_INDEX        ( 73U)
#define IPC_eTMR1_INDEX        ( 74U)
#define IPC_eTMR2_INDEX        ( 75U)
#define IPC_eTMR3_INDEX        ( 76U)
#define IPC_eTMR4_INDEX        ( 77U)
#define IPC_eTMR5_INDEX        ( 78U)
#define IPC_TMR0_INDEX         ( 84U)
#define IPC_pTMR0_INDEX        ( 90U)
#define IPC_lpTMR0_INDEX       ( 93U)
#define IPC_RTC_INDEX          ( 96U)
#define IPC_REGFILE_INDEX      ( 97U)
#define IPC_WKU_INDEX          ( 98U)
#define IPC_CRC_INDEX          (101U)
#define IPC_TRNG_INDEX         (102U)
#define IPC_HCU_INDEX          (103U)
#define IPC_WDG_INDEX          (106U)
#define IPC_EWDG_INDEX         (107U)
#define IPC_INTM_INDEX         (113U)
#define IPC_EMU_INDEX          (114U)
#define IPC_STU_INDEX          (119U)
#define IPC_CIM_INDEX          (123U)
#define IPC_SCU_INDEX          (124U)
#define IPC_PCU_INDEX          (126U)
#define IPC_RCU_INDEX          (127U)
#define IPC_IPC_PERI_END_OF_CLOCK_INDEX   (128U)
#define IPC_IPC_SIRC_INDEX     (129U)
#define IPC_IPC_FIRC_INDEX     (130U)
#define IPC_IPC_FXOSC_INDEX    (131U)
#define IPC_IPC_SXOSC_INDEX    (132U)
#define IPC_IPC_PLL_INDEX      (133U)
#define IPC_IPC_END_OF_CLOCK_INDEX   (134U)
#define IPC_CORE_INDEX         (135U)
#define IPC_FAST_BUS_INDEX     (136U)
#define IPC_SLOW_BUS_INDEX     (137U)
#define IPC_CLOCK_NAME_COUNT_INDEX   (138U)

#define  IPC_CLOCK_NAME_MAPPINGS \
{                                \
    IPC_DMA_INDEX,            /*!< DMA        clock source    8u */ \
    IPC_TRACE_INDEX,          /*!< TRACE      clock source   15u */ \
    IPC_EFM_INDEX,            /*!< EFM        clock source   16u */ \
    IPC_GPIO_INDEX,           /*!< GPIO       clock source   17u */ \
    IPC_PCTRLA_INDEX,         /*!< PCTRLA     clock source   18u */ \
    IPC_PCTRLB_INDEX,         /*!< PCTRLB     clock source   19u */ \
    IPC_PCTRLC_INDEX,         /*!< PCTRLC     clock source   20u */ \
    IPC_PCTRLD_INDEX,         /*!< PCTRLD     clock source   21u */ \
    IPC_PCTRLE_INDEX,         /*!< PCTRLE     clock source   22u */ \
    IPC_LINFlexD0_INDEX,      /*!< LINFlexD0  clock source   27u */ \
    IPC_LINFlexD1_INDEX,      /*!< LINFlexD1  clock source   28u */ \
    IPC_LINFlexD2_INDEX,      /*!< LINFlexD2  clock source   29u */ \
    IPC_LINFlexD3_INDEX,      /*!< LINFlexD3  clock source   30u */ \
    IPC_LINFlexD4_INDEX,      /*!< LINFlexD4  clock source   31u */ \
    IPC_LINFlexD5_INDEX,      /*!< LINFlexD5  clock source   32u */ \
    IPC_I2C0_INDEX,           /*!< I2C0       clock source   35u */ \
    IPC_I2C1_INDEX,           /*!< I2C1       clock source   36u */ \
    IPC_I2C2_INDEX,           /*!< I2C2       clock source   37u */ \
    IPC_SPI0_INDEX,           /*!< SPI0       clock source   42u */ \
    IPC_SPI1_INDEX,           /*!< SPI1       clock source   43u */ \
    IPC_SPI2_INDEX,           /*!< SPI2       clock source   44u */ \
    IPC_SPI3_INDEX,           /*!< SPI3       clock source   45u */ \
    IPC_SPI4_INDEX,           /*!< SPI4       clock source   46u */ \
    IPC_SPI5_INDEX,           /*!< SPI5       clock source   47u */ \
    IPC_FlexCAN0_INDEX,       /*!< FlexCAN0   clock source   48u */ \
    IPC_FlexCAN1_INDEX,       /*!< FlexCAN1   clock source   52u */ \
    IPC_FlexCAN2_INDEX,       /*!< FlexCAN2   clock source   56u */ \
    IPC_FlexCAN3_INDEX,       /*!< FlexCAN3   clock source   60u */ \
    IPC_FlexCAN4_INDEX,       /*!< FlexCAN4   clock source   61u */ \
    IPC_FlexCAN5_INDEX,       /*!< FlexCAN5   clock source   62u */ \
    IPC_ADC0_INDEX,           /*!< ADC0       clock source   64u */ \
    IPC_ADC1_INDEX,           /*!< ADC1       clock source   65u */ \
    IPC_ACMP0_INDEX,          /*!< ACMP0      clock source   67u */ \
    IPC_PTU0_INDEX,           /*!< PTU0       clock source   70u */ \
    IPC_PTU1_INDEX,           /*!< PTU1       clock source   71u */ \
    IPC_TMU_INDEX,            /*!< TMU        clock source   72u */ \
    IPC_eTMR0_INDEX,          /*!< eTMR0      clock source   73u */ \
    IPC_eTMR1_INDEX,          /*!< eTMR1      clock source   74u */ \
    IPC_eTMR2_INDEX,          /*!< eTMR2      clock source   75u */ \
    IPC_eTMR3_INDEX,          /*!< eTMR3      clock source   76u */ \
    IPC_eTMR4_INDEX,          /*!< eTMR4      clock source   77u */ \
    IPC_eTMR5_INDEX,          /*!< eTMR5      clock source   78u */ \
    IPC_TMR0_INDEX,           /*!< TMR0       clock source   84u */ \
    IPC_pTMR0_INDEX,          /*!< pTMR0      clock source   90u */ \
    IPC_lpTMR0_INDEX,         /*!< lpTMR0     clock source   93u */ \
    IPC_RTC_INDEX,            /*!< RTC        clock source   96u */ \
    IPC_REGFILE_INDEX,        /*!< REGFILE    clock source   97u */ \
    IPC_WKU_INDEX,            /*!< WKU        clock source   98u */ \
    IPC_CRC_INDEX,            /*!< CRC        clock source  101u */ \
    IPC_TRNG_INDEX,           /*!< TRNG       clock source  102u */ \
    IPC_HCU_INDEX,            /*!< HCU        clock source  103u */ \
    IPC_WDG_INDEX,            /*!< WDG        clock source  106u */ \
    IPC_EWDG_INDEX,           /*!< EWDG       clock source  107u */ \
    IPC_INTM_INDEX,           /*!< INTM       clock source  113u */ \
    IPC_EMU_INDEX,            /*!< EMU        clock source  114u */ \
    IPC_STU_INDEX,            /*!< STU        clock source  119u */ \
    IPC_CIM_INDEX,            /*!< CIM        clock source  123u */ \
    IPC_SCU_INDEX,            /*!< SCU        clock source  124u */ \
    IPC_PCU_INDEX,            /*!< PCU        clock source  126u */ \
    IPC_RCU_INDEX,            /*!< RCU        clock source  127u */ \
    IPC_IPC_PERI_END_OF_CLOCK_INDEX,     /*!< IPC_PERI_END_OF_CLOCK clock source  128u */ \
    IPC_IPC_SIRC_INDEX,       /*!< IPC_SIRC   clock source  129u */ \
    IPC_IPC_FIRC_INDEX,       /*!< IPC_FIRC   clock source  130u */ \
    IPC_IPC_FXOSC_INDEX,      /*!< IPC_FXOSC  clock source  131u */ \
    IPC_IPC_SXOSC_INDEX,      /*!< IPC_SXOSC  clock source  132u */ \
    IPC_IPC_PLL_INDEX,        /*!< IPC_PLL    clock source  133u */ \
    IPC_IPC_END_OF_CLOCK_INDEX,     /*!< IPC_END_OF_CLOCK clock source  134u */ \
    IPC_CORE_INDEX,           /*!< CORE       clock source  135u */ \
    IPC_FAST_BUS_INDEX,       /*!< FAST_BUS   clock source  136u */ \
    IPC_SLOW_BUS_INDEX,       /*!< SLOW_BUS   clock source  137u */ \
}

/* DMA module features */

/* @brief Number of DMA channels. */
#define FEATURE_DMA_CHANNELS (16U)
/* @brief Number of DMA virtual channels. */
#define FEATURE_DMA_VIRTUAL_CHANNELS (FEATURE_DMA_CHANNELS * DMA_INSTANCE_COUNT)
/* @brief Number of DMA interrupt lines. */
#define FEATURE_DMA_CHANNELS_INTERRUPT_LINES (16U)
/* @brief Number of DMA virtual interrupt lines. */
#define FEATURE_DMA_VIRTUAL_CHANNELS_INTERRUPT_LINES ((uint32_t)FEATURE_DMA_CHANNELS_INTERRUPT_LINES * (uint32_t)DMA_INSTANCE_COUNT)
/* @brief Number of DMA error interrupt lines. */
#define FEATURE_DMA_ERROR_INTERRUPT_LINES (1U)
/* @brief Number of DMA virtual error interrupt lines. */
#define FEATURE_DMA_VIRTUAL_ERROR_INTERRUPT_LINES ((uint32_t)FEATURE_DMA_ERROR_INTERRUPT_LINES * (uint32_t)DMA_INSTANCE_COUNT)
/* @brief DMA module has error interrupt. */
#define FEATURE_DMA_HAS_ERROR_IRQ
/* @brief DMA module separate interrupt lines for each channel */
#define FEATURE_DMA_SEPARATE_IRQ_LINES_PER_CHN
/* @brief Clock name for DMA */
#define FEATURE_DMA_CLOCK_NAMES {DMA_CLK}
/* @brief DMA channel width based on number of CTSs: 2^N, N=4,5,... */
#define FEATURE_DMA_CH_WIDTH (4U)
/* @brief DMA channel to instance */
#define FEATURE_DMA_VCH_TO_INSTANCE(x) 	((x) >> (uint32_t)FEATURE_DMA_CH_WIDTH)
/* @brief DMA virtual channel to channel */
#define FEATURE_DMA_VCH_TO_CH(x)        ((x) & ((uint32_t)FEATURE_DMA_CHANNELS - 1U))
/* @brief DMA supports bus bandwidth control. */
#define FEATURE_DMA_ENGINE_STALL

/* DMAMUX module features */

/* @brief DMAMUX peripheral is available in silicon. */
#define FEATURE_DMAMUX_AVAILABLE
/* @brief Number of DMA channels. */
#define FEATURE_DMAMUX_CHANNELS (16U)
/* @brief Conversion from request source to the actual DMAMUX channel */
#define FEATURE_DMAMUX_REQ_SRC_TO_CH(x) (x)
/* @brief Mapping between request source and DMAMUX instance */
#define FEATURE_DMAMUX_REQ_SRC_TO_INSTANCE(x) (0U)
/* @brief Conversion from DMA channel index to DMAMUX channel. */
#define FEATURE_DMAMUX_DMA_CH_TO_CH(x) (x)
/* @brief Conversion from DMAMUX channel DMAMUX register index. */
#define FEATURE_DMAMUX_CHN_REG_INDEX(x) (x)

/*!
 * @brief Structure for the DMA hardware request
 *
 * Defines the structure for the DMA hardware request collections. The user can configure the
 * hardware request into DMAMUX to trigger the DMA transfer accordingly. The index
 * of the hardware request varies according  to the to SoC.
 */
typedef enum {
    DMA_REQ_Disabled         =   0U,     /*!< Disabled         dma request    0u */ \
    DMA_REQ_LINFlexD0_RX     =   2U,     /*!< LINFlexD0_RX     dma request    2u */ \
    DMA_REQ_LINFlexD0_TX     =   3U,     /*!< LINFlexD0_TX     dma request    3u */ \
    DMA_REQ_LINFlexD1_RX     =   4U,     /*!< LINFlexD1_RX     dma request    4u */ \
    DMA_REQ_LINFlexD1_TX     =   5U,     /*!< LINFlexD1_TX     dma request    5u */ \
    DMA_REQ_LINFlexD2_RX     =   6U,     /*!< LINFlexD2_RX     dma request    6u */ \
    DMA_REQ_LINFlexD2_TX     =   7U,     /*!< LINFlexD2_TX     dma request    7u */ \
    DMA_REQ_I2C1_RX          =   8U,     /*!< I2C1_RX          dma request    8u */ \
    DMA_REQ_I2C1_TX          =   9U,     /*!< I2C1_TX          dma request    9u */ \
    DMA_REQ_LINFlexD3_RX     =  10U,     /*!< LINFlexD3_RX     dma request   10u */ \
    DMA_REQ_LINFlexD3_TX     =  11U,     /*!< LINFlexD3_TX     dma request   11u */ \
    DMA_REQ_LINFlexD4_RX     =  12U,     /*!< LINFlexD4_RX     dma request   12u */ \
    DMA_REQ_LINFlexD4_TX     =  13U,     /*!< LINFlexD4_TX     dma request   13u */ \
    DMA_REQ_SPI0_RX          =  14U,     /*!< SPI0_RX          dma request   14u */ \
    DMA_REQ_SPI0_TX          =  15U,     /*!< SPI0_TX          dma request   15u */ \
    DMA_REQ_SPI1_RX          =  16U,     /*!< SPI1_RX          dma request   16u */ \
    DMA_REQ_SPI1_TX          =  17U,     /*!< SPI1_TX          dma request   17u */ \
    DMA_REQ_SPI2_RX          =  18U,     /*!< SPI2_RX          dma request   18u */ \
    DMA_REQ_SPI2_TX          =  19U,     /*!< SPI2_TX          dma request   19u */ \
    DMA_REQ_eTMR1_CH0        =  20U,     /*!< eTMR1_CH0        dma request   20u */ \
    DMA_REQ_eTMR1_CH1        =  21U,     /*!< eTMR1_CH1        dma request   21u */ \
    DMA_REQ_eTMR1_CH2        =  22U,     /*!< eTMR1_CH2        dma request   22u */ \
    DMA_REQ_eTMR1_CH3        =  23U,     /*!< eTMR1_CH3        dma request   23u */ \
    DMA_REQ_eTMR1_CH4        =  24U,     /*!< eTMR1_CH4        dma request   24u */ \
    DMA_REQ_eTMR1_CH5        =  25U,     /*!< eTMR1_CH5        dma request   25u */ \
    DMA_REQ_eTMR1_CH6        =  26U,     /*!< eTMR1_CH6        dma request   26u */ \
    DMA_REQ_eTMR1_CH7        =  27U,     /*!< eTMR1_CH7        dma request   27u */ \
    DMA_REQ_eTMR2_CH0        =  28U,     /*!< eTMR2_CH0        dma request   28u */ \
    DMA_REQ_eTMR2_CH1        =  29U,     /*!< eTMR2_CH1        dma request   29u */ \
    DMA_REQ_eTMR2_CH2        =  30U,     /*!< eTMR2_CH2        dma request   30u */ \
    DMA_REQ_eTMR2_CH3        =  31U,     /*!< eTMR2_CH3        dma request   31u */ \
    DMA_REQ_eTMR2_CH4        =  32U,     /*!< eTMR2_CH4        dma request   32u */ \
    DMA_REQ_eTMR2_CH5        =  33U,     /*!< eTMR2_CH5        dma request   33u */ \
    DMA_REQ_eTMR2_CH6        =  34U,     /*!< eTMR2_CH6        dma request   34u */ \
    DMA_REQ_eTMR2_CH7        =  35U,     /*!< eTMR2_CH7        dma request   35u */ \
    DMA_REQ_eTMR0            =  36U,     /*!< eTMR0            dma request   36u */ \
    DMA_REQ_eTMR3            =  37U,     /*!< eTMR3            dma request   37u */ \
    DMA_REQ_eTMR4            =  38U,     /*!< eTMR4            dma request   38u */ \
    DMA_REQ_eTMR5            =  39U,     /*!< eTMR5            dma request   39u */ \
    DMA_REQ_ADC0             =  42U,     /*!< ADC0             dma request   42u */ \
    DMA_REQ_ADC1             =  43U,     /*!< ADC1             dma request   43u */ \
    DMA_REQ_I2C0_RX          =  44U,     /*!< I2C0_RX          dma request   44u */ \
    DMA_REQ_I2C0_TX          =  45U,     /*!< I2C0_TX          dma request   45u */ \
    DMA_REQ_GPIOA            =  49U,     /*!< GPIOA            dma request   49u */ \
    DMA_REQ_GPIOB            =  50U,     /*!< GPIOB            dma request   50u */ \
    DMA_REQ_GPIOC            =  51U,     /*!< GPIOC            dma request   51u */ \
    DMA_REQ_GPIOD            =  52U,     /*!< GPIOD            dma request   52u */ \
    DMA_REQ_GPIOE            =  53U,     /*!< GPIOE            dma request   53u */ \
    DMA_REQ_FLEXCAN0         =  54U,     /*!< FLEXCAN0         dma request   54u */ \
    DMA_REQ_FLEXCAN1         =  55U,     /*!< FLEXCAN1         dma request   55u */ \
    DMA_REQ_FLEXCAN2         =  56U,     /*!< FLEXCAN2         dma request   56u */ \
    DMA_REQ_FLEXCAN3         =  57U,     /*!< FLEXCAN3         dma request   57u */ \
    DMA_REQ_FLEXCAN4         =  58U,     /*!< FLEXCAN4         dma request   58u */ \
    DMA_REQ_FLEXCAN5         =  60U,     /*!< FLEXCAN5         dma request   60u */ \
    DMA_REQ_Always_On0       =  62U,     /*!< Always On        dma request   62u */ \
    DMA_REQ_Always_On1       =  63U,     /*!< Always On        dma request   63u */ \
    DMA_REQ_SPI3_RX          =  64U,     /*!< SPI3_RX          dma request   64u */ \
    DMA_REQ_SPI3_TX          =  65U,     /*!< SPI3_TX          dma request   65u */ \
    DMA_REQ_SPI4_RX          =  66U,     /*!< SPI4_RX          dma request   66u */ \
    DMA_REQ_SPI4_TX          =  67U,     /*!< SPI4_TX          dma request   67u */ \
    DMA_REQ_SPI5_RX          =  68U,     /*!< SPI5_RX          dma request   68u */ \
    DMA_REQ_SPI5_TX          =  69U,     /*!< SPI5_TX          dma request   69u */ \
    DMA_REQ_I2C2_RX          =  70U,     /*!< I2C2_RX          dma request   70u */ \
    DMA_REQ_I2C2_TX          =  71U,     /*!< I2C2_TX          dma request   71u */ \
    DMA_REQ_LINFlexD5_RX     =  72U,     /*!< LINFlexD5_RX     dma request   72u */ \
    DMA_REQ_LINFlexD5_TX     =  73U,     /*!< LINFlexD5_TX     dma request   73u */ \
    DMA_REQ_HCU_INGRESS      =  74U,     /*!< HCU_INGRESS      dma request   74u */ \
    DMA_REQ_HCU_EGRESS       =  75U,     /*!< HCU_EGRESS       dma request   75u */ \
} dma_request_source_t;

/* TMU module features */
/*!
 * @brief Enumeration for trigger source module of TMU
 *
 * Describes all possible inputs (trigger sources) of the TMU IP
 * This enumeration depends on the supported instances in device
 */
enum tmu_trigger_source_e
{
    TMU_TRIG_SOURCE_DISABLED                       = 0U,
    TMU_TRIG_SOURCE_VDD                            = 1U,
    TMU_TRIG_SOURCE_TMU_IN0                        = 2U,
    TMU_TRIG_SOURCE_TMU_IN1                        = 3U,
    TMU_TRIG_SOURCE_TMU_IN2                        = 4U,
    TMU_TRIG_SOURCE_TMU_IN3                        = 5U,
    TMU_TRIG_SOURCE_TMU_IN4                        = 6U,
    TMU_TRIG_SOURCE_TMU_IN5                        = 7U,
    TMU_TRIG_SOURCE_TMU_IN6                        = 8U,
    TMU_TRIG_SOURCE_TMU_IN7                        = 9U,
    TMU_TRIG_SOURCE_TMU_IN8                        = 10U,
    TMU_TRIG_SOURCE_TMU_IN9                        = 11U,
    TMU_TRIG_SOURCE_TMU_IN10                       = 12U,
    TMU_TRIG_SOURCE_TMU_IN11                       = 13U,
    TMU_TRIG_SOURCE_ACMP0_OUT                      = 14U,
    TMU_TRIG_SOURCE_pTMR_CH0                       = 17U,
    TMU_TRIG_SOURCE_pTMR_CH1                       = 18U,
    TMU_TRIG_SOURCE_pTMR_CH2                       = 19U,
    TMU_TRIG_SOURCE_pTMR_CH3                       = 20U,
    TMU_TRIG_SOURCE_lpTMR0                         = 21U,
    TMU_TRIG_SOURCE_eTMR0_INIT_TRIG                = 22U,
    TMU_TRIG_SOURCE_eTMR0_EXT_TRIG                 = 23U,
    TMU_TRIG_SOURCE_eTMR1_INIT_TRIG                = 24U,
    TMU_TRIG_SOURCE_eTMR1_EXT_TRIG                 = 25U,
    TMU_TRIG_SOURCE_eTMR2_INIT_TRIG                = 26U,
    TMU_TRIG_SOURCE_eTMR2_EXT_TRIG                 = 27U,
    TMU_TRIG_SOURCE_eTMR3_INIT_TRIG                = 28U,
    TMU_TRIG_SOURCE_eTMR3_EXT_TRIG                 = 29U,
    TMU_TRIG_SOURCE_ADC0_COCO                      = 30U,
    TMU_TRIG_SOURCE_ADC0_AWD                       = 31U,
    TMU_TRIG_SOURCE_ADC1_COCO                      = 32U,
    TMU_TRIG_SOURCE_ADC1_AWD                       = 33U,
    TMU_TRIG_SOURCE_PTU0_ADCH0_TRIG                = 34U,
    TMU_TRIG_SOURCE_PTU0_PULSE_OUT0                = 36U,
    TMU_TRIG_SOURCE_PTU1_ADCH0_TRIG                = 37U,
    TMU_TRIG_SOURCE_PTU1_PULSE_OUT1                = 39U,
    TMU_TRIG_SOURCE_RTC_ALARM                      = 43U,
    TMU_TRIG_SOURCE_RTC_SECOND                     = 44U,
    TMU_TRIG_SOURCE_I2C0_MASTER_TRIG               = 55U,
    TMU_TRIG_SOURCE_I2C0_SLAVE_TRIG                = 56U,
    TMU_TRIG_SOURCE_SPI0_FRAME                     = 59U,
    TMU_TRIG_SOURCE_SPI0_RX_DATA                   = 60U,
    TMU_TRIG_SOURCE_SPI1_FRAME                     = 61U,
    TMU_TRIG_SOURCE_SPI1_RX_DATA                   = 62U,
    TMU_TRIG_SOURCE_SIM_SW_TRIG                    = 63U,
    TMU_TRIG_SOURCE_I2C1_MASTER_TRIG               = 67U,
    TMU_TRIG_SOURCE_I2C1_SLAVE_TRIG                = 68U,
    TMU_TRIG_SOURCE_eTMR4_INIT_TRIG                = 69U,
    TMU_TRIG_SOURCE_eTMR4_EXT_TRIG                 = 70U,
    TMU_TRIG_SOURCE_eTMR5_INIT_TRIG                = 71U,
    TMU_TRIG_SOURCE_eTMR5_EXT_TRIG                 = 72U,
    TMU_TRIG_SOURCE_SPI2_FRAME                     = 77U,
    TMU_TRIG_SOURCE_SPI2_RX_DATA                   = 78U,
    TMU_TRIG_SOURCE_SPI3_FRAME                     = 79U,
    TMU_TRIG_SOURCE_SPI3_RX_DATA                   = 80U,
    TMU_TRIG_SOURCE_SPI4_FRAME                     = 81U,
    TMU_TRIG_SOURCE_SPI4_RX_DATA                   = 82U,
    TMU_TRIG_SOURCE_SPI5_FRAME                     = 83U,
    TMU_TRIG_SOURCE_SPI5_RX_DATA                   = 84U,
    TMU_TRIG_SOURCE_I2C2_MASTER_TRIG               = 85U,
    TMU_TRIG_SOURCE_I2C2_SLAVE_TRIG                = 86U,
};

/*!
 * @brief Enumeration for target module of TMU
 *
 * Describes all possible outputs (target modules) of the TMU IP
 * This enumeration depends on the supported instances in device
 */
enum tmu_target_module_e
{
    TMU_TARGET_MODULE_TMU_OUT0                       = 4U,
    TMU_TARGET_MODULE_TMU_OUT1                       = 5U,
    TMU_TARGET_MODULE_TMU_OUT2                       = 6U,
    TMU_TARGET_MODULE_TMU_OUT3                       = 7U,
    TMU_TARGET_MODULE_TMU_OUT4                       = 8U,
    TMU_TARGET_MODULE_TMU_OUT5                       = 9U,
    TMU_TARGET_MODULE_TMU_OUT6                       = 10U,
    TMU_TARGET_MODULE_TMU_OUT7                       = 11U,
    TMU_TARGET_MODULE_ADC0_EXT_TRIG0                 = 12U,
    TMU_TARGET_MODULE_ADC0_EXT_TRIG1                 = 13U,
    TMU_TARGET_MODULE_ADC0_EXT_TRIG2                 = 14U,
    TMU_TARGET_MODULE_ADC0_EXT_TRIG3                 = 15U,
    TMU_TARGET_MODULE_ADC1_EXT_TRIG0                 = 16U,
    TMU_TARGET_MODULE_ADC1_EXT_TRIG1                 = 17U,
    TMU_TARGET_MODULE_ADC1_EXT_TRIG2                 = 18U,
    TMU_TARGET_MODULE_ADC1_EXT_TRIG3                 = 19U,
    TMU_TARGET_MODULE_ACMP0_SAMPLE_INPUT             = 28U,
    TMU_TARGET_MODULE_eTMR0_HWTRIG0                  = 40U,
    TMU_TARGET_MODULE_eTMR0_FAULT0                   = 41U,
    TMU_TARGET_MODULE_eTMR0_FAULT1                   = 42U,
    TMU_TARGET_MODULE_eTMR0_FAULT2                   = 43U,
    TMU_TARGET_MODULE_eTMR1_HWTRIG0                  = 44U,
    TMU_TARGET_MODULE_eTMR1_FAULT0                   = 45U,
    TMU_TARGET_MODULE_eTMR1_FAULT1                   = 46U,
    TMU_TARGET_MODULE_eTMR1_FAULT2                   = 47U,
    TMU_TARGET_MODULE_eTMR2_HWTRIG0                  = 48U,
    TMU_TARGET_MODULE_eTMR2_FAULT0                   = 49U,
    TMU_TARGET_MODULE_eTMR2_FAULT1                   = 50U,
    TMU_TARGET_MODULE_eTMR2_FAULT2                   = 51U,
    TMU_TARGET_MODULE_eTMR3_HWTRIG0                  = 52U,
    TMU_TARGET_MODULE_eTMR3_FAULT0                   = 53U,
    TMU_TARGET_MODULE_eTMR3_FAULT1                   = 54U,
    TMU_TARGET_MODULE_eTMR3_FAULT2                   = 55U,
    TMU_TARGET_MODULE_PTU0_TRIG_IN0                  = 56U,
    TMU_TARGET_MODULE_PTU1_TRIG_IN0                  = 60U,
    TMU_TARGET_MODULE_LINFlexD0_TRIG                 = 76U,
    TMU_TARGET_MODULE_LINFlexD1_TRIG                 = 77U,
    TMU_TARGET_MODULE_LINFlexD2_TRIG                 = 78U,
    TMU_TARGET_MODULE_LINFlexD3_TRIG                 = 79U,
    TMU_TARGET_MODULE_LINFlexD4_TRIG                 = 80U,
    TMU_TARGET_MODULE_LINFlexD5_TRIG                 = 81U,
    TMU_TARGET_MODULE_I2C0_TRIG                      = 84U,
    TMU_TARGET_MODULE_SPI0_TRIG                      = 92U,
    TMU_TARGET_MODULE_SPI1_TRIG                      = 96U,
    TMU_TARGET_MODULE_SPI2_TRIG                      = 97U,
    TMU_TARGET_MODULE_SPI3_TRIG                      = 98U,
    TMU_TARGET_MODULE_SPI4_TRIG                      = 99U,
    TMU_TARGET_MODULE_lpTMR0_ALT0                    = 100U,
    TMU_TARGET_MODULE_SPI5_TRIG                      = 104U,
    TMU_TARGET_MODULE_I2C1_TRIG                      = 108U,
    TMU_TARGET_MODULE_I2C2_TRIG                      = 109U,
    TMU_TARGET_MODULE_eTMR4_HWTRIG0                  = 112U,
    TMU_TARGET_MODULE_eTMR5_HWTRIG0                  = 116U,
};

/* @brief Constant array storing the value of all TMU output(target module) identifiers */
#define FEATURE_TMU_TARGET_MODULE                     \
    {                                                 \
    TMU_TARGET_MODULE_TMU_OUT0,                       \
    TMU_TARGET_MODULE_TMU_OUT1,                       \
    TMU_TARGET_MODULE_TMU_OUT2,                       \
    TMU_TARGET_MODULE_TMU_OUT3,                       \
    TMU_TARGET_MODULE_TMU_OUT4,                       \
    TMU_TARGET_MODULE_TMU_OUT5,                       \
    TMU_TARGET_MODULE_TMU_OUT6,                       \
    TMU_TARGET_MODULE_TMU_OUT7,                       \
    TMU_TARGET_MODULE_ADC0_EXT_TRIG0,                 \
    TMU_TARGET_MODULE_ADC0_EXT_TRIG1,                 \
    TMU_TARGET_MODULE_ADC0_EXT_TRIG2,                 \
    TMU_TARGET_MODULE_ADC0_EXT_TRIG3,                 \
    TMU_TARGET_MODULE_ADC1_EXT_TRIG0,                 \
    TMU_TARGET_MODULE_ADC1_EXT_TRIG1,                 \
    TMU_TARGET_MODULE_ADC1_EXT_TRIG2,                 \
    TMU_TARGET_MODULE_ADC1_EXT_TRIG3,                 \
    TMU_TARGET_MODULE_ACMP0_SAMPLE_INPUT,             \
    TMU_TARGET_MODULE_eTMR0_HWTRIG0,                  \
    TMU_TARGET_MODULE_eTMR0_FAULT0,                   \
    TMU_TARGET_MODULE_eTMR0_FAULT1,                   \
    TMU_TARGET_MODULE_eTMR0_FAULT2,                   \
    TMU_TARGET_MODULE_eTMR1_HWTRIG0,                  \
    TMU_TARGET_MODULE_eTMR1_FAULT0,                   \
    TMU_TARGET_MODULE_eTMR1_FAULT1,                   \
    TMU_TARGET_MODULE_eTMR1_FAULT2,                   \
    TMU_TARGET_MODULE_eTMR2_HWTRIG0,                  \
    TMU_TARGET_MODULE_eTMR2_FAULT0,                   \
    TMU_TARGET_MODULE_eTMR2_FAULT1,                   \
    TMU_TARGET_MODULE_eTMR2_FAULT2,                   \
    TMU_TARGET_MODULE_eTMR3_HWTRIG0,                  \
    TMU_TARGET_MODULE_eTMR3_FAULT0,                   \
    TMU_TARGET_MODULE_eTMR3_FAULT1,                   \
    TMU_TARGET_MODULE_eTMR3_FAULT2,                   \
    TMU_TARGET_MODULE_PTU0_TRIG_IN0,                  \
    TMU_TARGET_MODULE_PTU1_TRIG_IN0,                  \
    TMU_TARGET_MODULE_LINFlexD0_TRIG,                 \
    TMU_TARGET_MODULE_LINFlexD1_TRIG,                 \
    TMU_TARGET_MODULE_LINFlexD2_TRIG,                 \
    TMU_TARGET_MODULE_LINFlexD3_TRIG,                 \
    TMU_TARGET_MODULE_LINFlexD4_TRIG,                 \
    TMU_TARGET_MODULE_LINFlexD5_TRIG,                 \
    TMU_TARGET_MODULE_I2C0_TRIG,                      \
    TMU_TARGET_MODULE_SPI0_TRIG,                      \
    TMU_TARGET_MODULE_SPI1_TRIG,                      \
    TMU_TARGET_MODULE_SPI2_TRIG,                      \
    TMU_TARGET_MODULE_SPI3_TRIG,                      \
    TMU_TARGET_MODULE_SPI4_TRIG,                      \
    TMU_TARGET_MODULE_lpTMR0_ALT0,                    \
    TMU_TARGET_MODULE_SPI5_TRIG,                      \
    TMU_TARGET_MODULE_I2C1_TRIG,                      \
    TMU_TARGET_MODULE_I2C2_TRIG,                      \
    TMU_TARGET_MODULE_eTMR4_HWTRIG0,                  \
    TMU_TARGET_MODULE_eTMR5_HWTRIG0,                  \
    }

/* SPI module features */
/* @brief Initial value for state structure */
#define FEATURE_SPI_STATE_STRUCTURES_NULL {NULL, NULL, NULL, NULL, NULL, NULL}
/* @brief Has transmitter/receiver DMA enable bits. */
#define FEATURE_SPI_HAS_DMA_ENABLE (1)
/* @brief Clock indexes for SPI clock */
#define FEATURE_SPI_CLOCKS_NAMES {SPI0_CLK, SPI1_CLK, SPI2_CLK, SPI3_CLK, SPI4_CLK, SPI5_CLK};

/* ADC module features */

/*! @brief ADC feature flag for extended number of SC1 and R registers,
 * generically named 'alias registers' */
#define FEATURE_ADC_HAS_EXTRA_NUM_REGS                    (0)

#define NUMBER_OF_ALT_CLOCKS  ADC_CLK_ALT_1
/*! @brief ADC feature flag for defining number of external ADC channels.
 * If each ADC instance has different number of external channels, then
 * this define is set with the maximum value. */
#define FEATURE_ADC_MAX_NUM_EXT_CHANS                     (24)
#define ADC_CLOCKS                                        {ADC0_CLK, ADC1_CLK}

/*! @brief ADC default clock divider from RM */
#define ADC_DEFAULT_CLOCK_DIVIDER                         (0x02U)
/*! @brief ADC default Sample Time from RM */
#define ADC_DEFAULT_SAMPLE_TIME                           (0x0CU)
/*! @brief ADC default Start Time from RM */
#define ADC_DEFAULT_START_TIME                            (0x20U)
/* @brief Max of adc clock frequency */
#define ADC_CLOCK_FREQ_MAX_RUNTIME                        (32000000u)
/* @brief Min of adc clock frequency */
#define ADC_CLOCK_FREQ_MIN_RUNTIME                        (2000000u)
/* @brief Errata of ADC E0002 */
#define ADC_ERRATA_E0002

/* CAN module features */

/* @brief Frames available in Rx FIFO flag shift */
#define FEATURE_CAN_RXFIFO_FRAME_AVAILABLE  (5U)
/* @brief Rx FIFO warning flag shift */
#define FEATURE_CAN_RXFIFO_WARNING          (6U)
/* @brief Rx FIFO overflow flag shift */
#define FEATURE_CAN_RXFIFO_OVERFLOW         (7U)
/* @brief The list contains definitions of the FD feature support on all instances */
#define FEATURE_CAN_INSTANCES_HAS_FD        {true, true, true, true, true, true}
/* @brief Has Flexible Data Rate for CAN0 */
#define FEATURE_CAN0_HAS_FD                 (1)
/* @brief Has Flexible Data Rate for CAN1 */
#define FEATURE_CAN1_HAS_FD                 (1)
/* @brief Has Flexible Data Rate for CAN2 */
#define FEATURE_CAN2_HAS_FD                 (1)
/* @brief Has Flexible Data Rate for CAN3 */
#define FEATURE_CAN3_HAS_FD                 (1)
/* @brief Has Flexible Data Rate for CAN4 */
#define FEATURE_CAN4_HAS_FD                 (1)
/* @brief Has Flexible Data Rate for CAN5 */
#define FEATURE_CAN5_HAS_FD                 (1)

#define FEATURE_CAN_HAS_RAM_ECC             (1)

/* @brief Maximum number of Message Buffers supported for payload size 8 for CAN0 */
#define FEATURE_CAN0_MAX_MB_NUM             (64U)
/* @brief Maximum number of Message Buffers supported for payload size 8 for CAN1 */
#define FEATURE_CAN1_MAX_MB_NUM             (64U)
/* @brief Maximum number of Message Buffers supported for payload size 8 for CAN2 */
#define FEATURE_CAN2_MAX_MB_NUM             (64U)
/* @brief Maximum number of Message Buffers supported for payload size 8 for CAN3 */
#define FEATURE_CAN3_MAX_MB_NUM             (32U)
/* @brief Maximum number of Message Buffers supported for payload size 8 for CAN4 */
#define FEATURE_CAN4_MAX_MB_NUM             (32U)
/* @brief Maximum number of Message Buffers supported for payload size 8 for CAN5 */
#define FEATURE_CAN5_MAX_MB_NUM             (32U)

/* @brief Has PE clock source select (bit field CAN_CTRL1[CLKSRC]). */
#define FEATURE_CAN_HAS_PE_CLKSRC_SELECT    (1)
/* @brief Has DMA enable (bit field MCR[DMA]). */
#define FEATURE_CAN_HAS_DMA_ENABLE          (1)

/* @brief Maximum number of Message Buffers supported for payload size 8 for any of the CAN instances */
#define FEATURE_CAN_MAX_MB_NUM              (64U)
/* @brief Maximum number of Message Buffers supported for payload size 8 for any of the CAN instances */
#define FEATURE_CAN_MAX_MB_NUM_ARRAY        { FEATURE_CAN0_MAX_MB_NUM, \
                                              FEATURE_CAN1_MAX_MB_NUM, \
                                              FEATURE_CAN2_MAX_MB_NUM, \
                                              FEATURE_CAN3_MAX_MB_NUM, \
                                              FEATURE_CAN4_MAX_MB_NUM, \
                                              FEATURE_CAN5_MAX_MB_NUM }
/* @brief Has Pretending Networking mode */
#define FEATURE_CAN_HAS_PRETENDED_NETWORKING    (0)
/* @brief Has Stuff Bit Count Enable Bit */
#define FEATURE_CAN_HAS_STFCNTEN_ENABLE         (0)
/* @brief Has ISO CAN FD Enable Bit */
#define FEATURE_CAN_HAS_ISOCANFDEN_ENABLE       (1)
/* @brief Has Message Buffer Data Size Region 1 */
#define FEATURE_CAN_HAS_MBDSR1                  (1)
/* @brief Has Message Buffer Data Size Region 2 */
#define FEATURE_CAN_HAS_MBDSR2                  (0)
/* @brief DMA hardware requests for all FlexCAN instances */
#define FEATURE_CAN_DMA_REQUESTS              { DMA_REQ_FLEXCAN0, \
                                                DMA_REQ_FLEXCAN1, \
                                                DMA_REQ_FLEXCAN2, \
                                                DMA_REQ_FLEXCAN3, \
                                                DMA_REQ_FLEXCAN4, \
                                                DMA_REQ_FLEXCAN5 }

/* @brief Maximum number of Message Buffers IRQs */
#define FEATURE_CAN_MB_IRQS_MAX_COUNT       (4U)
/* @brief Message Buffers IRQs */
#define FEATURE_CAN_MB_IRQS                 { CAN_ORed_0_15_MB_IRQS, CAN_ORed_16_31_MB_IRQS,  CAN_ORed_32_47_MB_IRQS,  CAN_ORed_48_63_MB_IRQS }
/* @brief Has Wake Up Irq channels (CAN_Wake_Up_IRQS_CH_COUNT > 0u) */
#define FEATURE_CAN_HAS_WAKE_UP_IRQ         (1)
/* @brief Has Self Wake Up mode */
#define FEATURE_CAN_HAS_SELF_WAKE_UP        (1)
/* @brief Has Flexible Data Rate */
#define FEATURE_CAN_HAS_FD                  (1)
/* @brief Clock name for the PE oscillator clock source */
#define FEATURE_CAN_PE_OSC_CLK_NAME         IPC_FXOSC_CLK
/* @bried FlexCAN has Detection And Correction of Memory Errors */
#define FEATURE_CAN_HAS_MEM_ERR_DET			(1)


#define FEATURE_CAN_RAM_COUNT               (256)
#define FEATURE_CAN_RXIMR_COUNT             (64)
/* @brief Has enhanced rx fifo feature for CAN0 */
#define FEATURE_CAN0_HAS_ENHANCE_RX_FIFO (1)
/* @brief Has enhanced rx fifo feature for CAN1 */
#define FEATURE_CAN1_HAS_ENHANCE_RX_FIFO (1)
/* @brief Has enhanced rx fifo feature for CAN2 */
#define FEATURE_CAN2_HAS_ENHANCE_RX_FIFO (1)
/* @brief Has enhanced rx fifo feature for CAN3 */
#define FEATURE_CAN3_HAS_ENHANCE_RX_FIFO (0)
/* @brief Has enhanced rx fifo feature for CAN4 */
#define FEATURE_CAN4_HAS_ENHANCE_RX_FIFO (0)
/* @brief Has enhanced rx fifo feature for CAN5 */
#define FEATURE_CAN5_HAS_ENHANCE_RX_FIFO (0)

/* @brief Has enhanced rx fifo feature for all CAN */
#define FEATURE_CAN_HAS_ENHANCE_RX_FIFO  (1)

/* @brief The list contains definitions of the rx-fifo feature support on all instances */
#define FEATURE_CAN_INSTANCES_HAS_ENHANCE_RX_FIFO        { FEATURE_CAN0_HAS_ENHANCE_RX_FIFO, \
                                                           FEATURE_CAN1_HAS_ENHANCE_RX_FIFO, \
                                                           FEATURE_CAN2_HAS_ENHANCE_RX_FIFO, \
                                                           FEATURE_CAN3_HAS_ENHANCE_RX_FIFO, \
                                                           FEATURE_CAN4_HAS_ENHANCE_RX_FIFO, \
                                                           FEATURE_CAN5_HAS_ENHANCE_RX_FIFO }

#define FEATURE_CAN_ENHANCE_RX_FIFO_COUNT (20U)
/* @brief Enhance fifo message buffer count */
#define FEATURE_CAN_ERFFELn_COUNT (128U)

/* pTMR module features */

/* @brief Clock names for pTMR */
#define pTMR_CLOCK_NAMES {SLOW_BUS_CLK}

/* @brief pTMR instance list */
typedef enum {
    pTMR0_INST = 0,
} ptmr_instance_t;

/* @brief pTMR channels list for each instance */
typedef enum {
    pTMR0_CH0 = 0U,
    pTMR0_CH1 = 1U,
    pTMR0_CH2 = 2U,
    pTMR0_CH3 = 3U,
} ptmr_channel_t;

/* TMR module features */
#define TMR_CLOCK_NAMES {SLOW_BUS_CLK}

/* lpTMR module features */

/* @brief lpTMR pulse counter input options */
#define FEATURE_LPTMR_HAS_INPUT_ALT1_SELECTION  (1U)
/* @brief Clock names for lpTMR. */
#define lpTMR_CLOCK_NAMES {lpTMR0_CLK }
/* @brief alt1 input for lpTMR. */
#define FEATURE_lpTMR_HAS_INPUT_ALT1_SELECTION  (1U)
/* @brief lpTMR ip clock selection */
#define FEATURE_lpTMR_HAS_CLOCK_SELECTION       (1U)
/* @brief lpTMR clock source support ipc */
#define FEATURE_lpTMR_CLKSRC_SUPPORT_IPC        (1U)
/* @brief lpTMR clock source support sxosc */
#define FEATURE_lpTMR_CLKSRC_SUPPORT_SXOSC      (1U)
/* @brief lpTMR clock source support sirc */
#define FEATURE_lpTMR_CLKSRC_SUPPORT_SIRC      (1U)

/* RTC module features */

/*!
 * @brief RTC clock select
 * Implements : rtc_clk_source_t_Class
 */
typedef enum
{
    RTC_CLK_SRC_OSC_32KHZ = 0x00U,  /*!< RTC Prescaler increments using 32 KHz crystal */
    RTC_CLK_SRC_RTC_PIN = 0x01U,   /*!< RTC Prescaler increments from RTC pin*/
} rtc_clk_source_t;
/* @brief RTC has separate second irq */
#define FEATURE_RTC_HAS_SEPARATE_SECOND_IRQ     (1U)
/* @brief RTC has 32.768 OSC clock support */
#define FEATURE_RTC_HAS_OSC                     (1U)

/* LINFlexD module features */

/* @brief LINFlexD has dma support */
#define LINFlexD_CLOCK_NAMES                     {FAST_BUS_CLK, \
                                                  FAST_BUS_CLK, \
                                                  FAST_BUS_CLK, \
                                                  FAST_BUS_CLK, \
                                                  FAST_BUS_CLK, \
                                                  FAST_BUS_CLK }
#define FEATURE_LINFlexD_ORED_INT_LINES          (1)
#define FEATURE_LINFlexD_HAS_DMA_ENABLED         (1)
/* @brief Address of the least significant byte in a 32-bit register (depends on endianess) */
#define FEATURE_LINFlexD_LSB_ADDR(reg)  ((uint32_t)(&(reg)) + 3U)
/* @brief Address of the least significant word in a 32-bit register (depends on endianess) */
#define FEATURE_LINFlexD_LSW_ADDR(reg)  ((uint32_t)(&(reg)) + 2U)
/* @brief LINFlexD "instance-implemented filters" mapping */
#define FEATURE_LINFlexD_INST_HAS_IFCR {true, true}
#define FEATURE_LINFlexD_TIMEOUT_LOOPS           (0xFFU)
/* @brief LINFlexD no receive edge detection support */
#define FEATURE_LINFlexD_HAS_RED_IRQ             (0)
/* @brief LINFlexD no different memory map */
#define FEATURE_LINFlexD_HAS_DIFFERENT_MEM_MAP   (0)
/* @brief LINFlexD no RX TX error INT lines */
#define FEATURE_LINFlexD_RX_TX_ERR_INT_LINES     (0)


/* HCU module features */
#define FEATURE_HCU_AES_ENGINE                           (1U)
#define FEATURE_HCU_SM4_ENGINE                           (1U)
#define FEATURE_HCU_SHA_ENGINE                           (1U)
#define FEATURE_HCU_ONE_LOOP_DATA_SIZE                   (4U)
#define FEATURE_HCU_ONE_LOOP_INPUT_WATERMARK             (3U)
#define FEATURE_HCU_HAS_FIXED_DMA                        (0U)
#define FEATURE_HCU_HAS_SHA_AUTHORIZE                    (0U)

#define FEATURE_HCU_FIFO_SIZE_IN_WORDS                   (8U)

/* @brief EFM AES area base address */
#define FEATURE_EFM_AES_KEY_BASE_ADDR                    (0x10000000U)
/* @brief EFM AES key size (bytes)*/
#define FEATURE_EFM_AES_KEY_SIZE                         (32U)
#define FEATURE_EFM_AES_KEY_COUNT_MAX                    (32U)
#define FEATURE_HCU_GET_KEY_ADDR(key_id)                 (FEATURE_EFM_AES_KEY_BASE_ADDR + (key_id * FEATURE_EFM_AES_KEY_SIZE))

/* WKU module features */
#define FEATURE_WKU_MAX_CHANNEL_COUNT                    (32U)
/* WKU module support pin isolation feature */
#define FEATURE_WKU_SUPPORT_PIN_ISOLATION                (0U)
/* WKU module support CLOCK SELECTION feature */
#define FEATURE_WKU_SUPPORT_FILTER_CLOCK_SEL             (1U)



/* OSIF module features */

#define FEATURE_OSIF_USE_SYSTICK                         (0)
#define FEATURE_OSIF_FREERTOS_ISR_CONTEXT_METHOD         (1) /* Cortex M device */


/* PTU module features */

/* @brief PTU has instance back to back mode between PTU0 CH0 and PTU1 CH0 pre-triggers */
#define FEATURE_PTU_HAS_INSTANCE_BACKTOBACK     (0)

/* @brief PTU has inter-channel back to back mode between PTUx CH0 and PTUx CH1 pre-triggers */
#define FEATURE_PTU_HAS_INTERCHANNEL_BACKTOBACK (0)


#if defined(USER_DEVICE_FEATURES_OVERRIDE)
#include "user_device_features_override.h"
#endif


#endif /* YTM32B1MD0_FEATURES_H */

/*******************************************************************************
 * EOF
 ******************************************************************************/
