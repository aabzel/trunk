
$(info CAN_IF_MK_INC=$(CAN_IF_MK_INC) )
ifneq ($(CAN_IF_MK_INC),Y)
    CAN_IF_MK_INC=Y
    CAN_IF_DIR = $(INTERFACES_DIR)/can_if
    #@echo $(error CAN_IF_DIR=$(CAN_IF_DIR))

    INCDIR += -I$(CAN_IF_DIR)
    OPT += -DHAS_CAN_IF

    SOURCES_C += $(CAN_IF_DIR)/can_if_drv.c

    ifeq ($(DIAG),Y)
        ifeq ($(CAN_IF_DIAG),Y)
            #@echo $(error CAN_IF_DIAG=$(CAN_IF_DIAG))
            OPT += -DHAS_CAN_IF_DIAG
            SOURCES_C += $(CAN_IF_DIR)/can_if_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CAN_IF_COMMANDS),Y)
            #@echo $(error CAN_IF_COMMANDS=$(CAN_IF_COMMANDS))
            OPT += -DHAS_CAN_IF_COMMANDS
            SOURCES_C += $(CAN_IF_DIR)/can_if_commands.c
        endif
    endif
endif
