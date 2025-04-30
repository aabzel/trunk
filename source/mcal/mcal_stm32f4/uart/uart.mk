$(info UART_DRV_MK_INC=  $(UART_DRV_MK_INC) )
ifneq ($(UART_DRV_MK_INC),Y)
    UART_DRV_MK_INC=Y

    UART_STM_DIR = $(MCAL_STM32F4_DIR)/uart
    #@echo $(error UART_STM_DIR=$(UART_STM_DIR))

    INCDIR += -I$(UART_STM_DIR)
    OPT += -DHAS_UART_CUSTOM

    ifeq ($(UART1),Y)
        OPT += -DHAS_UART1
    endif

    ifeq ($(UART2),Y)
        OPT += -DHAS_UART2
    endif

    ifeq ($(UART3),Y)
        OPT += -DHAS_UART3
    endif

    ifeq ($(UART4),Y)
        OPT += -DHAS_UART4
    endif

    ifeq ($(UART5),Y)
        OPT += -DHAS_UART5
    endif

    ifeq ($(UART6),Y)
        OPT += -DHAS_UART6
    endif

    OPT += -DHAS_UART_TX_TIMEOUT

    SOURCES_C += $(UART_STM_DIR)/uart_custom_isr.c
    SOURCES_C += $(UART_STM_DIR)/uart_mcal.c
    
    ifeq ($(UART_DIAG),Y)
        OPT += -DHAS_UART_DIAG
        SOURCES_C += $(UART_STM_DIR)/uart_custom_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(UART_COMMANDS),Y)
            OPT += -DHAS_UART_COMMANDS
            SOURCES_C += $(UART_STM_DIR)/uart_custom_commands.c
        endif
    endif
endif