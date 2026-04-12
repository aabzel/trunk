ifneq ($(IR_RECEIVER_MK_INC),Y)
    IR_RECEIVER_MK_INC=Y

    IR_RECEIVER_DIR = $(SENSITIVITY_DIR)/ir_receiver
    # $(error IR_RECEIVER_DIR=$(IR_RECEIVER_DIR))

    INCDIR += -I$(IR_RECEIVER_DIR)

    MCAL_OPT += -DHAS_IR_RECEIVER
    MCAL_OPT += -DHAS_IR_RECEIVER_PROC

    SOURCES_C += $(IR_RECEIVER_DIR)/ir_receiver_general.c

    ifeq ($(IR_RECEIVER_INTERRUPTS),Y)
        MCAL_OPT += -DHAS_IR_RECEIVER_INTERRUPTS
        SOURCES_C += $(IR_RECEIVER_DIR)/ir_receiver_isr.c
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(IR_RECEIVER_DIAG),Y)
            MCAL_OPT += -DHAS_IR_RECEIVER_DIAG
            SOURCES_C += $(IR_RECEIVER_DIR)/ir_receiver_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(IR_RECEIVER_COMMANDS),Y)
            MCAL_OPT += -DHAS_IR_RECEIVER_COMMANDS
            SOURCES_C += $(IR_RECEIVER_DIR)/ir_receiver_commands.c
        endif
    endif
endif
