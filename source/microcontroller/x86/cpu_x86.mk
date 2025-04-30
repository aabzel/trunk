#protection against repeated include as in C preprocessor
$(info MCU_CUSTOM_MK_INC=$(MCU_CUSTOM_MK_INC) )
ifneq ($(MCU_CUSTOM_MK_INC),Y)
    MCU_CUSTOM_MK_INC=Y

    MCU_CUSTOM_DIR = $(MICROCONTROLLER_DIR)/x86
    #@echo $(error MCU_CUSTOM_DIR=$(MCU_CUSTOM_DIR))
    OPT += -DHAS_X86

    FIRMWARE_TYPE_SELECTED=N

    #AT32F4XX_HAL_DRIVER=Y

    INCDIR += -I$(MCU_CUSTOM_DIR)

    ifeq ($(CLOCK),Y)
         SOURCES_C += $(MCU_CUSTOM_DIR)/clock_config.c
    endif






    ifeq ($(GPIO),Y)
        SOURCES_C += $(MCU_CUSTOM_DIR)/cpu_x86.c
    endif

    
    ifeq ($(NVS),Y)
        $(info Add config NVS)
        SOURCES_C += $(MCU_CUSTOM_DIR)/nvs_config.c
    endif

    ifeq ($(DMA),Y)
        $(info Config DMA)
        #@echo $(error DMA=$(DMA))
        SOURCES_C += $(MCU_CUSTOM_DIR)/dma_config.c
    endif

    ifeq ($(PARAM),Y)
        $(info Config Param)
        #@echo $(error PARAM=$(PARAM))
        SOURCES_C += $(MCU_CUSTOM_DIR)/param_config.c
    endif

    ifeq ($(FLASH),Y)
        $(info Config Flash)
        #@echo $(error FLASH=$(FLASH))
        SOURCES_C += $(MCU_CUSTOM_DIR)/flash_config.c
    endif

    ifeq ($(UART),Y)
        $(info Config UART)
        #@echo $(error UART=$(UART))
        SOURCES_C += $(MCU_CUSTOM_DIR)/uart_config.c
    endif
    
    ifeq ($(FLASH_FS),Y)
        #@echo $(error FLASH_FS=$(FLASH_FS))
        $(info Add config FlashFs)
        SOURCES_C += $(MCU_CUSTOM_DIR)/flash_fs_config.c
    endif


    MICROCONTROLLER_SELECTED=Y
endif
