$(info MCAL_MK_INC=$(MCAL_MK_INC))
ifneq ($(MCAL_MK_INC),Y)
    MCAL_MK_INC=Y

    $(info Build MCAL)

    MCAL_DIR = $(WORKSPACE_LOC)/mcal
    MCAL_DIR:=$(realpath $(MCAL_DIR))
    MCAL_DIR:=$(subst /cygdrive/c/,C:/,$(MCAL_DIR))
    
    # $(error MCAL_DIR=$(MCAL_DIR))
    MCAL_OPT += -DHAS_MCAL
    INCDIR += -I$(MCAL_DIR)

    ifeq ($(MCAL),Y)
        # $(error MCAL=$(MCAL))
        include $(MCAL_DIR)/mcal_common/mcal_common.mk
    endif

    #---------------------------------------------------------------------------

    ifeq ($(EHAL_MCAL),Y)
        # $(error EHAL_MCAL=$(EHAL_MCAL))
        include $(MCAL_DIR)/ehal_mcal/ehal_mcal.mk
    endif

    ifeq ($(MCAL_AT32),Y)
        # $(error MCAL_AT32=$(MCAL_AT32))
        include $(MCAL_DIR)/mcal_at32f4/mcal_at32f4.mk
    endif

    ifeq ($(MCAL_X86),Y)
        # $(error MCAL_X86=$(MCAL_X86))
        include $(MCAL_DIR)/mcal_x86/mcal_x86.mk
    endif
    
    ifeq ($(MCAL_CC26X2),Y)   
        include $(MCAL_DIR)/mcal_cc26x2/mcal_cc26x2.mk
    endif

    ifeq ($(MCAL_ESP32),Y) 
        include $(MCAL_DIR)/mcal_esp32/mcal_esp32.mk
    endif

    ifeq ($(MCAL_MIK32),Y)
        # $(error MCAL_MIK32=$(MCAL_MIK32))
        include $(MCAL_DIR)/mcal_mik32/mcal_mik32.mk
    endif

    ifeq ($(MCAL_NRF5340),Y)
        # $(error MCAL_NRF5340=$(MCAL_NRF5340))
        include $(MCAL_DIR)/mcal_nrf5340/mcal_nrf5340.mk
    endif

    ifeq ($(STM32_HAL),Y)
        # $(error STM32_HAL=$(STM32_HAL))
        #include $(MCAL_DIR)/mcal_stm32_hal/mcal_stm32_hal.mk
    endif

    ifeq ($(MCAL_STM32_HAL),Y)
        # $(error STM32_HAL=$(STM32_HAL))
        include $(MCAL_DIR)/mcal_stm32_hal/mcal_stm32_hal.mk
    endif

    ifeq ($(MCAL_STM32F7),Y)
        #include $(MCAL_DIR)/mcal_stm32f7/mcal_stm32f7.mk
    endif

endif