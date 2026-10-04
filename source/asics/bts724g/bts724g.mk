ifneq ($(BTS724G_MK_INC),Y)
    BTS724G_MK_INC=Y

    BTS724G_DIR = $(ASICS_DIR)/bts724g
    # $(error BTS724G_DIR=$(BTS724G_DIR))

    INCDIR += -I$(BTS724G_DIR)

    MCAL_OPT += -DHAS_BTS724G

    ifeq ($(BTS724G_PROC),Y)
        MCAL_OPT += -DHAS_BTS724G_PROC
    endif

    SOURCES_C += $(BTS724G_DIR)/bts724g_mcal.c

    ifeq ($(DIAG),Y)
        ifeq ($(BTS724G_DIAG),Y)
            MCAL_OPT += -DHAS_BTS724G_DIAG
            SOURCES_DIAG_C += $(BTS724G_DIR)/bts724g_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(BTS724G_COMMANDS),Y)
            MCAL_OPT += -DHAS_BTS724G_COMMANDS
            SOURCES_C += $(BTS724G_DIR)/bts724g_commands.c
        endif
    endif
endif
