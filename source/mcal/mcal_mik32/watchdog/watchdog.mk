$(info WATCHDOG_CUSTOM_MK_INC=$(WATCHDOG_CUSTOM_MK_INC) )
ifneq ($(WATCHDOG_CUSTOM_MK_INC),Y)
    WATCHDOG_CUSTOM_MK_INC=Y
    WATCHDOG=Y
    
    WATCHDOG_CUSTOM_DIR = $(MCAL_MIK32_DIR)/watchdog
    #@echo $(error WATCHDOG_CUSTOM_DIR=$(WATCHDOG_CUSTOM_DIR))
    INCDIR += -I$(WATCHDOG_CUSTOM_DIR)
    
    OPT += -DHAS_WATCHDOG

    SOURCES_C += $(WATCHDOG_CUSTOM_DIR)/watchdog_mcal.c

    ifeq ($(DIAG),Y)
        ifeq ($(WATCHDOG_DIAG),Y)
            OPT += -DHAS_WATCHDOG_COMMANDS
            SOURCES_C += $(WATCHDOG_CUSTOM_DIR)/watchdog_custom_diag.c
        endif
    endif
    
    ifeq ($(CLI),Y)
        ifeq ($(WATCHDOG_COMMANDS),Y)
            OPT += -DHAS_WATCHDOG_COMMANDS
            SOURCES_C += $(WATCHDOG_CUSTOM_DIR)/watchdog_custom_commands.c
        endif
    endif
endif


