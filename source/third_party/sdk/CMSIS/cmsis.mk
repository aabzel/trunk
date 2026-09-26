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
    
    include $(CMSIS_DIR)/Device/Device.mk
endif