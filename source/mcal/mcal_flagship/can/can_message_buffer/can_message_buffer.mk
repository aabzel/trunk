$(info CAN_MESSAGE_BUFFER_MK_INC=  $(CAN_MESSAGE_BUFFER_MK_INC) )
ifneq ($(CAN_MESSAGE_BUFFER_MK_INC),Y)
    CAN_MESSAGE_BUFFER_MK_INC=Y
 
    CAN_MESSAGE_BUFFER_DIR = $(CAN_FLAGSHIP_DIR)/can_message_buffer
    # $(error CAN_MESSAGE_BUFFER_DIR=$(CAN_MESSAGE_BUFFER_DIR))
    INCDIR += -I$(CAN_MESSAGE_BUFFER_DIR)
    MCAL_OPT += -DHAS_CAN_MESSAGE_BUFFER

    SOURCES_C += $(CAN_MESSAGE_BUFFER_DIR)/can_message_buffer.c
    
    SOURCES_DIAG_C += $(CAN_MESSAGE_BUFFER_DIR)/can_message_buffer_diag.c

    ifeq ($(CLI),Y)
        ifeq ($(CAN_DIAG),Y)
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CAN_COMMANDS),Y)
        endif
    endif
endif