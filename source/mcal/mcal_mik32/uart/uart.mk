$(info UART_DRV_MK_INC=  $(UART_DRV_MK_INC) )
ifneq ($(UART_DRV_MK_INC),Y)
    UART_DRV_MK_INC=Y

    UART_MIK_DIR = $(MCAL_MIK32_DIR)/uart
    # $(error UART_MIK_DIR=$(UART_MIK_DIR))

    INCDIR += -I$(UART_MIK_DIR)
    OPT += -DHAS_UART_CUSTOM

    ifeq ($(UART0),Y)
        OPT += -DHAS_UART0
    endif

    ifeq ($(UART1),Y)
        OPT += -DHAS_UART1
    endif

    OPT += -DHAS_UART_TX_TIMEOUT

    SOURCES_C += $(UART_MIK_DIR)/uart_mcal.c
    SOURCES_C += $(UART_MIK_DIR)/uart_custom_isr.c
    
    ifeq ($(UART_DIAG),Y)
        OPT += -DHAS_UART_CUSTOM_DIAG
        SOURCES_C += $(UART_MIK_DIR)/uart_custom_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(UART_COMMANDS),Y)
            OPT += -DHAS_UART_CUSTOM_COMMANDS
            SOURCES_C += $(UART_MIK_DIR)/uart_custom_commands.c
        endif
    endif
endif