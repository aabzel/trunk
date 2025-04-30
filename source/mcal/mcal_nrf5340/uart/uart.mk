$(info UART_DRV_MK_INC=  $(UART_DRV_MK_INC) )
ifneq ($(UART_DRV_MK_INC),Y)
    UART_DRV_MK_INC=Y
    
    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )
    
    UART_DIR = $(MCAL_NRF5340_DIR)/uart
    #@echo $(error UART_DIR=$(UART_DIR))

    INCDIR += -I$(UART_DIR)
    OPT += -DHAS_UART
    #OPT += -DHAS_UART_POLL
    OPT += -DHAS_UART_PROC

    ifeq ($(UART_INTERRUPT),Y)
        #@echo $(error UART_INTERRUPT=$(UART_INTERRUPT))
        OPT += -DHAS_UART_INTERRUPT
        OPT += -DHAS_UART_ISR
        SOURCES_C += $(UART_DIR)/uart_isr.c
        
    endif

    ifeq ($(UART0),Y)
        OPT += -DHAS_UART0
    endif

    ifeq ($(UART1),Y)
        OPT += -DHAS_UART1
    endif

    ifeq ($(UART2),Y)
        OPT += -DHAS_UART2
    endif
    
    ifeq ($(UART3),Y)
        OPT += -DHAS_UART3
    endif

    ifeq ($(CORE_APP),Y)
        ifeq ($(UART4),Y)
            @echo $(error Unreal UART)
        endif
    endif
    
    ifeq ($(CORE_NET),Y)
        ifeq ($(UART1),Y)
            @echo $(error Unreal UART)
        endif
        ifeq ($(UART2),Y)
            @echo $(error Unreal UART)
        endif
        ifeq ($(UART3),Y)
            @echo $(error Unreal UART)
        endif
    endif

    SOURCES_C += $(UART_DIR)/uart_mcal.c

    ifeq ($(DIAG),Y)
        SOURCES_C += $(UART_DIR)/uart_custom_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(UART_COMMANDS),Y)
            OPT += -DHAS_UART_COMMANDS
            SOURCES_C += $(UART_DIR)/uart_custom_commands.c
        endif
    endif
endif