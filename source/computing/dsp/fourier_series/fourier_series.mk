$(info FOURIER_SERIES_MK_INC=$(FOURIER_SERIES_MK_INC))


ifneq ($(FOURIER_SERIES_INC),Y)
    FOURIER_SERIES_INC=Y

    FOURIER_SERIES_DIR = $(DSP_DIR)/fourier_series
    #@echo $(error FOURIER_SERIES_DIR=$(FOURIER_SERIES_DIR))

    INCDIR += -I$(FOURIER_SERIES_DIR)
    OPT += -DHAS_FOURIER_SERIES

    SOURCES_C += $(FOURIER_SERIES_DIR)/fourier_series_config.c
    SOURCES_C += $(FOURIER_SERIES_DIR)/fourier_series.c

    ifeq ($(DIAG),Y)
        ifeq ($(FOURIER_SERIES_DIAG),Y)
            OPT += -DHAS_FOURIER_SERIES_DIAG
            SOURCES_C += $(FOURIER_SERIES_DIR)/fourier_series_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(FOURIER_SERIES_COMMANDS),Y)
            OPT += -DHAS_FOURIER_SERIES_COMMANDS
            SOURCES_C += $(FOURIER_SERIES_DIR)/fourier_series_commands.c
        endif
    endif
endif