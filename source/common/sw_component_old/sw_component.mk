ifneq ($(SW_COMPONENT_MK_INC),Y)
    SW_COMPONENT_MK_INC=Y

    SW_COMPONENT_DIR = $(COMMON_DIR)/sw_component
    # $(error SW_COMPONENT_DIR=$(SW_COMPONENT_DIR))

    INCDIR += -I$(SW_COMPONENT_DIR)

    MCAL_OPT += -DHAS_SW_COMPONENT

    ifeq ($(SW_COMPONENT_PROC),Y)
        MCAL_OPT += -DHAS_SW_COMPONENT_PROC
    endif

    SOURCES_C += $(SW_COMPONENT_DIR)/sw_component.c

    ifeq ($(SW_COMPONENT_INTERRUPTS),Y)
        MCAL_OPT += -DHAS_SW_COMPONENT_INTERRUPTS
        SOURCES_C += $(SW_COMPONENT_DIR)/sw_component_isr.c
    endif

    # must be outside
    SOURCES_C += $(SW_COMPONENT_DIR)/sw_component_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(SW_COMPONENT_DIAG),Y)
            MCAL_OPT += -DHAS_SW_COMPONENT_DIAG
            SOURCES_C += $(SW_COMPONENT_DIR)/sw_component_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(SW_COMPONENT_COMMANDS),Y)
            MCAL_OPT += -DHAS_SW_COMPONENT_COMMANDS
            SOURCES_C += $(SW_COMPONENT_DIR)/sw_component_commands.c
        endif
    endif
endif
