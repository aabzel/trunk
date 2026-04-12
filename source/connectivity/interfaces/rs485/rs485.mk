
$(info RS485_MK_INC=$(RS485_MK_INC) )

ifneq ($(RS485_MK_INC),Y)
    RS485_MK_INC=Y

    RS485_DIR = $(INTERFACES_DIR)/rs485
    #@echo $(error RS485_DIR=$(RS485_DIR))

    INCDIR += -I$(RS485_DIR)
    MCAL_OPT += -DHAS_RS485
    MCAL_OPT += -DHAS_RS485_PROC

    SOURCES_C += $(RS485_DIR)/rs485_mcal.c

    ifeq ($(DIAG),Y)
            MCAL_OPT += -DHAS_RS485_DIAG
            SOURCES_C += $(RS485_DIR)/rs485_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(RS485_COMMANDS),Y)
            #@echo $(error RS485_COMMANDS=$(RS485_COMMANDS))
            MCAL_OPT += -DHAS_RS485_COMMANDS
            SOURCES_C += $(RS485_DIR)/rs485_commands.c
        endif
    endif
endif

