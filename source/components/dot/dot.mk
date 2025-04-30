$(info DOT_MK_INC=$(DOT_MK_INC) )

ifneq ($(DOT_MK_INC),Y)
    DOT_MK_INC=Y
    DOT_DIR = $(WORKSPACE_LOC)components/dot
    #@echo $(error DOT_DIR=$(DOT_DIR))
    INCDIR += -I$(DOT_DIR)
    #OPT += -Dio_printf=printf
    OPT += -DHAS_DOT

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    SOURCES_C += $(DOT_DIR)/dot.c

endif