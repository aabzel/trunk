ifneq ($(STACK_FRAME_MK_INC),Y)
    STACK_FRAME_MK_INC=Y

    STACK_FRAME=Y
    OPT += -DHAS_STACK_FRAME

    STACK_FRAME_PROTO_DIR = $(PROTOCOLS_DIR)/stack_frame
    INCDIR += -I$(STACK_FRAME_PROTO_DIR)

    SOURCES_C += $(STACK_FRAME_PROTO_DIR)/stack_frame.c
    SOURCES_C += $(STACK_FRAME_PROTO_DIR)/stack_frame_config.c

    ifeq ($(CLI),Y)
        ifeq ($(STACK_FRAME_COMMANDS),Y)
            OPT += -DHAS_STACK_FRAME_COMMANDS
            SOURCES_C += $(STACK_FRAME_PROTO_DIR)/stack_frame_commands.c
        endif
    endif

    ifeq ($(DIAG),Y)
        OPT += -DHAS_STACK_FRAME_DIAG
        SOURCES_C += $(STACK_FRAME_PROTO_DIR)/stack_frame_diag.c
    endif
endif