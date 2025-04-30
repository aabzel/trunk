$(info MCAL_MK_INC=$(MCAL_MK_INC))
ifneq ($(MCAL_MK_INC),Y)
    MCAL_MK_INC=Y

    $(info Build MCAL)

    MCAL_DIR = $(WORKSPACE_LOC)/mcal
    # $(error MCAL_DIR=$(MCAL_DIR))
    OPT += -DHAS_MCAL
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

    ifeq ($(MCAL_EHAL),Y)
        # $(error MCAL_EHAL=$(MCAL_EHAL))
        include $(MCAL_DIR)/mcal_ehal/mcal_ehal.mk
    endif

    ifeq ($(MCAL_ESP32),Y) 
        include $(MCAL_DIR)/mcal_esp32/mcal_esp32.mk
    endif

    ifeq ($(MCAL_MIK32),Y)
        # $(error MCAL_MIK32=$(MCAL_MIK32))
        include $(MCAL_DIR)/mcal_mik32/mcal_mik32.mk
    endif

    ifeq ($(MCAL_CC26X2),Y)   
        include $(MCAL_DIR)/mcal_cc26x2/mcal_cc26x2.mk
    endif
 
    ifeq ($(MCAL_NRF5340),Y)
        # $(error MCAL_NRF5340=$(MCAL_NRF5340))
        include $(MCAL_DIR)/mcal_nrf5340/mcal_nrf5340.mk
    endif

    ifeq ($(MCAL_YUNTU),Y)
        # $(error MCAL_YUNTU=$(MCAL_YUNTU))
        include $(MCAL_DIR)/mcal_yuntu/mcal_yuntu.mk
    endif
    
    ifeq ($(MCAL_STM32),Y)
        # $(error MCAL_STM32=$(MCAL_STM32))
        include $(MCAL_DIR)/mcal_stm32f4/mcal_stm32f4.mk
    endif

endif