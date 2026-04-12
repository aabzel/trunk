ifneq ($(CMSIS_MK_INC),Y)
    CMSIS_MK_INC=Y

    $(info Add CMSIS)
    CMSIS_DIR = $(VENDOR_SDK_DIR)/CMSIS
    # $(error CMSIS_DIR=$(CMSIS_DIR))
    MCAL_OPT += -DHAS_CMSIS

    INCDIR += -I$(CMSIS_DIR)
    INCDIR += -I$(CMSIS_DIR)/Include
    INCDIR += -I$(CMSIS_DIR)/Core/Include
    INCDIR += -I$(CMSIS_DIR)/DSP/Include
    ifeq ($(STM32),Y)
        INCDIR += -I$(CMSIS_DIR)/Device/ST/STM32F4xx/Include
    endif
endif