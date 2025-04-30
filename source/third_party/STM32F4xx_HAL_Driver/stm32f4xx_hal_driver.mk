ifneq ($(STM32F4XX_HAL_DRIVER_MK_INC),Y)
    STM32F4XX_HAL_DRIVER_MK_INC=Y

    STM32F4X_HAL_DRIVER_DIR = $(THIRD_PARTY_DIR)/STM32F4xx_HAL_Driver
    STM32F4X_HAL_DRIVER_DIR := $(subst /cygdrive/c/,C:/, $(STM32F4X_HAL_DRIVER_DIR))
    #$(error STM32F4X_HAL_DRIVER_DIR=$(STM32F4X_HAL_DRIVER_DIR))
    
     
    STM32F4XX_HAL_DRIVER=Y
    OPT += -DHAS_STM32F4XX_HAL_DRIVER
    OPT += -DUSE_HAL_DRIVER
    OPT += -DHAL_CORTEX_MODULE_ENABLED
    OPT += -DHAL_PWR_MODULE_ENABLED
    OPT += -DHAL_MODULE_ENABLED
    OPT += -DHAL_NOR_MODULE_ENABLED

    ifeq ($(EXTI),Y)
        OPT += -DHAL_EXTI_MODULE_ENABLED
    endif

    INCDIR += -I$(STM32F4X_HAL_DRIVER_DIR)
    
    RCC=Y
    SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal.c
    SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_cortex.c

    ifeq ($(ADC),Y)
        OPT += -DHAL_ADC_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_adc.c
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_adc_ex.c
    endif
    
    ifeq ($(RCC),Y)
        OPT += -DHAL_RCC_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_rcc.c
        ifeq ($(HAL_RCC_EX),Y)
            #@echo $(error HAL_RCC_EX=$(HAL_RCC_EX))
            SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_rcc_ex.c
        endif
    endif

    ifeq ($(IWDG),Y)
        OPT += -DHAL_IWDG_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_iwdg.c
    endif

    ifeq ($(CRYP),Y)
        #@echo $(error CRYP=$(CRYP))
        OPT += -DHAL_CRYP_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_cryp.c
    endif

    
    ifeq ($(GPIO),Y)
        #@echo $(error GPIO=$(GPIO))
        OPT += -DHAL_GPIO_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_gpio.c
    endif

    ifeq ($(HAL_DMA),Y)
        OPT += -DHAL_DMA_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_dma.c
    endif

    ifeq ($(I2S),Y)
        OPT += -DHAL_I2S_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_i2s.c
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_i2s_ex.c
    endif

    ifeq ($(I2C),Y)
        OPT += -DHAL_I2C_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_i2c.c
    endif

    ifeq ($(SPI),Y)
        OPT += -DHAL_SPI_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_spi.c
    endif

    ifeq ($(SDIO),Y)
        OPT += -DHAL_SD_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_sd.c
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_ll_sdmmc.c
    endif

    HAL_FLASH=Y
    ifeq ($(HAL_FLASH),Y)
        #@echo $(error FLASH=$(FLASH))
        OPT += -DHAL_FLASH_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_flash.c
         
        ifeq ($(HAL_FLASH_EX),Y)
            SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_flash_ex.c
        endif
    endif

    ifeq ($(RTC),Y)
        OPT += -DHAL_RTC_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_rtc.c
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_rcc_ex.c
    endif

    ifeq ($(UART),Y)
        HAL_DMA=Y
        OPT += -DHAL_UART_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_uart.c
    endif

    ifeq ($(HAL_USB),Y)
        #Peripheral Controller Driver
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_ll_usb.c
        ifeq ($(USB_DEVICE),Y)
            OPT += -DHAL_PCD_MODULE_ENABLED
            SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_pcd.c
            SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_pcd_ex.c
        endif

        ifeq ($(USB_HOST),Y)
            OPT += -DHAL_HCD_MODULE_ENABLED
            SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_hcd.c
        endif
    endif

    ifeq ($(TIMER),Y)
        ifeq ($(HAL_TIM_PWM),Y)
            OPT += -DHAS_HAL_TIM_PWM
            OPT += -DHAS_HAL_TIM_OC
        endif
        OPT += -DHAL_TIM_MODULE_ENABLED
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_tim.c
        SOURCES_THIRD_PARTY_C += $(STM32F4X_HAL_DRIVER_DIR)/stm32f4xx_hal_tim_ex.c
    endif
endif
