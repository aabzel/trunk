#protection against repeated include as in C preprocessor
$(info MCU_CUSTOM_MK_INC=$(MCU_CUSTOM_MK_INC) )
ifneq ($(MCU_CUSTOM_MK_INC),Y)
    MCU_CUSTOM_MK_INC=Y

    MCU_CUSTOM_DIR = $(MICROCONTROLLER_DIR)/fc7300f8mdt
    #@echo $(error MCU_CUSTOM_DIR=$(MCU_CUSTOM_DIR))
    FC7300F8MDT=Y
    
    MCAL_OPT += -DHAS_FC7300F8MDT
    
    MCAL_OPT += -DDEVICE_TYPE=MCU_FC7300F8MDT
    MCAL_OPT += -DDEVICE_NAME=FC7300F8MDT2P176T1B
    #MCAL_OPT += -DEFM_CTRL_WE_MASK
    
    #FLOAT-ABI += -mfloat-abi=soft
    #MICROPROCESSOR = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)
    
    FIRMWARE_TYPE_SELECTED=N
    
    SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/fc7300f8mdt.c
    SOURCES_THIRD_PARTY_C += $(MCU_CUSTOM_DIR)/system_init.c
    


    ifeq ($(MULTICORE),Y)
        SOURCES_ASM += $(MCU_CUSTOM_DIR)/startup_FC7300F8MDx_Core0.S
        SOURCES_ASM += $(MCU_CUSTOM_DIR)/startup_FC7300F8MDx_Core1.S
        SOURCES_ASM += $(MCU_CUSTOM_DIR)/startup_FC7300F8MDx_Core2.S
        LDSCRIPT = $(MCU_CUSTOM_DIR)/FC7300F8MDT_flash_multicore.ld
    else
        SOURCES_ASM = $(MCU_CUSTOM_DIR)/startup_FC7300F8MDx.S
        LDSCRIPT = $(MCU_CUSTOM_DIR)/FC7300F8MDT_flash.ld
    endif

    ifeq ($(CLOCK_OUT),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/clock_out_config.c
    endif

    INCDIR += -I$(MCU_CUSTOM_DIR)

    ifeq ($(BOOTLOADER),Y)
        # link script
        FIRMWARE_TYPE_SELECTED=Y
        MCAL_OPT += -DVECT_TAB_OFFSET=0x01000000
        #LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_boot.ld
    endif


    ifeq ($(BOOT),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/boot_config.c
    endif
    
    ifeq ($(CLOCK),Y)
            SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/clock_config.c
    endif

    ifeq ($(INTERRUPT),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/interrupt_config.c
    endif

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

    ifeq ($(PIN),Y)
        SOURCES_THIRD_PARTY_C += $(MCU_CUSTOM_DIR)/pin_config.c
    endif

    ifeq ($(POWER),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/power_config.c
    endif

    ifeq ($(DIAG),Y)
        SOURCES_THIRD_PARTY_C += $(MCU_CUSTOM_DIR)/fc7300f8mdt_diag.c
    endif

    ifeq ($(GENERIC),Y)
        # link script
        ifeq ($(GENERIC_MONOLITHIC),Y)
            #@echo $(error GENERIC_MONOLITHIC=$(GENERIC_MONOLITHIC))
            FIRMWARE_TYPE_SELECTED=Y
            MCAL_OPT += -DVECT_TAB_OFFSET=0x01000000
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
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/mbr_config.c
        #MCAL_OPT += -DVECT_TAB_OFFSET=0x01000000
    endif

    ifeq ($(MAILBOX),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/mailbox_config.c
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/mailbox_channel_config.c
    endif


    ifeq ($(MULTICORE),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/multicore_config.c
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

    ifeq ($(SCHEDULER),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/scheduler_config.c
    endif
    
    ifeq ($(SYSTICK),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/systick_config.c
    endif

    ifeq ($(SUPER_CYCLE),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/super_cycle_config.c
    endif

    ifeq ($(WATCHDOG),Y)
        $(info Config WATCHDOG)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/watchdog_config.c
    endif

    MICROCONTROLLER_SELECTED=Y
endif
