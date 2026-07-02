$(info UART_DRV_MK_INC=  $(UART_DRV_MK_INC) )
ifneq ($(UART_DRV_MK_INC),Y)
    UART_DRV_MK_INC=Y

    UART_STM_DIR = $(MCAL_CUSTOM_DIR)/uart
    # $(error UART_STM_DIR=$(UART_STM_DIR))
    HAL_DMA=Y
    INCDIR += -I$(UART_STM_DIR)
    MCAL_OPT += -DHAS_UART_CUSTOM

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

    ifeq ($(UART9),Y)
        MCAL_OPT += -DHAS_UART9
    endif

    ifeq ($(UART_TIMEOUT),Y)
        MCAL_OPT += -DHAS_UART_TX_TIMEOUT
    endif

    ifeq ($(UART_DMA),Y)
        ifeq ($(UART1),Y)
            SOURCES_C += $(UART_STM_DIR)/dma_channel_config_uart1.c
        endif
        SOURCES_C += $(UART_STM_DIR)/uart_custom_dma.c
    endif

    SOURCES_C += $(UART_STM_DIR)/uart_custom_isr.c
    SOURCES_C += $(UART_STM_DIR)/uart_mcal.c

    ifeq ($(UART_POLLING),Y)
        SOURCES_C += $(UART_STM_DIR)/uart_custom_polling.c
    endif

    ifeq ($(UART_DIAG),Y)
        MCAL_OPT += -DHAS_UART_DIAG
        SOURCES_C += $(UART_STM_DIR)/uart_custom_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(UART_COMMANDS),Y)
            MCAL_OPT += -DHAS_UART_COMMANDS
            SOURCES_C += $(UART_STM_DIR)/uart_custom_commands.c
        endif
    endif
endif