$(info WATCHDOG_CUSTOM_MK_INC=$(WATCHDOG_CUSTOM_MK_INC) )
ifneq ($(WATCHDOG_CUSTOM_MK_INC),Y)
    WATCHDOG_CUSTOM_MK_INC=Y

    WATCHDOG_CUSTOM_DIR = $(MCAL_STM32F4_DIR)/watchdog
    # $(error WATCHDOG_CUSTOM_DIR=$(WATCHDOG_CUSTOM_DIR))
    WATCHDOG_CUSTOM=Y
    INCDIR += -I$(WATCHDOG_CUSTOM_DIR)
    IWDG=Y

    MCAL_OPT += -DHAS_WATCHDOG_CUSTOM
    MCAL_OPT += -DHAS_IWDG
    MCAL_OPT += -DHAL_IWDG_MODULE_ENABLED

    SOURCES_C += $(WATCHDOG_CUSTOM_DIR)/watchdog_mcal.c

    ifeq ($(DIAG),Y)
        MCAL_OPT += -DHAS_WATCHDOG_CUSTOM_DIAG
        SOURCES_DIAG_C += $(WATCHDOG_CUSTOM_DIR)/watchdog_custom_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(WATCHDOG_COMMANDS),Y)
            MCAL_OPT += -DHAS_WATCHDOG_CUSTOM_COMMANDS
            SOURCES_C += $(WATCHDOG_CUSTOM_DIR)/watchdog_custom_commands.c
        endif
    endif
endif


