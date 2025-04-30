$(info MODULATOR_MK_INC=$(MODULATOR_MK_INC))

ifneq ($(MODULATOR_MK_INC),Y)
    MODULATOR_MK_INC=Y

    MODULATOR_DIR = $(COMPUTING_DIR)/modulator
    #@echo $(error MODULATOR_DIR=$(MODULATOR_DIR))

    INCDIR += -I$(MODULATOR_DIR)
    OPT +=-DHAS_MODULATOR

    SOURCES_C += $(MODULATOR_DIR)/modulator.c

    ifeq ($(CLI),Y)
        ifeq ($(MODULATOR_COMMANDS),Y)
            OPT +=-DHAS_MODULATOR_COMMANDS
        endif
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(MODULATOR_DIAG),Y)
            SOURCES_C += $(MODULATOR_DIR)/modulator_diag.c
        endif
    endif

    ifeq ($(BPSK),Y)
        include $(MODULATOR_DIR)/bpsk/bpsk.mk
    endif
endif







