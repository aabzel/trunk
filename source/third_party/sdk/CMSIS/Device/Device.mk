ifneq ($(DEVICE_MK_INC),Y)
    DEVICE_MK_INC=Y
    DEVICE_DIR = $(CMSIS_DIR)/Device
    # $(error DEVICE_DIR=$(DEVICE_DIR))
    INCDIR += -I$(DEVICE_DIR)

    include $(DEVICE_DIR)/ST/ST.mk
endif

