ifneq ($(CONNECTIVITY_MK_INC),Y)
    CONNECTIVITY_MK_INC=Y

    MCAL_OPT += -DHAS_CONNECTIVITY
    CONNECTIVITY_DIR = $(WORKSPACE_LOC)/connectivity
    # $(error CONNECTIVITY_DIR= $(CONNECTIVITY_DIR))

    INCDIR += -I$(CONNECTIVITY_DIR)

    ifeq ($(LOG),Y)
        # $(error LOG=$(LOG))
        include $(CONNECTIVITY_DIR)/log/log.mk
    endif

    ifeq ($(INTERFACES),Y)
        # $(error INTERFACES=$(INTERFACES))
        include $(CONNECTIVITY_DIR)/interfaces/interfaces.mk
    endif

    ifeq ($(PROTOCOLS),Y)  
        # $(error PROTOCOLS=$(PROTOCOLS))
        include $(CONNECTIVITY_DIR)/protocols/protocols.mk
    endif

    # $(error CONNECTIVITY_DIR=$(CONNECTIVITY_DIR))
    SOURCES_C += $(CONNECTIVITY_DIR)/connectivity.c

    ifeq ($(CLI),Y)
        ifeq ($(CONNECTIVITY_COMMANDS),Y)
            # $(error CONNECTIVITY_COMMANDS=$(CONNECTIVITY_COMMANDS))
            MCAL_OPT += -DHAS_CONNECTIVITY_COMMANDS
            SOURCES_C += $(CONNECTIVITY_DIR)/connectivity_commands.c
        endif
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(CONNECTIVITY_DIAG),Y)
            MCAL_OPT += -DHAS_CONNECTIVITY_DIAG
            # $(error CONNECTIVITY_DIAG=$(CONNECTIVITY_DIAG))
            SOURCES_C += $(CONNECTIVITY_DIR)/connectivity_diag.c
        endif
    endif
endif