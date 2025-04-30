ifneq ($(SOCKET_MK_INC),Y)
    SOCKET_MK_INC=Y
    $(info + SOCKET)

    SOCKET_DIR = $(INTERFACES_DIR)/socket

    INCDIR += -I$(SOCKET_DIR)
    #OPT += -DHAS_SOCKET_PROC
    OPT += -DHAS_SOCKET
    OPT += -DHAS_SOCKET_PROC

    SOURCES_C += $(SOCKET_DIR)/socket_if.c
    SOURCES_C += $(SOCKET_DIR)/socket_server.c
    SOURCES_C += $(SOCKET_DIR)/socket_client.c

    LFLAGS += -lws2_32

    ifeq ($(DIAG),Y)
        ifeq ($(SOCKET_DIAG),Y)
            $(info +SOCKET_DIAG)
            OPT += -DHAS_SOCKET_DIAG
             SOURCES_C += $(SOCKET_DIR)/socket_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(SOCKET_COMMANDS),Y)
            #@echo $(error SOCKET_COMMANDS=$(SOCKET_COMMANDS))
            $(info +SOCKET_COMMANDS)
            OPT += -DHAS_SOCKET_COMMANDS
            SOURCES_C += $(SOCKET_DIR)/socket_commands.c
        endif
    endif
endif
