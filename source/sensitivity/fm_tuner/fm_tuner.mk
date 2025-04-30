ifneq ($(FM_TUNER_MK_INC),Y)
    FM_TUNER_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    FM_TUNER_DIR = $(SENSITIVITY_DIR)/fm_tuner
    #@echo $(error FM_TUNER_DIR=$(FM_TUNER_DIR))
    INCDIR += -I$(FM_TUNER_DIR)

    FM_TUNER=Y
    OPT += -DHAS_FM_TUNER
    OPT += -DHAS_MULTIMEDIA
    SOURCES_C += $(FM_TUNER_DIR)/fm_tuner_rus.c
endif
