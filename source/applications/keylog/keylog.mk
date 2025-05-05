
ifneq ($(KEYLOG_MK_INC),Y)
    KEYLOG_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    KEYLOG_DIR = $(APPLICATIONS_DIR)/keylog
    #@echo $(error KEYLOG_DIR= $(KEYLOG_DIR))

    INCDIR += -I$(KEYLOG_DIR)

    OPT += -DHAS_KEYLOG
    OPT += -DHAS_KEYLOG_PROC

    FIFO_ARRAY=Y
    ifeq ($(DIAG),Y)
        ifeq ($(KEYLOG_DIAG),Y)
            OPT += -DHAS_KEYLOG_DIAG
            SOURCES_C += $(KEYLOG_DIR)/keylog_diag.c
        endif
    endif

    SOURCES_C += $(KEYLOG_DIR)/keylog.c

    ifeq ($(CLI),Y)
        ifeq ($(KEYLOG_COMMANDS),Y)
            SOURCES_C += $(KEYLOG_DIR)/keylog_commands.c
        endif
    endif
    
endif