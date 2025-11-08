ifneq ($(GAME_PAD_PS2_MK_INC),Y)
    GAME_PAD_PS2_MK_INC=Y

    GAME_PAD_PS2_DIR = $(SENSITIVITY_DIR)/game_pad_ps2
    # $(error GAME_PAD_PS2_DIR=$(GAME_PAD_PS2_DIR))

    INCDIR += -I$(GAME_PAD_PS2_DIR)

    OPT += -DHAS_GAME_PAD_PS2
    OPT += -DHAS_GAME_PAD_PS2_PROC

    SOURCES_C += $(GAME_PAD_PS2_DIR)/game_pad_ps2.c

    ifeq ($(GAME_PAD_PS2_INTERRUPTS),Y)
        OPT += -DHAS_GAME_PAD_PS2_INTERRUPTS
        SOURCES_C += $(GAME_PAD_PS2_DIR)/game_pad_ps2_isr.c
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(GAME_PAD_PS2_DIAG),Y)
            OPT += -DHAS_GAME_PAD_PS2_DIAG
            SOURCES_C += $(GAME_PAD_PS2_DIR)/game_pad_ps2_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(GAME_PAD_PS2_COMMANDS),Y)
            OPT += -DHAS_GAME_PAD_PS2_COMMANDS
            SOURCES_C += $(GAME_PAD_PS2_DIR)/game_pad_ps2_commands.c
        endif
    endif
endif
