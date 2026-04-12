$(info UART_DRV_MK_INC=  $(UART_DRV_MK_INC) )
ifneq ($(UART_DRV_MK_INC),Y)
    UART_DRV_MK_INC=Y

    UART_CUSTOM_DIR = $(MCAL_AT32F4_DIR)/uart
    #@echo $(error UART_CUSTOM_DIR=$(UART_CUSTOM_DIR))

    INCDIR += -I$(UART_CUSTOM_DIR)
    MCAL_OPT += -DHAS_UART
    MCAL_OPT += -DHAS_UART_CUSTOM
    MCAL_OPT += -DHAS_UART_PROC

    ifeq ($(UART1),Y)
        MCAL_OPT += -DHAS_UART1
    endif

    ifeq ($(UART2),Y)
        MCAL_OPT += -DHAS_UART2
    endif

    ifeq ($(UART3),Y)
        MCAL_OPT += -DHAS_UART3
    endif

    ifeq ($(UART4),Y)
        MCAL_OPT += -DHAS_UART4
    endif

    ifeq ($(UART5),Y)
        MCAL_OPT += -DHAS_UART5
    endif

    ifeq ($(UART6),Y)
        MCAL_OPT += -DHAS_UART6
    endif

    ifeq ($(UART7),Y)
        MCAL_OPT += -DHAS_UART7
    endif

    ifeq ($(UART8),Y)
        MCAL_OPT += -DHAS_UART8
    endif

    MCAL_OPT += -DHAS_UART_TX_TIMEOUT
    SOURCES_C += $(UART_CUSTOM_DIR)/uart_mcal.c
    SOURCES_C += $(UART_CUSTOM_DIR)/uart_custom_isr.c

    ifeq ($(CLI),Y)
        ifeq ($(UART_COMMANDS),Y)
            MCAL_OPT += -DHAS_UART_COMMANDS
            SOURCES_C += $(UART_CUSTOM_DIR)/uart_custom_commands.c
        endif
    endif
endif