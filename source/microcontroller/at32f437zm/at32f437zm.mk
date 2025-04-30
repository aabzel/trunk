#protection against repeated include as in C preprocessor
$(info MCU_CUSTOM_MK_INC=$(MCU_CUSTOM_MK_INC) )
ifneq ($(MCU_CUSTOM_MK_INC),Y)
    MCU_CUSTOM_MK_INC=Y

    MCU_CUSTOM_DIR = $(MICROCONTROLLER_DIR)/at32f437zm
    #@echo $(error MCU_CUSTOM_DIR=$(MCU_CUSTOM_DIR))
    OPT += -DHAS_AT32F437ZM
    OPT += -DHAS_AT32
    OPT += -DAT32F4xxxx
    OPT += -DAT32F437xx
    OPT += -DAT32F437ZM
    OPT += -DAT32F437xM
    OPT += -DAT32F437Zx
    OPT += -DAT32F437ZMT7

    FIRMWARE_TYPE_SELECTED=N

    #AT32F4XX_HAL_DRIVER=Y

    INCDIR += -I$(MCU_CUSTOM_DIR)

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


    ifeq ($(MCAL_AT32),Y)
        SOURCES_C += $(MCU_CUSTOM_DIR)/system_at32f435_437.c
    endif

    ifeq ($(GPIO),Y)
        SOURCES_C += $(MCU_CUSTOM_DIR)/at32f437zm.c
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

    SOURCES_ASM += $(MCU_CUSTOM_DIR)/startup_at32f435_437.S

    MICROCONTROLLER_SELECTED=Y
endif
