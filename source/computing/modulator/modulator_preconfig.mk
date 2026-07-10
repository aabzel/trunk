
ifneq ($(MODULATOR_PRECONFIG_INC),Y)
    MODULATOR_PRECONFIG_INC=Y

    MODULATOR_DIR = $(COMPUTING_DIR)/modulator

    BASE16=Y

    ifeq ($(BPSK_4FS),Y)
        include $(MODULATOR_DIR)/bpsk_4fs/bpsk_4fs_preconfig.mk
    endif

    ifeq ($(BPSK),Y)
        include $(MODULATOR_DIR)/bpsk/bpsk_preconfig.mk
    endif
endif







