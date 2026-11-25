ifneq ($(CLOCK_FC7300X_MK_INC),Y)
    CLOCK_FC7300X_MK_INC=Y
    CLOCK_FC7300X_DIR = $(MCAL_FC7300X_DIR)/clock
    #@echo $(error CLOCK_FC7300X_DIR=$(CLOCK_FC7300X_DIR))
    #@echo $(error CLOCK=$(CLOCK))

    INCDIR += -I$(CLOCK_FC7300X_DIR)

    MCAL_OPT += -DHAS_CLOCK_CUSTOM
    
    #PLL_CALC=Y
    SOURCES_C += $(CLOCK_FC7300X_DIR)/clock.c

    ifeq ($(DIAG),Y)
        ifeq ($(CLOCK_DIAG),Y)
            MCAL_OPT += -DHAS_CLOCK_DIAG
            SOURCES_C += $(CLOCK_FC7300X_DIR)/clock_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CLOCK_COMMANDS),Y)
            MCAL_OPT += -DHAS_CLOCK_CUSTOM_COMMANDS
            SOURCES_C += $(CLOCK_FC7300X_DIR)/clock_custom_commands.c
        endif
    endif
endif
