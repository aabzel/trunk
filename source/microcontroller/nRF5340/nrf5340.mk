#protection against repeated include as in C preprocessor
ifneq ($(NRF5340_MK_INC),Y)
    NRF5340_MK_INC=Y


    MCU_SELECT_DIR = $(MICROCONTROLLER_DIR)/nRF5340
    #@echo $(error MCU_SELECT_DIR=$(MCU_SELECT_DIR))

    OPT += -DNRF5340
    OPT += -DHAS_ARM
    OPT += -DHAS_NRF53
    OPT += -DHAS_NRF5340
    OPT += -DHAS_MULTICORE

    BOARD=Y
    CORTEX_M33=Y
    NRF5340=Y
    MCAL_NRF5340=Y

    ifeq ($(CORE_APP),Y)
        ifeq ($(CORE_NET),Y)
            @echo $(error "Only one core alloved in a single build")
        endif
    endif

    INCDIR += -I$(MCU_SELECT_DIR)

    SOURCES_C += $(MCU_SELECT_DIR)/nrf5340.c

    ifeq ($(PINS),Y)
        OPT += -DHAS_PINS
        SOURCES_C += $(MCU_SELECT_DIR)/pin_config.c
    endif

    ifeq ($(CLOCK),Y)
        #@echo $(error CLOCK=$(CLOCK))
        SOURCES_C += $(MCU_SELECT_DIR)/clock_config.c
    endif

    ifeq ($(FLASH),Y)
        SOURCES_C += $(MCU_SELECT_DIR)/flash_config.c
    endif

    ifeq ($(FLASH_FS),Y)
        SOURCES_C += $(MCU_SELECT_DIR)/flash_fs_config.c
    endif

    ifeq ($(PARAM),Y)
        SOURCES_C += $(MCU_SELECT_DIR)/param_config.c
    endif

    ifeq ($(NVS),Y)
        $(info Add config NVS)
        SOURCES_C += $(MCU_SELECT_DIR)/nvs_config.c
    endif

    ifeq ($(CORE_APP),Y)
        #@echo $(error CORE_APP=$(CORE_APP))
        #@echo $(error NRF5340_APP=$(NRF5340_APP))
        OPT += -DHAS_CORE_APP
        OPT += -DNRF5340_APP
        OPT += -DNRF5340_XXAA_APPLICATION
        SOURCES_C += $(MCU_SELECT_DIR)/nrf5340_app_nvic_diag.c
        ifeq ($(BOOTLOADER),Y)
            LDSCRIPT = $(MCU_SELECT_DIR)/nrf5340_bootloader_app.ld
        endif
        
        ifeq ($(GENERIC),Y)
            LDSCRIPT = $(MCU_SELECT_DIR)/nrf5340_app.ld
        endif
    endif

    ifeq ($(CORE_NET),Y)
        #@echo $(error NRF5340_NET=$(NRF5340_NET))
        OPT += -DHAS_CORE_NET
        OPT += -DNRF5340_NET
        OPT += -DNRF5340_XXAA_NETWORK
        LDSCRIPT = $(MCU_SELECT_DIR)/nrf5340_net.ld
    endif

    SOURCES_ASM += $(MCU_SELECT_DIR)/startup_nrf5340.S
    MICROCONTROLLER_SELECTED=Y
endif