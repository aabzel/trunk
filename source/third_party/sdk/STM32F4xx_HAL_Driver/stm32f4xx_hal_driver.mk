ifneq ($(STM32F4XX_HAL_DRIVER_MK_INC),Y)
    STM32F4XX_HAL_DRIVER_MK_INC=Y

    STM32F4X_HAL_DRIVER_DIR = $(SDK_DIR)/STM32F4xx_HAL_Driver
    STM32F4X_HAL_DRIVER_DIR := $(subst /cygdrive/c/,C:/, $(STM32F4X_HAL_DRIVER_DIR))
    # $(error STM32F4X_HAL_DRIVER_DIR=$(STM32F4X_HAL_DRIVER_DIR))
    
     
    STM32F4XX_HAL_DRIVER=Y
    MCAL_OPT += -DHAS_STM32F4XX_HAL_DRIVER
    MCAL_OPT += -DUSE_HAL_DRIVER
    MCAL_OPT += -DHAL_CORTEX_MODULE_ENABLED
    MCAL_OPT += -DHAL_PWR_MODULE_ENABLED
    MCAL_OPT += -DHAL_MODULE_ENABLED
    MCAL_OPT += -DHAL_NOR_MODULE_ENABLED

    ifeq ($(EXTI),Y)
        MCAL_OPT += -DHAL_EXTI_MODULE_ENABLED
    endif

    INCDIR += -I$(STM32F4X_HAL_DRIVER_DIR)
    
    RCC=Y
    SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal.c
    SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_cortex.c

    ifeq ($(ADC),Y)
        MCAL_OPT += -DHAL_ADC_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_adc.c
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_adc_ex.c
    endif

    ifeq ($(CAN),Y)
        MCAL_OPT += -DHAL_CAN_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/Src/stm32f4xx_hal_can.c
    endif
    
    ifeq ($(RCC),Y)
        MCAL_OPT += -DHAL_RCC_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_rcc.c
        ifeq ($(HAL_RCC_EX),Y)
            # $(error HAL_RCC_EX=$(HAL_RCC_EX))
            SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_rcc_ex.c
        endif
    endif

    ifeq ($(IWDG),Y)
        MCAL_OPT += -DHAL_IWDG_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_iwdg.c
    endif

    ifeq ($(CRYP),Y)
        # $(error CRYP=$(CRYP))
        MCAL_OPT += -DHAL_CRYP_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_cryp.c
    endif

    ifeq ($(GPIO),Y)
        # $(error GPIO=$(GPIO))
        MCAL_OPT += -DHAL_GPIO_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_gpio.c
    endif

    ifeq ($(HAL_DMA),Y)
        MCAL_OPT += -DHAL_DMA_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_dma.c
    endif

    ifeq ($(I2S),Y)
        MCAL_OPT += -DHAL_I2S_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_i2s.c
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_i2s_ex.c
    endif

    ifeq ($(I2C),Y)
        MCAL_OPT += -DHAL_I2C_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_i2c.c
    endif

    ifeq ($(SPI),Y)
        MCAL_OPT += -DHAL_SPI_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_spi.c
    endif

    ifeq ($(SDIO),Y)
        MCAL_OPT += -DHAL_SD_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_sd.c
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_ll_sdmmc.c
    endif

    HAL_FLASH=Y
    ifeq ($(HAL_FLASH),Y)
        # $(error FLASH=$(FLASH))
        MCAL_OPT += -DHAL_FLASH_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_flash.c
         
        ifeq ($(HAL_FLASH_EX),Y)
            SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_flash_ex.c
        endif
    endif

    ifeq ($(RTC),Y)
        MCAL_OPT += -DHAL_RTC_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_rtc.c
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_rcc_ex.c
    endif

    ifeq ($(UART),Y)
        HAL_DMA=Y
        MCAL_OPT += -DHAL_UART_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_uart.c
    endif

    ifeq ($(HAL_USB),Y)
        # Peripheral Controller Driver
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_ll_usb.c
        ifeq ($(USB_DEVICE),Y)
            MCAL_OPT += -DHAL_PCD_MODULE_ENABLED
            SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_pcd.c
            SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_pcd_ex.c
        endif

        ifeq ($(USB_HOST),Y)
            MCAL_OPT += -DHAL_HCD_MODULE_ENABLED
            SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_hcd.c
        endif
    endif

    ifeq ($(TIMER),Y)
        ifeq ($(HAL_TIM_PWM),Y)
            MCAL_OPT += -DHAS_HAL_TIM_PWM
            MCAL_OPT += -DHAS_HAL_TIM_OC
        endif
        MCAL_OPT += -DHAL_TIM_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_tim.c
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_tim_ex.c
    endif
endif
