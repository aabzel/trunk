
ifneq ($(RUNNING_LINE_MK_INC),Y)
    RUNNING_LINE_MK_INC=Y
    RUNNING_LINE_DIR = $(STORAGE_DIR)/running_line
    #@echo $(error RUNNING_LINE_DIR= $(RUNNING_LINE_DIR))
    INCDIR += -I$(RUNNING_LINE_DIR)

    MCAL_OPT += -DHAS_RUNNING_LINE
    MCAL_OPT += -DHAS_RUNNING_LINE_PROC

    SOURCES_C += $(RUNNING_LINE_DIR)/running_line.c

    ifeq ($(DIAG),Y)
        ifeq ($(RUNNING_LINE_DIAG),Y)
            MCAL_OPT += -DHAS_RUNNING_LINE_DIAG
            SOURCES_C += $(RUNNING_LINE_DIR)/running_line_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(RUNNING_LINE_COMMANDS),Y)
            #@echo $(error RUNNING_LINE_COMMANDS=$(RUNNING_LINE_COMMANDS))
            MCAL_OPT += -DHAS_RUNNING_LINE_COMMANDS
            SOURCES_C += $(RUNNING_LINE_DIR)/running_line_commands.c
        endif
    endif
endif