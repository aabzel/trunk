ifneq ($(SERIAL_PORT_MK_INC),Y)
    SERIAL_PORT_MK_INC=Y
    $(info + SERIAL_PORT)

    SERIAL_PORT_DIR = $(INTERFACES_DIR)/serial_port

    INCDIR += -I$(SERIAL_PORT_DIR)
    #OPT += -DHAS_SERIAL_PORT_PROC
    OPT += -DHAS_SERIAL_PORT
    OPT += -DHAS_SERIAL_PORT_PROC

    SOURCES_C += $(SERIAL_PORT_DIR)/serial_port.c

    ifeq ($(DIAG),Y)
        ifeq ($(SERIAL_PORT_DIAG),Y)
            $(info +SERIAL_PORT_DIAG)
            OPT += -DHAS_SERIAL_PORT_DIAG
             SOURCES_C += $(SERIAL_PORT_DIR)/serial_port_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(SERIAL_PORT_COMMANDS),Y)
            #@echo $(error SERIAL_PORT_COMMANDS=$(SERIAL_PORT_COMMANDS))
            $(info +SERIAL_PORT_COMMANDS)
            OPT += -DHAS_SERIAL_PORT_COMMANDS
            SOURCES_C += $(SERIAL_PORT_DIR)/serial_port_commands.c
        endif
    endif
endif
