#protection against repeated include as in C preprocessor
$(info MCU_CUSTOM_MK_INC=$(MCU_CUSTOM_MK_INC) )
ifneq ($(MCU_CUSTOM_MK_INC),Y)
    MCU_CUSTOM_MK_INC=Y

    MCU_CUSTOM_DIR = $(MICROCONTROLLER_DIR)/ytm32b1me05g0mlq
    #@echo $(error MCU_CUSTOM_DIR=$(MCU_CUSTOM_DIR))
    YTM32B1ME05G0MLQ=Y
    
    MCAL_OPT += -DHAS_YTM32B1ME05G0MLQ
    MCAL_OPT += -DCPU_YTM32B1ME0
    #MCAL_OPT += -DEFM_CTRL_WE_MASK
    
    #FLOAT-ABI += -mfloat-abi=soft
    #MICROPROCESSOR = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)
    
    FIRMWARE_TYPE_SELECTED=N

    #SOURCES_ASM += $(MCU_CUSTOM_DIR)/YTM32B1ME0_startup_gcc.S
    #SOURCES_THIRD_PARTY_C += $(MCU_CUSTOM_DIR)/system_YTM32B1ME0.c

    INCDIR += -I$(MCU_CUSTOM_DIR)

    ifeq ($(BOOTLOADER),Y)
        # link script
        FIRMWARE_TYPE_SELECTED=Y
        MCAL_OPT += -DVECT_TAB_OFFSET=0x00000000
        #LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_boot.ld
    endif

    ifeq ($(CLOCK),Y)
            SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/clock_config.c
        ifeq ($(YTM32B1ME0_1_3_1),Y)
        endif
    endif

    SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/interrupt_config.c

    ifeq ($(DMA),Y)
        $(info Config DMA)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/dma_config.c
    endif
    
    ifeq ($(FLASH),Y)
        #@echo $(error FLASH=$(FLASH))
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/flash_config.c
    endif

    ifeq ($(FLASH_FS),Y)
        #@echo $(error FLASH_FS=$(FLASH_FS))
        $(info Add config FlashFs)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/flash_fs_config.c
    endif

    ifeq ($(GPIO),Y)
        SOURCES_THIRD_PARTY_C += $(MCU_CUSTOM_DIR)/ytm32b1me05g0mlq.c
    endif

    ifeq ($(POWER),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/power_config.c
    endif

    ifeq ($(DIAG),Y)
        SOURCES_THIRD_PARTY_C += $(MCU_CUSTOM_DIR)/ytm32b1me05g0mlq_diag.c
    endif

    ifeq ($(GENERIC),Y)
        # link script
        ifeq ($(GENERIC_MONOLITHIC),Y)
            #@echo $(error GENERIC_MONOLITHIC=$(GENERIC_MONOLITHIC))
            FIRMWARE_TYPE_SELECTED=Y
            MCAL_OPT += -DVECT_TAB_OFFSET=0x00000000
            MCAL_OPT += -DHAS_GENERIC_MONOLITHIC
            #LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_generic_monolithic.ld
        else
            FIRMWARE_TYPE_SELECTED=Y
            MCAL_OPT += -DVECT_TAB_OFFSET=0x08010000
            #LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_generic.ld
        endif
    endif


    ifeq ($(MBR),Y)
        FIRMWARE_TYPE_SELECTED=Y
        MCAL_OPT += -DVECT_TAB_OFFSET=0x00000000
        ifeq ($(MBR_ADVANCED),Y)
            LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_mbr_advanced.ld
        else
            LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_mbr.ld
        endif
    endif

    ifeq ($(NVS),Y)
        $(info Add config NVS)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/nvs_config.c
    endif

    ifeq ($(PARAM),Y)
        $(info Config Param)
        #@echo $(error PARAM=$(PARAM))
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/param_config.c
    endif

    ifeq ($(SDIO),Y)
        $(info Config SDIO)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/sdio_config.c
    endif

    ifeq ($(SYSTICK),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/systick_general_config.c
    endif

    ifeq ($(WATCHDOG),Y)
        $(info Config WATCHDOG)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/watchdog_config.c
    endif

    MICROCONTROLLER_SELECTED=Y
endif
