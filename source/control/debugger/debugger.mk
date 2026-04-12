
ifneq ($(DEBUGGER_MK_INC),Y)
    DEBUGGER_MK_INC=Y

    DEBUGGER_DIR = $(CONTROL_DIR)/debugger
    # $(error DEBUGGER_DIR = $(DEBUGGER_DIR))

    MCAL_OPT += -DHAS_DEBUGGER
    INCDIR += -I$(DEBUGGER_DIR)

    ifeq ($(WRITE_ADDR),Y)
        MCAL_OPT += -DHAS_WRITE_ADDR
    endif


    SOURCES_C += $(DEBUGGER_DIR)/debugger.c
    
    ifeq ($(CLI),Y)
        #@echo $(error CLI=$(CLI))
        ifeq ($(DEBUGGER_COMMANDS),Y)
            #@echo $(error DEBUGGER_COMMANDS = $(DEBUGGER_COMMANDS))
            MCAL_OPT += -DHAS_DEBUGGER_COMMANDS
            SOURCES_C += $(DEBUGGER_DIR)/debugger_commands.c
        endif
    endif
endif