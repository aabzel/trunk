
$(info ECHO_EFFECT_MK_INC=$(ECHO_EFFECT_MK_INC))

ifneq ($(ECHO_EFFECT_MK_INC),Y)
    ECHO_EFFECT_MK_INC=Y

    ECHO_EFFECT_DIR = $(DSP_DIR)/echo_effect
    #@echo $(error ECHO_EFFECT_DIR = $(ECHO_EFFECT_DIR))

    OPT += -DHAS_ECHO_EFFECT

    ifeq ($(ECHO_EFFECT_PROC),Y)
        OPT += -DHAS_ECHO_EFFECT_PROC
    endif

    INCDIR += -I$(ECHO_EFFECT_DIR)

    SOURCES_C += $(ECHO_EFFECT_DIR)/echo_effect.c
    SOURCES_C += $(ECHO_EFFECT_DIR)/echo_effect_isr.c


    ifeq ($(DIAG),Y)
        ifeq ($(ECHO_EFFECT_DIAG),Y)
            OPT += -DHAS_ECHO_EFFECT_DIAG
            SOURCES_C += $(ECHO_EFFECT_DIR)/echo_effect_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(ECHO_EFFECT_COMMANDS),Y)
            #@echo $(error ECHO_EFFECT_COMMANDS = $(ECHO_EFFECT_COMMANDS))
            OPT += -DHAS_ECHO_EFFECT_COMMANDS
            SOURCES_C += $(ECHO_EFFECT_DIR)/echo_effect_commands.c
        endif
    endif
endif
