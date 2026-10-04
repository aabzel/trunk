#protection against repeated include as in C preprocessor
$(info MCU_CUSTOM_MK_INC=$(MCU_CUSTOM_MK_INC) )
ifneq ($(MCU_CUSTOM_MK_INC),Y)
    MCU_CUSTOM_MK_INC=Y

    MCU_CUSTOM_DIR = $(MICROCONTROLLER_DIR)/x86
    # $(error MCU_CUSTOM_DIR=$(MCU_CUSTOM_DIR))
    MCAL_OPT += -DHAS_X86

    FIRMWARE_TYPE_SELECTED=N

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

    ifeq ($(SUPER_CYCLE),Y)
        SOURCES_C += $(MCU_CUSTOM_DIR)/super_cycle_config.c
    endif

    ifeq ($(DMA),Y)
        $(info Config DMA)
        # $(error DMA=$(DMA))
        SOURCES_C += $(MCU_CUSTOM_DIR)/dma_config.c
    endif

    ifeq ($(FLASH),Y)
        $(info Config Flash)
        # $(error FLASH=$(FLASH))
        SOURCES_C += $(MCU_CUSTOM_DIR)/flash_config.c
    endif

    ifeq ($(UART),Y)
        $(info Config UART)
        # $(error UART=$(UART))
        SOURCES_C += $(MCU_CUSTOM_DIR)/uart_config.c
    endif
    
    ifeq ($(FLASH_FS),Y)
        # $(error FLASH_FS=$(FLASH_FS))
        $(info Add config FlashFs)
        SOURCES_C += $(MCU_CUSTOM_DIR)/flash_fs_config.c
    endif

    ifeq ($(STORAGE),Y)
        $(info Config STORAGE)
        # $(error STORAGE=$(STORAGE))
        SOURCES_C += $(MCU_CUSTOM_DIR)/storage_config.c
    endif

    ifeq ($(SCHEDULER),Y)
        SOURCES_C += $(MCU_CUSTOM_DIR)/scheduler_config.c
    endif

    ifeq ($(WRITER),Y)
        #  $(error WRITER=$(WRITER))
        SOURCES_C += $(MCU_CUSTOM_DIR)/writer_config.c
    endif


    MICROCONTROLLER_SELECTED=Y
endif
