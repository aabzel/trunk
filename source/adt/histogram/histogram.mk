ifneq ($(HISTOGRAM_MK_INC),Y)
    HISTOGRAM_MK_INC=Y

    HISTOGRAM_DIR = $(ADT_DIR)/histogram
 
    $(info + histogram)

    INCDIR += -I$(HISTOGRAM_DIR)

    MCAL_OPT += -DHAS_HISTOGRAM

    SOURCES_C += $(HISTOGRAM_DIR)/histogram.c

    ifeq ($(DIAG),Y)
        ifeq ($(HISTOGRAM_DIAG),Y)
            MCAL_OPT += -DHAS_HISTOGRAM_DIAG
            SOURCES_C += $(HISTOGRAM_DIR)/histogram_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(HISTOGRAM_COMMANDS),Y)
            $(info +HISTOGRAM_COMMANDS)
            MCAL_OPT += -DHAS_HISTOGRAM_COMMANDS
            SOURCES_C += $(HISTOGRAM_DIR)/histogram_command.c
        endif
    endif
endif
