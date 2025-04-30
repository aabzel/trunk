$(info SYSTEM_MK_INC=$(SYSTEM_MK_INC))

ifneq ($(SYSTEM_MK_INC),Y)
    SYSTEM_MK_INC=Y


    SYSTEM_DIR = $(CONTROL_DIR)/system
    #@ echo $(error SYSTEM_DIR = $(SYSTEM_DIR))

    INCDIR += -I$(SYSTEM_DIR)

    OPT += -DHAS_SYSTEM
    
    ifeq ($(SYSTEM_EXT),Y)
        OPT += -DHAS_SYSTEM_EXT
    endif

    SOURCES_C += $(SYSTEM_DIR)/system.c
    # SOURCES_C += $(SYSTEM_DIR)/if_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(SYSTEM_DIAG),Y)
            OPT += -DHAS_SYSTEM_DIAG
            #@echo $(error SYSTEM_DIAG=[$(SYSTEM_DIAG)])
            SOURCES_C += $(SYSTEM_DIR)/system_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(SYSTEM_COMMANDS),Y)
            OPT += -DHAS_SYSTEM_COMMANDS
            #@echo $(error SYSTEM_COMMANDS=[$(SYSTEM_COMMANDS)])
            SOURCES_C += $(SYSTEM_DIR)/system_commands.c
        endif
    endif
    
endif