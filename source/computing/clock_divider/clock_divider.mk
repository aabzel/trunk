
$(info CLOCK_DIVIDER_MK_INC=$(CLOCK_DIVIDER_MK_INC))

ifneq ($(CLOCK_DIVIDER_MK_INC),Y)
    CLOCK_DIVIDER_MK_INC=Y

    CLOCK_DIVIDER_DIR = $(COMPUTING_DIR)/clock_divider
    #@echo $(error CLOCK_DIVIDER_DIR = $(CLOCK_DIVIDER_DIR))

    OPT += -DHAS_CLOCK_DIVIDER
    OPT += -DHAS_CLOCK_DIVIDER_PROC
    
    INCDIR += -I$(CLOCK_DIVIDER_DIR)

    SOURCES_C += $(CLOCK_DIVIDER_DIR)/clock_divider.c


    ifeq ($(DIAG),Y)
        ifeq ($(CLOCK_DIVIDER_DIAG),Y)
            OPT += -DHAS_CLOCK_DIVIDER_DIAG
            SOURCES_C += $(CLOCK_DIVIDER_DIR)/clock_divider_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CLOCK_DIVIDER_COMMANDS),Y)
            #@echo $(error CLOCK_DIVIDER_COMMANDS = $(CLOCK_DIVIDER_COMMANDS))
            OPT += -DHAS_CLOCK_DIVIDER_COMMANDS
            SOURCES_C += $(CLOCK_DIVIDER_DIR)/clock_divider_commands.c
        endif
    endif
endif
