ifneq ($(ST_MK_INC),Y)
    ST_MK_INC=Y
    ST_DIR = $(DEVICE_DIR)/ST
    # $(error ST_DIR=$(ST_DIR))
    #INCDIR += -I$(ST_DIR)
    ifeq ($(STM32F7X),Y)
        include $(ST_DIR)/STM32F7x/STM32F7x.mk
    endif

    ifeq ($(STM32F4X),Y)
        # $(error STM32F4X=$(STM32F4X))
        include $(ST_DIR)/STM32F4x/STM32F4x.mk
    endif
endif

