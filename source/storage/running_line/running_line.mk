
ifneq ($(RUNNING_LINE_MK_INC),Y)
    RUNNING_LINE_MK_INC=Y
    RUNNING_LINE_DIR = $(STORAGE_DIR)/running_line
    #@echo $(error RUNNING_LINE_DIR= $(RUNNING_LINE_DIR))
    INCDIR += -I$(RUNNING_LINE_DIR)

    OPT += -DHAS_RUNNING_LINE
    OPT += -DHAS_RUNNING_LINE_PROC

    SOURCES_C += $(RUNNING_LINE_DIR)/running_line.c

    ifeq ($(DIAG),Y)
        ifeq ($(RUNNING_LINE_DIAG),Y)
            OPT += -DHAS_RUNNING_LINE_DIAG
            SOURCES_C += $(RUNNING_LINE_DIR)/running_line_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(RUNNING_LINE_COMMANDS),Y)
            #@echo $(error RUNNING_LINE_COMMANDS=$(RUNNING_LINE_COMMANDS))
            OPT += -DHAS_RUNNING_LINE_COMMANDS
            SOURCES_C += $(RUNNING_LINE_DIR)/running_line_commands.c
        endif
    endif
endif