ifneq ($(BICYCLE_HEADLAMP_MK_INC),Y)
    BICYCLE_HEADLAMP_MK_INC=Y

    BICYCLE_HEADLAMP_DIR = $(APPLICATIONS_DIR)/bicycle_headlamp
    # $(error BICYCLE_HEADLAMP_DIR=$(BICYCLE_HEADLAMP_DIR))

    INCDIR += -I$(BICYCLE_HEADLAMP_DIR)

    MCAL_OPT += -DHAS_BICYCLE_HEADLAMP

    ifeq ($(BICYCLE_HEADLAMP_PROC),Y)
        MCAL_OPT += -DHAS_BICYCLE_HEADLAMP_PROC
    endif

    SOURCES_C += $(BICYCLE_HEADLAMP_DIR)/bicycle_headlamp_mcal.c

    # must be outside
    SOURCES_CONFIGURATION_C += $(BOARD_CFG_DIR)/bicycle_headlamp_config.c

    ifeq ($(DIAG),Y)
        ifeq ($(BICYCLE_HEADLAMP_DIAG),Y)
            MCAL_OPT += -DHAS_BICYCLE_HEADLAMP_DIAG
            SOURCES_DIAG_C += $(BICYCLE_HEADLAMP_DIR)/bicycle_headlamp_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(BICYCLE_HEADLAMP_COMMANDS),Y)
            MCAL_OPT += -DHAS_BICYCLE_HEADLAMP_COMMANDS
            SOURCES_C += $(BICYCLE_HEADLAMP_DIR)/bicycle_headlamp_commands.c
        endif
    endif
endif
