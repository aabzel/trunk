ifneq ($(SW_UART_MK_INC),Y)
    SW_UART_MK_INC=Y

    SW_UART_DIR = $(INTERFACES_DIR)/sw_uart
    # $(error SW_UART_DIR=$(SW_UART_DIR))

    INCDIR += -I$(SW_UART_DIR)

    MCAL_OPT += -DHAS_SW_UART
    MCAL_OPT += -DHAS_SW_UART_PROC

    SOURCES_C += $(SW_UART_DIR)/sw_uart_mcal.c

    MCAL_OPT += -DHAS_SW_UART_INTERRUPTS
    SOURCES_C += $(SW_UART_DIR)/sw_uart_isr.c

    ifeq ($(DIAG),Y)
        ifeq ($(SW_UART_DIAG),Y)
            MCAL_OPT += -DHAS_SW_UART_DIAG
            SOURCES_C += $(SW_UART_DIR)/sw_uart_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(SW_UART_COMMANDS),Y)
            MCAL_OPT += -DHAS_SW_UART_COMMANDS
            SOURCES_C += $(SW_UART_DIR)/sw_uart_commands.c
        endif
    endif
endif
