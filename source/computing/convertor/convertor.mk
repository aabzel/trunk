$(info CONVERTOR_MK_INC=$(CONVERTOR_MK_INC))
ifneq ($(CONVERTOR_MK_INC),Y)
    CONVERTOR_MK_INC=Y
    $(info Add SW DAC)

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )
    CONVERTOR=Y

    CONVERTOR_DIR = $(COMPUTING_DIR)/convertor
    INCDIR += -I$(CONVERTOR_DIR)
    OPT += -DHAS_CONVERTOR


    SOURCES_C += $(CONVERTOR_DIR)/convertor.c

    ifeq ($(DIAG),Y)
        ifeq ($(CONVERTOR_DIAG),Y)
            #@echo $(error CONVERTOR_DIAG=$(CONVERTOR_DIAG))
            OPT += -DHAS_CONVERTOR_DIAG
            SOURCES_C += $(CONVERTOR_DIR)/convertor_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CONVERTOR_COMMANDS),Y)
            OPT += -DHAS_CONVERTOR_COMMANDS
            SOURCES_C += $(CONVERTOR_DIR)/convertor_commands.c
        endif
    endif

endif
