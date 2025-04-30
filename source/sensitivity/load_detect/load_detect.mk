
$(info LOAD_DETECT_MK_INC=$(LOAD_DETECT_MK_INC) )
ifneq ($(LOAD_DETECT_MK_INC),Y)
    LOAD_DETECT_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    LOAD_DETECT_DIR = $(SENSITIVITY_DIR)/load_detect
    #@echo $(error LOAD_DETECT_DIR=$(LOAD_DETECT_DIR))

    INCDIR += -I$(LOAD_DETECT_DIR)

    OPT += -DHAS_LOAD_DETECT
    OPT += -DHAS_LOAD_DETECT_PROC
    
    SOURCES_C += $(LOAD_DETECT_DIR)/load_detect_drv.c

    ifeq ($(DIAG),Y)
        ifeq ($(LOAD_DETECT_DIAG),Y)
            OPT += -DHAS_LOAD_DETECT_DIAG
            #@echo $(error LOAD_DETECT_DIAG=$(LOAD_DETECT_DIAG))
            SOURCES_C += $(LOAD_DETECT_DIR)/load_detect_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(LOAD_DETECT_COMMANDS),Y)
            OPT += -DHAS_LOAD_DETECT_COMMANDS
            SOURCES_C += $(LOAD_DETECT_DIR)/load_detect_commands.c
        endif
    endif
endif