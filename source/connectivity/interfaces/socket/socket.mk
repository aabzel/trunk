ifneq ($(SOCKET_MK_INC),Y)
    SOCKET_MK_INC=Y
    $(info + SOCKET)

    SOCKET_DIR = $(INTERFACES_DIR)/socket

    INCDIR += -I$(SOCKET_DIR)
    #MCAL_OPT += -DHAS_SOCKET_PROC
    MCAL_OPT += -DHAS_SOCKET
    MCAL_OPT += -DHAS_SOCKET_PROC

    SOURCES_C += $(SOCKET_DIR)/socket_if.c

    ifeq ($(SOCKET_SERVER),Y)
        MCAL_OPT += -DHAS_SOCKET_SERVER
        SOURCES_C += $(SOCKET_DIR)/socket_server.c
    endif

    ifeq ($(SOCKET_CLIENT),Y)
        MCAL_OPT += -DHAS_SOCKET_CLIENT
        SOURCES_C += $(SOCKET_DIR)/socket_client.c
    endif

    LFLAGS += -lws2_32

    ifeq ($(DIAG),Y)
        ifeq ($(SOCKET_DIAG),Y)
            $(info +SOCKET_DIAG)
            MCAL_OPT += -DHAS_SOCKET_DIAG
            SOURCES_DIAG_C += $(SOCKET_DIR)/socket_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(SOCKET_COMMANDS),Y)
            #@echo $(error SOCKET_COMMANDS=$(SOCKET_COMMANDS))
            $(info +SOCKET_COMMANDS)
            MCAL_OPT += -DHAS_SOCKET_COMMANDS
            SOURCES_C += $(SOCKET_DIR)/socket_commands.c
        endif
    endif
endif
