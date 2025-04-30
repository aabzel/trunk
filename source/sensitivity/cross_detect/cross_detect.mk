
$(info CROSS_DETECT_MK_INC=$(CROSS_DETECT_MK_INC) )
ifneq ($(CROSS_DETECT_MK_INC),Y)
    CROSS_DETECT_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    CROSS_DETECT_DIR = $(SENSITIVITY_DIR)/cross_detect
    #@echo $(error CROSS_DETECT_DIR=$(CROSS_DETECT_DIR))

    INCDIR += -I$(CROSS_DETECT_DIR)

    OPT += -DHAS_CROSS_DETECT
    OPT += -DHAS_CROSS_DETECT_PROC
    OPT += -DHAS_IO_BANG

    SOURCES_C += $(CROSS_DETECT_DIR)/cross_detect_drv.c

    ifeq ($(DIAG),Y)
        ifeq ($(CROSS_DETECT_DIAG),Y)
            OPT += -DHAS_CROSS_DETECT_DIAG
            #@echo $(error CROSS_DETECT_DIAG=$(CROSS_DETECT_DIAG))
            SOURCES_C += $(CROSS_DETECT_DIR)/cross_detect_diag.c
        endif
    endif

    DEPEND_GVI += $(CROSS_DETECT_DIR)/cross_detect.gvi

    ifeq ($(CLI),Y)
        ifeq ($(CROSS_DETECT_COMMANDS),Y)
            OPT += -DHAS_CROSS_DETECT_COMMANDS
            SOURCES_C += $(CROSS_DETECT_DIR)/cross_detect_commands.c
        endif
    endif
endif