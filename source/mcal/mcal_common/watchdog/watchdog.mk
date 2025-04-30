$(info WATCHDOG_GENERAL_DRV_MK_INC=$(WATCHDOG_GENERAL_DRV_MK_INC) )

ifneq ($(WATCHDOG_GENERAL_DRV_MK_INC),Y)
    WATCHDOG_GENERAL_DRV_MK_INC=Y

    WATCHDOG_MCAL_DIR = $(MCAL_COMMON_DIR)/watchdog
    #@echo $(error WATCHDOG_MCAL_DIR=$(WATCHDOG_MCAL_DIR))

    WATCHDOG=Y
    INCDIR += -I$(WATCHDOG_MCAL_DIR)
    OPT += -DHAS_WATCHDOG
    OPT += -DHAS_WATCHDOG_PROC

    SOURCES_C += $(WATCHDOG_MCAL_DIR)/watchdog_general.c

    ifeq ($(DIAG),Y)
        ifeq ($(WATCHDOG_DIAG),Y)
            OPT += -DHAS_WATCHDOG_DIAG
            SOURCES_C += $(WATCHDOG_MCAL_DIR)/watchdog_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(WATCHDOG_COMMANDS),Y)
            OPT += -DHAS_WATCHDOG_COMMANDS
            SOURCES_C += $(WATCHDOG_MCAL_DIR)/watchdog_commands.c
        endif
    endif
    
endif