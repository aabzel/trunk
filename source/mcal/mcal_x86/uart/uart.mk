$(info UART_DRV_MK_INC=  $(UART_DRV_MK_INC) )
ifneq ($(UART_DRV_MK_INC),Y)
    UART_DRV_MK_INC=Y

    UART_CUSTOM_DIR = $(MCAL_X86_DIR)/uart
    #@echo $(error UART_CUSTOM_DIR=$(UART_CUSTOM_DIR))

    INCDIR += -I$(UART_CUSTOM_DIR)
    MCAL_OPT += -DHAS_UART
    MCAL_OPT += -DHAS_UART_CUSTOM
    MCAL_OPT += -DHAS_UART_PROC

    ifeq ($(UART0),Y)
        MCAL_OPT += -DHAS_UART0
    endif

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
    
    ifeq ($(UART10),Y)
        MCAL_OPT += -DHAS_UART10
    endif
    
    ifeq ($(UART11),Y)
        MCAL_OPT += -DHAS_UART11
    endif

    ifeq ($(UART12),Y)
        MCAL_OPT += -DHAS_UART12
    endif
    
    ifeq ($(UART13),Y)
        MCAL_OPT += -DHAS_UART13
    endif
    
    ifeq ($(UART14),Y)
        MCAL_OPT += -DHAS_UART14
    endif
    
    ifeq ($(UART15),Y)
        MCAL_OPT += -DHAS_UART15
    endif
    
    ifeq ($(UART16),Y)
        MCAL_OPT += -DHAS_UART16
    endif

    ifeq ($(UART17),Y)
        MCAL_OPT += -DHAS_UART17
    endif

    ifeq ($(UART_TIMEOUT),Y)
        MCAL_OPT += -DHAS_UART_TX_TIMEOUT
    endif

    SOURCES_C += $(UART_CUSTOM_DIR)/uart_mcal.c
    SOURCES_C += $(UART_CUSTOM_DIR)/uart_custom_isr.c

    ifeq ($(UART_DIAG),Y)
        MCAL_OPT += -DHAS_UART_DIAG
        SOURCES_C += $(UART_CUSTOM_DIR)/uart_custom_diag.c
    endif
            
    ifeq ($(CLI),Y)
        ifeq ($(UART_COMMANDS),Y)
            MCAL_OPT += -DHAS_UART_COMMANDS
            SOURCES_C += $(UART_CUSTOM_DIR)/uart_custom_commands.c
        endif
    endif
endif