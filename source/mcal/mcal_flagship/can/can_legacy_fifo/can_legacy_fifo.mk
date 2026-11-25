$(info CAN_LEGACY_FIFO_MK_INC=  $(CAN_LEGACY_FIFO_MK_INC) )
ifneq ($(CAN_LEGACY_FIFO_MK_INC),Y)
    CAN_LEGACY_FIFO_MK_INC=Y

    CAN_LEGACY_FIFO_DIR = $(CAN_FLAGSHIP_DIR)/can_legacy_fifo
    # $(error CAN_LEGACY_FIFO_DIR=$(CAN_LEGACY_FIFO_DIR))
    INCDIR += -I$(CAN_LEGACY_FIFO_DIR)
    MCAL_OPT += -DHAS_CAN_LEGACY_FIFO

    SOURCES_C += $(CAN_LEGACY_FIFO_DIR)/can_legacy_fifo.c

    ifeq ($(CLI),Y)
        ifeq ($(CAN_DIAG),Y)
            SOURCES_C += $(CAN_LEGACY_FIFO_DIR)/can_legacy_fifo_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CAN_COMMANDS),Y)
            SOURCES_C += $(CAN_LEGACY_FIFO_DIR)/can_legacy_fifo_commands.c
        endif
    endif
endif