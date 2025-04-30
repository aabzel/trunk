ifneq ($(HEX_BIN_MK_INC),Y)
    HEX_BIN_MK_INC=Y

    HEX_BIN_DIR = $(STORAGE_DIR)/hex_bin
    #@ echo $(error HEX_BIN_DIR = $(HEX_BIN_DIR))

    OPT += -DHAS_HEX_BIN

    INCDIR += -I$(HEX_BIN_DIR)

    SOURCES_C += $(HEX_BIN_DIR)/hex_bin.c

    ifeq ($(DIAG),Y)
        ifeq ($(HEX_BIN_DIAG),Y)
            OPT += -DHAS_HEX_BIN_DIAG
            SOURCES_C += $(HEX_BIN_DIR)/hex_bin_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(HEX_BIN_COMMANDS),Y)
            OPT += -DHAS_HEX_BIN_COMMANDS
            SOURCES_C += $(HEX_BIN_DIR)/hex_bin_commands.c
        endif
    endif
endif


