$(info POWER_CUSTOM_MK_INC=$(POWER_CUSTOM_MK_INC) )

ifneq ($(POWER_CUSTOM_MK_INC),Y)
    POWER_CUSTOM_MK_INC=Y


    POWER_CUSTOM_DIR = $(MCAL_X86_DIR)/power
    #@echo $(error POWER_CUSTOM_DIR=$(POWER_CUSTOM_DIR))

    INCDIR += -I$(POWER_CUSTOM_DIR)

    SOURCES_C += $(POWER_CUSTOM_DIR)/power_mcal.c
    MCAL_OPT += -DHAS_POWER_CUSTOM

    ifeq ($(POWER_ISR),Y)
        $(info + POWER ISR )
        MCAL_OPT += -DHAS_POWER_ISR
        SOURCES_C += $(POWER_CUSTOM_DIR)/power_custom_isr.c
    endif

    MCAL_OPT += -DHAS_POWER1

    ifeq ($(DIAG),Y)
        ifeq ($(POWER_DIAG),Y)
            MCAL_OPT += -DHAS_POWER_CUSTOM_DIAG
            SOURCES_C += $(POWER_CUSTOM_DIR)/power_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(POWER_COMMANDS),Y)
            MCAL_OPT += -DHAS_POWER_CUSTOM_COMMANDS
            SOURCES_C += $(POWER_CUSTOM_DIR)/power_custom_commands.c
        endif
    endif
endif