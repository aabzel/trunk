ifneq ($(BARKER_CODE_MK_INC),Y)
    BARKER_CODE_MK_INC=Y

    BARKER_CODE_DIR = $(DSP_DIR)/barker_code
    # $(error BARKER_CODE_DIR=$(BARKER_CODE_DIR))
    INCDIR += -I$(BARKER_CODE_DIR)
    MCAL_OPT += -DHAS_BARKER_CODE
    SOURCES_C += $(BARKER_CODE_DIR)/barker_code.c
endif
