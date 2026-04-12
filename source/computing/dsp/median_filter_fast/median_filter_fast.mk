$(info MEDIAN_FILTER_FAST_MK_INC=$(MEDIAN_FILTER_FAST_MK_INC) )

ifneq ($(MEDIAN_FILTER_FAST_MK_INC),Y)
    MEDIAN_FILTER_FAST_MK_INC=Y

    MEDIAN_FILTER_FAST_DIR = $(DSP_DIR)/median_filter_fast
    # $(error MEDIAN_FILTER_FAST_DIR=[$(MEDIAN_FILTER_FAST_DIR)])
    INCDIR += -I$(MEDIAN_FILTER_FAST_DIR)

    ifeq ($(MEDIAN_FILTER_FAST_HASH_TABLE),Y)
        MCAL_OPT += -DHAS_MEDIAN_FILTER_FAST_HASH_TABLE
    endif
    MCAL_OPT += -DHAS_MED_FILT_DEBUG
    MCAL_OPT += -DHAS_MEDIAN_FILTER_FAST
    
    #MCAL_OPT += -DHAS_MEDIAN_FILTER_FAST_SMALL_SIZE
    SOURCES_C += $(MEDIAN_FILTER_FAST_DIR)/median_filter_fast.c
    SOURCES_C += $(MEDIAN_FILTER_FAST_DIR)/median_filter_fast_isr.c
    SOURCES_C += $(MEDIAN_FILTER_FAST_DIR)/median_filter_fast_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(MEDIAN_FILTER_FAST_DIAG),Y)
            MCAL_OPT += -DHAS_MEDIAN_FILTER_FAST_DIAG
            SOURCES_C += $(MEDIAN_FILTER_FAST_DIR)/median_filter_fast_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(MEDIAN_FILTER_FAST_COMMANDS),Y)
            # $(error MEDIAN_FILTER_FAST_COMMANDS=[$(MEDIAN_FILTER_FAST_COMMANDS)])
            MCAL_OPT += -DHAS_MEDIAN_FILTER_FAST_COMMANDS
            SOURCES_C += $(MEDIAN_FILTER_FAST_DIR)/median_filter_fast_commands.c
        endif
    endif
endif






