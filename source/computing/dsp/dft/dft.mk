$(info DFT_MK_INC=$(DFT_MK_INC))

ifneq ($(DFT_MK_INC),Y)
    DFT_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path))
    DFT_DIR=$(DSP_DIR)/dft

    INCDIR += -I$(DFT_DIR)

    OPT += -DHAS_DFT
    SOURCES_C += $(DFT_DIR)/dft.c

    ifeq ($(DIAG),Y)
        ifeq ($(DFT_DIAG),Y)
            OPT += -DHAS_DFT_DIAG
            SOURCES_C += $(DFT_DIR)/dft_diag.c
        endif
    endif
endif
