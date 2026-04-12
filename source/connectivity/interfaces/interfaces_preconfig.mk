$(info RS485_MK_INC=$(RS485_MK_INC) )

ifneq ($(INTERFACE_PRECONFIG_INC),Y)
    INTERFACE_PRECONFIG_INC=Y

    INTERFACES_DIR = $(CONNECTIVITY_DIR)/interfaces
 
    CONNECTIVITY=Y
    INTERFACES=Y

    ifeq ($(A2B),Y)
        include $(INTERFACES_DIR)/a2b/a2b_preconfig.mk
    endif

    ifeq ($(SW_UART),Y)
        # $(error SW_UART=$(SW_UART))
        include $(INTERFACES_DIR)/sw_uart/sw_uart_preconfig.mk
    endif

    ifeq ($(RS485),Y)
        # $(error RS485=$(RS485))
        include $(INTERFACES_DIR)/rs485/rs485_preconfig.mk
    endif

    ifeq ($(RS232),Y)
        # $(error RS232=$(RS232))
        include $(INTERFACES_DIR)/rs232/rs232_preconfig.mk
    endif

    ifeq ($(CAN),Y)
        include $(INTERFACES_DIR)/can_if/can_if_preconfig.mk
    endif

    ifeq ($(SOCKET),Y)
        # $(error SOCKET=$(SOCKET))
        include $(INTERFACES_DIR)/socket/socket_preconfig.mk
    endif

    ifeq ($(DTMF),Y)
        # $(error DTMF=$(DTMF))
        include $(INTERFACES_DIR)/dtmf/dtmf_preconfig.mk
    endif

    ifeq ($(RADIO),Y)
        include $(INTERFACES_DIR)/radio/radio_preconfig.mk
    endif

    ifeq ($(UWB),Y)
        include $(INTERFACES_DIR)/uwb/uwb_preconfig.mk
    endif

endif
