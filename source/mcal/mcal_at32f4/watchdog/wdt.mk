$(info WATCHDOG_MK_INC=$(WATCHDOG_MK_INC) )
ifneq ($(WATCHDOG_MK_INC),Y)
    WATCHDOG_MK_INC=Y
    WATCHDOG=Y

    WATCHDOG_CUSTOM_DIR = $(MCAL_AT32F4_DIR)/watchdog
    #@echo $(error WATCHDOG_CUSTOM_DIR=$(WATCHDOG_CUSTOM_DIR))
    INCDIR += -I$(WATCHDOG_CUSTOM_DIR)
    MCAL_OPT += -DHAS_WATCHDOG

    SOURCES_C += $(WATCHDOG_CUSTOM_DIR)/watchdog_mcal.c

    ifeq ($(DIAG),Y)
       MCAL_OPT += -DHAS_WATCHDOG_CUSTOM_DIAG
       SOURCES_C += $(WATCHDOG_CUSTOM_DIR)/watchdog_custom_diag.c
    endif
    
    ifeq ($(CLI),Y)
        ifeq ($(WATCHDOG_COMMANDS),Y)
            MCAL_OPT += -DHAS_WATCHDOG_CUSTOM_COMMANDS
            SOURCES_C += $(WATCHDOG_CUSTOM_DIR)/watchdog_custom_commands.c
        endif
    endif
endif


