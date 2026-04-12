$(info SYSTEM_MK_INC=$(SYSTEM_MK_INC))

ifneq ($(SYSTEM_MK_INC),Y)
    SYSTEM_MK_INC=Y


    SYSTEM_DIR = $(CONTROL_DIR)/system
    # $(error SYSTEM_DIR = $(SYSTEM_DIR))

    INCDIR += -I$(SYSTEM_DIR)

    MCAL_OPT += -DHAS_SYSTEM

    ifeq ($(SYSTEM_EXT),Y)
        MCAL_OPT += -DHAS_SYSTEM_EXT
    endif

    SOURCES_C += $(SYSTEM_DIR)/system.c
    # SOURCES_C += $(SYSTEM_DIR)/if_config.c
    SYSTEM_FACILITY_TOKENS =$(SYSTEM_DIR)/system_facility_tokens.h

    ifeq ($(DIAG),Y)
        ifeq ($(SYSTEM_DIAG),Y)
            MCAL_OPT += -DHAS_SYSTEM_DIAG
            # $(error SYSTEM_DIAG=[$(SYSTEM_DIAG)])
            SOURCES_DIAG_C += $(SYSTEM_DIR)/system_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(SYSTEM_COMMANDS),Y)
            MCAL_OPT += -DHAS_SYSTEM_COMMANDS
            # $(error SYSTEM_COMMANDS=[$(SYSTEM_COMMANDS)])
            SOURCES_C += $(SYSTEM_DIR)/system_commands.c
        endif
    endif
    
.PHONY: sort_system_facility_tokens
sort_system_facility_tokens: $(SYSTEM_FACILITY_TOKENS)
	$(info sort_system_facility_tokens...)
	$(SORTER_TOOL) -u $(SYSTEM_FACILITY_TOKENS) -o $(SYSTEM_FACILITY_TOKENS)

endif