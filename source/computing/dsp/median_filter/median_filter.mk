$(info MEDIAN_FILTER_MK_INC=$(MEDIAN_FILTER_MK_INC) )

ifneq ($(MEDIAN_FILTER_MK_INC),Y)
    MEDIAN_FILTER_MK_INC=Y

    MEDIAN_FILTER_DIR = $(DSP_DIR)/median_filter
    # $(error MEDIAN_FILTER_DIR=[$(MEDIAN_FILTER_DIR)])
    INCDIR += -I$(MEDIAN_FILTER_DIR)

    MCAL_OPT += -DHAS_MEDIAN_FILTER
    SOURCES_C += $(MEDIAN_FILTER_DIR)/median_filter.c
    SOURCES_C += $(MEDIAN_FILTER_DIR)/median_filter_isr.c
    SOURCES_C += $(MEDIAN_FILTER_DIR)/median_filter_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(MEDIAN_FILTER_DIAG),Y)
            MCAL_OPT += -DHAS_MEDIAN_FILTER_DIAG
            SOURCES_C += $(MEDIAN_FILTER_DIR)/median_filter_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(MEDIAN_FILTER_COMMANDS),Y)
            # $(error MEDIAN_FILTER_COMMANDS=[$(MEDIAN_FILTER_COMMANDS)])
            MCAL_OPT += -DHAS_MEDIAN_FILTER_COMMANDS
            SOURCES_C += $(MEDIAN_FILTER_DIR)/median_filter_commands.c
        endif
    endif
endif






