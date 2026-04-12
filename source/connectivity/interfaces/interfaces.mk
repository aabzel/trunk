$(info RS485_MK_INC=$(RS485_MK_INC) )

ifneq ($(INTERFACE_MK_INC),Y)
    INTERFACE_MK_INC=Y

    INTERFACES_DIR = $(CONNECTIVITY_DIR)/interfaces
    # $(error INTERFACES_DIR=$(INTERFACES_DIR))

    INCDIR += -I$(INTERFACES_DIR)
    MCAL_OPT += -DHAS_INTERFACE
    MCAL_OPT += -DHAS_INTERFACES

    SOURCES_C +=${INTERFACES_DIR}/interface_drv.c

    ifeq ($(INTERFACE_PROC),Y)
        MCAL_OPT += -DHAS_INTERFACE_PROC
    endif

    ifeq ($(INTERFACE_EXT),Y)
        MCAL_OPT += -DHAS_INTERFACE_EXT
    endif

    ifeq ($(A2B),Y)
        include $(INTERFACES_DIR)/a2b/a2b.mk
    endif

    ifeq ($(CAN),Y)
        include $(INTERFACES_DIR)/can_if/can_if.mk
    endif

    ifeq ($(DTMF),Y)
        # $(error DTMF=$(DTMF))
        include $(INTERFACES_DIR)/dtmf/dtmf.mk
    endif

    ifeq ($(SERIAL_PORT),Y)
        include $(INTERFACES_DIR)/serial_port/serial_port.mk
    endif

    ifeq ($(RADIO),Y)
        include $(INTERFACES_DIR)/radio/radio.mk
    endif

    ifeq ($(RS485),Y)
        # $(error RS485=$(RS485))
        include $(INTERFACES_DIR)/rs485/rs485.mk
    endif

    ifeq ($(RS232),Y)
        # $(error RS232=$(RS232))
        include $(INTERFACES_DIR)/rs232/rs232.mk
    endif

    ifeq ($(SEGGER_RTT),Y)
        # $(error SOCKET=$(SOCKET))
        include $(INTERFACES_DIR)/segger_rtt/segger_rtt.mk
    endif


    ifeq ($(SOCKET),Y)
        # $(error SOCKET=$(SOCKET))
        include $(INTERFACES_DIR)/socket/socket.mk
    endif

    ifeq ($(UWB),Y)
        include $(INTERFACES_DIR)/uwb/uwb.mk
    endif

    ifeq ($(SW_UART),Y)
        # $(error SW_UART=$(SW_UART))
        include $(INTERFACES_DIR)/sw_uart/sw_uart.mk
    endif


    ifeq ($(WIFI),Y)
        # $(error WIFI=$(WIFI))
        include $(INTERFACES_DIR)/wifi/wifi.mk
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(INTERFACE_DIAG),Y)
            # $(error INTERFACE_DIAG=$(INTERFACE_DIAG))
            MCAL_OPT += -DHAS_INTERFACES_DIAG
            MCAL_OPT += -DHAS_INTERFACE_DIAG
            SOURCES_DIAG_C +=${INTERFACES_DIR}/interfaces_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(INTERFACES_COMMANDS),Y)
            # $(error INTERFACES_COMMANDS=$(INTERFACES_COMMANDS))
            MCAL_OPT += -DHAS_INTERFACES_COMMANDS
            MCAL_OPT += -DHAS_INTERFACE_COMMANDS
        endif
    endif
endif
