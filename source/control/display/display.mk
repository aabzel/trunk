ifneq ($(DISPLAY_MK_INC),Y)
    DISPLAY_MK_INC=Y

    DISPLAY_DIR = $(CONTROL_DIR)/display
    #@echo $(error DISPLAY_DIR=$(DISPLAY_DIR))

    INCDIR += -I$(DISPLAY_DIR)

    OPT += -DHAS_DISPLAY

    SOURCES_C += $(DISPLAY_DIR)/display_drv.c

    ifeq ($(DIAG),Y)
        ifeq ($(DISPLAY_DIAG),Y)
            OPT += -DHAS_DISPLAY_DIAG
            SOURCES_C += $(DISPLAY_DIR)/display_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(DISPLAY_COMMANDS),Y)
            OPT += -DHAS_DISPLAY_COMMANDS
            BIN_2_STR=Y
            SOURCES_C += $(DISPLAY_DIR)/display_commands.c
        endif
    endif
endif
