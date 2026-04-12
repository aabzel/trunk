
$(info ANALOG_FILTER_MK_INC=$(ANALOG_FILTER_MK_INC))

ifneq ($(ANALOG_FILTER_MK_INC),Y)
    ANALOG_FILTER_MK_INC=Y

    $(info Build  + voltage divider)

    ANALOG_FILTER_DIR = $(COMPUTING_DIR)/analog_filter
    # $(error ANALOG_FILTER_DIR=$(ANALOG_FILTER_DIR))

    INCDIR += -I$(ANALOG_FILTER_DIR)

    SOURCES_C += $(ANALOG_FILTER_DIR)/analog_filter.c

    MCAL_OPT += -DHAS_ANALOG_FILTER

    ifeq ($(DIAG),Y)
        ifeq ($(ANALOG_FILTER_DIAG),Y)
            MCAL_OPT += -DHAS_ANALOG_FILTER_DIAG
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(ANALOG_FILTER_COMMANDS),Y)
            # $(error ANALOG_FILTER_COMMANDS=$(ANALOG_FILTER_COMMANDS))
            MCAL_OPT += -DHAS_ANALOG_FILTER_COMMANDS
            SOURCES_C += $(ANALOG_FILTER_DIR)/analog_filter_commands.c
        endif
    endif
endif