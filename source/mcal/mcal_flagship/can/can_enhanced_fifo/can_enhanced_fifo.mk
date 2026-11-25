$(info CAN_ENHANCED_FIFO_MK_INC=  $(CAN_ENHANCED_FIFO_MK_INC) )
ifneq ($(CAN_ENHANCED_FIFO_MK_INC),Y)
    CAN_ENHANCED_FIFO_MK_INC=Y

    CAN_ENHANCED_FIFO_DIR = $(CAN_FLAGSHIP_DIR)/can_enhanced_fifo
    # $(error CAN_ENHANCED_FIFO_DIR=$(CAN_ENHANCED_FIFO_DIR))
    INCDIR += -I$(CAN_ENHANCED_FIFO_DIR)
    MCAL_OPT += -DHAS_CAN_ENHANCED_FIFO

    SOURCES_C += $(CAN_ENHANCED_FIFO_DIR)/can_enhanced_fifo.c

    ifeq ($(CLI),Y)
        ifeq ($(CAN_DIAG),Y)
            SOURCES_C += $(CAN_ENHANCED_FIFO_DIR)/can_enhanced_fifo_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CAN_COMMANDS),Y)
            SOURCES_C += $(CAN_ENHANCED_FIFO_DIR)/can_enhanced_fifo_commands.c
        endif
    endif
endif