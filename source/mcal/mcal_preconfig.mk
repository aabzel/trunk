
$(info MCAL_PRECONFIG_MK_INC=$(MCAL_PRECONFIG_MK_INC))
ifneq ($(MCAL_PRECONFIG_MK_INC),Y)
    MCAL_PRECONFIG_MK_INC=Y
    #@echo $(error MCAL_PRECONFIG_MK_INC=$(MCAL_PRECONFIG_MK_INC))

    MCAL_DIR = $(WORKSPACE_LOC)/mcal
    MCAL=Y

    ifeq ($(MCAL),Y)
        include $(MCAL_DIR)/mcal_common/mcal_common_preconfig.mk
    endif

    ifeq ($(MCAL_AT32),Y)
        #@echo $(error MCAL_AT32=$(MCAL_AT32))
        include $(MCAL_DIR)/mcal_at32f4/mcal_at32f4_preconfig.mk
    endif

    ifeq ($(MCAL_STM32),Y)
        #@echo $(error MCAL_STM32=$(MCAL_STM32))
        include $(MCAL_DIR)/mcal_stm32f4/mcal_stm32f4_preconfig.mk
    endif

    ifeq ($(MCAL_NRF5340),Y)
        #@echo $(error MCAL_NRF5340=$(MCAL_NRF5340))
        include $(MCAL_DIR)/mcal_nrf5340/mcal_nrf5340_preconfig.mk
    endif

    ifeq ($(MCAL_CC26X2),Y)   
        include $(MCAL_DIR)/mcal_cc26x2/mcal_cc26x2_preconfig.mk
    endif

    ifeq ($(MCAL_ESP32),Y) 
        include $(MCAL_DIR)/mcal_esp32/mcal_esp32_preconfig.mk
    endif

    ifeq ($(MCAL_EHAL),Y)
        #@echo $(error MCAL_EHAL=$(MCAL_EHAL))
        include $(MCAL_DIR)/mcal_ehal/mcal_ehal_preconfig.mk
    endif

    ifeq ($(MCAL_YUNTU),Y)
        #@echo $(error MCAL_YUNTU=$(MCAL_YUNTU))
        include $(MCAL_DIR)/mcal_yuntu/mcal_yuntu_preconfig.mk
    endif

endif