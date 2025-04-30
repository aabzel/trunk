



ifneq ($(MODULATOR_PRECONFIG_INC),Y)
    MODULATOR_PRECONFIG_INC=Y

    MODULATOR_DIR = $(COMPUTING_DIR)/modulator

    BASE16=Y

    ifeq ($(BPSK),Y)
        include $(MODULATOR_DIR)/bpsk/bpsk_preconfig.mk
    endif
endif







