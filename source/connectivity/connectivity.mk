ifneq ($(CONNECTIVITY_MK_INC),Y)
    CONNECTIVITY_MK_INC=Y

    OPT += -DHAS_CONNECTIVITY
    CONNECTIVITY_DIR = $(WORKSPACE_LOC)/connectivity
    #@echo $(error CONNECTIVITY_DIR= $(CONNECTIVITY_DIR))

    INCDIR += -I$(CONNECTIVITY_DIR)

    ifeq ($(LOG),Y)
        #@echo $(error LOG=$(LOG))
        include $(CONNECTIVITY_DIR)/log/log.mk
    endif

    ifeq ($(INTERFACES),Y)
        #@echo $(error INTERFACES=$(INTERFACES))
        include $(CONNECTIVITY_DIR)/interfaces/interfaces.mk
    endif

    ifeq ($(PROTOCOLS),Y)  
        #@echo $(error PROTOCOLS=$(PROTOCOLS))
        include $(CONNECTIVITY_DIR)/protocols/protocols.mk
    endif

    #@echo $(error CONNECTIVITY_DIR=$(CONNECTIVITY_DIR))

    ifeq ($(CLI),Y)
        ifeq ($(CONNECTIVITY_COMMANDS),Y)
            #@echo $(error CONNECTIVITY_COMMANDS=$(CONNECTIVITY_COMMANDS))
            OPT += -DHAS_CONNECTIVITY_COMMANDS
            SOURCES_C += $(CONNECTIVITY_DIR)/connectivity_commands.c
        endif
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(CONNECTIVITY_DIAG),Y)
            OPT += -DHAS_CONNECTIVITY_DIAG
            #@echo $(error CONNECTIVITY_DIAG=$(CONNECTIVITY_DIAG))
            #SOURCES_C += $(CONNECTIVITY_DIR)/connectivity_diag.c
        endif
    endif
endif