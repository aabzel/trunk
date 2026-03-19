ifneq ($(POWER_GENERAL_DRV_MK_INC),Y)
    POWER_GENERAL_DRV_MK_INC=Y


    POWER_MCAL_DIR = $(MCAL_COMMON_DIR)/power
    #@echo $(error POWER_MCAL_DIR=$(POWER_MCAL_DIR))

    INCDIR += -I$(POWER_MCAL_DIR)
    MCAL_OPT += -DHAS_POWER

    SOURCES_C += $(POWER_MCAL_DIR)/power_general.c

    ifeq ($(DIAG),Y)
        ifeq ($(POWER_DIAG),Y)
            MCAL_OPT += -DHAS_POWER_DIAG
            SOURCES_C += $(POWER_MCAL_DIR)/power_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(POWER_COMMANDS),Y)
            MCAL_OPT += -DHAS_POWER_COMMANDS
            SOURCES_C += $(POWER_MCAL_DIR)/power_commands.c
        endif
    endif
endif
