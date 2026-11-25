ifneq ($(CLOCK_FLAGSHIP_MK_INC),Y)
    CLOCK_FLAGSHIP_MK_INC=Y

    CLOCK_FLAGSHIP_DIR = $(MCAL_FLAGSHIP_DIR)/clock
    # $(error CLOCK_FLAGSHIP_DIR=$(CLOCK_FLAGSHIP_DIR))

    INCDIR += -I$(CLOCK_FLAGSHIP_DIR)
    MCAL_OPT += -DHAS_CLOCK_FLAGSHIP

    SOURCES_C += $(CLOCK_FLAGSHIP_DIR)/clock_module.c

    ifeq ($(DIAG),Y)
        ifeq ($(CLOCK_DIAG),Y)
            #MCAL_OPT += -DHAS_CLOCK_FLAGSHIP_DIAG
            #SOURCES_C += $(CLOCK_FLAGSHIP_DIR)/clock_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CLOCK_COMMANDS),Y)
            #MCAL_OPT += -DHAS_CLOCK_FLAGSHIP_COMMANDS
            #SOURCES_C += $(CLOCK_FLAGSHIP_DIR)/clock_custom_commands.c
        endif
    endif
endif
