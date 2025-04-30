#protection against repeated include as in C preprocessor
$(info MCU_CUSTOM_MK_INC=$(MCU_CUSTOM_MK_INC) )
ifneq ($(MCU_CUSTOM_MK_INC),Y)
    MCU_CUSTOM_MK_INC=Y

    MCU_CUSTOM_DIR = $(MICROCONTROLLER_DIR)/at32f435zm
    #@echo $(error MCU_CUSTOM_DIR=$(MCU_CUSTOM_DIR))
    #AT32F435xM defined in .h code from Artery
    #OPT += -DAT32F435xM
    #OPT += -DAT32F435xx
    #OPT += -DAT32F435Zx
    OPT += -DHAS_SCFG
    ARTERY=Y
    OPT += -DHAS_AT32
    OPT += -DHAS_AT32F43X
    OPT += -DHAS_AT32F435ZM
    OPT += -DAT32F4xxxx
    OPT += -DAT32F43X
    OPT += -DAT32F435ZM
    #for flash tool
    ARTERY_DEVICE=AT32F435ZMT7

    FIRMWARE_TYPE_SELECTED=N

    #AT32F4XX_HAL_DRIVER=Y

    OPT += -D__NVIC_PRIO_BITS=4
    OPT += -D__FPU_PRESENT=1

    INCDIR += -I$(MCU_CUSTOM_DIR)
    
    ifeq ($(EHAL),Y)
        EHAL_AT32F43X=Y
    endif
    
    SOURCES_C += $(MCU_CUSTOM_DIR)/interrupt_config.c
    
    ifeq ($(CLOCK),Y)
            SOURCES_C += $(MCU_CUSTOM_DIR)/clock_config.c
        ifeq ($(MCAL_AT32),Y)
        endif
    endif

    ifeq ($(MBR),Y)
        FIRMWARE_TYPE_SELECTED=Y
        OPT += -DVECT_TAB_OFFSET=0x08000000
        ifeq ($(MBR_ADVANCED),Y)
            LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_mbr_advanced.ld
        else
            LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_mbr.ld
        endif  
    endif  

    ifeq ($(BOOTLOADER),Y)
        # link script
        FIRMWARE_TYPE_SELECTED=Y
        OPT += -DVECT_TAB_OFFSET=0x08000000
        LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_boot.ld
    endif

    ifeq ($(SDIO),Y)
        $(info Config SDIO)
        SOURCES_C += $(MCU_CUSTOM_DIR)/sdio_config.c
    endif

    ifeq ($(WATCHDOG),Y)
        $(info Config WATCHDOG)
        SOURCES_C += $(MCU_CUSTOM_DIR)/watchdog_config.c
    endif

    ifeq ($(GENERIC),Y)
        # link script
        ifeq ($(GENERIC_MONOLITHIC),Y)
            #@echo $(error GENERIC_MONOLITHIC=$(GENERIC_MONOLITHIC))
            FIRMWARE_TYPE_SELECTED=Y
            OPT += -DVECT_TAB_OFFSET=0x08000000
            OPT += -DHAS_GENERIC_MONOLITHIC
            LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_generic_monolithic.ld
        else
            FIRMWARE_TYPE_SELECTED=Y
            OPT += -DVECT_TAB_OFFSET=0x08010000
            LDSCRIPT = $(MCU_CUSTOM_DIR)/gcc_arm_generic.ld
        endif
    endif

    SOURCES_ASM += $(MCU_CUSTOM_DIR)/startup_at32f435_437.S
    ifeq ($(MCAL_AT32),Y)
        SOURCES_THIRD_PARTY_C += $(MCU_CUSTOM_DIR)/system_at32f435_437.c
    endif

    ifeq ($(GPIO),Y)
        SOURCES_THIRD_PARTY_C += $(MCU_CUSTOM_DIR)/at32f435zm.c
    endif

    ifeq ($(DIAG),Y)
        SOURCES_THIRD_PARTY_C += $(MCU_CUSTOM_DIR)/at32f435zm_diag.c
    endif

    ifeq ($(SYSTICK),Y)
        SOURCES_C += $(MCU_CUSTOM_DIR)/systick_general_config.c
    endif

    ifeq ($(NVS),Y)
        $(info Add config NVS)
        SOURCES_C += $(MCU_CUSTOM_DIR)/nvs_config.c
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

    ifeq ($(FLASH_FS),Y)
        #@echo $(error FLASH_FS=$(FLASH_FS))
        $(info Add config FlashFs)
        SOURCES_C += $(MCU_CUSTOM_DIR)/flash_fs_config.c
    endif


    MICROCONTROLLER_SELECTED=Y
endif
