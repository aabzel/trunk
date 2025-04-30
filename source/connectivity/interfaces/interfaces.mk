$(info RS485_MK_INC=$(RS485_MK_INC) )

ifneq ($(INTERFACE_MK_INC),Y)
    INTERFACE_MK_INC=Y

    INTERFACES_DIR = $(CONNECTIVITY_DIR)/interfaces
    #@echo $(error INTERFACES_DIR=$(INTERFACES_DIR))

    INCDIR += -I$(INTERFACES_DIR)
    OPT += -DHAS_INTERFACE
    OPT += -DHAS_INTERFACES

    SOURCES_C +=${INTERFACES_DIR}/interface_drv.c
    ifeq ($(INTERFACE_PROC),Y)
        SOURCES_C += $(INTERFACES_DIR)/if_config.c
    endif
    
    ifeq ($(INTERFACE_EXT),Y)
        OPT += -DHAS_INTERFACE_EXT
    endif
    

    ifeq ($(A2B),Y)
        include $(INTERFACES_DIR)/a2b/a2b.mk
    endif

    ifeq ($(CAN),Y)
        include $(INTERFACES_DIR)/can_if/can_if.mk
    endif

    ifeq ($(DTMF),Y)
        #@echo $(error DTMF=$(DTMF))
        include $(INTERFACES_DIR)/dtmf/dtmf.mk
    endif

    ifeq ($(RADIO),Y)
        include $(INTERFACES_DIR)/radio/radio.mk
    endif

    ifeq ($(RS485),Y)
        #@echo $(error RS485=$(RS485))
        include $(INTERFACES_DIR)/rs485/rs485.mk
    endif

    ifeq ($(RS232),Y)
        #@echo $(error RS232=$(RS232))
        include $(INTERFACES_DIR)/rs232/rs232.mk
    endif

    ifeq ($(SOCKET),Y)
        #@echo $(error SOCKET=$(SOCKET))
        include $(INTERFACES_DIR)/socket/socket.mk
    endif

    ifeq ($(UWB),Y)
        include $(INTERFACES_DIR)/uwb/uwb.mk
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(INTERFACE_DIAG),Y)
            #$(error INTERFACE_DIAG=$(INTERFACE_DIAG))
            OPT += -DHAS_INTERFACES_DIAG
            OPT += -DHAS_INTERFACE_DIAG
            SOURCES_C +=${INTERFACES_DIR}/interfaces_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(INTERFACES_COMMANDS),Y)
            #@echo $(error INTERFACES_COMMANDS=$(INTERFACES_COMMANDS))
            OPT += -DHAS_INTERFACES_COMMANDS
            OPT += -DHAS_INTERFACE_COMMANDS
        endif
    endif
endif
