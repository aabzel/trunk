$(info UART_COMMON_MCAL_MK_INC=$(UART_COMMON_MCAL_MK_INC) )

ifneq ($(UART_COMMON_MCAL_MK_INC),Y)
    UART_COMMON_MCAL_MK_INC=Y

    UART_MCAL_DIR = $(MCAL_COMMON_DIR)/uart
    #@echo $(error UART_MCAL_DIR=$(UART_MCAL_DIR))

    INCDIR += -I$(UART_MCAL_DIR)
    OPT += -DHAS_UART

    ifeq ($(UART_EXT),Y)
        OPT += -DHAS_UART_EXT
    endif

    ifeq ($(UART_PROC),Y)
        OPT += -DHAS_UART_PROC
    endif

    ifeq ($(UART_INT),Y)
        OPT += -DHAS_UART_INT
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

    ifeq ($(UART4),Y)
        OPT += -DHAS_UART4
    endif

    ifeq ($(UART5),Y)
        OPT += -DHAS_UART5
    endif

    SOURCES_C += $(UART_MCAL_DIR)/uart_general.c
    SOURCES_C += $(UART_MCAL_DIR)/uart_isr.c

    ifeq ($(UART_DIAG),Y)
        SOURCES_C += $(UART_MCAL_DIR)/uart_diag.c
    endif

    ifeq ($(UART_COMMANDS),Y)
        OPT += -DHAS_UART_COMMANDS
        SOURCES_C += $(UART_MCAL_DIR)/uart_commands.c
    endif

endif



