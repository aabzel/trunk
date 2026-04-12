#protection against repeated include as in C preprocessor
$(info MCU_CUSTOM_MK_INC=$(MCU_CUSTOM_MK_INC) )
ifneq ($(MCU_CUSTOM_MK_INC),Y)
    MCU_CUSTOM_MK_INC=Y

    MCU_CUSTOM_DIR = $(MICROCONTROLLER_DIR)/dummy_mcu
    # $(error MCU_CUSTOM_DIR=$(MCU_CUSTOM_DIR))
    DUMMY_MCU=Y
    
    MCAL_OPT += -DHAS_DUMMY_MCU
    
    MCAL_OPT += -DDEVICE_TYPE=MCU_DUMMY_MCU
    MCAL_OPT += -DDEVICE_NAME=DUMMY_MCU2P176T1B
    #MCAL_OPT += -DEFM_CTRL_WE_MASK
    
    #FLOAT-ABI += -mfloat-abi=soft
    #MICROPROCESSOR = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)
    
    FIRMWARE_TYPE_SELECTED=N
    
    SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/dummy_mcu.c
    SOURCES_THIRD_PARTY_C += $(MCU_CUSTOM_DIR)/system_init.c
    
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
    


    SOURCES_ASM = $(MCU_CUSTOM_DIR)/startup_DUMMY_MCU.S
    LDSCRIPT = $(MCU_CUSTOM_DIR)/DUMMY_MCU_flash.ld

    ifeq ($(CLOCK_OUT),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/clock_out_config.c
    endif

    ifeq ($(CLOCK),Y)
            SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/clock_config.c
    endif

    ifeq ($(DMA),Y)
        $(info Config DMA)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/dma_config.c
    endif

    ifeq ($(DMA_CHANNEL),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/dma_channel_config.c
    endif
    
    ifeq ($(EIM),Y)
        # $(error EIM=$(EIM))
        $(info Add config EIM)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/eim_config.c
    endif
    
    ifeq ($(ERM),Y)
        # $(error ERM=$(ERM))
        $(info Add config ERM)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/erm_config.c
    endif

    ifeq ($(DIAG),Y)
        SOURCES_THIRD_PARTY_C += $(MCU_CUSTOM_DIR)/dummy_mcu_diag.c
    endif
    
    ifeq ($(FLASH),Y)
        # $(error FLASH=$(FLASH))
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/flash_config.c
    endif

    ifeq ($(FCSMU),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/fcsmu_config.c
    endif

    ifeq ($(FLASH_FS),Y)
        # $(error FLASH_FS=$(FLASH_FS))
        $(info Add config FlashFs)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/flash_fs_config.c
    endif

    ifeq ($(MAM),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/mam_config.c
    endif

    ifeq ($(MPU),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/mpu_config.c
    endif

    ifeq ($(MBR),Y)
        FIRMWARE_TYPE_SELECTED=Y
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/mbr_config.c
        #MCAL_OPT += -DVECT_TAB_OFFSET=0x01000000
    endif

    ifeq ($(INTERRUPT),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/interrupt_config.c
    endif

    ifeq ($(GENERIC),Y)
        # link script
        ifeq ($(GENERIC_MONOLITHIC),Y)
            # $(error GENERIC_MONOLITHIC=$(GENERIC_MONOLITHIC))
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

    ifeq ($(MAILBOX),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/mailbox_config.c
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/mailbox_channel_config.c
    endif
    
    ifeq ($(LOCKSTEP),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/lockstep_config.c
    endif

    ifeq ($(MULTICORE),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/multicore_config.c
    endif

    ifeq ($(NVS),Y)
        $(info Add config NVS)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/nvs_config.c
    endif

    ifeq ($(PIN),Y)
        SOURCES_THIRD_PARTY_C += $(MCU_CUSTOM_DIR)/pin_config.c
    endif

    ifeq ($(POWER),Y)
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/power_config.c
    endif

    ifeq ($(STORAGE),Y)
        $(info Config Param)
        # $(error STORAGE=$(STORAGE))
        SOURCES_CONFIGURATION_C += $(MCU_CUSTOM_DIR)/storage_config.c
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
